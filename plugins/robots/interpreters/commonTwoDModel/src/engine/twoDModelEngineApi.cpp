#include "twoDModelEngineApi.h"

#include <QtCore/QDebug>
#include <QtCore/qmath.h>

#include <qrkernel/settingsManager.h>
#include <qrutils/mathUtils/math.h>
/// @todo: Get rid of it!s
#include <interpreterBase/robotModel/robotParts/touchSensor.h>
#include <interpreterBase/robotModel/robotParts/colorSensorFull.h>
#include <interpreterBase/robotModel/robotParts/colorSensorPassive.h>
#include <interpreterBase/robotModel/robotParts/colorSensorRed.h>
#include <interpreterBase/robotModel/robotParts/colorSensorGreen.h>
#include <interpreterBase/robotModel/robotParts/colorSensorBlue.h>

#include "model/model.h"
#include "model/constants.h"

#include "view/d2ModelWidget.h"

using namespace twoDModel;
using namespace interpreterBase::robotModel;

TwoDModelEngineApi::TwoDModelEngineApi(Model &model, D2ModelWidget &view)
	: mModel(model)
	, mView(view)
{
	mNoiseGenerator.setApproximationLevel(qReal::SettingsManager::value("approximationLevel").toUInt());
}

void TwoDModelEngineApi::setNewMotor(int speed, uint degrees, PortInfo const &port, bool breakMode)
{
	mModel.robotModel().setNewMotor(speed, degrees, port, breakMode);
}

int TwoDModelEngineApi::readEncoder(PortInfo const &port) const
{
	return mModel.robotModel().readEncoder(port);
}

void TwoDModelEngineApi::resetEncoder(PortInfo const &port)
{
	mModel.robotModel().resetEncoder(port);
}

int TwoDModelEngineApi::readTouchSensor(PortInfo const &port) const
{
	if (!mModel.robotModel().configuration().type(port).isA<robotParts::TouchSensor>()) {
		return touchSensorNotPressedSignal;
	}

	QPair<QPointF, qreal> const neededPosDir = countPositionAndDirection(port);
	QPointF sensorPosition(neededPosDir.first);
	qreal const width = SensorItem::sensorWidth / 2.0;
	QRectF const scanningRect = QRectF(
			sensorPosition.x() - width - touchSensorStrokeIncrement / 2.0
			, sensorPosition.y() - width - touchSensorStrokeIncrement / 2.0
			, 2 * width + touchSensorStrokeIncrement
			, 2 * width + touchSensorStrokeIncrement);

	QPainterPath sensorPath;
	sensorPath.addRect(scanningRect);
	bool const res = mModel.worldModel().checkCollision(sensorPath, touchSensorWallStrokeIncrement);

	return res ? touchSensorPressedSignal : touchSensorNotPressedSignal;
}

int TwoDModelEngineApi::readSonarSensor(PortInfo const &port) const
{
	QPair<QPointF, qreal> neededPosDir = countPositionAndDirection(port);
	int const res = mModel.worldModel().sonarReading(neededPosDir.first, neededPosDir.second);

	return mModel.settings().realisticSensors() ? spoilSonarReading(res) : res;
}

int TwoDModelEngineApi::spoilSonarReading(int const distance) const
{
	qreal const ran = mNoiseGenerator.generate(mNoiseGenerator.approximationLevel(), spoilSonarDispersion);
	return mathUtils::Math::truncateToInterval(0, 255, round(distance + ran));
}

int TwoDModelEngineApi::readColorSensor(PortInfo const &port) const
{
	QImage const image = printColorSensor(port);
	QHash<uint, int> countsColor;

	uint const *data = reinterpret_cast<uint const *>(image.bits());
	int const n = image.byteCount() / 4;
	for (int i = 0; i < n; ++i) {
		uint const color = mModel.settings().realisticSensors() ? spoilColor(data[i]) : data[i];
		++countsColor[color];
	}

	if (mModel.robotModel().configuration().type(port).isA<robotParts::ColorSensorFull>()) {
		return readColorFullSensor(countsColor);
	} else if (mModel.robotModel().configuration().type(port).isA<robotParts::ColorSensorPassive>()) {
		return readColorNoneSensor(countsColor, n);
	} else if (mModel.robotModel().configuration().type(port).isA<robotParts::ColorSensorRed>()) {
		return readSingleColorSensor(red, countsColor, n);
	} else if (mModel.robotModel().configuration().type(port).isA<robotParts::ColorSensorGreen>()) {
		return readSingleColorSensor(green, countsColor, n);
	} else if (mModel.robotModel().configuration().type(port).isA<robotParts::ColorSensorBlue>()) {
		return readSingleColorSensor(blue, countsColor, n);
	}

	qDebug() << "Incorrect 2d model sensor configuration";
	return 0;
}

uint TwoDModelEngineApi::spoilColor(uint const color) const
{
	qreal const ran = mNoiseGenerator.generate(
			mNoiseGenerator.approximationLevel()
			, spoilColorDispersion
			);

	int r = round(((color >> 16) & 0xFF) + ran);
	int g = round(((color >> 8) & 0xFF) + ran);
	int b = round(((color >> 0) & 0xFF) + ran);
	int const a = (color >> 24) & 0xFF;

	r = mathUtils::Math::truncateToInterval(0, 255, r);
	g = mathUtils::Math::truncateToInterval(0, 255, g);
	b = mathUtils::Math::truncateToInterval(0, 255, b);

	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF) + ((a & 0xFF) << 24);
}

QImage TwoDModelEngineApi::printColorSensor(PortInfo const &port) const
{
	if (mModel.robotModel().configuration().type(port).isNull()) {
		return QImage();
	}

	QPair<QPointF, qreal> const neededPosDir = countPositionAndDirection(port);
	QPointF const position = neededPosDir.first;
	qreal const width = SensorItem::sensorWidth / 2.0;
	QRectF const scanningRect = QRectF(position.x() - width, position.y() - width, 2 * width, 2 * width);

	QImage image(scanningRect.size().toSize(), QImage::Format_RGB32);
	QPainter painter(&image);

	QBrush brush(Qt::SolidPattern);
	brush.setColor(Qt::white);
	painter.setBrush(brush);
	painter.setPen(QPen(Qt::white));
	painter.drawRect(scanningRect.translated(-scanningRect.topLeft()));

	bool const wasSelected = mView.sensorItem(port)->isSelected();
	mView.setSensorVisible(port, false);
	mView.scene()->render(&painter, QRectF(), scanningRect);
	mView.setSensorVisible(port, true);
	mView.sensorItem(port)->setSelected(wasSelected);

	return image;
}

int TwoDModelEngineApi::readColorFullSensor(QHash<uint, int> const &countsColor) const
{
	if (countsColor.isEmpty()) {
		return 0;
	}

	QList<int> const values = countsColor.values();
	int maxValue = INT_MIN;
	for (int value : values) {
		if (value > maxValue) {
			maxValue = value;
		}
	}

	uint const maxColor = countsColor.key(maxValue);
	switch (maxColor) {
	case (black):
		return 1;
	case (red):
		return 5;
	case (green):
		return 3;
	case (blue) :
		return 2;
	case (yellow):
		return 4;
	case (white):
		return 6;
	case (cyan):
		return 7;
	case (magenta):
		return 8;
	default:
		return 0;
	}
}

int TwoDModelEngineApi::readSingleColorSensor(uint color, QHash<uint, int> const &countsColor, int n) const
{
	return (static_cast<double>(countsColor[color]) / static_cast<double>(n)) * 100.0;
}

int TwoDModelEngineApi::readColorNoneSensor(QHash<uint, int> const &countsColor, int n) const
{
	double allWhite = static_cast<double>(countsColor[white]);

	QHashIterator<uint, int> i(countsColor);
	while(i.hasNext()) {
		i.next();
		uint const color = i.key();
		if (color != white) {
			int const b = (color >> 0) & 0xFF;
			int const g = (color >> 8) & 0xFF;
			int const r = (color >> 16) & 0xFF;
			qreal const k = qSqrt(static_cast<qreal>(b * b + g * g + r * r)) / 500.0;
			allWhite += static_cast<qreal>(i.value()) * k;
		}
	}

	return (allWhite / static_cast<qreal>(n)) * 100.0;
}

int TwoDModelEngineApi::readLightSensor(PortInfo const &port) const
{
	// Must return 1023 on white and 0 on black normalized to percents
	// http://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color

	QImage const image = printColorSensor(port);
	if (image.isNull()) {
		return 0;
	}

	uint sum = 0;
	uint const *data = reinterpret_cast<uint const *>(image.bits());
	int const n = image.byteCount() / 4;

	for (int i = 0; i < n; ++i) {
		int const color = mModel.settings().realisticSensors() ? spoilLight(data[i]) : data[i];
		int const b = (color >> 0) & 0xFF;
		int const g = (color >> 8) & 0xFF;
		int const r = (color >> 16) & 0xFF;
		// brightness in [0..256]
		int const brightness = 0.2126 * r + 0.7152 * g + 0.0722 * b;

		sum += 4 * brightness; // 4 = max sensor value / max brightness value
	}
	qreal const rawValue = sum / n; // Average by whole region
	return rawValue * 100 / maxLightSensorValur; // Normalizing to percents
}

void TwoDModelEngineApi::playSound(int timeInMs)
{
	mModel.robotModel().playSound(timeInMs);
}

utils::TimelineInterface &TwoDModelEngineApi::modelTimeline()
{
	return mModel.timeline();
}

engine::TwoDModelDisplayInterface *TwoDModelEngineApi::display()
{
	return mView.display();
}

uint TwoDModelEngineApi::spoilLight(uint const color) const
{
	qreal const ran = mNoiseGenerator.generate(mNoiseGenerator.approximationLevel(), spoilLightDispersion);

	if (ran > (1.0 - percentSaltPepperNoise / 100.0)) {
		return white;
	} else if (ran < (-1.0 + percentSaltPepperNoise / 100.0)) {
		return black;
	}

	return color;
}

int TwoDModelEngineApi::varySpeed(int const speed) const
{
	qreal const ran = mNoiseGenerator.generate(mNoiseGenerator.approximationLevel(), varySpeedDispersion);
	return mathUtils::Math::truncateToInterval(-100, 100, round(speed * (1 + ran)));
}

QPair<QPointF, qreal> TwoDModelEngineApi::countPositionAndDirection(PortInfo const &port) const
{
	SensorItem const *sensor = mView.sensorItem(port);
	QPointF const position = sensor ? sensor->scenePos() : QPointF();
	qreal const direction = sensor ? sensor->rotation() + mModel.robotModel().rotateAngle() : 0;
	return { position, direction };
}

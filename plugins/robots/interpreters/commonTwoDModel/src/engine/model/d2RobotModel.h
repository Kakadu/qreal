#pragma once

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/qmath.h>

#include <interpreterBase/devicesConfigurationProvider.h>
#include <interpreterBase/robotModel/robotModelInterface.h>
#include <interpreterBase/robotModel/portInfo.h>

#include <qrutils/mathUtils/gaussNoise.h>

#include "commonTwoDModel/engine/twoDModelEngineInterface.h"
#include "commonTwoDModel/engine/twoDModelDisplayWidget.h"
#include "commonTwoDModel/engine/configurer.h"

#include "twoDRobotModelInterface.h"

namespace twoDModel {

namespace physics {
class PhysicsEngineBase;
}

class D2ModelWidget;
class WorldModel;
class Timeline;

class D2RobotModel : public QObject
		, public TwoDRobotRobotModelInterface
		, public interpreterBase::DevicesConfigurationProvider
		, public engine::TwoDModelEngineInterface
{
	Q_OBJECT

public:
	enum ATime {
		DoInf,
		DoByLimit,
		End
	};

	/// @param configurer - allows to configure various model parameters specific to a kit. Takes ownership.
	D2RobotModel(interpreterBase::robotModel::RobotModelInterface &robotModel
			, Configurer const * const configurer
			, QObject *parent = 0);

	~D2RobotModel();

	void init();

	void clear() override;
	void startInit();
	void startInterpretation();
	void stopRobot();
	void playSound(int timeInMs) override;

	void setNewMotor(int speed, uint degrees
			, interpreterBase::robotModel::PortInfo const &port, bool breakMode) override;

	SensorsConfiguration &configuration() override;
	int readEncoder(interpreterBase::robotModel::PortInfo const &port) const override;
	void resetEncoder(interpreterBase::robotModel::PortInfo const &port) override;

	engine::TwoDModelDisplayInterface *display() override;

	int readTouchSensor(interpreterBase::robotModel::PortInfo const &port) const override;
	int readSonarSensor(interpreterBase::robotModel::PortInfo const &port) const override;
	int readColorSensor(interpreterBase::robotModel::PortInfo const &port) const override;
	int readLightSensor(interpreterBase::robotModel::PortInfo const &port) const override;

	virtual void setRotation(qreal angle);
	virtual qreal rotateAngle() const;

	void setRobotPos(QPointF const &newPos);
	QPointF robotPos();

	virtual void serialize(QDomDocument &target);
	virtual void deserialize(const QDomElement &robotElement);

	Timeline *timeline() const;
	utils::TimelineInterface &modelTimeline() override;

	void setNoiseSettings();

	void setMotorPortOnWheel(WheelEnum wheel, interpreterBase::robotModel::PortInfo const &port) override;

	/// Loads the given xml obtaied by the previous serialization.
	void loadModel(QDomDocument const &model);

public slots:
	void showModelWidget();
	void closeModelWidget();
	void setRunStopButtonsEnabled(bool enabled);

signals:
	void runButtonPressed();
	void stopButtonPressed();
	void widgetClosed();

	/// Emitted each time when some user actions lead to world model modifications
	/// @param xml World model description in xml format
	void modelChanged(QDomDocument const &xml);

private slots:
	void recalculateParams();
	void nextFragment();

private:
	struct Engine
	{
		int radius;
		int speed;
		int spoiledSpeed;
		int degrees;
		ATime activeTimeType;
		bool isUsed;
		bool breakMode;
	};

	QPointF rotationCenter() const;
	QVector2D robotDirectionVector() const;

	void setSpeedFactor(qreal speedMul);
	void initPosition();

	Engine *initEngine(int radius, int speed, long unsigned int degrees
			, interpreterBase::robotModel::PortInfo const &port, bool isUsed);

	void countNewForces();
	void countBeep();

	QPair<QPointF, qreal> countPositionAndDirection(interpreterBase::robotModel::PortInfo const &port) const;

	void countMotorTurnover();

	QImage printColorSensor(interpreterBase::robotModel::PortInfo const &port) const;
	int readColorFullSensor(QHash<uint, int> const &countsColor) const;
	int readColorNoneSensor(QHash<uint, int> const &countsColor, int n) const;
	int readSingleColorSensor(uint color, QHash<uint, int> const &countsColor, int n) const;

	void synchronizePositions();
	uint spoilColor(uint const color) const;
	uint spoilLight(uint const color) const;
	int varySpeed(int const speed) const;
	int spoilSonarReading(int const distance) const;
	int truncateToInterval(int const a, int const b, int const res) const;

	void nextStep();

	D2ModelWidget *createModelWidget();

	D2ModelWidget *mD2ModelWidget;
	int mBeepTime;
	engine::TwoDModelDisplayWidget *mDisplay;
	QPointF mRotatePoint;

	/// Simulated robot engines.
	/// Has ownership.
	QHash<interpreterBase::robotModel::PortInfo, Engine*> mEngines;

	/// Stores how many degrees the motor rotated on.
	QHash<interpreterBase::robotModel::PortInfo, qreal> mTurnoverEngines;

	/// Describes which wheel is driven by which motor.
	QHash<WheelEnum, interpreterBase::robotModel::PortInfo> mWheelsToMotorPortsMap;

	SensorsConfiguration mSensorsConfiguration;
	WorldModel *mWorldModel;
	physics::PhysicsEngineBase *mPhysicsEngine;
	Timeline *mTimeline;
	qreal mSpeedFactor;
	mathUtils::GaussNoise mNoiseGen;
	bool mNeedSync;
	bool mIsRealisticPhysics;
	bool mNeedSensorNoise;
	bool mNeedMotorNoise;

	QPointF mPos;
	qreal mAngle;

	interpreterBase::robotModel::RobotModelInterface &mRobotModel;

	QHash<interpreterBase::robotModel::PortInfo, interpreterBase::robotModel::PortInfo> mMotorToEncoderPortMap;

	QScopedPointer<Configurer const> mConfigurer;
};

}

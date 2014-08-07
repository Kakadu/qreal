#include "realRobotModelBase.h"

#include <qrkernel/settingsManager.h>
#include <qrkernel/exception/exception.h>

#include "parts/display.h"
#include "parts/speaker.h"
#include "parts/button.h"

#include "parts/powerMotor.h"
#include "parts/servoMotor.h"
#include "parts/encoderSensor.h"

#include "parts/lightSensor.h"
#include "parts/infraredSensor.h"

#include "parts/sonarSensor.h"

#include "parts/motionSensor.h"

#include "parts/colorSensor.h"
#include "parts/led.h"
#include "parts/lineSensor.h"
#include "parts/objectSensor.h"

using namespace trikKitInterpreter::robotModel::real;
using namespace interpreterBase::robotModel;

RealRobotModelBase::RealRobotModelBase(QString const &kitId)
	: TrikRobotModelBase(kitId)
{
}

bool RealRobotModelBase::needsConnection() const
{
	return true;
}

void RealRobotModelBase::connectToRobot()
{
}

void RealRobotModelBase::disconnectFromRobot()
{
}

robotParts::Device *RealRobotModelBase::createDevice(PortInfo const &port, DeviceInfo const &deviceInfo)
{
	if (deviceInfo.isA(displayInfo())) {
		return new parts::Display(displayInfo(), port);
	} else if (deviceInfo.isA(speakerInfo())) {
		return new parts::Speaker(speakerInfo(), port);
	} else if (deviceInfo.isA(buttonInfo())) {
		return new parts::Button(buttonInfo(), port);
	} else if (deviceInfo.isA(powerMotorInfo())) {
		return new parts::PowerMotor(powerMotorInfo(), port);
	} else if (deviceInfo.isA(servoMotorInfo())) {
		return new parts::ServoMotor(servoMotorInfo(), port);
	} else if (deviceInfo.isA(encoderInfo())) {
		return new parts::EncoderSensor(encoderInfo(), port);
	} else if (deviceInfo.isA(lightSensorInfo())) {
		return new parts::LightSensor(lightSensorInfo(), port);
	} else if (deviceInfo.isA(infraredSensorInfo())) {
		return new parts::InfraredSensor(infraredSensorInfo(), port);
	} else if (deviceInfo.isA(sonarSensorInfo())) {
		return new parts::SonarSensor(sonarSensorInfo(), port);
	} else if (deviceInfo.isA(motionSensorInfo())) {
		return new parts::MotionSensor(motionSensorInfo(), port);
	} else if (deviceInfo.isA(ledInfo())) {
		return new parts::Led(ledInfo(), port);
	} else if (deviceInfo.isA(lineSensorInfo())) {
		return new parts::LineSensor(lineSensorInfo(), port);
	} else if (deviceInfo.isA(colorSensorInfo())) {
		return new parts::LineSensor(colorSensorInfo(), port);
	} else if (deviceInfo.isA(objectSensorInfo())) {
		return new parts::LineSensor(objectSensorInfo(), port);
	}

	throw qReal::Exception("Unknown device " + deviceInfo.toString() + " requested on port " + port.name());
}

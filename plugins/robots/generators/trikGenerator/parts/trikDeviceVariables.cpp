#include "trikDeviceVariables.h"

#include <QtCore/QMetaClassInfo>

using namespace trik::parts;

QString TrikDeviceVariables::variableTemplatePath(interpreterBase::robotModel::DeviceInfo const &device
		, interpreterBase::robotModel::PortInfo const &port) const
{
	if (device.name() == "trikLineSensor"
			|| device.name() == "trikObjectSensor"
			|| device.name() == "trikColorSensor")
	{
		QString templateName = port.name();
		templateName.remove("Port");
		return "videosensors/" + templateName + ".t";
	}

	return generatorBase::parts::DeviceVariables::variableTemplatePath(device, port);
}

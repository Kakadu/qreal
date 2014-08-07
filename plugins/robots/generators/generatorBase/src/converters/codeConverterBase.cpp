#include "codeConverterBase.h"

#include <qrkernel/settingsManager.h>
#include <interpreterBase/robotModel/robotParts/button.h>

using namespace generatorBase::converters;
using namespace qReal;

CodeConverterBase::CodeConverterBase(QString const &pathToTemplates
		, qReal::ErrorReporterInterface &errorReporter
		, interpreterBase::robotModel::RobotModelInterface const &robotModel
		, QMap<interpreterBase::robotModel::PortInfo, interpreterBase::robotModel::DeviceInfo> const &devices
		, simple::Binding::ConverterInterface const *inputPortConverter
		, simple::Binding::ConverterInterface const *functionInvocationsConverter, const parts::DeviceVariables &deviceVariables)
	: TemplateParametrizedConverter(pathToTemplates)
	, mErrorReporter(errorReporter)
	, mRobotModel(robotModel)
	, mDevices(devices)
	, mInputConverter(inputPortConverter)
	, mFunctionInvocationsConverter(functionInvocationsConverter)
	, mDeviceVariables(deviceVariables)
{
}

CodeConverterBase::~CodeConverterBase()
{
	delete mInputConverter;
	delete mFunctionInvocationsConverter;
}

QString CodeConverterBase::convert(QString const &data) const
{
	return replaceFunctionInvocations(replaceSystemVariables(data)).trimmed();
}

QString CodeConverterBase::replaceSystemVariables(QString const &expression) const
{
	QString result = expression;

	for (interpreterBase::robotModel::PortInfo const &port : mRobotModel.availablePorts()) {
		QString const variable = port.reservedVariable();
		if (!variable.isEmpty() && result.contains(variable)) {
			result.replace(variable, deviceExpression(port));
		}
	}

	result.replace("time", timelineExpression());
	return result;
}

QString CodeConverterBase::replaceFunctionInvocations(QString const &expression) const
{
	QString result = expression;

	QString const randomTemplate = mFunctionInvocationsConverter->convert("random");

	QRegExp const randomFunctionInvocationRegEx("random\\((.*)\\)");
	int pos = randomFunctionInvocationRegEx.indexIn(result, 0);
	while (pos != -1) {
		QString const param = randomFunctionInvocationRegEx.cap(1);
		QString randomInvocation = randomTemplate;
		randomInvocation.replace("@@UPPER_BOUND@@", param);
		result.replace(randomFunctionInvocationRegEx, randomInvocation);
		pos += randomFunctionInvocationRegEx.matchedLength();
		pos = randomFunctionInvocationRegEx.indexIn(result, pos);
	}

	return result;
}

QString CodeConverterBase::deviceExpression(interpreterBase::robotModel::PortInfo const &port) const
{
	interpreterBase::robotModel::DeviceInfo const device = mDevices[port];
	if (device.isNull()) {
		mErrorReporter.addError(QObject::tr("Device on port %1 is not configured."\
				" Please select it on the left-side panel.").arg(port.name()));
		return QObject::tr("/* ERROR: SELECT DEVICE TYPE */");
	}

	QString const templatePath = mDeviceVariables.variableTemplatePath(device, port);

	// Converter must take a string like "1" or "2" (and etc) and return correct value
	return readTemplate(templatePath).replace("@@PORT@@", mInputConverter->convert(port.name()));
}

QString CodeConverterBase::timelineExpression() const
{
	/// @todo: generate timestamps code in nxt c when required
	return readTemplate("whatTime.t");
}

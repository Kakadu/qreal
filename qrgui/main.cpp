#include <time.h>

#include <QtCore/QtPlugin>
#include <QtWidgets/QApplication>

#include "mainwindow/mainWindow.h"
#include "thirdparty/windowsmodernstyle.h"
#include <qrkernel/logging.h>
#include <qrutils/uxInfo/uxInfo.h>

#include "qrealApplication.h"

using namespace qReal;

int const maxLogSize = 10 * 1024 * 1024;  // 10 MB

void clearConfig()
{
	SettingsManager::clearSettings();
	SettingsManager::instance()->saveData();
}

void setDefaultLocale(bool localizationDisabled)
{
	if (localizationDisabled) {
		QLocale::setDefault(QLocale::English);
		return;
	}

	QString const locale = SettingsManager::value("systemLocale").toString();
	if (!locale.isEmpty()) {
		QLocale::setDefault(QLocale(locale));
	}
}

void initLogging()
{
	QDir const logsDir(QApplication::applicationDirPath() + "/logs");
	if (logsDir.mkpath(logsDir.absolutePath())) {
		Logger::addLogTarget(logsDir.filePath("qreal.log"), maxLogSize, 2, QsLogging::DebugLevel);
		Logger::addLogTarget(logsDir.filePath("actions.log"), maxLogSize, 2, QsLogging::TraceLevel);
	}
}

#if defined Q_OS_WIN32
QString prettyWindowsVersion(QSysInfo::WinVersion version)
{
	// Adapted from https://qt.gitorious.org/qt/thiago-intels-qtbase/commit/5757c458157bcb11da40c43e98eeb7a539d20912
	switch (version)
	{
	case QSysInfo::WV_95:
		return "95";
	case QSysInfo::WV_98:
		return "98";
	case QSysInfo::WV_Me:
		return "ME";
	case QSysInfo::WV_NT:
		return "NT";
	case QSysInfo::WV_2000:
		return "2000";
	case QSysInfo::WV_XP:
		return "XP";
	case QSysInfo::WV_2003:
		return "2003";
	case QSysInfo::WV_VISTA:
		return "Vista";
	case QSysInfo::WV_WINDOWS7:
		return "7";
	case QSysInfo::WV_WINDOWS8:
		return "8";
	case QSysInfo::WV_WINDOWS8_1:
		return "8.1";
	case QSysInfo::WV_CE:
		return "CE";
	case QSysInfo::WV_CENET:
		return "CENET";
	case QSysInfo::WV_CE_5:
		return "CE5";
	case QSysInfo::WV_CE_6:
		return "CE6";
	default:
		return "";
	}
}
#endif

QString platformInfo()
{
#if defined Q_OS_WIN32
	return QString("Windows ") + prettyWindowsVersion(QSysInfo().windowsVersion());
#elif defined Q_OS_LINUX
	return "Linux";
#elif defined Q_OS_MAC
	return QString("Mac ") + QSysInfo().macVersion();
#endif
}

int main(int argc, char *argv[])
{
	QDateTime const startedTime = QDateTime::currentDateTime();
	QRealApplication app(argc, argv);

	qsrand(time(0));
	setDefaultLocale(app.arguments().contains("--no-locale"));

	QTranslator guiTranslator;
	QTranslator utilsTranslator;
	QTranslator qtTranslator;
	guiTranslator.load(":/qrgui_" + QLocale().name());
	utilsTranslator.load(":/qrutils_" + QLocale().name());
	qtTranslator.load(":/qt_" + QLocale().name());
	app.installTranslator(&guiTranslator);
	app.installTranslator(&utilsTranslator);
	app.installTranslator(&qtTranslator);

	initLogging();
	QLOG_INFO() << "------------------- APPLICATION STARTED --------------------";
	QLOG_INFO() << "Running on" << platformInfo();
	QLOG_INFO() << "Arguments:" << app.arguments();
	QLOG_INFO() << "Setting default locale to" << QLocale().name();

	QString fileToOpen;
	if (app.arguments().count() > 1) {
		if (app.arguments().contains("--clear-conf")) {
			clearConfig();
			return 0;
		} else {
			int const setIndex = app.arguments().indexOf("--config");
			if (setIndex > -1) {
				QString const settingsFileName = app.arguments().at(setIndex + 1);
				SettingsManager::instance()->loadSettings(settingsFileName);
			}
			for (int i = 0; i < argc; i++) {
				if (app.arguments().at(i).endsWith(".qrs")) {
					fileToOpen = app.arguments().at(i);
					break;
				}
			}
		}
	}

#ifndef NO_STYLE_WINDOWSMODERN
	app.setStyle(new WindowsModernStyle());
#endif

	MainWindow window(fileToOpen);
	int exitCode = 0; // The window decided to not show itself, exiting now.

	if (window.isVisible()) {
		exitCode = app.exec();
	}

	QDateTime const currentTime = QDateTime::currentDateTime();
	QString const totalTime = QString::number(static_cast<qlonglong>(startedTime.secsTo(currentTime)));
	utils::UXInfo::reportTotalTime(totalTime, exitCode);
	QLOG_INFO() << "------------------- APPLICATION FINISHED -------------------";
	return exitCode;
}

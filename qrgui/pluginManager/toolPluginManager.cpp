#include "toolPluginManager.h"

#include <QtWidgets/QApplication>

#include "hotKeyManager/hotKeyManager.h"

using namespace qReal;

ToolPluginManager::ToolPluginManager()
	: mCustomizer()
{
	mPluginsDir = QDir(qApp->applicationDirPath());

	while (!mPluginsDir.isRoot() && !mPluginsDir.entryList(QDir::Dirs).contains("plugins")) {
		mPluginsDir.cdUp();
	}

	mPluginsDir.cd("plugins");

	for (QString const &fileName : mPluginsDir.entryList(QDir::Files)) {
		// TODO: Free memory
		QPluginLoader *loader = new QPluginLoader(mPluginsDir.absoluteFilePath(fileName));
		QObject *plugin = loader->instance();

		if (plugin) {
			ToolPluginInterface *toolPlugin = qobject_cast<ToolPluginInterface *>(plugin);
			if (toolPlugin) {
				mPlugins << toolPlugin;
				mLoaders << loader;
			} else {
				// TODO: Does not work on linux. See editorManager.cpp for more details.
				// loader->unload();
				delete loader;
			}
		} else {
			loader->unload();
			delete loader;
		}
	}

	setHotKeyActions();
}

ToolPluginManager::~ToolPluginManager()
{
	qDeleteAll(mLoaders);
}

void ToolPluginManager::init(PluginConfigurator const &configurator)
{
	mSystemEvents = &configurator.systemEvents();

	for (ToolPluginInterface * const toolPlugin : mPlugins) {
		toolPlugin->init(configurator);
	}
}

QList<ActionInfo> ToolPluginManager::actions() const
{
	QList<ActionInfo> result;
	for (ToolPluginInterface * const toolPlugin : mPlugins) {
		result += toolPlugin->actions();
	}

	return result;
}

QList<HotKeyActionInfo> ToolPluginManager::hotKeyActions() const
{
	QList<HotKeyActionInfo> result;
	for (ToolPluginInterface * const toolPlugin : mPlugins) {
		result += toolPlugin->hotKeyActions();
	}

	return result;
}

void ToolPluginManager::setHotKeyActions() const
{
	for (HotKeyActionInfo const &actionInfo : hotKeyActions()) {
		HotKeyManager::setCommand(actionInfo.id(), actionInfo.label(), actionInfo.action());
	}
}

QList<QPair<QString, PreferencesPage *> > ToolPluginManager::preferencesPages() const
{
	QList<QPair<QString, PreferencesPage *> > result;
	for (ToolPluginInterface * const toolPlugin : mPlugins) {
		if (toolPlugin->preferencesPage().second) {
			result << toolPlugin->preferencesPage();
		}
	}

	return result;
}

QMultiMap<QString, ProjectConverter> ToolPluginManager::projectConverters() const
{
	QMultiMap<QString, ProjectConverter> result;
	for (ToolPluginInterface * const toolPlugin : mPlugins) {
		for (ProjectConverter const &converter : toolPlugin->projectConverters()) {
			result.insertMulti(converter.editor(), converter);
		}
	}

	return result;
}

Customizer *ToolPluginManager::customizer() const
{
	for (ToolPluginInterface * const toolPlugin : mPlugins) {
		if (toolPlugin->customizationInterface()) {
			return toolPlugin->customizationInterface();
		}
	}
	return const_cast<qReal::Customizer *>(&mCustomizer);
}

void ToolPluginManager::updateSettings()
{
	emit mSystemEvents->settingsUpdated();
}

void ToolPluginManager::activeTabChanged(Id const & rootElementId)
{
	emit mSystemEvents->activeTabChanged(rootElementId);
}

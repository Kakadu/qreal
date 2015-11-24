#pragma once

#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QRadioButton>

#include <qrgui/dialogs/preferencesPages/preferencesPage.h>
#include <interpreterBase/devicesConfigurationProvider.h>

#include "managers/kitPluginManager.h"
#include "managers/robotModelManager.h"

namespace Ui {
class PreferencesRobotSettingsPage;
}

namespace interpreterCore {
namespace ui {

/// Preferences page for robots interpreter plugin. Contains constructor kit selector and a placeholder for
/// kit-specific settings.
class RobotsSettingsPage : public PreferencesPage, public interpreterBase::DevicesConfigurationProvider
{
	Q_OBJECT

public:
	explicit RobotsSettingsPage(
			KitPluginManager &kitPluginManager
			, RobotModelManager &robotModelManager
			, QWidget *parent = nullptr
			);

	~RobotsSettingsPage() override;

	void save() override;
	void restoreSettings() override;

signals:
	void saved();

protected:
	void changeEvent(QEvent *e);

private slots:
	void onKitRadioButtonToggled(bool checked);
	void onRobotModelRadioButtonToggled(bool checked);

private:
	void initializeAdditionalWidgets();
	void initializeKitRadioButtons();
	QButtonGroup *initializeRobotModelsButtons(QString const &kitId, QRadioButton * const kitButton);

	void showAdditionalPreferences(QString const &kitId);
	void showRadioButtonGroup(QWidget * const container
			, QButtonGroup * const radioButtons
			, QWidget * const emptyCaseWidget = nullptr);

	void saveSelectedRobotModel();
	void checkSelectedRobotModelButtonFor(QAbstractButton * const kitButton);

	Ui::PreferencesRobotSettingsPage *mUi;
	KitPluginManager &mKitPluginManager;
	RobotModelManager &mRobotModelManager;
	QButtonGroup *mKitButtons;
	QHash<QAbstractButton *, QButtonGroup *> mKitRobotModels;
	QHash<QAbstractButton *, interpreterBase::robotModel::RobotModelInterface *> mButtonsToRobotModelsMapping;
};

}
}

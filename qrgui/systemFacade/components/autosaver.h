#pragma once

#include <QtCore/QObject>
#include <QtCore/QTimer>

namespace qReal {

class ProjectManager;

/// @brief class provides automatic saving of the project at equal time intervals.
/// All options for working are retrieved from the settings manager.
/// Autosaver provides an interface that allows you to make it reload parameters
class Autosaver : public QObject
{
	Q_OBJECT

public:
	class Pauser
	{
	public:
		Pauser(Autosaver &autosaver);
		~Pauser();

	private:
		Autosaver &mAutosaver;
	};

	explicit Autosaver(ProjectManager &projectManager);
	void reinit();

	QString tempFilePath() const;
	bool isAutosave(const QString &fileName) const;
	bool isTempFile(const QString &fileName) const;
	QString originalFile(const QString &fileName) const;

	bool openTemp();
	bool openAutosave(const QString &fileName);

	bool removeTemp();
	bool removeAutoSave();
	bool removeAutoSave(const QString &fileName);

	/// Performs search in project`s folder and tries to find autosaved version
	/// of specified project. If such version was not found returns false.
	/// Otherwise prompts user to recover the newest version.
	/// Returns true if user agrees and autosave was opened successfully,
	/// otherwise returns false.
	bool checkAutoSavedVersion(const QString &originalProjectPath);

	/// Similar to @see checkAutoSavedVersion, but searches for temp save
	bool checkTempFile();

private slots:
	void saveAutoSave();
	void saveTemp();

private:
	QString autosaveFilePath() const;
	QString autosaveFilePath(const QString &currentFilePath) const;
	void resume();
	void suspend();

	uint interval() const;
	QString openAutosavePrompt() const;
	QString openTempFilePrompt() const;
	bool removeFile(const QString &fileName);

	// if option AutosaveInterval in not specified
	static uint const defaultInterval = 600;

	ProjectManager &mProjectManager;
	QTimer mTimer;
};

}
#pragma once

#include <QtCore/QFileInfo>
#include <QtXml/QDomDocument>

/// Loads xml document in the given file substituting contents instead of 'external' tags
/// and detecting cyclic dependencies.
class DocumentLoader
{
public:
	/// Loads the given xml file with the external tags expanding (substitutes the contents as child tag
	/// if the external file has xml format or like the inner text else).
	QDomDocument load(QFileInfo const &fileInfo);

private:
	void processElement(QDomElement &element, QDomElement &parent
		, QString const &currentDir);

	QList<QString> mUsedFiles;
};

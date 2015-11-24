#include "documentLoader.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include <qrutils/xmlUtils.h>
#include <qrutils/inFile.h>

QDomDocument DocumentLoader::load(QFileInfo const &fileInfo)
{
	QString const path = fileInfo.absoluteFilePath();
	QDomDocument const document = utils::xmlUtils::loadDocument(path);
	if (mUsedFiles.contains(path)) {
		qDebug() << "ERROR: Cyclic external tags references; proceeding with empty document";
		return QDomDocument();
	}

	mUsedFiles.append(path);
	QDomElement root = document.documentElement();
	QDomElement dumbParent = root.parentNode().toElement();
	if (!root.isNull()) {
		processElement(root, dumbParent, fileInfo.absoluteDir().absolutePath());
	}

	mUsedFiles.removeOne(path);

	return document;
}

void DocumentLoader::processElement(QDomElement &element, QDomElement &parent
		, QString const &currentDir)
{
	if (element.tagName().toLower() == "external") {
		QString const externalFileName = element.attribute("file");
		parent.removeChild(element);
		if (externalFileName.isEmpty()) {
			return;
		}

		qDebug() << "Processing exernal link to " + externalFileName;
		QDir dir(currentDir);
		QFileInfo info(dir, externalFileName);
		QDomDocument const externalDoc = load(info);
		if (externalDoc.isNull()) {
			QString const fileContents = utils::InFile::readAll(info.absoluteFilePath());
			QDomText const textElement = parent.ownerDocument().createTextNode(fileContents);
			parent.appendChild(textElement);
		}

		QDomElement const newElement = externalDoc.documentElement().cloneNode().toElement();
		parent.appendChild(newElement);
		element = newElement;
	}

	QDomElement child = element.firstChildElement();
	while (!child.isNull()) {
		processElement(child, element, currentDir);
		child = child.nextSiblingElement();
	}
}

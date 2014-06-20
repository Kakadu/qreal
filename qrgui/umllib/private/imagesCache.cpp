#include "imagesCache.h"

#include <QtCore/QDir>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>

using namespace qReal;

void ImagesCache::drawImage(
		QString const &fileName
		, QPainter &painter
		, QRect const &rect)
{
	if (mFileNamePixmapMap.contains(fileName)) {
		painter.drawPixmap(rect, mFileNamePixmapMap.value(fileName));
	} else if (mFileNameSvgRendererMap.contains(fileName)) {
		mFileNameSvgRendererMap.value(fileName)->render(&painter, rect);
	} else {
		// Cache miss - finding best file to load and loading it.
		QString const actualFileName = fileName.startsWith("./")
				? QApplication::applicationDirPath() + "/" + fileName
				: fileName;

		QFileInfo const actualFile = selectBestImageFile(actualFileName);

		QByteArray const rawImage = loadPixmap(actualFile);
		if (actualFile.suffix() == "svg") {
			QSharedPointer<QSvgRenderer> renderer(new QSvgRenderer(rawImage));
			mFileNameSvgRendererMap.insert(fileName, renderer);
			renderer->render(&painter, rect);
		} else {
			QPixmap pixmap;
			pixmap.loadFromData(rawImage);
			mFileNamePixmapMap.insert(fileName, pixmap);
			painter.drawPixmap(rect, pixmap);
		}
	}
}

QFileInfo ImagesCache::selectBestImageFile(QString const &filePath)
{
	QFileInfo const originalFileInfo(filePath);
	QFileInfo const svgVersion(originalFileInfo.path() + originalFileInfo.completeBaseName() + "svg");

	if (svgVersion.exists()) {
		return svgVersion;
	}

	QFileInfo const fileInfo(filePath);
	if (fileInfo.exists()) {
		return fileInfo;
	}

	QDir dir(fileInfo.absolutePath());
	auto candidates = dir.entryInfoList({fileInfo.completeBaseName() + ".*"}, QDir::Files);
	if (!candidates.empty()) {
		return candidates.at(0);
	}

	if (fileInfo.completeBaseName() != "default") {
		return selectBestImageFile(fileInfo.absolutePath() + "/default.svg");
	}

	return QFileInfo(":/icons/default.svg");
}

QByteArray ImagesCache::loadPixmap(QFileInfo const &fileInfo)
{
	QFile file(fileInfo.absoluteFilePath());
	if (!file.open(QIODevice::ReadOnly)) {
		return QByteArray();
	}

	return file.readAll();
}

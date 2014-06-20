#pragma once

#include <QtCore/QFileInfo>
#include <QtGui/QPixmap>
#include <QtSvg/QSvgRenderer>

namespace qReal {

/// Cache for images that contains them pre-loaded and parsed and is able to quickly draw it on a painter.
/// Pixmaps and svg images are contained separately as they are rendered differently.
class ImagesCache {
public:
	/// Draws image with given file name on given painter in given rectangle. Note that actual file, from which
	/// an image will be loaded may be different from fileName, as described in selectBestImageFile.
	/// @see selectBestImageFile
	void drawImage(QString const &fileName, QPainter &painter, QRect const &rect);

private:
	/// Selects "best available" image file, using following rules:
	/// - if there is .svg file with given name in a directory from filePath, it is used as actual image file.
	/// - else if there is a file with other extension but with correct name, it is used.
	/// - else, if there is no such file, it tries to select a file with name "default" in given directory, using the
	///   rules above.
	/// - if everything above fails, system default image file, from qrgui/icons (or, when compiled,
	///   from ":/icons/default.svg"), is used.
	static QFileInfo selectBestImageFile(QString const &filePath);

	/// Loads pixmap from given file, returns empty QByteArray if file does not exist.
	static QByteArray loadPixmap(QFileInfo const &fileInfo);

	/// Maps file name to pre-loaded pixmap with image.
	QHash<QString, QPixmap> mFileNamePixmapMap;

	/// Maps file name to a svg renderer object.
	QHash<QString, QSharedPointer<QSvgRenderer>> mFileNameSvgRendererMap;
};

}

#pragma once

#include <QtCore/QMap>
#include <QtGui/QIcon>

class QDeclarativeEngine;

namespace qReal {

/// Caches qml-described icons.
class QmlIconLoader
{
public:
	/// Configures the only qml icon loader instance to use the given qml engine for rendering icons.
	static void setQmlEngine(QDeclarativeEngine * const engine);

	/// Returns a pixmap of element in specified qml-file
	static QIcon iconOf(QString const &fileName);

	/// Returns a size of the pixmap of element in specified qml-file
	static QSize preferedSizeOf(QString const &fileName);

private:
	static QmlIconLoader *instance();
	static QIcon loadPixmap(QString const &fileName);

	QmlIconLoader();
	~QmlIconLoader();

	QDeclarativeEngine *mQmlEngine;
	QMap<QString, QIcon> mLoadedIcons;
	QMap<QString, QSize> mPreferedSizes;
};

}

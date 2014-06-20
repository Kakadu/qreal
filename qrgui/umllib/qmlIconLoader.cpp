#include "qmlIconLoader.h"

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeItem>

#include <qrutils/graphicsUtils/itemRenderer.h>

using namespace qReal;

QmlIconLoader::QmlIconLoader()
{
}

QmlIconLoader::~QmlIconLoader()
{
}

void QmlIconLoader::setQmlEngine(QDeclarativeEngine * const engine)
{
	instance()->mQmlEngine = engine;
}

QIcon QmlIconLoader::iconOf(QString const &fileName)
{
	return loadPixmap(fileName);
}

QSize QmlIconLoader::preferedSizeOf(QString const &fileName)
{
	loadPixmap(fileName);
	return instance()->mPreferedSizes[fileName];
}

QmlIconLoader *QmlIconLoader::instance()
{
	static QmlIconLoader instance;
	return &instance;
}

QIcon QmlIconLoader::loadPixmap(QString const &fileName)
{
	if (!instance()->mLoadedIcons.contains(fileName)) {
		QDeclarativeComponent component(instance()->mQmlEngine, QUrl(fileName));
		if (component.isReady()) {
			QDeclarativeItem * const item = qobject_cast<QDeclarativeItem *>(component.create());
			QIcon const icon = graphicsUtils::ItemRenderer::renderRecursively(item
					, item->width(), item->height(), QColor(Qt::white));

			instance()->mLoadedIcons[fileName] = icon;
			instance()->mPreferedSizes[fileName] = QSize(item->width(), item->height());
		} else {
			QIcon const icon(":/icons/default.svg");
			instance()->mLoadedIcons[fileName] = icon;
			instance()->mPreferedSizes[fileName] = QSize(50, 50);
		}
	}

	return instance()->mLoadedIcons[fileName];
}

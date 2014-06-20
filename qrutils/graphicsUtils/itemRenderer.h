#pragma once

#include <QtWidgets/QGraphicsItem>

#include "qrutils/utilsDeclSpec.h"

namespace graphicsUtils {

/// Provides some utils on rendering QGraphicsItems into QPixmaps and others.
class QRUTILS_EXPORT ItemRenderer
{
public:
	/// Performs graphics item rendering into pixmap of the given size considering all item`s children.
	static QPixmap renderRecursively(QGraphicsItem * const item, int w, int h, QColor const &backgroundColor);

private:
	static void renderItem(QGraphicsItem * const item
			, QPainter *painter
			, QStyleOptionGraphicsItem * const option
			, QTransform const &baseTransform);
};

}

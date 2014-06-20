#include "itemRenderer.h"

#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionGraphicsItem>

using namespace graphicsUtils;

QPixmap ItemRenderer::renderRecursively(QGraphicsItem * const item, int w, int h, QColor const &backgroundColor)
{
	// +1 due to strange rendering behaviour
	QPixmap result(w + 1, h + 1);
	QPainter painter(&result);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::TextAntialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.save();
	painter.setBrush(backgroundColor);
	painter.setPen(backgroundColor);
	painter.drawRect(0, 0, w + 1, h + 1);
	painter.restore();
	QStyleOptionGraphicsItem option;

	// Get the inverse transform of the root item's scene transform; all the
	// children's transforms will be transformed by this in order to bring
	// their coordinate systems from the scene space to the root item space.
	QTransform const inverse = item->sceneTransform().inverted();

	// Recursively render the item and all its children.
	renderItem(item, &painter, &option, inverse);

	return result;
}

void ItemRenderer::renderItem(QGraphicsItem * const item
		, QPainter *painter
		, QStyleOptionGraphicsItem * const option
		, QTransform const &baseTransform)
{
	QTransform const itemTransform = item->sceneTransform() * baseTransform;
	painter->setWorldTransform(itemTransform, false);
	item->paint(painter, option, nullptr);

	// Recurse into children
	/// @todo this should be breadth-first not depth-first!
	for (QGraphicsItem * const child : item->childItems()) {
		renderItem(child, painter, option, baseTransform);
	}
}

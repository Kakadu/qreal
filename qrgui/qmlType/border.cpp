#include "border.h"
#include <QtGui/QPainter>

using namespace qmlTypes;

Border::Border(QDeclarativeItem *parent) :
		QDeclarativeItem(parent), mWidth(0), mColor(Qt::black)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

QColor Border::color()
{
	return mColor;
}

int Border::width()
{
	return mWidth;
}

QPen Border::getPen()
{
	QPen mPen(mColor, mWidth);
	return mPen;
}

void Border::setColor(const QColor &color) {
	if(mColor == color) return;
	mColor = color;
	emit colorChanged();
	update();
}

void Border::setWidth(int width){
		if(mWidth == width) return;
		mWidth = width;
		emit widthChanged();
		update();
}

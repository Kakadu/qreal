#include "border.h"

#include <QtGui/QPainter>

using namespace qmlTypes;

Border::Border(QDeclarativeItem *parent)
	: QDeclarativeItem(parent)
	, mStyle("solid")
	, mWidth(0)
	, mColor(Qt::black)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

QColor Border::color() const
{
	return mColor;
}

int Border::width() const
{
	return mWidth;
}

QString Border::style() const
{
	return mStyle;
}

QPen Border::pen() const
{
	QPen mPen(mColor, mWidth);
	if (mStyle == "solid") {
		mPen.setStyle(Qt::SolidLine);
	}
	if (mStyle == "dot") {
		mPen.setStyle(Qt::DotLine);
	}
	if (mStyle == "dash") {
		mPen.setStyle(Qt::DashLine);
	}
	if (mStyle == "dashdot") {
		mPen.setStyle(Qt::DashDotLine);
	}
	if (mStyle == "dashdotdot") {
		mPen.setStyle(Qt::DashDotDotLine);
	}
	if (mStyle == "none") {
		mPen.setStyle(Qt::NoPen);
	}
	return mPen;
}

void Border::setColor(QColor const &color) {
	if (mColor == color) { return; }
	mColor = color;
	emit colorChanged();
	update();
}

void Border::setWidth(int width){
		if (mWidth == width) { return; }
		mWidth = width;
		emit widthChanged();
		update();
}

void Border::setStyle(QString const style)
{
	if(mStyle == style) return;
	mStyle = style;
	emit styleChanged();
	update();
}

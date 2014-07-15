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
	QPen pen(mColor, mWidth);
	if (mStyle == "solid") {
		pen.setStyle(Qt::SolidLine);
	} else if (mStyle == "dot") {
		pen.setStyle(Qt::DotLine);
	} else if (mStyle == "dash") {
		pen.setStyle(Qt::DashLine);
	} else if (mStyle == "dashdot") {
		pen.setStyle(Qt::DashDotLine);
	} else if (mStyle == "dashdotdot") {
		pen.setStyle(Qt::DashDotDotLine);
	} else if (mStyle == "none") {
		pen.setStyle(Qt::NoPen);
	}

	return pen;
}

void Border::setColor(QColor const &color)
{
	if (mColor != color) {
		mColor = color;
		emit colorChanged();
		update();
	}
}

void Border::setWidth(int width)
{
	if (mWidth != width) {
		mWidth = width;
		emit widthChanged();
		update();
	}
}

void Border::setStyle(QString const style)
{
	if(mStyle != style) {
		mStyle = style;
		emit styleChanged();
		update();
	}
}

#include "declarativePen.h"

#include <QtGui/QPainter>

using namespace qmlTypes;

DeclarativePen::DeclarativePen(QDeclarativeItem *parent)
	: QDeclarativeItem(parent)
	, mStyle("solid")
	, mWidth(0)
	, mColor(Qt::black)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

QColor DeclarativePen::color() const
{
	return mColor;
}

int DeclarativePen::width() const
{
	return mWidth;
}

QString DeclarativePen::style() const
{
	return mStyle;
}

QPen DeclarativePen::pen() const
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

void DeclarativePen::setColor(QColor const &color)
{
	if (mColor != color) {
		mColor = color;
		emit colorChanged();
		update();
	}
}

void DeclarativePen::setWidth(int width)
{
	if (mWidth != width) {
		mWidth = width;
		emit widthChanged();
		update();
	}
}

void DeclarativePen::setStyle(QString const style)
{
	if (mStyle != style) {
		mStyle = style;
		emit styleChanged();
		update();
	}
}

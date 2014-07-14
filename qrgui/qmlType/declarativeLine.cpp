#include "declarativeLine.h"
#include <QPainter>

using namespace qmlTypes;

DeclarativeLine::DeclarativeLine(QDeclarativeItem *parent) :
		QDeclarativeItem(parent), mX1(0), mY1(0), mX2(0), mY2(0),
		mColor(Qt::black), mPenWidth(1), mStyle("solid")
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(mColor, mPenWidth);
	if (mStyle == "solid") {
		pen.setStyle(Qt::SolidLine);
	}
	if (mStyle == "dot") {
		pen.setStyle(Qt::DotLine);
	}
	if (mStyle == "dash") {
		pen.setStyle(Qt::DashLine);
	}
	if (mStyle == "dashdot") {
		pen.setStyle(Qt::DashDotLine);
	}
	if (mStyle == "dashdotdot") {
		pen.setStyle(Qt::DashDotDotLine);
	}
	if (mStyle == "none") {
		pen.setStyle(Qt::NoPen);
	}

	painter->setPen(pen);
	if(smooth() == true) {
		painter->setRenderHint(QPainter::Antialiasing, true);
	}

	int x = qMin(mX1, mX2) - mPenWidth/2;
	int y = qMin(mY1, mY2) - mPenWidth/2;
	painter->drawLine(mX1 - x, mY1 - y, mX2 - x, mY2 - y);
}

int DeclarativeLine::x1()
{
	return mX1;
}

int DeclarativeLine::y1()
{
	return mY1;
}

int DeclarativeLine::x2()
{
	return mX2;
}

int DeclarativeLine::y2()
{
	return mY2;
}

QColor DeclarativeLine::color()
{
	return mColor;
}

QString DeclarativeLine::style()
{
	return mStyle;
}

int DeclarativeLine::penWidth()
{
	return mPenWidth;
}

// Set methods
void DeclarativeLine::setX1(int x1) {
	if(mX1 == x1) return;
	mX1 = x1;
	updateSize();
	emit x1Changed();
	update();
}

void DeclarativeLine::setY1(int y1) {
	if(mY1 == y1) return;
	mY1 = y1;
	updateSize();
	emit y1Changed();
	update();
}

void DeclarativeLine::setX2(int x2)
{
	if(mX2 == x2) return;
	mX2 = x2;
	updateSize();
	emit x2Changed();
	update();
}

void DeclarativeLine::setY2(int y2)
{
	if(mY2 == y2) return;
	mY2 = y2;
	updateSize();
	emit x2Changed();
	update();
}

void DeclarativeLine::setColor(const QColor &color) {
	if(mColor == color) return;
	mColor = color;
	emit colorChanged();
	update();
}

void DeclarativeLine::setStyle(const QString style)
{
	if(mStyle == style) return;
	mStyle = style;
	emit styleChanged();
	update();
}

void DeclarativeLine::setPenWidth(int newWidth) {
	if(mPenWidth == newWidth) return;
	mPenWidth = newWidth;
	updateSize();
	emit penWidthChanged();
	update();
}

void DeclarativeLine::updateSize() {
	setX1(mX1);
	setY1(mY1);
	setX2(mX2);
	setY2(mY2);
}

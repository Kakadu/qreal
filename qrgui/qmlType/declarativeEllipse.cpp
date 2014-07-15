#include "declarativeEllipse.h"
#include "border.h"

#include <QtGui/QPainter>

using namespace qmlTypes;

DeclarativeEllipse::DeclarativeEllipse(QDeclarativeItem *parent)
	: QDeclarativeItem(parent)
	, mX(0)
	, mY(0)
	, mWidth(0)
	, mHeight(0)
	, mColor(Qt::black)
	, mBorder(new Border())
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(mBorder.pen());

	if(smooth()) {
		painter->setRenderHint(QPainter::Antialiasing, true);
	}

	painter->setBrush(mColor);
	painter->drawEllipse(mX - mWidth / 2, mY - mHeight / 2, mWidth, mHeight);
}

int DeclarativeEllipse::x() const
{
	return mX;
}

int DeclarativeEllipse::y() const
{
	return mY;
}

int DeclarativeEllipse::width() const
{
	return mWidth;
}

int DeclarativeEllipse::height() const
{
	return mHeight;
}

QColor DeclarativeEllipse::color() const
{
	return mColor;
}

Border *DeclarativeEllipse::border()
{
	return &mBorder;
}

void DeclarativeEllipse::setX(int x)
{
	if (mX != x) {
		mX = x;
		updateSize();
		emit xChanged();
		update();
	}
}

void DeclarativeEllipse::setY(int y)
{
	if (mY != y) {
		mY = y;
		updateSize();
		emit yChanged();
		update();
	}
}

void DeclarativeEllipse::setWidth(int width)
{
	if (mWidth != width) {
		mWidth = width;
		updateSize();
		emit widthChanged();
		update();
	}
}

void DeclarativeEllipse::setHeight(int height)
{
	if (mHeight != height) {
		mHeight = height;
		updateSize();
		emit heightChanged();
		update();
	}
}

void DeclarativeEllipse::setColor(QColor const &color)
{
	if (mColor != color) {
		mColor = color;
		emit colorChanged();
		update();
	}
}

void DeclarativeEllipse::setBorder(Border *border)
{
	if (mBorder.width() != border->width() || mBorder.color() != border->color()) {
		mBorder.setWidth( border->width());
		mBorder.setColor(border->color());
		emit borderChanged();
		update();
	}
}

void DeclarativeEllipse::updateSize()
{
	setX(mX);
	setY(mY);
	setWidth(mWidth);
	setHeight(mHeight);
}

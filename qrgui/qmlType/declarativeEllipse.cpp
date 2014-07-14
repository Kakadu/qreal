#include "declarativeEllipse.h"
#include "border.h"
#include <QtGui/QPainter>

using namespace qmlTypes;

DeclarativeEllipse::DeclarativeEllipse(QDeclarativeItem *parent):
	QDeclarativeItem(parent), mX(0), mY(0), mWidth(0), mHeight(0),
	mColor(Qt::black), mPenWidth(1), mStyle("solid"), mBorder(new Border())
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = mBorder.getPen();
	painter->setPen(pen);
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

	if(smooth() == true) {
		painter->setRenderHint(QPainter::Antialiasing, true);
	}
	qDebug() << pen.color();
	//painter->drawdeclarativedeclarativeEllipse(mX-mWidth/2,mY-mHeight/2,mWidth, mHeight);
	painter->setBrush(mColor);
	painter->drawEllipse(mX-mWidth/2,mY-mHeight/2,mWidth, mHeight);
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

QString DeclarativeEllipse::style() const
{
	return mStyle;
}

Border* DeclarativeEllipse::border()
{
	return &mBorder;
}

int DeclarativeEllipse::penWidth() const
{
	return mPenWidth;
}

void DeclarativeEllipse::setX(int x) {
	if(mX == x) return;
	mX = x;
	updateSize();
	emit xChanged();
	update();
}

void DeclarativeEllipse::setY(int y) {
	if(mY == y) return;
	mY = y;
	updateSize();
	emit yChanged();
	update();
}

void DeclarativeEllipse::setWidth(int width) {
	if(mWidth == width) return;
	mWidth = width;
	updateSize();
	emit widthChanged();
	update();
}

void DeclarativeEllipse::setHeight(int height) {
	if(mHeight == height) return;
	mHeight = height;
	updateSize();
	emit heightChanged();
	update();
}

void DeclarativeEllipse::setColor(const QColor &color) {
	if(mColor == color) return;
	mColor = color;
	emit colorChanged();
	update();
}

void DeclarativeEllipse::setStyle(const QString style)
{
	if(mStyle == style) return;
	mStyle = style;
	emit styleChanged();
	update();
}

void DeclarativeEllipse::setBorder(Border* border)
{
	if(mBorder.width() == border->width() && mBorder.color() == border->color())
	mBorder.setWidth( border->width());
	mBorder.setColor(border->color());
	emit borderChanged();
	update();
}

void DeclarativeEllipse::setPenWidth(int newWidth) {
	if(mPenWidth == newWidth) return;
	mPenWidth = newWidth;
	updateSize();
	emit penWidthChanged();
	update();
}

void DeclarativeEllipse::updateSize() {
	setX(mX-mPenWidth/2);
	setY(mY-mPenWidth/2);
	setWidth(mWidth);
	setHeight(mHeight);
}

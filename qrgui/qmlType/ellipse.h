#pragma once

#include <QtDeclarative/QDeclarativeItem>
#include <QtGui/QPainter>

#include "border.h"

namespace qmlTypes {

class Ellipse : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
	Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
	Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
	Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)
	Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
	Q_PROPERTY(Border *border READ border WRITE setBorder NOTIFY borderChanged)

public:
	Ellipse(QDeclarativeItem *parent = 0) :
			QDeclarativeItem(parent), mX(0), mY(0), mWidth(0), mHeight(0),
			mColor(Qt::black), mPenWidth(1), mStyle("solid"), mBorder(new Border())
	{
		// Important, otherwise the paint method is never called
		setFlag(QGraphicsItem::ItemHasNoContents, false);
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		QPen pen(mBorder.color(), mBorder.width() );
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
		//painter->drawEllipse(mX-mWidth/2,mY-mHeight/2,mWidth, mHeight);
		painter->setBrush(mColor);
		painter->drawEllipse(mX-mWidth/2,mY-mHeight/2,mWidth, mHeight);
	}

	// Get methods
	int x() const { return mX; }
	int y() const { return mY; }
	int width() const { return mWidth; }
	int height() const {return mHeight;}
	QColor color() const { return mColor; }
	int penWidth() const { return mPenWidth; }
	QString style() const { return mStyle; }
	Border *border() { return &mBorder; }

    // Set methods
	void setX(int x) {
		if(mX == x) return;
		mX = x;
		updateSize();
		emit xChanged();
		update();
	}

	void setY(int y) {
		if(mY == y) return;
		mY = y;
		updateSize();
		emit yChanged();
		update();
	}

	void setWidth(int width) {
		if(mWidth == width) return;
		mWidth = width;
		updateSize();
		emit widthChanged();
		update();
	}

	void setHeight(int height) {
		if(mHeight == height) return;
		mHeight = height;
		updateSize();
		emit heightChanged();
		update();
	}

	void setColor(const QColor &color) {
		if(mColor == color) return;
		mColor = color;
		emit colorChanged();
		update();
	}

	void setStyle(const QString style)
	{
		if(mStyle == style) return;
		mStyle = style;
		emit styleChanged();
		update();
	}
	void setBorder(Border* border)
	{
		qDebug() << __FUNCTION__;
		if(mBorder.width() == border->width() && mBorder.color() == border->color())
			return;
		mBorder.setWidth( border->width());
		mBorder.setColor(border->color());
		qDebug() << "signal";
		emit borderChanged();

		update();
	}

	void setPenWidth(int newWidth) {
		if(mPenWidth == newWidth) return;
		mPenWidth = newWidth;
		updateSize();
		emit penWidthChanged();
		update();
	}

signals:
	void xChanged();
	void yChanged();
	void widthChanged();
	void heightChanged();
	void colorChanged();
	void styleChanged();
	void penWidthChanged();
	void borderChanged();

protected:
	void updateSize() {
		setX(mX-mPenWidth/2);
		setY(mY-mPenWidth/2);
		setWidth(mWidth);
		setHeight(mHeight);
	}
protected:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	QColor mColor;
	QString mStyle;
	int mPenWidth;
	Border mBorder;
};
}
QML_DECLARE_TYPE(qmlTypes::Ellipse)

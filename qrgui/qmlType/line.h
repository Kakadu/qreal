#pragma once

#include <QtDeclarative/QDeclarativeItem>
#include <QPainter>
#include "QString"
namespace qmlTypes {
class Line : public QDeclarativeItem
{
    Q_OBJECT
	Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed)
	Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY y1Changed)
	Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed)
	Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed)
	Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(int penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged)


public:
	Line(QDeclarativeItem *parent = 0) :
			QDeclarativeItem(parent), mX1(0), mY1(0), mX2(0), mY2(0),
			mColor(Qt::black), mPenWidth(1), mStyle("solid")
	{
		// Important, otherwise the paint method is never called
		setFlag(QGraphicsItem::ItemHasNoContents, false);
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

	// Get methods
	int x1() const { return mX1; }
	int y1() const { return mY1; }
	int x2() const { return mX2; }
	int y2() const { return mY2; }
	QString style() const { return mStyle;}
	QColor color() const { return mColor; }
	int penWidth() const { return mPenWidth; }

	// Set methods
	void setX1(int x1) {
		if(mX1 == x1) return;
		mX1 = x1;
		updateSize();
		emit x1Changed();
		update();
	}

	void setY1(int y1) {
		if(mY1 == y1) return;
		mY1 = y1;
		updateSize();
		emit y1Changed();
		update();
	}

	void setX2(int x2) {
		if(mX2 == x2) return;
		mX2 = x2;
		updateSize();
		emit x2Changed();
		update();
	}

	void setY2(int y2) {
		if(mY2 == y2) return;
		mY2 = y2;
		updateSize();
		emit x2Changed();
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

	void setPenWidth(int newWidth) {
		if(mPenWidth == newWidth) return;
		mPenWidth = newWidth;
		updateSize();
		emit penWidthChanged();
		update();
	}

signals:
	void x1Changed();
	void y1Changed();
	void x2Changed();
	void y2Changed();
	void styleChanged();
	void colorChanged();
	void penWidthChanged();

protected:
	void updateSize() {
		setX(qMin(mX1, mX2) - mPenWidth/2);
		setY(qMin(mY1, mY2) - mPenWidth/2);
		setWidth(qAbs(mX2 - mX1) + mPenWidth);
		setHeight(qAbs(mY2 - mY1) + mPenWidth);
	}

protected:
	int mX1;
	int mY1;
	int mX2;
	int mY2;
	QColor mColor;
	int mPenWidth;
	QString mStyle;
};
}
QML_DECLARE_TYPE(qmlTypes::Line)


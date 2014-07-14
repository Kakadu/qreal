#pragma once

#include <QtDeclarative/QDeclarativeItem>

#include "border.h"

namespace qmlTypes {

class DeclarativeEllipse : public QDeclarativeItem
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
	explicit DeclarativeEllipse(QDeclarativeItem *parent = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	// Get methods
	int x() const;
	int y() const;
	int width() const;
	int height() const;
	QColor color() const;
	int penWidth() const;
	QString style() const;
	Border *border();

    // Set methods
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setColor(const QColor &color);
	void setStyle(const QString style);
	void setBorder(Border* border);
	void setPenWidth(int newWidth);

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
	void updateSize();
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
QML_DECLARE_TYPE(qmlTypes::DeclarativeEllipse)

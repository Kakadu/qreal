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
	Border *border();

    // Set methods
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setColor(QColor const &color);
	void setBorder(Border* border);

signals:
	void xChanged();
	void yChanged();
	void widthChanged();
	void heightChanged();
	void colorChanged();
	void borderChanged();

protected:
	void updateSize();
protected:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	QColor mColor;
	Border mBorder;
};

}
QML_DECLARE_TYPE(qmlTypes::DeclarativeEllipse)

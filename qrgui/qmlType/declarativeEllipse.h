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

	/// Returns the X coordinate of the center
	int x() const;
	/// Returns the Y coordinate of the center
	int y() const;
	/// Returns the width of the ellipse
	int width() const;
	/// Returns the height of the ellipse
	int height() const;
	/// Returns the color of the ellipse
	QColor color() const;
	/// Returns the pointer to the border, which stores border properties
	Border *border();

signals:
	void xChanged();
	void yChanged();
	void widthChanged();
	void heightChanged();
	void colorChanged();
	void borderChanged();

protected:
	void updateSize();
	/// Sets the x coordinate of the center
	void setX(int x);
	/// Sets the y coordinate of the center
	void setY(int y);
	/// Sets the width of the ellipse
	void setWidth(int width);
	/// Sets the height of the ellipse
	void setHeight(int height);
	/// Sets the color of the ellipse
	void setColor(QColor const &color);
	/// Sets the pointer to border
	void setBorder(Border* border);

private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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

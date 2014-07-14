#pragma once

#include <QtDeclarative/QDeclarativeItem>
#include <QtGui/QPainter>

namespace qmlTypes {

class Border : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)

	public:
		Border(QDeclarativeItem *parent = 0);

		QColor color();
		int width();
		QPen getPen();

		void setColor(const QColor &color);
		void setWidth(int width);
	signals:
		void colorChanged();
		void widthChanged();

	protected:
		QColor mColor;
		int mWidth;
};

}

QML_DECLARE_TYPE(qmlTypes::Border)

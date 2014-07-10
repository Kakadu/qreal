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
		Border(QDeclarativeItem *parent = 0) :
				QDeclarativeItem(parent), mWidth(0), mColor(Qt::black)
	{
		// Important, otherwise the paint method is never called
		setFlag(QGraphicsItem::ItemHasNoContents, false);
	}

	QColor color()
	{
		return mColor;
	}

	int width()
	{
		return mWidth;
	}

	void setColor(const QColor &color) {
		if(mColor == color) return;
		mColor = color;
		emit colorChanged();
		update();
	}
	void setWidth(int width)
{
		if(mWidth == width) return;
		mWidth = width;
		emit widthChanged();
		update();
	}
	signals:
		void colorChanged();
		void widthChanged();

protected:
	QColor mColor;
	int mWidth;
};

}

QML_DECLARE_TYPE(qmlTypes::Border)

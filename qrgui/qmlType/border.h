#pragma once

#include <QtDeclarative/QDeclarativeItem>
#include <QtGui/QPainter>

namespace qmlTypes {

class Border : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
	Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)

public:
	Border(QDeclarativeItem *parent = 0);

	QString style() const;
	QColor color() const;
	int width() const;
	QPen pen() const;

	void setStyle(QString const style);
	void setColor(QColor const &color);
	void setWidth(int width);
signals:
	void colorChanged();
	void widthChanged();
	void styleChanged();

protected:
	QString mStyle;
	QColor mColor;
	int mWidth;
};

}

QML_DECLARE_TYPE(qmlTypes::Border)

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
	explicit Border(QDeclarativeItem *parent = 0);

	/// Returns  the type of border. For example "solid", "dot"
	QString style() const;
	/// Returns the color of the border
	QColor color() const;
	/// Returns the width of the border
	int width() const;
	/// Return pen, which will be used to render
	QPen pen() const;

	/// Sets the цшвер of the border
	void setWidth(int width);
	/// Sets the color of the border
	void setColor(QColor const &color);
	/// Sets the dtyle of the border
	void setStyle(QString const style);

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

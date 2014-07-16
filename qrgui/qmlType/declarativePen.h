#pragma once

#include <QtDeclarative/QDeclarativeItem>
#include <QtGui/QPainter>

namespace qmlTypes {

/// DeclarativePen class is a class that provide qml border
class DeclarativePen : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
	Q_PROPERTY(QString style READ style WRITE setStyle NOTIFY styleChanged)

public:
	explicit DeclarativePen(QDeclarativeItem *parent = 0);

	/// Returns  the type of border. For example "solid", "dot"
	QString style() const;
	/// Returns the color of the pen
	QColor color() const;
	/// Returns the width of the pen
	int width() const;
	/// Return pen, which will be used to render
	QPen pen() const;

	/// Sets the width of the pen
	void setWidth(int width);
	/// Sets the color of the pen
	void setColor(QColor const &color);
	/// Sets the dtyle of the pen
	void setStyle(QString const &style);

signals:
	/// Signal change pen color
	void colorChanged();
	/// Signal change pen width
	void widthChanged();
	/// Signal change pen style
	void styleChanged();

protected:
	QString mStyle;
	QColor mColor;
	int mWidth;
};

}

QML_DECLARE_TYPE(qmlTypes::DeclarativePen)

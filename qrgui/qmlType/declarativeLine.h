#pragma once

#include <QtDeclarative/QDeclarativeItem>

namespace qmlTypes {

class DeclarativeLine : public QDeclarativeItem
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
	explicit DeclarativeLine(QDeclarativeItem *parent = 0);

	/// Returns the x1 coordinate of the line
	int x1() const;
	/// Returns the y1 coordinate of the line
	int y1() const;
	/// Returns the x2 coordinate of the line
	int x2() const;
	/// Returns the y2 coordinate of the line
	int y2() const;
	/// Returns the color of the line.
	QColor color() const;
	/// Returns the type of the line.
	QString style() const;
	/// Returns the width of the line
	int penWidth() const;

signals:
	void x1Changed();
	void y1Changed();
	void x2Changed();
	void y2Changed();
	void colorChanged();
	void penWidthChanged();
	void styleChanged();

protected:
	/// Sets the x1 coordinate of the line
	void setX1(int x);
	/// Sets the y1 coordinate of the line
	void setY1(int y);
	/// Sets the x2 coordinate of the line
	void setX2(int x);
	/// Sets the y2 coordinate of the line
	void setY2(int y);
	/// Sets the color of the line
	void setColor(const QColor &color);
	/// Sets the style of the line
	void setStyle(const QString style);
	/// Sets the width of the line
	void setPenWidth(int newWidth);
	void updateSize();

private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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

QML_DECLARE_TYPE(qmlTypes::DeclarativeLine)


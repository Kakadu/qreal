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
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	// Get methods
	int x1();
	int y1();
	int x2();
	int y2();

	QColor color();
	QString style();
	int penWidth();

protected:
	// Set methods
	void setX1(int x);
	void setY1(int y);
	void setX2(int x);
	void setY2(int y);
	void setColor(const QColor &color);
	void setStyle(const QString style);
	void setPenWidth(int newWidth);
	void updateSize();

signals:
	void x1Changed();
	void y1Changed();
	void x2Changed();
	void y2Changed();
	void colorChanged();
	void penWidthChanged();
	void styleChanged();

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


#pragma once

#include "declarativePen.h"

#include <QtDeclarative/QDeclarativeItem>

namespace qmlTypes {

/// DeclarativeLineclass is a class that provide qml line
class DeclarativeLine : public DeclarativePen
{
	Q_OBJECT

	Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed)
	Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY y1Changed)
	Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed)
	Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed)

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

signals:
	void x1Changed();
	void y1Changed();
	void x2Changed();
	void y2Changed();

protected:
	/// Sets the x1 coordinate of the line
	void setX1(int x);
	/// Sets the y1 coordinate of the line
	void setY1(int y);
	/// Sets the x2 coordinate of the line
	void setX2(int x);
	/// Sets the y2 coordinate of the line
	void setY2(int y);
	void updateSize();

private:
	void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);

protected:
	int mX1;
	int mY1;
	int mX2;
	int mY2;
};

}

QML_DECLARE_TYPE(qmlTypes::DeclarativeLine)

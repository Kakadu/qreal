#pragma once
#include <QtDeclarative/QDeclarativeItem>

class Canvas : public QDeclarativeItem
{
	Q_OBJECT
	Q_DISABLE_COPY(Canvas)

public:
    Canvas(QDeclarativeItem *parent = 0);
    ~Canvas();
    Q_INVOKABLE void init();
};

QML_DECLARE_TYPE(Canvas)

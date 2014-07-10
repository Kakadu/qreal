#include "canvas.h"

#include <QtDeclarative/QDeclarativeItem>

Canvas::Canvas(QDeclarativeItem *parent):
    QDeclarativeItem(parent)
{
    // By default, QDeclarativeItem does not draw anything. If you subclass
    // QDeclarativeItem to create a visual item, you will need to uncomment the
    // following line:

    // setFlag(ItemHasNoContents, false);
}

Canvas::~Canvas()
{
}


void Canvas::init() {
    qDebug() << "Decide how you will dra it there";
}

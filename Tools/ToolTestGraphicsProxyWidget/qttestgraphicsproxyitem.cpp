#include <cassert>
#include <cmath>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QPainter>
#include "qttestgraphicsproxyitem.h"
#pragma GCC diagnostic pop

QtTestGraphicsProxyItem::QtTestGraphicsProxyItem(QGraphicsItem *parent, Qt::WindowFlags wFlags)
 : QGraphicsProxyWidget(parent,wFlags)
{

}

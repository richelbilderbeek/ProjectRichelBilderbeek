#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "mygraphicsview.h"

#include <QWheelEvent>
#pragma GCC diagnostic pop


MyGraphicsView::MyGraphicsView(QWidget *parent)
  : QGraphicsView(parent)
{

}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
  const double new_scale = 1.0 + (static_cast<double>(event->delta()) / 1000.0);
  this->scale(new_scale,new_scale);
}

#ifndef QTWIDGET_H
#define QTWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsView>
#pragma GCC diagnostic pop

///The widget holding the items
struct QtWidget : public QGraphicsView
{
  QtWidget(QWidget *parent = 0);
};

#endif // QTWIDGET_H

#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QWheelEvent;

class MyGraphicsView : public QGraphicsView
{
  Q_OBJECT

  public:
  MyGraphicsView(QWidget *parent = 0);
  MyGraphicsView(const MyGraphicsView&) = delete;
  MyGraphicsView& operator=(const MyGraphicsView&) = delete;

  void wheelEvent(QWheelEvent *event);
};

#endif // MYGRAPHICSVIEW_H

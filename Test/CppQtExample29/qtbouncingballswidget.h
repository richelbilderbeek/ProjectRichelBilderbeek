#ifndef QTBOUNCINGBALLSWIDGET_H
#define QTBOUNCINGBALLSWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QGraphicsScene;

struct QtBouncingRectsWidget : public QGraphicsView
{
  QtBouncingRectsWidget(QWidget *parent = 0);


  protected:
  void resizeEvent(QResizeEvent *event);

  private:
  QGraphicsScene * const m_scene;
};

#endif // QTBOUNCINGBALLSWIDGET_H

#ifndef QTBOUNCINGBALLSWIDGET_H
#define QTBOUNCINGBALLSWIDGET_H

#include <QGraphicsView>

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

#ifndef QTBOUNCINGRECTSWIDGET_H
#define QTBOUNCINGRECTSWIDGET_H

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

#endif // QTBOUNCINGRECTSWIDGET_H

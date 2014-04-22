#ifndef QTBOUNCINGRECTSWIDGET_H
#define QTBOUNCINGRECTSWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QGraphicsScene;

struct QtBouncingRectsWidget : public QGraphicsView
{
  QtBouncingRectsWidget(QWidget *parent = 0);
  QtBouncingRectsWidget(const QtBouncingRectsWidget&) = delete;
  QtBouncingRectsWidget& operator=(const QtBouncingRectsWidget&) = delete;


  protected:
  void resizeEvent(QResizeEvent *event);

  private:
  QGraphicsScene * const m_scene;
};

#endif // QTBOUNCINGRECTSWIDGET_H

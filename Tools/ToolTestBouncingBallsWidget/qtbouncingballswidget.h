#ifndef QTBOUNCINGBALLSWIDGET_H
#define QTBOUNCINGBALLSWIDGET_H

#include <QGraphicsView>

struct QGraphicsScene;

struct QtBouncingBallsWidget : public QGraphicsView
{
  QtBouncingBallsWidget(QWidget *parent = 0);
  QtBouncingBallsWidget(const QtBouncingBallsWidget&) = delete;
  QtBouncingBallsWidget& operator=(const QtBouncingBallsWidget&) = delete;


  protected:
  void resizeEvent(QResizeEvent *event);

  private:
  QGraphicsScene * const m_scene;
};

#endif // QTBOUNCINGBALLSWIDGET_H

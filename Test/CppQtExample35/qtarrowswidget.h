#ifndef QTARROWSWIDGET_H
#define QTARROWSWIDGET_H

#include <QGraphicsView>

struct QtArrowsWidget : public QGraphicsView
{
  QtArrowsWidget();

  protected:
  ///Respond to a key press
  void keyPressEvent(QKeyEvent *event);

  private:
  ///The QGraphicsScene working on
  QGraphicsScene * const m_scene;
};

#endif // QTARROWSWIDGET_H

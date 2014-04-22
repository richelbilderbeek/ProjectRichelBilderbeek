#ifndef QTARROWSWIDGET_H
#define QTARROWSWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QGraphicsView>
#pragma GCC diagnostic pop

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

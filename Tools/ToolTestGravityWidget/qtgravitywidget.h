#ifndef QTGRAVITYWIDGET_H
#define QTGRAVITYWIDGET_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QGraphicsView>
#pragma GCC diagnostic pop

struct QGraphicsScene;

struct QtGravityWidget : public QGraphicsView
{
  QtGravityWidget(QWidget * parent = 0);


  protected:
  void resizeEvent(QResizeEvent *);

  private:
  QGraphicsScene * const m_scene;
};

#endif // QTGRAVITYWIDGET_H

#ifndef QTGRAVITYWIDGET_H
#define QTGRAVITYWIDGET_H

#include <QGraphicsView>

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

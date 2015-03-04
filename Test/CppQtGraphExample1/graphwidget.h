// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;

class GraphWidget : public QGraphicsView
{
  Q_OBJECT

public:
  GraphWidget(QWidget *parent = 0);
  GraphWidget(const GraphWidget&) = delete;
  GraphWidget& operator=(const GraphWidget&) = delete;

  void itemMoved();

public slots:
  void shuffle();
  void zoomIn();
  void zoomOut();

protected:
  void keyPressEvent(QKeyEvent *event);
  void timerEvent(QTimerEvent *event);
  void wheelEvent(QWheelEvent *event);
  void drawBackground(QPainter *painter, const QRectF &rect);

  void scaleView(qreal scaleFactor);

private:
  int m_timer_id;
  Node * const m_centerNode;
};

#endif

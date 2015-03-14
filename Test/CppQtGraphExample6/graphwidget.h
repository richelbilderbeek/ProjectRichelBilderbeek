// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;
class PopUp;

class GraphWidget : public QGraphicsView
{
  Q_OBJECT

public:
  GraphWidget(QWidget *parent = 0);
  GraphWidget(const GraphWidget&) = delete;
  GraphWidget& operator=(const GraphWidget&) = delete;

  ///Create a new node. The Node* is managed by GraphWidget
  Node* createNode() noexcept;

  void itemMoved() noexcept;

public slots:
  void shuffle() noexcept;
  void zoomIn() noexcept;
  void zoomOut() noexcept;

protected:
  void keyPressEvent(QKeyEvent *event) noexcept override;
  void scaleView(qreal scaleFactor) noexcept;
  void timerEvent(QTimerEvent *event) noexcept override;
  void wheelEvent(QWheelEvent *event) noexcept override;

private:
  int m_timer_id;
  PopUp * const m_popup;
  void OnNodeFocusInEvent(Node* const node) noexcept;
  void OnNodeFocusOutEvent(Node* const node) noexcept;
  void OnNodePositionChangedEvent(Node* const node) noexcept;
  void OnPopUpClicked(PopUp* const popup) noexcept;
};

#endif

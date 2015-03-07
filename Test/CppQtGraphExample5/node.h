// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html
#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <boost/signals2.hpp>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem
{
public:
  Node(GraphWidget *graphWidget);
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  void addEdge(Edge *edge) noexcept;
  QList<Edge *> edges() const noexcept;

  enum { Type = UserType + 1 };
  int type() const noexcept override { return Type; }

  void calculateForces() noexcept;
  bool advance() noexcept;

  QRectF boundingRect() const noexcept override;
  QPainterPath shape() const noexcept override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) noexcept override;
  void setShowBoundingRect(const bool show_bounding_rect) noexcept;

  boost::signals2::signal<void(Node*)> m_signal_focus_changed;

  protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) noexcept override;

  void focusInEvent(QFocusEvent *event) noexcept override;
  void focusOutEvent(QFocusEvent *event) noexcept override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) noexcept override;

  private:
  QList<Edge*> m_edges;
  GraphWidget * const m_graph;
  QPointF m_new_pos;
  bool m_show_bounding_rect;
};

#endif

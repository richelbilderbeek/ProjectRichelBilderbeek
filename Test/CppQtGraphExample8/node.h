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
  enum { Type = UserType + 1 };

  Node(GraphWidget * const graphWidget);
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  void addEdge(Edge *edge) noexcept;
  bool advance() noexcept;
  QRectF boundingRect() const noexcept override;
  void calculateForces() noexcept;
  QList<Edge *> edges() const noexcept;
  bool GetHasShadow() const noexcept { return m_has_shadow; }
  double GetRay() const noexcept { return m_ray; }
  bool GetShowBoundingRect() const noexcept { return m_show_bounding_rect; }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) noexcept override;
  void SetHasShadow(const bool has_shadow) noexcept { m_has_shadow = has_shadow; }
  void SetRay(const double ray);
  void setShowBoundingRect(const bool show_bounding_rect) noexcept;
  QPainterPath shape() const noexcept override;
  int type() const noexcept override { return Type; }

  boost::signals2::signal<void(Node * const)> m_signal_focus_in;
  boost::signals2::signal<void(Node * const)> m_signal_focus_out;
  boost::signals2::signal<void(Node * const)> m_signal_position_changed;

protected:

  void focusInEvent(QFocusEvent *event) noexcept override;
  void focusOutEvent(QFocusEvent *event) noexcept override;
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) noexcept override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) noexcept override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) noexcept override;

  private:
  QList<Edge*> m_edges;
  GraphWidget * const m_graph;
  bool m_has_shadow;
  QPointF m_new_pos;
  double m_ray; //The ray of the circle
  bool m_show_bounding_rect;
};

void DrawNode(
  QPainter * const painter,
  const QStyleOptionGraphicsItem * const option,
  const Node * const node
) noexcept;

#endif

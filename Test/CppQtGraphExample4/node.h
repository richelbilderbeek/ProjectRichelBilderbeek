// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html
#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class Node : public QGraphicsItem
{
public:
  Node(GraphWidget *graphWidget);
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  void addEdge(Edge *edge);
  QList<Edge *> edges() const;

  enum { Type = UserType + 1 };
  int type() const { return Type; }

  void calculateForces();
  bool advance();

  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

  private:
  QList<Edge*> m_edges;
  QPointF m_new_pos;
  GraphWidget * const m_graph;
};

#endif

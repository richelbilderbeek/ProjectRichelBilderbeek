// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

struct GraphWidget;
struct Node;

class Edge : public QGraphicsItem
{
public:
  Edge(
    Node * const source_node,
    Node * const center_node,
    Node * const dest_node
  );
  Edge(const Edge&) = delete;
  Edge& operator=(const Edge&) = delete;

  Node * sourceNode() const noexcept;
  Node * destNode() const noexcept;

  void adjust() noexcept;

  enum { Type = UserType + 2 };
  int type() const { return Type; }

protected:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
  const double m_arrow_size;
  Node * const m_center_node; //This node is managed by Edge
  Node * const m_dest_node; //This is a node pointed to by Edge
  QPointF m_dest_point;
  bool m_show_bounding_rect;
  Node * const m_source_node; //This is a node pointed to by Edge
  QPointF m_source_point;
};

 #endif

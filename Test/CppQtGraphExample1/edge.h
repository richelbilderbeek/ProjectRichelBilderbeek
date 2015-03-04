// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

class Edge : public QGraphicsItem
{
public:
  Edge(Node *sourceNode, Node *destNode);
  Edge(const Edge&) = delete;
  Edge& operator=(const Edge&) = delete;

  Node *sourceNode() const;
  Node *destNode() const;

  void adjust();

  enum { Type = UserType + 2 };
  int type() const { return Type; }

protected:
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
  Node *m_source_node;
  Node *m_dest_node;

  QPointF m_source_point;
  QPointF m_dest_point;
  qreal m_arrow_size;
};

 #endif

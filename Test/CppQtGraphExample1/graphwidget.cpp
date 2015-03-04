// Adapted from Qt example 'Elastic nodes'
// http://qt-project.org/doc/qt-4.8/graphicsview-elasticnodes.html

#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <QtGui>

#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
: QGraphicsView(parent),
  m_timer_id(0),
  m_centerNode{new Node(this)}
{
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-200, -200, 400, 400);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.8), qreal(0.8));
  setMinimumSize(400, 400);
  setWindowTitle(tr("Elastic Nodes"));

  Node *node1 = new Node(this);
  Node *node2 = new Node(this);
  Node *node3 = new Node(this);
  Node *node4 = new Node(this);
  Node *node6 = new Node(this);
  Node *node7 = new Node(this);
  Node *node8 = new Node(this);
  Node *node9 = new Node(this);
  scene->addItem(node1);
  scene->addItem(node2);
  scene->addItem(node3);
  scene->addItem(node4);
  scene->addItem(m_centerNode);
  scene->addItem(node6);
  scene->addItem(node7);
  scene->addItem(node8);
  scene->addItem(node9);
  scene->addItem(new Edge(node1, node2));
  scene->addItem(new Edge(node2, node3));
  scene->addItem(new Edge(node2, m_centerNode));
  scene->addItem(new Edge(node3, node6));
  scene->addItem(new Edge(node4, node1));
  scene->addItem(new Edge(node4, m_centerNode));
  scene->addItem(new Edge(m_centerNode, node6));
  scene->addItem(new Edge(m_centerNode, node8));
  scene->addItem(new Edge(node6, node9));
  scene->addItem(new Edge(node7, node4));
  scene->addItem(new Edge(node8, node7));
  scene->addItem(new Edge(node9, node8));

  node1->setPos(-50, -50);
  node2->setPos(0, -50);
  node3->setPos(50, -50);
  node4->setPos(-50, 0);
  m_centerNode->setPos(0, 0);
  node6->setPos(50, 0);
  node7->setPos(-50, 50);
  node8->setPos(0, 50);
  node9->setPos(50, 50);
}

void GraphWidget::itemMoved()
{
if (!m_timer_id)
m_timer_id = startTimer(1000 / 25);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
switch (event->key()) {
case Qt::Key_Up:
m_centerNode->moveBy(0, -20);
break;
case Qt::Key_Down:
m_centerNode->moveBy(0, 20);
break;
case Qt::Key_Left:
m_centerNode->moveBy(-20, 0);
break;
case Qt::Key_Right:
m_centerNode->moveBy(20, 0);
break;
case Qt::Key_Plus:
zoomIn();
break;
case Qt::Key_Minus:
zoomOut();
break;
case Qt::Key_Space:
case Qt::Key_Enter:
shuffle();
break;
default:
QGraphicsView::keyPressEvent(event);
}
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
Q_UNUSED(event);

QList<Node *> nodes;
foreach (QGraphicsItem *item, scene()->items()) {
if (Node *node = qgraphicsitem_cast<Node *>(item))
nodes << node;
}

foreach (Node *node, nodes)
node->calculateForces();

bool itemsMoved = false;
foreach (Node *node, nodes) {
if (node->advance())
itemsMoved = true;
}

if (!itemsMoved) {
killTimer(m_timer_id);
m_timer_id = 0;
}
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
  Q_UNUSED(rect);

  // Shadow
  QRectF sceneRect = this->sceneRect();
  QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
  QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
  if (rightShadow.intersects(rect) || rightShadow.contains(rect))
  painter->fillRect(rightShadow, Qt::darkGray);
  if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
  painter->fillRect(bottomShadow, Qt::darkGray);

  // Fill
  QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
  gradient.setColorAt(0, Qt::white);
  gradient.setColorAt(1, Qt::lightGray);
  painter->fillRect(rect.intersected(sceneRect), gradient);
  painter->setBrush(Qt::NoBrush);
  painter->drawRect(sceneRect);

  #if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_MAEMO_5)
  // Text
  QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
  sceneRect.width() - 4, sceneRect.height() - 4);
  QString message(tr("Click and drag the nodes around, and zoom with the mouse "
  "wheel or the '+' and '-' keys"));

  QFont font = painter->font();
  font.setBold(true);
  font.setPointSize(14);
  painter->setFont(font);
  painter->setPen(Qt::lightGray);
  painter->drawText(textRect.translated(2, 2), message);
  painter->setPen(Qt::black);
  painter->drawText(textRect, message);
  #endif
}

void GraphWidget::scaleView(qreal scaleFactor)
{
qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
if (factor < 0.07 || factor > 100)
return;

scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
foreach (QGraphicsItem *item, scene()->items()) {
if (qgraphicsitem_cast<Node *>(item))
item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
}
}

void GraphWidget::zoomIn()
{
scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
scaleView(1 / qreal(1.2));
}

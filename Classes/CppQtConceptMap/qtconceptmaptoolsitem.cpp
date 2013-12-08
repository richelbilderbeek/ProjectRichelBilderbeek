#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaptoolsitem.h"

#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "qtconceptmapnode.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTool::QtTool()
  : m_signal_clicked(),
    m_item(nullptr)
{
  this->setPixmap(QPixmap(":/CppQtConceptMap/images/CppQtConceptMapArrow14x14.png"));

  assert(!this->pixmap().isNull());

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsSelectable);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);

  this->setVisible(false);

  this->setZValue(3.0);
}


ribi::cmap::QtNode * ribi::cmap::QtTool::GetBuddyItem()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<QtNode * >(const_cast<const QtTool *>(this)->GetBuddyItem());
}

const ribi::cmap::QtNode * ribi::cmap::QtTool::GetBuddyItem() const
{
  assert(m_item);
  return m_item;
}


void ribi::cmap::QtTool::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void ribi::cmap::QtTool::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
  QGraphicsPixmapItem::mousePressEvent(event);
  m_signal_clicked();
}

void ribi::cmap::QtTool::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  assert(m_item);
  this->setPos(
    m_item->pos().x(),
    m_item->pos().y() - 32.0);

  QGraphicsPixmapItem::paint(painter,option,widget);

  if (this->isSelected() || this->hasFocus())
  {
    QPen pen;
    pen.setColor(QColor(255,0,0));
    painter->setPen(pen);
    //No idea why these relative coordinats are best
    //I'd expect no adjustment to look best...
    painter->drawRect(this->boundingRect().adjusted(0.0,0.0,-2.0,-2.0));
  }
}

void ribi::cmap::QtTool::SetBuddyItem(const QtNode * const item)
{
  if (item != m_item)
  {
    m_item = item;
    if (m_item)
    {
      this->setVisible(true);
      this->update();
    }
    else
    {
      this->setVisible(false);
    }
  }
}

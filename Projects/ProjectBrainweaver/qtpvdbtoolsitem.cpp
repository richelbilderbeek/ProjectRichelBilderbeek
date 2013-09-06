#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbtoolsitem.h"

#include <QCursor>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "qtpvdbnodeitem.h"
#include "trace.h"

ribi::pvdb::QtPvdbToolsItem::QtPvdbToolsItem()
  : m_signal_clicked(),
    m_item(nullptr)
{
  this->setPixmap(QPixmap(":/images/PicArrow14x14.png"));

  assert(!this->pixmap().isNull());

  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsSelectable);

  //Allow mouse tracking
  this->setAcceptHoverEvents(true);

  this->setVisible(false);

  this->setZValue(3.0);
}


ribi::pvdb::QtPvdbNodeItem * ribi::pvdb::QtPvdbToolsItem::GetBuddyItem()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<QtPvdbNodeItem * >(const_cast<const QtPvdbToolsItem *>(this)->GetBuddyItem());
}

const ribi::pvdb::QtPvdbNodeItem * ribi::pvdb::QtPvdbToolsItem::GetBuddyItem() const
{
  assert(m_item);
  return m_item;
}


void ribi::pvdb::QtPvdbToolsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *)
{
  this->setCursor(QCursor(Qt::PointingHandCursor));
}

void ribi::pvdb::QtPvdbToolsItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
  QGraphicsPixmapItem::mousePressEvent(event);
  m_signal_clicked();
}

void ribi::pvdb::QtPvdbToolsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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

void ribi::pvdb::QtPvdbToolsItem::SetBuddyItem(const QtPvdbNodeItem * const item)
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

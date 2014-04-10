#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QCursor>
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include "qttextpositionitem.h"
#pragma GCC diagnostic pop

QtTextPositionItem::QtTextPositionItem(
  const std::string& text,
  QGraphicsItem *parent)
  : QGraphicsItem(parent),
    m_text(text),
    //Add a margin of 2 pixels at the edges
    m_rect(
      -2,
      -2,
      //For a pixels size of 13, the characters will be 8 pixels wide
      4 + (8 * static_cast<int>(text.size())),
      //For a pixels size of 13, the characters will be 13 pixels high
      4 + 13)

{
  this->setFlags(ItemIsMovable);
}

QRectF QtTextPositionItem::boundingRect() const
{
  return m_rect;
}

void QtTextPositionItem::paint(
  QPainter *painter,
  const QStyleOptionGraphicsItem * /*option*/,
  QWidget * /*widget*/
)
{
  QFont font;
  font.setFamily("monospace");
  font.setPixelSize(13);
  painter->setFont(font);
  painter->setBrush(QBrush(QColor(228,228,228)));
  painter->drawRect(m_rect);
  //Use a margin of 2 around the edges
  painter->drawText(m_rect.adjusted(2,2,-2,-2),m_text.c_str());
}

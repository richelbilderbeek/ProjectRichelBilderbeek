#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtrectitem.h"

#include <cassert>
#include <sstream>
#include <QGraphicsScene>
#include <QPainter>
#pragma GCC diagnostic pop

QtRectItem::QtRectItem(QGraphicsItem *parent)
 : QGraphicsRectItem(parent)
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
}

void QtRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  //Create the text
  std::stringstream s;
  s << "(" << static_cast<int>(this->pos().x()) << "," << static_cast<int>(this->pos().y()) << ")";
  const std::string t = s.str();

  //Resize the rect to the text its size (using QFontMetrics to find this out)
  QFontMetrics q(painter->font());
  const double width = q.width(t.c_str());
  const double height = q.height();
  this->setRect(-0.5 * width, -0.5 * height, width, height);

  //Draw the text
  painter->drawText(rect(),t.c_str());

  //Let QGraphicsRectItem handle the default painting
  QGraphicsRectItem::paint(painter,option,widget);
}

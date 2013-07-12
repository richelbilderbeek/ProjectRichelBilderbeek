#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtroundedrectitem.h"

#include <cassert>
#include <sstream>
#include <QFont>
#include <QGraphicsScene>
#include <QPainter>

QtRoundedRectItem::QtRoundedRectItem(QGraphicsItem *parent)
  : QGraphicsRectItem(parent), //New since Qt5
   m_contour_pen(QPen(QColor(0,0,0))),
   m_focus_pen(QPen(QColor(0,0,0),1,Qt::DashLine))
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->SetRoundedRect(QRectF(-16.0,-16.0,32.0,32.0),4.0,4.0);
}

const std::string QtRoundedRectItem::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> QtRoundedRectItem::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-13: version 1.0: initial version");
  v.push_back("2012-12-19: version 1.1: added use of pen, brush and focus-indicating pen");
  v.push_back("2012-12-22: version 1.2: correctly uses the focus and regular pen, added contour pen");
  return v;
}

void QtRoundedRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsRectItem::mouseMoveEvent(event);
  m_signal_request_scene_update();
}

void QtRoundedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  painter->setBrush(brush());
  //The item can be selected by clicking on it, or can have focus by moving towards it
  if (this->isSelected() || this->hasFocus())
  {
    painter->setPen(m_focus_pen);
    painter->drawRoundedRect(this->rect(),m_radius_x,m_radius_y);
  }
  else
  {
    painter->setPen(m_contour_pen);
    painter->drawRoundedRect(this->rect(),m_radius_x,m_radius_y);
  }
}

void QtRoundedRectItem::SetContourPen(const QPen& pen)
{
  if (m_contour_pen != pen)
  {
    m_contour_pen = pen;
    this->update();
    m_signal_item_has_updated(this);
  }
}

void QtRoundedRectItem::SetFocusPen(const QPen& pen)
{
  if (m_focus_pen != pen)
  {
    m_focus_pen = pen;
    this->update();
    m_signal_item_has_updated(this);
  }
}

void QtRoundedRectItem::SetRadiusX(const double radius_x)
{
  if (m_radius_x != radius_x)
  {
    m_radius_x = radius_x;
    this->update();
    m_signal_item_has_updated(this);
  }
}

void QtRoundedRectItem::SetRadiusY(const double radius_y)
{
  if (m_radius_y != radius_y)
  {
    m_radius_y = radius_y;
    this->update();
    m_signal_item_has_updated(this);
  }
}


void QtRoundedRectItem::SetRoundedRect(const QRectF rect, const double radius_x, const double radius_y)
{
  this->setRect(rect);
  this->SetRadiusX(radius_x);
  this->SetRadiusY(radius_y);
  this->update();
}

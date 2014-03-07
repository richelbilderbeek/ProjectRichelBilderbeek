#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtroundedrectitem.h"

#include <cassert>
#include <sstream>

#include <QFont>
#include <QGraphicsScene>
#include <QPainter>
#pragma GCC diagnostic pop

ribi::QtRoundedRectItem::QtRoundedRectItem(QGraphicsItem *parent)
  : QGraphicsRectItem(parent), //New since Qt5
   m_signal_item_has_updated{},
   m_signal_request_scene_update{},
   m_contour_pen(QPen(QColor(0,0,0))),
   m_focus_pen(QPen(QColor(0,0,0),1,Qt::DashLine)),
   m_radius_x{4.0},
   m_radius_y{4.0}
{
  this->setFlags(
      QGraphicsItem::ItemIsFocusable
    | QGraphicsItem::ItemIsMovable
    | QGraphicsItem::ItemIsSelectable);
  this->SetRoundedRect(QRectF(-16.0,-16.0,32.0,32.0),m_radius_x,m_radius_y);
}

std::string ribi::QtRoundedRectItem::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::QtRoundedRectItem::GetVersionHistory() noexcept
{
  return {
    "2012-12-13: version 1.0: initial version",
    "2012-12-19: version 1.1: added use of pen, brush and focus-indicating pen",
    "2012-12-22: version 1.2: correctly uses the focus and regular pen, added contour pen"
  };
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
void ribi::QtRoundedRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsRectItem::mouseMoveEvent(event);
  m_signal_request_scene_update();
}
#pragma GCC diagnostic pop

void ribi::QtRoundedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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

void ribi::QtRoundedRectItem::SetContourPen(const QPen& pen)
{
  if (m_contour_pen != pen)
  {
    m_contour_pen = pen;
    this->update();
    m_signal_item_has_updated(this);
  }
}

void ribi::QtRoundedRectItem::SetFocusPen(const QPen& pen)
{
  if (m_focus_pen != pen)
  {
    m_focus_pen = pen;
    this->update();
    m_signal_item_has_updated(this);
  }
}

void ribi::QtRoundedRectItem::SetRadiusX(const double radius_x)
{
  if (m_radius_x != radius_x)
  {
    m_radius_x = radius_x;
    this->update();
    m_signal_item_has_updated(this);
  }
}

void ribi::QtRoundedRectItem::SetRadiusY(const double radius_y)
{
  if (m_radius_y != radius_y)
  {
    m_radius_y = radius_y;
    this->update();
    m_signal_item_has_updated(this);
  }
}


void ribi::QtRoundedRectItem::SetRoundedRect(const QRectF rect, const double radius_x, const double radius_y)
{
  this->setRect(rect);
  this->SetRadiusX(radius_x);
  this->SetRadiusY(radius_y);
  this->update();
}

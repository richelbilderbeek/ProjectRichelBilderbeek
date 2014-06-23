#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtscaleitem.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

#include <QPainter>
#include <QCursor>
#include "units.h"
#pragma GCC diagnostic pop

const double QtScaleItem::m_length
  = boost::units::quantity<boost::units::si::length>(
    1.0 * boost::units::si::centi * boost::units::si::meter
  ).value();

const std::string QtScaleItem::m_type_string = "QtScaleItem";

QtScaleItem::QtScaleItem(QGraphicsItem * parent)
  : QGraphicsItem(parent)
{
  this->setZValue(4.0);

  this->setAcceptHoverEvents(true);
}

QRectF QtScaleItem::boundingRect() const
{
  return QRectF(-m_length,-m_length,2.0*m_length,2.0*m_length);
}

void QtScaleItem::GetRgb(
  const double x,
  double& r,
  double& g,
  double& b)
{
  assert(x >= 0.0);
  assert(x <= 1.0);

  const double f_r = std::max(0.0,
    (x < 0.5
    ? std::cos(x * 1.5 * boost::math::constants::pi<double>())
    : -std::sin(x * 1.5 * boost::math::constants::pi<double>())
    ) );
  const double f_g = std::max(0.0, std::sin( x * 1.5 * boost::math::constants::pi<double>() ) );
  const double f_b = std::max(0.0, -std::cos( x * 1.5 * boost::math::constants::pi<double>() ) );
  const double max = std::max(f_r, std::max(f_g,f_b));
  assert(max!=0);

  r = f_r / max;
  g = f_g / max;
  b = f_b / max;
}

void QtScaleItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
  if (this->flags() & QGraphicsItem::ItemIsMovable)
  {
    this->setCursor(QCursor(Qt::PointingHandCursor));
  }
}

void QtScaleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
  assert(painter);
  assert(painter->isActive());

  double mylength = m_length;
  const int n = 6;
  for (int i=0; i!=n; ++i)
  {
    const double f = static_cast<double>(i) / static_cast<double>(n);
    double r = 0.0; double g = 0.0; double b = 0.0;
    GetRgb(f,r,g,b);
    const QPen pen(QColor(r * 255.0, g * 255.0, b * 255.0));
    painter->setPen(pen);
    //Cross
    const QPointF left(-mylength,0.0);
    const QPointF right(mylength,0.0);
    const QPointF top(   0.0,-mylength);
    const QPointF bottom(0.0, mylength);
    painter->drawLine(left,right);
    painter->drawLine(top,bottom);
    //Crosshairs
    const QPointF go_up(  0.0,-mylength * 0.1);
    const QPointF go_down(0.0, mylength * 0.1);
    const QPointF go_left( -mylength * 0.1,0.0);
    const QPointF go_right( mylength * 0.1,0.0);
    painter->drawLine( left  + go_up  ,  left + go_down );
    painter->drawLine(right  + go_up  , right + go_down );
    painter->drawLine(  top  + go_left,   top + go_right);
    painter->drawLine(bottom + go_left,bottom + go_right);
    mylength *= 0.1;
  }
}

QPainterPath QtScaleItem::shape() const
{
  QPainterPath p;
  const QPointF left(-m_length,0.0);
  const QPointF right(m_length,0.0);
  const QPointF top(   0.0,-m_length);
  const QPointF bottom(0.0, m_length);
  p.moveTo(left);
  p.lineTo(right);
  p.moveTo(top);
  p.lineTo(bottom);
  return p;
}


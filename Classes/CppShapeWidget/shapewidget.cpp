#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "shapewidget.h"

#include <cassert>
#include <cmath>

#include <boost/numeric/conversion/cast.hpp>

#include "shape.h"
#include "rectangle.h"
//#include "trace.h"

#pragma GCC diagnostic pop

ribi::ShapeWidget::ShapeWidget(
  const int n_corners,
  const double rotation,
  const int x,
  const int y,
  const int width,
  const int height,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
  : m_shape(new Shape(n_corners,rotation,red,green,blue))
{
  this->SetGeometry(Rect(x,y,width,height));
}

ribi::ShapeWidget * ribi::ShapeWidget::Clone() const noexcept
{
  ShapeWidget * const w = new ShapeWidget(
    this->GetShape()->GetNumberOfCorners(),
    this->GetShape()->GetRotation(),
    this->GetGeometry().GetX(),
    this->GetGeometry().GetY(),
    this->GetGeometry().GetWidth(),
    this->GetGeometry().GetHeight(),
    this->GetShape()->GetRed(),
    this->GetShape()->GetGreen(),
    this->GetShape()->GetBlue());
  assert(*w == *this);
  return w;
}

const std::string ribi::ShapeWidget::GetVersion() noexcept
{
  return "2.0";
}

const std::vector<std::string> ribi::ShapeWidget::GetVersionHistory() noexcept
{
  return {
    "2011-07-13: Version 1.0: initial version",
    "2011-07-18: Version 1.1: removed useless methods",
    "2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget"
  };
}

bool ribi::operator==(const ShapeWidget& lhs,const ShapeWidget& rhs) noexcept
{
  return  lhs.GetGeometry() ==  rhs.GetGeometry()
    &&   *lhs.GetShape()    == *rhs.GetShape();
}


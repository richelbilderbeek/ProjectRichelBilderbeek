#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "shapewidget.h"

#include <cassert>
#include <cmath>

//Terrible #define, but my crosscompiler cannot find the definition of M_PI in cmath.h :-(
#ifndef M_PI
# define M_PI		3.14159265358979323846	/* pi */
#endif
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "shape.h"
#include "rectangle.h"
//#include "trace.h"
//---------------------------------------------------------------------------
ShapeWidget::ShapeWidget(
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
//---------------------------------------------------------------------------
///Make a deep copy of ShapeWidget
ShapeWidget * ShapeWidget::Clone() const
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
//---------------------------------------------------------------------------
const std::string ShapeWidget::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> ShapeWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-07-13: Version 1.0: initial version");
  v.push_back("2011-07-18: Version 1.1: removed useless methods");
  v.push_back("2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget");
  return v;
}
//---------------------------------------------------------------------------
bool operator==(const ShapeWidget& lhs,const ShapeWidget& rhs)
{
  return  lhs.GetGeometry() ==  rhs.GetGeometry()
    &&   *lhs.GetShape()    == *rhs.GetShape();
}
//---------------------------------------------------------------------------

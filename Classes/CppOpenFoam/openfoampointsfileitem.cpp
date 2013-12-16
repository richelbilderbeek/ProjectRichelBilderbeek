#include "openfoampointsfileitem.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include "fuzzy_equal_to.h"
#include "trace.h"

ribi::foam::PointsFileItem::PointsFileItem(
  const Coordinat3D& coordinat
  )
  : m_coordinat(coordinat)
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
void ribi::foam::PointsFileItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::PointsFileItem::Test");
  //operator== and operator!=
  {
    const PointsFileItem i( Coordinat3D(1.1,2.2,3.3) );
    PointsFileItem j( Coordinat3D(2.2,3.3,4.4) );
    assert(i == i);
    assert(i != j);
    assert(j != i);
    assert(j == j);
  }
  //operator<< and operator>>
  {
    const PointsFileItem i( Coordinat3D(1.1,2.2,3.3) );
    std::stringstream s;
    s << i;
    PointsFileItem j;
    s >> j;
    if (i != j)
    {
      TRACE(i);
      TRACE(j);
    }
    assert(i == j);
  }
  TRACE("Finished ribi::foam::PointsFileItem::Test successfully");
}
#endif

bool ribi::foam::operator==(const PointsFileItem& lhs, const PointsFileItem& rhs)
{
  const double abs_tolerance = 0.001;
  return
        fuzzy_equal_to_abs(abs_tolerance)(lhs.GetCoordinat().GetX(),rhs.GetCoordinat().GetX())
     && fuzzy_equal_to_abs(abs_tolerance)(lhs.GetCoordinat().GetY(),rhs.GetCoordinat().GetY())
     && fuzzy_equal_to_abs(abs_tolerance)(lhs.GetCoordinat().GetZ(),rhs.GetCoordinat().GetZ())
  ;
}

bool ribi::foam::operator!=(const PointsFileItem& lhs, const PointsFileItem& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const PointsFileItem& item)
{
  os
    << "("
    << item.GetCoordinat().GetX() << " "
    << item.GetCoordinat().GetY() << " "
    << item.GetCoordinat().GetZ()
    << ")"
  ;

  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, PointsFileItem& f)
{

  {
    char bracket_open;
    is >> bracket_open;
    assert(bracket_open == '(');
  }
  {
    double d = 0.0;
    is >> d;
    assert(is);
    f.m_coordinat.SetX(d);
  }
  {
    double d = 0.0;
    is >> d;
    assert(is);
    f.m_coordinat.SetY(d);
  }
  {
    double d = 0.0;
    is >> d;
    assert(is);
    f.m_coordinat.SetZ(d);
  }
  {
    char bracket_close;
    is >> bracket_close;
    assert(is);
    assert(bracket_close == ')');
  }
  return is;
}

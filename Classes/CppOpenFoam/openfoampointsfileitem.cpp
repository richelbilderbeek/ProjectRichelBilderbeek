#include "openfoampointsfileitem.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include "fuzzy_equal_to.h"
#include "trace.h"

ribi::foam::PointsFileItem::PointsFileItem(
  const std::array<double,3>& coordinat
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
    const PointsFileItem i( {1.1,2.2,3.3} );
    PointsFileItem j( {2.2,3.3,4.4} );
    assert(i == i);
    assert(i != j);
    assert(j != i);
    assert(j == j);
  }
  //operator<< and operator>>
  {
    const PointsFileItem i( {1.1,2.2,3.3} );
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
        fuzzy_equal_to_abs(abs_tolerance)(lhs.GetCoordinat()[0],rhs.GetCoordinat()[0])
     && fuzzy_equal_to_abs(abs_tolerance)(lhs.GetCoordinat()[1],rhs.GetCoordinat()[1])
     && fuzzy_equal_to_abs(abs_tolerance)(lhs.GetCoordinat()[2],rhs.GetCoordinat()[2])
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
  ;

  std::stringstream s;
  for (const double d: item.GetCoordinat()) { s << d << " "; }
  std::string t { s.str() };
  assert(t.back() == ' ');
  t.pop_back();
  assert(t.back() != ' ');
  os
    << t
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
  for (int i=0; i!=3; ++i)
  {
    double d = 0.0;
    is >> d;
    f.m_coordinat[i] = d;
  }
  {
    char bracket_close;
    is >> bracket_close;
    assert(bracket_close == ')');
  }
  return is;
}

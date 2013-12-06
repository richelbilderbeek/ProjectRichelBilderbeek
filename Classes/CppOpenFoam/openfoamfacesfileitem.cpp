#include "openfoamfacesfileitem.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "openfoamparseerror.h"
#include "trace.h"

ribi::foam::FacesFileItem::FacesFileItem(
  const std::vector<PointIndex>& point_indices
  )
  : m_point_indices{point_indices}
{
  #ifndef NDEBUG
  Test();
  for (PointIndex index: m_point_indices)
  {
    assert(index.Get() > 0); //NONSENSE? I'd guess an index starts at zero?
  }
  #endif
}

#ifndef NDEBUG
void ribi::foam::FacesFileItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::FacesFileItem::Test");
  const FacesFileItem i( { PointIndex(1),PointIndex(2),PointIndex(3),PointIndex(4) } );
  std::stringstream s;
  s << i;
  FacesFileItem j;
  s >> j;
  if (i != j)
  {
    TRACE(i);
    TRACE(j);
  }
  assert(i == j);
  TRACE("Finished ribi::foam::FacesFileItem::Test successfully");
}
#endif

bool ribi::foam::operator==(const FacesFileItem& lhs, const FacesFileItem& rhs)
{
  return
       lhs.GetPointIndices() == rhs.GetPointIndices()
  ;
}

bool ribi::foam::operator!=(const FacesFileItem& lhs, const FacesFileItem& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const FacesFileItem& item)
{
  os
    << item.GetPointIndices().size()
    << "("
  ;

  std::stringstream s;
  for (const PointIndex i: item.GetPointIndices()) { s << i << " "; }
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

std::istream& ribi::foam::operator>>(std::istream& is, FacesFileItem& f)
{
  assert(f.GetPointIndices().empty()); //Or empty it
  int n_nodes = 0;
  {
    is >> n_nodes;
    assert(is);
    if (n_nodes <= 0)
    {
      throw ParseError();
    }
    assert(n_nodes > 0);
  }
  {
    char bracket_open;
    is >> bracket_open;
    assert(bracket_open == '(');
  }
  for (int i=0; i!=n_nodes; ++i)
  {
    PointIndex node;
    is >> node;
    f.m_point_indices.push_back(node);
  }
  {
    char bracket_close;
    is >> bracket_close;
    assert(bracket_close == ')');
  }
  return is;
}

#include "openfoamneighbourfileitem.h"

#include <cassert>
#include <iostream>

#include "trace.h"

ribi::foam::NeighbourFileItem::NeighbourFileItem(
  const int face_index
  )
  : m_face_index{face_index}
{
  #ifndef NDEBUG
  Test();
  assert(m_face_index >= -1 && "Also allow -1");
  #endif
}

#ifndef NDEBUG
void ribi::foam::NeighbourFileItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::NeighbourFileItem::Test");
  const NeighbourFileItem i(123);
  std::stringstream s;
  s << i;
  NeighbourFileItem j;
  s >> j;
  if (i != j)
  {
    TRACE(i);
    TRACE(j);
  }
  assert(i == j);
  TRACE("Finished ribi::foam::NeighbourFileItem::Test successfully");
}
#endif

bool ribi::foam::operator==(const NeighbourFileItem& lhs, const NeighbourFileItem& rhs)
{
  return
       lhs.GetFaceIndex() == rhs.GetFaceIndex()
  ;
}

bool ribi::foam::operator!=(const NeighbourFileItem& lhs, const NeighbourFileItem& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const NeighbourFileItem& item)
{
  os << item.GetFaceIndex();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, NeighbourFileItem& f)
{
  is >> f.m_face_index;
  assert(f.GetFaceIndex() >= -1);
  return is;
}

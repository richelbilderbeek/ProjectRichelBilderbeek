#include "openfoamownerfileitem.h"

#include <cassert>
#include <iostream>

#include "trace.h"

ribi::foam::OwnerFileItem::OwnerFileItem(
  const int face_index
  )
  : m_face_index{face_index}
{
  #ifndef NDEBUG
  Test();
  assert(m_face_index >= 0);
  #endif
}

#ifndef NDEBUG
void ribi::foam::OwnerFileItem::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::OwnerFileItem::Test");
  const OwnerFileItem i(123);
  std::stringstream s;
  s << i;
  OwnerFileItem j;
  s >> j;
  if (i != j)
  {
    TRACE(i);
    TRACE(j);
  }
  assert(i == j);
  TRACE("Finished ribi::foam::OwnerFileItem::Test successfully");
}
#endif

bool ribi::foam::operator==(const OwnerFileItem& lhs, const OwnerFileItem& rhs)
{
  return
       lhs.GetFaceIndex() == rhs.GetFaceIndex()
  ;
}

bool ribi::foam::operator!=(const OwnerFileItem& lhs, const OwnerFileItem& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const OwnerFileItem& item)
{
  os << item.GetFaceIndex();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, OwnerFileItem& f)
{
  is >> f.m_face_index;
  if (f.GetFaceIndex() < 0) TRACE(f.GetFaceIndex());
  assert(f.GetFaceIndex() >= 0);
  return is;
}

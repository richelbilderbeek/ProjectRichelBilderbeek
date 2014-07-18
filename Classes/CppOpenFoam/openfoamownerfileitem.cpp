#include "openfoamownerfileitem.h"

#include <cassert>
#include <iostream>

#include "trace.h"

ribi::foam::OwnerFileItem::OwnerFileItem(
  const CellIndex& cell_index
  )
  : m_cell_index{cell_index}
{
  #ifndef NDEBUG
  Test();
  assert(m_cell_index.Get() >= 0);
  #endif
}

#ifndef NDEBUG
void ribi::foam::OwnerFileItem::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::OwnerFileItem::Test");
  //operator==
  {
    const OwnerFileItem i(CellIndex(123));
    assert(i == i);
    const OwnerFileItem j(CellIndex(123));
    assert(i == j);
    assert(j == i);
    assert(j == j);
  }
  //operator!=
  {
    const OwnerFileItem i(CellIndex(123));
    const OwnerFileItem j(CellIndex(234));
    assert(i != j);
    assert(j != i);
  }
  //operator<< and operator>>
  {
    const OwnerFileItem i(CellIndex(123));
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
  }
  TRACE("Finished ribi::foam::OwnerFileItem::Test successfully");
}
#endif

bool ribi::foam::operator==(const OwnerFileItem& lhs, const OwnerFileItem& rhs)
{
  return
       lhs.GetCellIndex() == rhs.GetCellIndex()
  ;
}

bool ribi::foam::operator!=(const OwnerFileItem& lhs, const OwnerFileItem& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const OwnerFileItem& item)
{
  os << item.GetCellIndex();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, OwnerFileItem& f)
{
  is >> f.m_cell_index;
  assert(is);
  if (f.GetCellIndex().Get() < 0) TRACE(f.GetCellIndex());
  assert(f.GetCellIndex().Get() >= 0);
  return is;
}

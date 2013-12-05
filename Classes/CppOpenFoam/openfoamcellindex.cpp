#include "openfoamcellindex.h"

#include <cassert>
#include <iostream>

ribi::foam::CellIndex::CellIndex(const int index)
  : m_index(index)
{
  assert(m_index >= 0
    && "A CellIndex must be zero or a positive value");
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const CellIndex& face_index)
{
  os << face_index.Get();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, CellIndex& face_index)
{
  is >> face_index.m_index;
  return is;
}

bool ribi::foam::operator==(const CellIndex& lhs, const CellIndex& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}


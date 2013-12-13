#include "openfoampointindex.h"

#include <cassert>
#include <iostream>

ribi::foam::PointIndex::PointIndex(const int index)
  : m_index(index)
{
  assert(m_index >= 0
    && "A PointIndex must be zero or a positive value");
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const PointIndex& face_index)
{
  os << face_index.Get();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, PointIndex& face_index)
{
  is >> face_index.m_index;
  assert(is);
  return is;
}

bool ribi::foam::operator==(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

bool ribi::foam::operator!=(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return !(lhs == rhs);
}

bool ribi::foam::operator<(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return lhs.Get() < rhs.Get();
}

bool ribi::foam::operator>(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return lhs.Get() > rhs.Get();
}

bool ribi::foam::operator<=(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return !(lhs > rhs);
}

bool ribi::foam::operator>=(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return !(lhs < rhs);
}

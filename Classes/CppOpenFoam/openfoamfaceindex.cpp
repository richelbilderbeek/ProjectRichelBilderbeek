#include "openfoamfaceindex.h"

#include <cassert>
#include <iostream>

ribi::foam::FaceIndex::FaceIndex(const int index)
  : m_index(index)
{
  assert(m_index >= 0
    && "A FaceIndex must be zero or a positive value");
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const FaceIndex& face_index)
{
  os << face_index.Get();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, FaceIndex& face_index)
{
  is >> face_index.m_index;
  return is;
}

bool ribi::foam::operator==(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

bool ribi::foam::operator!=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return !(lhs == rhs);
}

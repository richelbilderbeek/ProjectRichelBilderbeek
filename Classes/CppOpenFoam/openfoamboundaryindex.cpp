#include "openfoamboundaryindex.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "trace.h"

ribi::foam::BoundaryIndex::BoundaryIndex(const int index)
  : m_index(index)
{
  #ifndef NDEBUG
  if (m_index < 0)
  {
    TRACE("ERROR");
    TRACE(m_index);
  }
  #endif
  assert(m_index >= 0
    && "A BoundaryIndex must be zero or a positive value");
  if (m_index < 0)
  {
    throw std::invalid_argument("A BoundaryIndex must be zero or a positive value");
  }
}

ribi::foam::BoundaryIndex& ribi::foam::BoundaryIndex::operator-=(const BoundaryIndex& rhs)
{
  m_index -= rhs.Get();

  assert(m_index >= 0
    && "A BoundaryIndex must be zero or a positive value");
  if (m_index < 0)
  {
    throw std::invalid_argument(
      "BoundaryIndex::operator-=: BoundaryIndex cannot be negative");
  }
  return *this;
}

ribi::foam::BoundaryIndex& ribi::foam::BoundaryIndex::operator++() noexcept
{
  ++m_index;
  return *this;
}

ribi::foam::BoundaryIndex ribi::foam::BoundaryIndex::operator++(int) noexcept
{
  BoundaryIndex old(*this);
  ++(*this);
  return old;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const BoundaryIndex& face_index) noexcept
{
  os << face_index.Get();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, BoundaryIndex& face_index) noexcept
{
  is >> face_index.m_index;
  return is;
}

const ribi::foam::BoundaryIndex ribi::foam::operator+(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return BoundaryIndex(lhs.Get() + rhs.Get());
}

const ribi::foam::BoundaryIndex ribi::foam::operator-(const BoundaryIndex& lhs, const BoundaryIndex& rhs)
{
  return BoundaryIndex(lhs.Get() - rhs.Get());
}

bool ribi::foam::operator==(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

bool ribi::foam::operator!=(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return !(lhs == rhs);
}

bool ribi::foam::operator<(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return lhs.Get() < rhs.Get();
}

bool ribi::foam::operator>(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return lhs.Get() > rhs.Get();
}

bool ribi::foam::operator>=(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return !(lhs < rhs);
}

bool ribi::foam::operator<=(const BoundaryIndex& lhs, const BoundaryIndex& rhs) noexcept
{
  return !(lhs > rhs);
}

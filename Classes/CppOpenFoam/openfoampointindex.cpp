#include "openfoampointindex.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

ribi::foam::PointIndex::PointIndex(const int index)
  : m_index(index)
{
  assert(m_index >= 0
    && "A PointIndex must be zero or a positive value");
  if (index < 0)
  {
     throw std::logic_error("A PointIndex must be zero or a positive value");
  }
}

ribi::foam::PointIndex& ribi::foam::PointIndex::operator++() noexcept
{
  ++m_index;
  return *this;
}

ribi::foam::PointIndex ribi::foam::PointIndex::operator++(int) noexcept
{
  PointIndex old(*this);
  ++(*this);
  return old;
}

ribi::foam::PointIndex& ribi::foam::PointIndex::operator--() noexcept
{
  --m_index;
  return *this;
}

ribi::foam::PointIndex ribi::foam::PointIndex::operator--(int) noexcept
{
  PointIndex old(*this);
  --(*this);
  return old;
}

ribi::foam::PointIndex& ribi::foam::PointIndex::operator+=(const PointIndex& rhs) noexcept
{
  m_index += rhs.Get();
  assert(m_index >= 0
    && "A PointIndex must be zero or a positive value");
  return *this;
}

ribi::foam::PointIndex& ribi::foam::PointIndex::operator-=(const PointIndex& rhs) noexcept
{
  assert(rhs.Get() <= m_index);
  m_index -= rhs.Get();
  assert(m_index >= 0
    && "A PointIndex must be zero or a positive value");
  return *this;
}


std::ostream& ribi::foam::operator<<(std::ostream& os, const PointIndex& face_index) noexcept
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

const ribi::foam::PointIndex ribi::foam::operator+(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  return PointIndex(lhs.Get() + rhs.Get());
}

const ribi::foam::PointIndex ribi::foam::operator-(const PointIndex& lhs, const PointIndex& rhs) noexcept
{
  assert(lhs >= rhs);
  return PointIndex(lhs.Get() - rhs.Get());
}

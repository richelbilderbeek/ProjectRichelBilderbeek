#include "openfoamfaceindex.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "trace.h"

ribi::foam::FaceIndex::FaceIndex(const int index)
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
    && "A FaceIndex must be zero or a positive value");
  if (m_index < 0)
  {
    throw std::invalid_argument("A FaceIndex must be zero or a positive value");
  }
}

ribi::foam::FaceIndex& ribi::foam::FaceIndex::operator+=(const FaceIndex& rhs)
{
  m_index += rhs.Get();

  assert(m_index >= 0
    && "A FaceIndex must be zero or a positive value, must have overflowed");
  if (m_index < 0)
  {
    throw std::invalid_argument(
      "FaceIndex::operator+=: FaceIndex cannot be negative, must have overflowed");
  }
  return *this;
}

ribi::foam::FaceIndex& ribi::foam::FaceIndex::operator-=(const FaceIndex& rhs)
{
  m_index -= rhs.Get();

  assert(m_index >= 0
    && "A FaceIndex must be zero or a positive value");
  if (m_index < 0)
  {
    throw std::invalid_argument(
      "FaceIndex::operator-=: FaceIndex cannot be negative");
  }
  return *this;
}

ribi::foam::FaceIndex& ribi::foam::FaceIndex::operator++() noexcept
{
  ++m_index;
  assert(m_index >= 0);
  return *this;
}

ribi::foam::FaceIndex ribi::foam::FaceIndex::operator++(int) noexcept
{
  FaceIndex old(*this);
  ++(*this);
  assert(m_index >= 0);
  return old;
}

ribi::foam::FaceIndex& ribi::foam::FaceIndex::operator--() noexcept
{
  --m_index;
  assert(m_index >= 0);
  return *this;
}

ribi::foam::FaceIndex ribi::foam::FaceIndex::operator--(int) noexcept
{
  FaceIndex old(*this);
  --(*this);
  assert(m_index >= 0);
  return old;
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const FaceIndex& face_index) noexcept
{
  os << face_index.Get();
  return os;
}

std::istream& ribi::foam::operator>>(std::istream& is, FaceIndex& face_index) noexcept
{
  is >> face_index.m_index;
  assert(is);
  return is;
}

const ribi::foam::FaceIndex ribi::foam::operator+(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return FaceIndex(lhs.Get() + rhs.Get());
}

const ribi::foam::FaceIndex ribi::foam::operator-(const FaceIndex& lhs, const FaceIndex& rhs)
{
  return FaceIndex(lhs.Get() - rhs.Get());
}

bool ribi::foam::operator==(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return lhs.Get() == rhs.Get();
}

bool ribi::foam::operator!=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return !(lhs == rhs);
}

bool ribi::foam::operator<(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return lhs.Get() < rhs.Get();
}

bool ribi::foam::operator>(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return lhs.Get() > rhs.Get();
}

bool ribi::foam::operator>=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return !(lhs < rhs);
}

bool ribi::foam::operator<=(const FaceIndex& lhs, const FaceIndex& rhs) noexcept
{
  return !(lhs > rhs);
}

#ifndef EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_H

#ifdef USE_CUSTOM_RIBI_EUCLIDIAN_VECTOR

#include <cassert>
#include <utility>

namespace ribi {

//A Euclidean vector
template <class T>
struct EuclideanVector
{
  explicit EuclideanVector(const T& any_x, const T& any_y) noexcept
    : x { any_x }, y { any_y }
  {

  }
  explicit EuclideanVector(const std::pair<T,T>& p) noexcept
    : x { p.first }, y { p.second }
  {

  }
  explicit EuclideanVector(const EuclideanVector<T>& rhs) noexcept
    : x { rhs.x }, y { rhs.y }
  {

  }
  EuclideanVector& operator+=(const EuclideanVector& rhs) noexcept
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  EuclideanVector& operator*=(const double f) noexcept
  {
    x*=f;
    y*=f;
    return *this;
  }

  T x;
  T y;
};

template <class T>
bool operator==(const EuclideanVector<T>& lhs, const EuclideanVector<T>& rhs) noexcept
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <class T>
bool operator!=(const EuclideanVector<T>& lhs, const EuclideanVector<T>& rhs) noexcept
{
  return !(lhs == rhs);
}

template <class T>
const EuclideanVector<T> operator+(const EuclideanVector<T>& lhs, const EuclideanVector<T>& rhs) noexcept
{
  return EuclideanVector<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <class T, class U, class V>
const EuclideanVector<T> operator/(const EuclideanVector<U>& lhs, const V& rhs)
{
  #ifndef NDEBUG
  { const int x = int {}; assert(x == 0); }
  { const double x = double {}; assert(x == 0.0); }
  #endif
  return EuclideanVector<T>(lhs.x / rhs, lhs.y / rhs);
}

} //~namespace ribi

#endif

#endif // EUCLIDEANVECTOR_H

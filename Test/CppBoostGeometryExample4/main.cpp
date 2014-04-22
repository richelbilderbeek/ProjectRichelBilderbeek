#include <cassert>
#include <functional>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/point.hpp>
#pragma GCC diagnostic pop

typedef boost::geometry::model::point<int,3,boost::geometry::cs::cartesian> Point3D;

std::function<bool(const Point3D& lhs, const Point3D& rhs)> OrderByX() noexcept
{
  return [](const Point3D& lhs, const Point3D& rhs)
  {
    using boost::geometry::get;
    if (get<0>(lhs) < get<0>(rhs)) return true;
    if (get<0>(lhs) > get<0>(rhs)) return false;
    if (get<1>(lhs) < get<1>(rhs)) return true;
    if (get<1>(lhs) > get<1>(rhs)) return false;
    return get<2>(lhs) < get<2>(rhs);
  };
}

std::function<bool(const Point3D& lhs, const Point3D& rhs)> OrderByZ() noexcept
{
  return [](const Point3D& lhs, const Point3D& rhs)
  {
    using boost::geometry::get;
    if (get<2>(lhs) < get<2>(rhs)) return true;
    if (get<2>(lhs) > get<2>(rhs)) return false;
    if (get<1>(lhs) < get<1>(rhs)) return true;
    if (get<1>(lhs) > get<1>(rhs)) return false;
    return get<0>(lhs) < get<0>(rhs);
  };
}

std::ostream& operator<<(std::ostream& os, const Point3D& p)
{
  using boost::geometry::get;
  os << "("  << get<0>(p) << "," << get<1>(p) << "," << get<2>(p) << ")";
  return os;
}

int main()
{
  std::vector<Point3D> v {
    Point3D(0,0,0),
    Point3D(0,0,1),
    Point3D(0,1,0),
    Point3D(0,1,1),
    Point3D(1,0,0),
    Point3D(1,0,1),
    Point3D(1,1,0),
    Point3D(1,1,1)
  };
  std::random_shuffle(v.begin(),v.end());
  std::cout << "Random" << '\n';
  for (const auto p:v) { std::cout << p << '\n'; }
  std::sort(v.begin(),v.end(),OrderByX());

  std::cout << "Sorted by X-Y-Z" << '\n';
  for (const auto p:v) { std::cout << p << '\n'; }
  std::sort(v.begin(),v.end(),OrderByZ());

  std::cout << "Sorted by Z-Y-X" << '\n';
  for (const auto p:v) { std::cout << p << '\n'; }
}

/* Screen output

Random
(1,0,0)
(0,0,1)
(1,1,0)
(0,1,0)
(0,0,0)
(1,0,1)
(1,1,1)
(0,1,1)
Sorted by X-Y-Z
(0,0,0)
(0,0,1)
(0,1,0)
(0,1,1)
(1,0,0)
(1,0,1)
(1,1,0)
(1,1,1)
Sorted by Z-Y-X
(0,0,0)
(1,0,0)
(0,1,0)
(1,1,0)
(0,0,1)
(1,0,1)
(0,1,1)
(1,1,1)
Press <RETURN> to close this window...

*/

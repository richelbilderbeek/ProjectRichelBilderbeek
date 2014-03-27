#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#pragma GCC diagnostic pop

template <class T>
boost::geometry::model::linestring<boost::geometry::model::d2::point_xy<T>>
CreateLine(const std::vector<boost::geometry::model::d2::point_xy<T> >& v)
{
  return boost::geometry::model::linestring<
    boost::geometry::model::d2::point_xy<T>
  >(v.begin(),v.end());
}

template <class T>
boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>
  CreateRect(
    const T& left,
    const T& top,
    const T& right,
    const T& bottom
  )
{
  typedef boost::geometry::model::d2::point_xy<T> Point;
  boost::geometry::model::box<Point> rect(
    Point( left, top   ),
    Point(right, bottom)
  );
  return rect;
}

template <class T>
T GetHeight(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) noexcept
{
  using boost::geometry::get;
  using boost::geometry::min_corner;
  using boost::geometry::max_corner;
  const auto top   (get<min_corner,1>(r));
  const auto bottom(get<max_corner,1>(r));
  assert(top <= bottom);
  return bottom - top;
}

template <class T>
T GetWidth(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) noexcept
{
  using boost::geometry::get;
  using boost::geometry::min_corner;
  using boost::geometry::max_corner;
  const auto left (get<min_corner,0>(r));
  const auto right(get<max_corner,0>(r));
  assert(left <= right);
  return right - left;
}

template <class T>
auto GetArea(const boost::geometry::model::box<boost::geometry::model::d2::point_xy<T>>& r) noexcept
  -> decltype(T{} * T{})
{
  return boost::geometry::area(r);
}


int main()
{
  {
    typedef boost::geometry::model::d2::point_xy<int> Coordinat2D;
    typedef boost::geometry::model::box<Coordinat2D> Rect;
    const Rect r(CreateRect(10,10,14,15));
    assert(GetWidth(r) == 4);
    assert(GetHeight(r) == 5);
    assert(GetArea(r) == 20);
  }
  {
    using boost::units::si::meter;
    typedef boost::units::quantity<boost::units::si::length> Length;
    typedef boost::geometry::model::d2::point_xy<Length> Coordinat2D;
    typedef boost::geometry::model::box<Coordinat2D> Rect;
    const Rect r(
      CreateRect(
        10.0 * meter,
        10.0 * meter,
        14.0 * meter,
        15.0 * meter
      )
    );
    assert(GetWidth(r) == 4.0 * meter);
    assert(GetHeight(r) == 5.0 * meter);
    assert(GetArea(r) == 20.0 * meter * meter);
  }
  assert(1==2);
}

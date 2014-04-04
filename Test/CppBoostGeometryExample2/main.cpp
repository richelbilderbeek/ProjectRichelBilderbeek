#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/ring.hpp>
//#include <boost/geometry/geometries/adapted/std_as_ring.hpp> //Is absent in 1.54.0
#pragma GCC diagnostic pop

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  /* Polygon used:

    3-
     |
    2-    0 #
     |   / \
    1-  4   1
     |  | * |
    0-  3---2
     |
     +--|---|---|
        0   1   2

  *: point that is tested to be within the polygon
  #: point that is tested to be outside of the polygon

  */

  const std::vector<Coordinat2D> points {
    {0.5, 2.0}, //0
    {1.0, 1.0}, //1
    {1.0, 0.0}, //2
    {0.0, 0.0}, //3
    {0.0, 1.0}  //4
  };

  boost::geometry::model::polygon<Coordinat2D> house;
  boost::geometry::append(house, points);

  boost::geometry::model::ring<Coordinat2D> points_again;
  boost::geometry::convert(house,points_again);

  //Instead of using this syntax:
  //  assert(points == points_again);
  //operator== needs to be defined, which is done by a lambda function
  assert(
    std::equal(
      points.begin(),points.end(),
      points_again.begin(),
      [](const Coordinat2D& a,const Coordinat2D& b)
      {
        return boost::geometry::equals(a,b);
      }
    )
  );


  assert( boost::geometry::within(Coordinat2D(0.5, 0.5), house));
  assert(!boost::geometry::within(Coordinat2D(1.0, 2.0), house));

  const double area = boost::geometry::area(house);
  std::cout << "Area: " << area << std::endl;
}

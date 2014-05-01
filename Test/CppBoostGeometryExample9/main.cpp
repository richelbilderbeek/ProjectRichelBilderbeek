#include <cassert>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/ring.hpp>
#pragma GCC diagnostic pop

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  Translate(
    const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>& shape,
    const double dx,
    const double dy
  ) noexcept
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  boost::geometry::model::ring<Coordinat2D> points;
  boost::geometry::convert(shape,points);

  for (auto& point:points)
  {
    point = Coordinat2D(point.x() + dx, point.y() + dy);
  }

  Polygon new_shape;
  boost::geometry::append(new_shape, points);
  return new_shape;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  Rescale(
    const boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>& shape,
    const double scale,
    const double scale_origin_x = 0.0,
    const double scale_origin_y = 0.0
  ) noexcept
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  boost::geometry::model::ring<Coordinat2D> points;
  boost::geometry::convert(shape,points);

  for (auto& point:points)
  {
    const double x = point.x();
    const double dx = x - scale_origin_x;
    const double new_x = scale_origin_x + (scale * dx);

    const double y = point.y();
    const double dy = y - scale_origin_y;
    const double new_y = scale_origin_y + (scale * dy);

    point = Coordinat2D(new_x,new_y);
  }

  Polygon new_shape;
  boost::geometry::append(new_shape, points);
  return new_shape;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>
  CreateHouseShape() noexcept
{
  /*

    3-
     |
    2-    0
     |   / \
    1-  4   1
     |  |   |
    0-  3---2
     |
     +--|---|---|
        0   1   2

  */
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  const std::vector<Coordinat2D> points {
    {0.5, 2.0}, //0
    {1.0, 1.0}, //1
    {1.0, 0.0}, //2
    {0.0, 0.0}, //3
    {0.0, 1.0}  //4
  };

  boost::geometry::model::polygon<Coordinat2D> house;
  boost::geometry::append(house, points);
  return house;
}

int main()
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  {
    //Translate (0.5,1.0) to origin
    const auto house = CreateHouseShape();
    const auto translated_house = Translate(house,-0.5,-1.0);
    boost::geometry::model::ring<Coordinat2D> translated_points;
    boost::geometry::convert(translated_house,translated_points);
    const std::vector<Coordinat2D> translated_points_expected {
      { 0.0, 1.0}, //0
      { 0.5, 0.0}, //1
      { 0.5,-1.0}, //2
      {-0.5,-1.0}, //3
      {-0.5, 0.0}  //4
    };
    assert(
      std::equal(
        translated_points.begin(),translated_points.end(),
        translated_points_expected.begin(),
        [](const Coordinat2D& a,const Coordinat2D& b)
        {
          return boost::geometry::equals(a,b);
        }
      )
      && "Points must be translated as expected"
    );
  }

  {
    //Scale twice up, from origin
    const auto house = CreateHouseShape();
    const auto rescaled_house = Rescale(house,2.0);
    boost::geometry::model::ring<Coordinat2D> rescaled_points;
    boost::geometry::convert(rescaled_house,rescaled_points);
    const std::vector<Coordinat2D> rescaled_points_expected {
      {1.0, 4.0}, //0
      {2.0, 2.0}, //1
      {2.0, 0.0}, //2
      {0.0, 0.0}, //3
      {0.0, 2.0}  //4
    };
    assert(
      std::equal(
        rescaled_points.begin(),rescaled_points.end(),
        rescaled_points_expected.begin(),
        [](const Coordinat2D& a,const Coordinat2D& b)
        {
          //std::cout << "(" << a.x() << "," << a.y() << ")-("
          //  << b.x() << "," << b.y() << ")" << std::endl;
          return boost::geometry::equals(a,b);
        }
      )
      && "Points must be rescaled as expected"
    );
  }

  {
    //Scale up, from center at (0.5,1.0)
    /*

      3-
       |
      2-    0
       |   / \
      1-  4 * 1
       |  |   |
      0-  3---2
       |
       +--|---|---|
          0   1   2

    */
    const auto house = CreateHouseShape();
    const auto rescaled_house = Rescale(house,2.0,0.5,1.0);
    boost::geometry::model::ring<Coordinat2D> rescaled_points;
    boost::geometry::convert(rescaled_house,rescaled_points);
    const std::vector<Coordinat2D> rescaled_points_expected {
      { 0.5, 3.0}, //0
      { 1.5, 1.0}, //1
      { 1.5,-1.0}, //2
      {-0.5,-1.0}, //3
      {-0.5, 1.0}  //4
    };
    assert(
      std::equal(
        rescaled_points.begin(),rescaled_points.end(),
        rescaled_points_expected.begin(),
        [](const Coordinat2D& a,const Coordinat2D& b)
        {
          //std::cout << "(" << a.x() << "," << a.y() << ")-("
          //  << b.x() << "," << b.y() << ")" << std::endl;
          return boost::geometry::equals(a,b);
        }
      )
      && "Points must be rescaled as expected"
    );
  }
}

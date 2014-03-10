#ifndef PLANEZ_H
#define PLANEZ_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#pragma GCC diagnostic pop

namespace ribi {

///A 3D plane that can have its Z expressed as a function of X and Y.
///Can be constructed from its equation and at least three 3D points
//A plane stores its coefficients in the following form:
// A.x + B.y + C.z = D
//Converting this to z being a function of x and y:
// -C.z =  A  .x + B  .y - D
//    z = -A/C.x - B/C.y + D/C
struct PlaneZ
{
  ///Construct from its coefficients
  explicit PlaneZ(const std::vector<double>& coefficients = {0.0,0.0,0.0,0.0});

  ///Construct from three points
  explicit PlaneZ(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
  ) noexcept : PlaneZ(CalcPlaneZ(p1,p2,p3))
  {
    #ifndef NDEBUG
    Test();
    #endif
  }


  ///Construct from four points
  ///Assumes these are in the same plane
  explicit PlaneZ(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p4
  ) noexcept : PlaneZ(CalcPlaneZ(p1,p2,p3,p4))
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  ///Get the 2D projection of these 3D points,
  ///Assumes these are in a plane
  /*

  A: (0,0,1)                  A: (0,0)
  B: (1,0,0)                  B: (SQRT(2),0)
  C: (1,1,0)                  C: (SQRT(2),SQRT(2))

  |    /
  |   /                       |
  A-----C                     |  C
  |\/  /      -> becomes ->   | /|
  |/\ /                       |/ |
  +--B---                     A--B-----

  */
  static std::vector<boost::geometry::model::d2::point_xy<double>> CalcProjection(
    const std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>& points
  );

  ///Throws when cannot calculate Z, which is when the plane is vertical
  double CalcZ(const double x, const double y) const;

  const std::vector<double>& GetCoefficients() const noexcept { return m_coefficients; }

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Convert the NonVerticalPlane to a z(x,y), e.g 'z=(2*x) + (3*y) + 5' (spaces exactly as shown)
  std::string ToFunction() const;

  private:
  //m_coefficients.size == 4
  const std::vector<double> m_coefficients;

  static std::vector<double> CalcPlaneZ(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3
  ) noexcept;

  static std::vector<double> CalcPlaneZ(
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p1,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p2,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p3,
    const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p4
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // PLANEZ_H

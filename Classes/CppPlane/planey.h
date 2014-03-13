#ifndef PLANEY_H
#define PLANEY_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "planez.h"
#pragma GCC diagnostic pop

namespace ribi {

///A 3D plane that can have its X expressed as a function of Y and Z.
///Can be constructed from its equation and at least three 3D points
//A plane stores its coefficients in the following form:
// A.z + B.x + C.y = D
//Converting this to x being a function of y and z:
// -B.x =  A  .z + C  .y - D
//    x = -A/B.z - C/B.y + D/B
struct PlaneY
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  ///Create plane Y = 0.0
  PlaneY() : PlaneY(Coordinat3D(0.0,0.0,0.0),Coordinat3D(1.0,0.0,0.0),Coordinat3D(0.0,0.0,1.0))
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  ///Construct from three points
  explicit PlaneY(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept : m_plane_z{Create(p1,p2,p3)}
  {
    #ifndef NDEBUG
    Test();
    #endif
  }

  ///Get the 2D projection of these 3D points,
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
  std::vector<boost::geometry::model::d2::point_xy<double>> CalcProjection(
    const std::vector<Coordinat3D>& points
  ) const;

  ///Throws when cannot calculate Y, which is when the plane is horizontal
  double CalcY(const double y, const double z) const;

  const std::vector<double> GetCoefficients() const noexcept;

  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  ///Convert the PlaneY to a x(y,z), e.g 'x=(2*y) + (3*z) + 5' (spaces exactly as shown)
  std::string ToFunction() const;

  private:
  ///A PlaneY is actually a PlaneZ used with its coordinats rotated from (X,Y,Z) to (Z,Y,Y)
  const PlaneZ m_plane_z;

  static PlaneZ Create(
    const Coordinat3D& p1,
    const Coordinat3D& p2,
    const Coordinat3D& p3
  ) noexcept;

  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static std::vector<std::string> GetRegexMatchesBoostXpressive(
    const std::string& s,
    const std::string& r_str
  );


  static std::vector<double> Rotate(const std::vector<double>& coefficients) noexcept;
  static Coordinat3D Rotate(
    const Coordinat3D& point
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // PLANEY_H

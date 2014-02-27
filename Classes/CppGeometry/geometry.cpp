#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "geometry.h"

#include <cassert>
#include <cmath>

#include <boost/math/constants/constants.hpp>

#include "coordinat3d.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Geometry::Geometry()
{
  #ifndef NDEBUG
  Test();
  #endif
}

double ribi::Geometry::Fmod(const double x, const double mod) const noexcept
{
  assert(mod != 0.0 && "Cannot do a modulus of zero");
  assert(mod >= 0.0 && "Cannot do a modulus by a negative value");
  if (x < 0.0)
  {
    const double new_x {
      x + (mod * (1 + static_cast<int>(-x / mod)))
    };
    assert(new_x >= 0.0);
    return Fmod(new_x,mod);
  }
  double result = x - (mod * static_cast<int>(x / mod));

  assert(result >= 0.0 && "Fmod must return a value between zero and mod");
  assert(result < mod  && "Fmod must return a value between zero and mod");
  return result;
}

double ribi::Geometry::GetAngle(const double dx, const double dy) const noexcept
{
  const double pi { boost::math::constants::pi<double>() };
  const double tau { boost::math::constants::two_pi<double>() };
  const double angle { Fmod(pi - (std::atan2(dx,dy)),tau) };
  assert(angle >= 0.0 && "GetAngle must return a value between zero and two pi");
  assert(angle < tau  && "GetAngle must return a value between zero and two pi");
  return angle;
}

double ribi::Geometry::GetDistance(const double dx, const double dy) const noexcept
{
  return std::sqrt( (dx * dx) + (dy * dy) );
}

const std::string ribi::Geometry::GetVersion() const noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::Geometry::GetVersionHistory() const noexcept
{
  return {
    "2014-02-25: version 1.0: initial version"
  };
}

bool ribi::Geometry::IsClockwise(const double a, const double b) const noexcept
{
  const double pi  = boost::math::constants::pi<double>();
  const double tau = boost::math::constants::two_pi<double>();
  const double c { Fmod(a,tau) };
  const double d { Fmod(b,tau) };
  assert(c >= 0);
  assert(c < tau);
  assert(d >= 0);
  assert(d < tau);
  if (d - c >= 0.0 && d - c < pi) return true;
  if (d + tau - c >= 0.0 && d + tau - c < pi) return true;
  return false;
}

bool ribi::Geometry::IsClockwise(const std::vector<double>& angles) const noexcept
{
  const int sz = static_cast<int>(angles.size());
  assert(sz >= 2 && "Need at least two angles to determine if these are clockwise");
  for (int i=0; i!=sz-1; ++i)
  {
    if (!IsClockwise(angles[i],angles[i+1])) return false;
  }
  return true;
}

bool ribi::Geometry::IsClockwise(const std::vector<Coordinat3D>& points, const Coordinat3D& observer) const noexcept
{
  //assert(!"TODO");
  //const Coordinat3D center { CalcCenter(points) };
  //const Coordinat3D center { observer }; //? Correct or not?
  const int n_points { static_cast<int>(points.size()) };
  for (int i=0; i!=n_points-2; ++i)
  {
    const Coordinat3D a { points[i  ] };
    const Coordinat3D b { points[i+1] };
    const Coordinat3D c { points[i+2] };
    const Coordinat3D normal { CalcNormal(a,b,c) };
    const double direction {
      CalcDotProduct(normal,a - observer)
    };
    if (direction > 0.0) return false;
  }
  return true;
}

bool ribi::Geometry::IsClockwiseHorizontal(const std::vector<Coordinat3D>& points) const noexcept
{
  //Points are determined from their center
  const Coordinat3D center {
    CalcCenter(points)
  };
  std::vector<double> angles;
  angles.reserve(points.size());
  std::transform(points.begin(),points.end(),
    std::back_inserter(angles),
    [this,center](const Coordinat3D& coordinat)
    {
      return GetAngle(
        coordinat.GetX() - center.GetX(),
        coordinat.GetY() - center.GetY()
      );
    }
  );
  return IsClockwise(angles);
}

#ifndef NDEBUG
void ribi::Geometry::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Geometry::Test");
  const double pi = boost::math::constants::pi<double>();
  const Geometry g;
  //Fmod
  {
    const double expected_min = 1.0 - 0.00001;
    const double expected_max = 1.0 + 0.00001;
    assert(g.Fmod(3.0,2.0) > expected_min && g.Fmod(3.0,2.0) < expected_max);
    assert(g.Fmod(13.0,2.0) > expected_min && g.Fmod(13.0,2.0) < expected_max);
    assert(g.Fmod(-1.0,2.0) > expected_min && g.Fmod(-1.0,2.0) < expected_max);
    assert(g.Fmod(-3.0,2.0) > expected_min && g.Fmod(-3.0,2.0) < expected_max);
    assert(g.Fmod(-13.0,2.0) > expected_min && g.Fmod(-13.0,2.0) < expected_max);
  }
  //GetAngle
  {
    const double angle =  g.GetAngle(0.0,-1.0); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,-1.0); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,0.0); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(1.0,1.0); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(0.0,1.0); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,1.0); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,0.0); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngle(-1.0,-1.0); //North-West
    const double expected = 1.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  //GetDistance
  {
    const double distance = g.GetDistance(3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(-3.0,4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  {
    const double distance = g.GetDistance(-3.0,-4.0);
    const double expected = 5.0;
    assert(std::abs(distance-expected) < 0.01);
  }
  //IsClockWise of two angles, doubles
  {
    assert( g.IsClockwise(-2.5 * pi,-2.0 * pi));
    assert(!g.IsClockwise(-2.0 * pi,-2.5 * pi));
    assert( g.IsClockwise(-1.5 * pi,-1.0 * pi));
    assert(!g.IsClockwise(-1.0 * pi,-1.5 * pi));
    assert( g.IsClockwise(-0.5 * pi, 0.0 * pi));
    assert(!g.IsClockwise( 0.0 * pi,-0.5 * pi));
    assert( g.IsClockwise( 0.0 * pi, 0.5 * pi));
    assert(!g.IsClockwise( 0.5 * pi, 0.0 * pi));
    assert( g.IsClockwise( 0.5 * pi, 1.0 * pi));
    assert(!g.IsClockwise( 1.0 * pi, 0.5 * pi));
    assert( g.IsClockwise( 1.5 * pi, 2.0 * pi));
    assert(!g.IsClockwise( 2.0 * pi, 1.5 * pi));
    assert( g.IsClockwise( 2.5 * pi, 3.0 * pi));
    assert(!g.IsClockwise( 3.0 * pi, 2.5 * pi));
  }
  //IsClockWise of two, vector
  {
    assert( g.IsClockwise( {-2.5 * pi,-2.0 * pi } ));
    assert(!g.IsClockwise( {-2.0 * pi,-2.5 * pi } ));
    assert( g.IsClockwise( {-1.5 * pi,-1.0 * pi } ));
    assert(!g.IsClockwise( {-1.0 * pi,-1.5 * pi } ));
    assert( g.IsClockwise( {-0.5 * pi, 0.0 * pi } ));
    assert(!g.IsClockwise( { 0.0 * pi,-0.5 * pi } ));
    assert( g.IsClockwise( { 0.0 * pi, 0.5 * pi } ));
    assert(!g.IsClockwise( { 0.5 * pi, 0.0 * pi } ));
    assert( g.IsClockwise( { 0.5 * pi, 1.0 * pi } ));
    assert(!g.IsClockwise( { 1.0 * pi, 0.5 * pi } ));
    assert( g.IsClockwise( { 1.5 * pi, 2.0 * pi } ));
    assert(!g.IsClockwise( { 2.0 * pi, 1.5 * pi } ));
    assert( g.IsClockwise( { 2.5 * pi, 3.0 * pi } ));
    assert(!g.IsClockwise( { 3.0 * pi, 2.5 * pi } ));
  }
  //IsClockWise of three, vector
  {
    assert( g.IsClockwise( {-2.5 * pi,-2.0 * pi,-1.75 * pi} ));
    assert(!g.IsClockwise( {-2.0 * pi,-2.5 * pi,-1.75 * pi} ));
    assert( g.IsClockwise( {-1.5 * pi,-1.0 * pi,-0.75 * pi} ));
    assert(!g.IsClockwise( {-1.0 * pi,-1.5 * pi,-0.75 * pi} ));
    assert( g.IsClockwise( {-0.5 * pi, 0.0 * pi, 0.25 * pi } ));
    assert(!g.IsClockwise( { 0.0 * pi,-0.5 * pi, 0.25 * pi } ));
    assert( g.IsClockwise( { 0.0 * pi, 0.5 * pi, 0.75 * pi } ));
    assert(!g.IsClockwise( { 0.5 * pi, 0.0 * pi, 0.75 * pi } ));
    assert( g.IsClockwise( { 0.5 * pi, 1.0 * pi, 1.25 * pi } ));
    assert(!g.IsClockwise( { 1.0 * pi, 0.5 * pi, 1.25 * pi } ));
    assert( g.IsClockwise( { 1.5 * pi, 2.0 * pi, 2.25 * pi } ));
    assert(!g.IsClockwise( { 2.0 * pi, 1.5 * pi, 2.25 * pi } ));
    assert( g.IsClockwise( { 2.5 * pi, 3.0 * pi, 3.25 * pi } ));
    assert(!g.IsClockwise( { 3.0 * pi, 2.5 * pi, 3.25 * pi } ));
  }
  //IsClockwise in three dimensions, points in XY plane
  {
    /*

       0 1 2 3
     0 +------X
       |
     1 | A       (seen from above, Z = 1)
       | |\
     2 | C-B
       |
     3 |
       Y

    */
    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(2.0, 2.0, 1.0);
    const Coordinat3D c(1.0, 2.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert( g.IsClockwise(coordinats,above));
        assert(!g.IsClockwise(coordinats,below));
      }
    }
  }
  //IsClockwise in three dimensions, points in XY plane
  {
    /*
       0 1 2 3
     0 +------X
       |
     1 | A       (seen from above, Z = 1)
       | |\
     2 | B-C
       |
     3 |
       Y

    */
    const Coordinat3D a(1.0, 1.0, 1.0);
    const Coordinat3D b(1.0, 2.0, 1.0);
    const Coordinat3D c(2.0, 2.0, 1.0);
    const std::vector<Coordinat3D> coordinats { a,b,c };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const Coordinat3D above(x, y, 2.0);
        const Coordinat3D below(x, y,-1.0);
        assert(!g.IsClockwise(coordinats,above));
        assert( g.IsClockwise(coordinats,below));
      }
    }
  }
  TRACE("Finished ribi::Geometry::Test successfully");
}
#endif

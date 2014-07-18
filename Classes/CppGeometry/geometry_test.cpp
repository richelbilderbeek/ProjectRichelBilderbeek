#include "geometry.h"

#include <cassert>

#include "apcplx.h" //apfloat's atan2
#include "trace.h"

#ifndef NDEBUG
void ribi::Geometry::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Geometry::Test");
  const bool verbose{false};
  const double pi = boost::math::constants::pi<double>();
  const Geometry g;
  if (verbose) { TRACE("CalcPlane"); }
  {
    //using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const double p1_x =  1.0;
    const double p1_y =  2.0;
    const double p1_z =  3.0;
    const double p2_x =  4.0;
    const double p2_y =  6.0;
    const double p2_z =  9.0;
    const double p3_x = 12.0;
    const double p3_y = 11.0;
    const double p3_z =  9.0;
    const Coordinat3D p1(p1_x,p1_y,p1_z);
    const Coordinat3D p2(p2_x,p2_y,p2_z);
    const Coordinat3D p3(p3_x,p3_y,p3_z);
    const auto t(g.CalcPlane(p1,p2,p3));
    const double a = t[0];
    const double b = t[1];
    const double c = t[2];
    const double d = t[3];
    const double d_p1_expected = (a * p1_x) + (b * p1_y) + (c * p1_z);
    const double d_p2_expected = (a * p2_x) + (b * p2_y) + (c * p2_z);
    const double d_p3_expected = (a * p3_x) + (b * p3_y) + (c * p3_z);
    const bool verbose{false};
    if (verbose)
    {
      std::clog
        << "(a * x) + (b * y) + (c * z) = d" << '\n'
        << "(" << a << " * x) + (" << b << " * y) + (" << c << " * z) = " << d << '\n'
        << "(" << a << " * " << p1_x << ") + (" << b << " * " << p1_y << ") + (" << c << " * " << p1_z << ") = " << d << '\n'
        << "(" << (a * p1_x) << ") + (" << (b * p1_y) << ") + (" << (c * p1_z) << ") = " << d << '\n'
        << "(" << a << " * " << p2_x << ") + (" << b << " * " << p2_y << ") + (" << c << " * " << p2_z << ") = " << d << '\n'
        << "(" << (a * p2_x) << ") + (" << (b * p2_y) << ") + (" << (c * p2_z) << ") = " << d << '\n'
        << "(" << a << " * " << p3_x << ") + (" << b << " * " << p3_y << ") + (" << c << " * " << p3_z << ") = " << d << '\n'
        << "(" << (a * p3_x) << ") + (" << (b * p3_y) << ") + (" << (c * p3_z) << ") = " << d << '\n'
      ;
      /* Screen output

      (a * x) + (b * y) + (c * z) = d
      (30 * x) + (-48 * y) + (17 * z) = -15
      (30 * 1) + (-48 * 2) + (17 * 3) = -15
      (30) + (-96) + (51) = -15
      (30 * 4) + (-48 * 6) + (17 * 9) = -15
      (120) + (-288) + (153) = -15
      (30 * 12) + (-48 * 11) + (17 * 9) = -15
      (360) + (-528) + (153) = -15

      */
    }
    assert(std::abs(d - d_p1_expected) < 0.001);
    assert(std::abs(d - d_p2_expected) < 0.001);
    assert(std::abs(d - d_p3_expected) < 0.001);
  }
  if (verbose) { TRACE("CalcPlane"); }
  {
    //CalcPlane return the coefficients in the following form:
    // A.x + B.y + C.z = D
    //Converting this to z being a function of x and y:
    // -C.z = A.x + B.y - D
    // z = -A/C.x - B/C.y + D/C
    //In this test, use the formula:
    //  z = (2.0 * x) + (3.0 * y) + (5.0)
    //Coefficients must then become:
    //  -A/C = 2.0
    //  -B/C = 3.0
    //   D/C = 5.0
    //Coefficients are, when setting C to 1.0:
    //  -A = 2.0 => A = -2.0
    //  -B = 3.0 => B = -3.0
    //   C = 1.0
    //   D = 5.0
    using boost::geometry::model::point;
    using boost::geometry::cs::cartesian;
    const Coordinat3D p1(1.0,1.0,10.0);
    const Coordinat3D p2(1.0,2.0,13.0);
    const Coordinat3D p3(2.0,1.0,12.0);
    const auto t(g.CalcPlane(p1,p2,p3));
    const double a = t[0];
    const double b = t[1];
    const double c = t[2];
    const double d = t[3];
    const double a_expected = -2.0;
    const double b_expected = -3.0;
    const double c_expected =  1.0;
    const double d_expected =  5.0;
    assert(std::abs(a - a_expected) < 0.001);
    assert(std::abs(b - b_expected) < 0.001);
    assert(std::abs(c - c_expected) < 0.001);
    assert(std::abs(d - d_expected) < 0.001);
    const double d_p1_expected = (a * 1.0) + (b * 1.0) + (c * 10.0);
    const double d_p2_expected = (a * 1.0) + (b * 2.0) + (c * 13.0);
    const double d_p3_expected = (a * 2.0) + (b * 1.0) + (c * 12.0);
    assert(std::abs(d - d_p1_expected) < 0.001);
    assert(std::abs(d - d_p2_expected) < 0.001);
    assert(std::abs(d - d_p3_expected) < 0.001);

  }
  if (verbose) { TRACE("Fmod"); }
  {
    const double expected_min = 1.0 - 0.00001;
    const double expected_max = 1.0 + 0.00001;
    assert(g.Fmod(3.0,2.0) > expected_min && g.Fmod(3.0,2.0) < expected_max);
    assert(g.Fmod(13.0,2.0) > expected_min && g.Fmod(13.0,2.0) < expected_max);
    assert(g.Fmod(-1.0,2.0) > expected_min && g.Fmod(-1.0,2.0) < expected_max);
    assert(g.Fmod(-3.0,2.0) > expected_min && g.Fmod(-3.0,2.0) < expected_max);
    assert(g.Fmod(-13.0,2.0) > expected_min && g.Fmod(-13.0,2.0) < expected_max);
  }
  //std::atan2 versus apfloat's atan2
  {
    for (double dx = -1.0; dx < 1.01; dx += 1.0)
    {
      for (double dy = -1.0; dy < 1.01; dy += 1.0)
      {
        if (dx == 0.0 && dy == 0.0) continue;
        const auto a = std::atan2(dx,dy);
        const auto b = atan2(Apfloat(dx),Apfloat(dy));
        const auto c = g.Atan2(Apfloat(dx),Apfloat(dy));
        //std::stringstream s;
        //s << dx << '\t' << dy << '\t' << (a/pi) << " pi\t" << (b/pi) << " pi\t" << g.ToStrSafe(c/Apfloat(pi)) << " pi\n";
        //TRACE(s.str());
        const auto error = abs(a - c);
        if (error >= 0.01)
        {
          TRACE("ERROR");
          TRACE(dx);
          TRACE(dy);
          TRACE(Geometry().ToStrSafe(a));
          TRACE(b);
          TRACE(Geometry().ToStrSafe(error));
          TRACE("BREAK");
        }
        assert(error < 0.01); //abfloat does not use namespace std::
      }
    }
  }

  if (verbose) { TRACE("GetAngleClockCartesian, double"); }
  {
    const double angle =  g.GetAngleClockCartesian(0.0, 1.0); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(1.0, 1.0); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(1.0,0.0); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(1.0,-1.0); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(0.0,-1.0); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(-1.0,-1.0); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(-1.0,0.0); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockCartesian(-1.0,1.0); //North-West
    const double expected = 1.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  if (verbose) { TRACE("GetAngleClockCartesian, Apfloat"); }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(0.0),Apfloat(1.0)); //North
    const auto expected = 0.0 * pi;
    const auto error = abs(angle-expected); //abfloat does not use namespace std::
    if (error >= 0.01)
    {
      TRACE("ERROR");
      TRACE(Geometry().ToStrSafe(angle));
      TRACE(Geometry().ToStrSafe(expected));
      TRACE(Geometry().ToStrSafe(error));
      TRACE("BREAK");
    }
    assert(error < 0.01);
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(1.0),Apfloat(1.0)); //North-East
    const auto expected = 0.25 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(1.0),Apfloat(0.0)); //East
    const auto expected = 0.5 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(1.0),Apfloat(-1.0)); //South-East
    const auto expected = 0.75 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(0.0),Apfloat(-1.0)); //South
    const auto expected = 1.0 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(-1.0),Apfloat(-1.0)); //South-West
    const auto expected = 1.25 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(-1.0),Apfloat(0.0)); //West
    const auto expected = 1.5 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockCartesian(Apfloat(-1.0),Apfloat(1.0)); //North-West
    const auto expected = 1.75 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }

  if (verbose) { TRACE("GetAngleClockScreen, double"); }
  {
    const double angle =  g.GetAngleClockScreen(0.0,-1.0); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(1.0,-1.0); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(1.0,0.0); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(1.0,1.0); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(0.0,1.0); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(-1.0,1.0); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(-1.0,0.0); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const double angle =  g.GetAngleClockScreen(-1.0,-1.0); //North-West
    const double expected = 1.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  if (verbose) { TRACE("GetAngleClockScreen, Apfloat"); }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(0.0),Apfloat(-1.0)); //North
    const auto expected = 0.0 * pi;
    const auto error = abs(angle-expected); //abfloat does not use namespace std::
    if (error >= 0.01)
    {
      TRACE("ERROR");
      TRACE(Geometry().ToStrSafe(angle));
      TRACE(Geometry().ToStrSafe(expected));
      TRACE(Geometry().ToStrSafe(error));
      TRACE("BREAK");
    }
    assert(error < 0.01);
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(1.0),Apfloat(-1.0)); //North-East
    const auto expected = 0.25 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(1.0),Apfloat(0.0)); //East
    const auto expected = 0.5 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(1.0),Apfloat(1.0)); //South-East
    const auto expected = 0.75 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(0.0),Apfloat(1.0)); //South
    const auto expected = 1.0 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(-1.0),Apfloat(1.0)); //South-West
    const auto expected = 1.25 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(-1.0),Apfloat(0.0)); //West
    const auto expected = 1.5 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }
  {
    const auto angle =  g.GetAngleClockScreen(Apfloat(-1.0),Apfloat(-1.0)); //North-West
    const auto expected = 1.75 * pi;
    assert(abs(angle-expected) < 0.01); //abfloat does not use namespace std::
  }



  if (verbose) { TRACE("GetDistance"); }
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
  if (verbose) TRACE("double -> apfloat -> double conversion");
  {
    for (const double x:
      {
        1.0,
        0.0,
        boost::math::constants::pi<double>(),
        boost::numeric::bounds<double>::smallest(),
        boost::numeric::bounds<double>::lowest(),
        boost::numeric::bounds<double>::highest()
      }
    )
    {
      const apfloat y = x;
      const double z = g.ToDouble(y);
      assert(x == z);
    }
  }
  if (verbose) TRACE("IsClockWise of two angles, doubles");
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
  if (verbose) TRACE("IsCounterClockWise of two angles, doubles");
  {
    assert(!g.IsCounterClockwise(-2.5 * pi,-2.0 * pi));
    assert( g.IsCounterClockwise(-2.0 * pi,-2.5 * pi));
    assert(!g.IsCounterClockwise(-1.5 * pi,-1.0 * pi));
    assert( g.IsCounterClockwise(-1.0 * pi,-1.5 * pi));
    assert(!g.IsCounterClockwise(-0.5 * pi, 0.0 * pi));
    assert( g.IsCounterClockwise( 0.0 * pi,-0.5 * pi));
    assert(!g.IsCounterClockwise( 0.0 * pi, 0.5 * pi));
    assert( g.IsCounterClockwise( 0.5 * pi, 0.0 * pi));
    assert(!g.IsCounterClockwise( 0.5 * pi, 1.0 * pi));
    assert( g.IsCounterClockwise( 1.0 * pi, 0.5 * pi));
    assert(!g.IsCounterClockwise( 1.5 * pi, 2.0 * pi));
    assert( g.IsCounterClockwise( 2.0 * pi, 1.5 * pi));
    assert(!g.IsCounterClockwise( 2.5 * pi, 3.0 * pi));
    assert( g.IsCounterClockwise( 3.0 * pi, 2.5 * pi));
  }
  if (verbose) TRACE("IsClockWise of two, vector");
  {
    assert( g.IsClockwise(Doubles( {-2.5 * pi,-2.0 * pi } )));
    assert(!g.IsClockwise(Doubles( {-2.0 * pi,-2.5 * pi } )));
    assert( g.IsClockwise(Doubles( {-1.5 * pi,-1.0 * pi } )));
    assert(!g.IsClockwise(Doubles( {-1.0 * pi,-1.5 * pi } )));
    assert( g.IsClockwise(Doubles( {-0.5 * pi, 0.0 * pi } )));
    assert(!g.IsClockwise(Doubles( { 0.0 * pi,-0.5 * pi } )));
    assert( g.IsClockwise(Doubles( { 0.0 * pi, 0.5 * pi } )));
    assert(!g.IsClockwise(Doubles( { 0.5 * pi, 0.0 * pi } )));
    assert( g.IsClockwise(Doubles( { 0.5 * pi, 1.0 * pi } )));
    assert(!g.IsClockwise(Doubles( { 1.0 * pi, 0.5 * pi } )));
    assert( g.IsClockwise(Doubles( { 1.5 * pi, 2.0 * pi } )));
    assert(!g.IsClockwise(Doubles( { 2.0 * pi, 1.5 * pi } )));
    assert( g.IsClockwise(Doubles( { 2.5 * pi, 3.0 * pi } )));
    assert(!g.IsClockwise(Doubles( { 3.0 * pi, 2.5 * pi } )));
  }
  if (verbose) TRACE("IsCounterClockWise of two, vector");
  {
    assert(!g.IsCounterClockwise(Doubles( {-2.5 * pi,-2.0 * pi } )));
    assert( g.IsCounterClockwise(Doubles( {-2.0 * pi,-2.5 * pi } )));
    assert(!g.IsCounterClockwise(Doubles( {-1.5 * pi,-1.0 * pi } )));
    assert( g.IsCounterClockwise(Doubles( {-1.0 * pi,-1.5 * pi } )));
    assert(!g.IsCounterClockwise(Doubles( {-0.5 * pi, 0.0 * pi } )));
    assert( g.IsCounterClockwise(Doubles( { 0.0 * pi,-0.5 * pi } )));
    assert(!g.IsCounterClockwise(Doubles( { 0.0 * pi, 0.5 * pi } )));
    assert( g.IsCounterClockwise(Doubles( { 0.5 * pi, 0.0 * pi } )));
    assert(!g.IsCounterClockwise(Doubles( { 0.5 * pi, 1.0 * pi } )));
    assert( g.IsCounterClockwise(Doubles( { 1.0 * pi, 0.5 * pi } )));
    assert(!g.IsCounterClockwise(Doubles( { 1.5 * pi, 2.0 * pi } )));
    assert( g.IsCounterClockwise(Doubles( { 2.0 * pi, 1.5 * pi } )));
    assert(!g.IsCounterClockwise(Doubles( { 2.5 * pi, 3.0 * pi } )));
    assert( g.IsCounterClockwise(Doubles( { 3.0 * pi, 2.5 * pi } )));
  }
  if (verbose) TRACE("IsClockWise of three, vector");
  {
    assert( g.IsClockwise(Doubles( {-2.5 * pi,-2.0 * pi,-1.8 * pi} ))); //CW
    assert(!g.IsClockwise(Doubles( {-1.8 * pi,-2.0 * pi,-2.5 * pi} ))); //CCW
    assert(!g.IsClockwise(Doubles( {-2.0 * pi,-2.5 * pi,-1.8 * pi} ))); //Mess

    assert( g.IsClockwise(Doubles( {-1.5 * pi,-1.0 * pi,-0.8 * pi} ))); //CW
    assert(!g.IsClockwise(Doubles( {-0.8 * pi,-1.0 * pi,-1.5 * pi} ))); //CCW
    assert(!g.IsClockwise(Doubles( {-1.0 * pi,-1.5 * pi,-0.8 * pi} ))); //Mess

    assert( g.IsClockwise(Doubles( {-0.5 * pi, 0.0 * pi, 0.3 * pi } ))); //CW
    assert(!g.IsClockwise(Doubles( { 0.3 * pi, 0.0 * pi,-0.5 * pi } ))); //CCW
    assert(!g.IsClockwise(Doubles( { 0.0 * pi,-0.5 * pi, 0.3 * pi } ))); //Mess

    assert( g.IsClockwise(Doubles( { 0.0 * pi, 0.5 * pi, 0.8 * pi } ))); //CW
    assert(!g.IsClockwise(Doubles( { 0.8 * pi, 0.5 * pi, 0.0 * pi } ))); //CCW
    assert(!g.IsClockwise(Doubles( { 0.5 * pi, 0.0 * pi, 0.8 * pi } ))); //Mess

    assert( g.IsClockwise(Doubles( { 0.5 * pi, 1.0 * pi, 1.3 * pi } ))); //CW
    assert(!g.IsClockwise(Doubles( { 1.3 * pi, 1.0 * pi, 0.5 * pi } ))); //CCW
    assert(!g.IsClockwise(Doubles( { 1.0 * pi, 0.5 * pi, 1.3 * pi } ))); //Mess

    assert( g.IsClockwise(Doubles( { 1.5 * pi, 2.0 * pi, 2.3 * pi } ))); //CW
    assert(!g.IsClockwise(Doubles( { 2.3 * pi, 2.0 * pi, 1.5 * pi } ))); //CCW
    assert(!g.IsClockwise(Doubles( { 2.0 * pi, 1.5 * pi, 2.3 * pi } ))); //Mess

    assert( g.IsClockwise(Doubles( { 2.5 * pi, 3.0 * pi, 3.3 * pi } ))); //CW
    assert(!g.IsClockwise(Doubles( { 3.3 * pi, 3.0 * pi, 2.5 * pi } ))); //CCW
    assert(!g.IsClockwise(Doubles( { 3.0 * pi, 2.5 * pi, 3.3 * pi } ))); //Mess
  }
  if (verbose) TRACE("IsCounterClockWise of three, vector");
  {
    assert(!g.IsCounterClockwise(Doubles( {-2.5 * pi,-2.0 * pi,-1.8 * pi} ))); //CW
    assert( g.IsCounterClockwise(Doubles( {-1.8 * pi,-2.0 * pi,-2.5 * pi} ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( {-2.0 * pi,-2.5 * pi,-1.8 * pi} ))); //Mess

    assert(!g.IsCounterClockwise(Doubles( {-1.5 * pi,-1.0 * pi,-0.8 * pi} ))); //CW
    assert( g.IsCounterClockwise(Doubles( {-0.8 * pi,-1.0 * pi,-1.5 * pi} ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( {-1.0 * pi,-1.5 * pi,-0.8 * pi} ))); //Mess

    assert(!g.IsCounterClockwise(Doubles( {-0.5 * pi, 0.0 * pi, 0.3 * pi } ))); //CW
    assert( g.IsCounterClockwise(Doubles( { 0.3 * pi, 0.0 * pi,-0.5 * pi } ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( { 0.0 * pi,-0.5 * pi, 0.3 * pi } ))); //Mess

    assert(!g.IsCounterClockwise(Doubles( { 0.0 * pi, 0.5 * pi, 0.8 * pi } ))); //CW
    assert( g.IsCounterClockwise(Doubles( { 0.8 * pi, 0.5 * pi, 0.0 * pi } ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( { 0.5 * pi, 0.0 * pi, 0.8 * pi } ))); //Mess

    assert(!g.IsCounterClockwise(Doubles( { 0.5 * pi, 1.0 * pi, 1.3 * pi } ))); //CW
    assert( g.IsCounterClockwise(Doubles( { 1.3 * pi, 1.0 * pi, 0.5 * pi } ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( { 1.0 * pi, 0.5 * pi, 1.3 * pi } ))); //Mess

    assert(!g.IsCounterClockwise(Doubles( { 1.5 * pi, 2.0 * pi, 2.3 * pi } ))); //CW
    assert( g.IsCounterClockwise(Doubles( { 2.3 * pi, 2.0 * pi, 1.5 * pi } ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( { 2.0 * pi, 1.5 * pi, 2.3 * pi } ))); //Mess

    assert(!g.IsCounterClockwise(Doubles( { 2.5 * pi, 3.0 * pi, 3.3 * pi } ))); //CW
    assert( g.IsCounterClockwise(Doubles( { 3.3 * pi, 3.0 * pi, 2.5 * pi } ))); //CCW
    assert(!g.IsCounterClockwise(Doubles( { 3.0 * pi, 2.5 * pi, 3.3 * pi } ))); //Mess
  }
  if (verbose) TRACE("IsClockWise of four, vector");
  {
    //Correct order
    assert( g.IsClockwise(Doubles( {-2.5 * pi,-2.0 * pi,-1.5 * pi,-1.0 * pi} )));
    assert( g.IsClockwise(Doubles( {-2.0 * pi,-1.5 * pi,-1.0 * pi,-0.5 * pi} )));
    assert( g.IsClockwise(Doubles( {-1.5 * pi,-1.0 * pi,-0.5 * pi, 0.0 * pi} )));
    assert( g.IsClockwise(Doubles( {-1.0 * pi,-0.5 * pi, 0.0 * pi, 0.5 * pi} )));
    assert( g.IsClockwise(Doubles( {-0.5 * pi, 0.0 * pi, 0.5 * pi, 1.0 * pi} )));
    assert( g.IsClockwise(Doubles( { 0.0 * pi, 0.5 * pi, 1.0 * pi, 1.5 * pi} )));
    assert( g.IsClockwise(Doubles( { 0.5 * pi, 1.0 * pi, 1.5 * pi, 2.0 * pi} )));
    assert( g.IsClockwise(Doubles( { 1.0 * pi, 1.5 * pi, 2.0 * pi, 2.5 * pi} )));
    assert( g.IsClockwise(Doubles( { 1.5 * pi, 2.0 * pi, 2.5 * pi, 3.0 * pi} )));
    assert( g.IsClockwise(Doubles( { 2.0 * pi, 2.5 * pi, 3.0 * pi, 3.5 * pi} )));
    assert( g.IsClockwise(Doubles( { 2.5 * pi, 3.0 * pi, 3.5 * pi, 4.0 * pi} )));

    //Swap [0] and [1]
    assert(!g.IsClockwise(Doubles( {-2.0 * pi,-2.5 * pi,-1.5 * pi,-1.0 * pi} )));
    assert(!g.IsClockwise(Doubles( {-1.5 * pi,-2.0 * pi,-1.0 * pi,-0.5 * pi} )));
    assert(!g.IsClockwise(Doubles( {-1.0 * pi,-1.5 * pi,-0.5 * pi, 0.0 * pi} )));
    assert(!g.IsClockwise(Doubles( {-0.5 * pi,-1.0 * pi, 0.0 * pi, 0.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 0.0 * pi,-0.5 * pi, 0.5 * pi, 1.0 * pi} )));
    assert(!g.IsClockwise(Doubles( { 0.5 * pi, 0.0 * pi, 1.0 * pi, 1.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 1.0 * pi, 0.5 * pi, 1.5 * pi, 2.0 * pi} )));
    assert(!g.IsClockwise(Doubles( { 1.5 * pi, 1.0 * pi, 2.0 * pi, 2.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 2.0 * pi, 1.5 * pi, 2.5 * pi, 3.0 * pi} )));
    assert(!g.IsClockwise(Doubles( { 2.5 * pi, 2.0 * pi, 3.0 * pi, 3.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 3.0 * pi, 2.5 * pi, 3.5 * pi, 4.0 * pi} )));

    //Swap [2] and [3]
    assert(!g.IsClockwise(Doubles( {-2.5 * pi,-2.0 * pi,-1.0 * pi,-1.5 * pi} )));
    assert(!g.IsClockwise(Doubles( {-2.0 * pi,-1.5 * pi,-0.5 * pi,-1.0 * pi} )));
    assert(!g.IsClockwise(Doubles( {-1.5 * pi,-1.0 * pi, 0.0 * pi,-0.5 * pi} )));
    assert(!g.IsClockwise(Doubles( {-1.0 * pi,-0.5 * pi, 0.5 * pi, 0.0 * pi} )));
    assert(!g.IsClockwise(Doubles( {-0.5 * pi, 0.0 * pi, 1.0 * pi, 0.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 0.0 * pi, 0.5 * pi, 1.5 * pi, 1.0 * pi} )));
    assert(!g.IsClockwise(Doubles( { 0.5 * pi, 1.0 * pi, 2.0 * pi, 1.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 1.0 * pi, 1.5 * pi, 2.5 * pi, 2.0 * pi} )));
    assert(!g.IsClockwise(Doubles( { 1.5 * pi, 2.0 * pi, 3.0 * pi, 2.5 * pi} )));
    assert(!g.IsClockwise(Doubles( { 2.0 * pi, 2.5 * pi, 3.5 * pi, 3.0 * pi} )));
    assert(!g.IsClockwise(Doubles( { 2.5 * pi, 3.0 * pi, 4.0 * pi, 3.5 * pi} )));
  }
  if (verbose) TRACE("IsCounterClockWise of four, vector");
  {
    //Clockwise order
    assert(!g.IsCounterClockwise(Doubles( {-2.5 * pi,-2.0 * pi,-1.5 * pi,-1.0 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( {-2.0 * pi,-1.5 * pi,-1.0 * pi,-0.5 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( {-1.5 * pi,-1.0 * pi,-0.5 * pi, 0.0 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( {-1.0 * pi,-0.5 * pi, 0.0 * pi, 0.5 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( {-0.5 * pi, 0.0 * pi, 0.5 * pi, 1.0 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( { 0.0 * pi, 0.5 * pi, 1.0 * pi, 1.5 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( { 0.5 * pi, 1.0 * pi, 1.5 * pi, 2.0 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( { 1.0 * pi, 1.5 * pi, 2.0 * pi, 2.5 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( { 1.5 * pi, 2.0 * pi, 2.5 * pi, 3.0 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( { 2.0 * pi, 2.5 * pi, 3.0 * pi, 3.5 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( { 2.5 * pi, 3.0 * pi, 3.5 * pi, 4.0 * pi} )));
  }

  if (verbose) TRACE("IsClockWise of four, vector, going round more than once");
  /*
       A
       | _-D
     _-+-
    C  |
     \  |
      \ |
       \|
        B

  */
  {
    assert(!g.IsClockwise(Doubles( {0.0 * pi,0.9 * pi,1.8 * pi,2.7 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( {0.0 * pi,0.9 * pi,1.8 * pi,2.7 * pi} )));
  }
  if (verbose) TRACE("IsCounterClockWise of four, vector, going round more than once");
  /*
       D
       | _-A
     _-+-
    B  |
     \  |
      \ |
       \|
        C

  */
  {
    assert(!g.IsCounterClockwise(Doubles( {2.0 * pi,1.1 * pi,0.2 * pi,-0.7 * pi} )));
    assert(!g.IsCounterClockwise(Doubles( {2.7 * pi,1.8 * pi,0.9 * pi,0.0 * pi} )));
  }
  if (verbose) { TRACE("IsClockwise, 3D, from #228, test for positive, three of four points"); }
  {
    /*
    (-3.78624,2,10)
    (-3.78624,2,0)
    (-0.55,2,0)
    Removed: (-0.55,2,10)
    Observer: (-2.1871,3.74169,5)
    */
    const Coordinats3D points {
      Coordinat3D(-3.78624,2,10),
      Coordinat3D(-3.78624,2,0),
      Coordinat3D(-0.55,2,0)
    };
    const Coordinat3D observer{-2.1871,3.74169,5};
    assert(g.IsClockwiseCartesian(points,observer));
  }

  if (verbose) { TRACE("IsCounterClockwise, 3D, from #228, test for positive, three of four points"); }
  {
    /*
    (-0.55,2,0)
    (-3.78624,2,0)
    (-3.78624,2,10)
    Removed: (-0.55,2,10)
    Observer: (-2.1871,3.74169,5)
    */
    const Coordinats3D points {
      Coordinat3D(-0.55,2,0),
      Coordinat3D(-3.78624,2,0),
      Coordinat3D(-3.78624,2,10)
    };
    const Coordinat3D observer{-2.1871,3.74169,5};
    assert(g.IsCounterClockwiseCartesian(points,observer));
  }
  if (verbose) { TRACE("IsCounterClockwise, 3D, from #228, test for positive, all four points"); }
  {
    /*
    (-0.55,2,0)
    (-3.78624,2,0)
    (-3.78624,2,10)
    (-0.55,2,10)
    Observer: (-2.1871,3.74169,5)
    */
    const Coordinats3D points {
      Coordinat3D(-0.55,2,0),
      Coordinat3D(-3.78624,2,0),
      Coordinat3D(-3.78624,2,10),
      Coordinat3D(-0.55,2,10)
    };
    const Coordinat3D observer{-2.1871,3.74169,5};
    assert(g.IsCounterClockwiseCartesian(points,observer));
  }
  if (verbose) TRACE("IsConvex, two dimensions");
  {
    /* Polygons used:

    0123456789012    0123456789012
   0+------------   0+------------
   1|               1|
   2| A---------B   2| A---------B
   3| E        /    3|  \   D   /
   4|  \      /     4|   \ / \ /
   5|   D----C      5|    E   C
    |                |

       Convex           Concave

    */

    //Convex shape
    {
      const std::vector<Coordinat2D> points {
        { 2.0, 2.0}, //A
        {12.0, 2.0}, //B
        { 9.0, 5.0}, //C
        { 4.0, 5.0}, //D
        { 2.0, 3.0}  //E
      };

      Polygon polygon;
      boost::geometry::append(polygon, points);
      assert(g.IsConvex(polygon));
    }
    //Concave shape
    {
      const std::vector<Coordinat2D> points {
        { 2.0, 2.0}, //A
        {12.0, 2.0}, //B
        { 9.0, 5.0}, //C
        { 7.0, 3.0}, //D
        { 5.0, 5.0}  //E
      };

      Polygon polygon;
      boost::geometry::append(polygon, points);
      assert(!g.IsConvex(polygon));
    }
  }
  if (verbose) TRACE("Convex shape, 2D, from error #1");
  {

    /*

       __--3
     2-
     |
     |
     |
     |  __-0
     1--


    */
    {
      const std::vector<Coordinat2D> points {
        {17.4971,33.0765},
        {9.28854,29.5636},
        {9.28854,40.6764},
        {17.4971,44.4009}
      };
      assert(g.IsConvex(points));
    }
  }
  if (verbose) TRACE("Convex shape, 2D, from error #2");
  {
    //From 3D points:
    /*
    // (2.35114,3.23607,5) (index: 644)'
    // (1.17557,2.35781,5) (index: 658)'
    // (2.35114,3.23607,6) (index: 668)'
    // (1.17557,2.35781,6) (index: 682)'
    */
    /*

       __--2
     3-   /
         /
        /
       /
      / __-0
     1--

    */
    {
      const std::vector<Coordinat2D> points {
        {17.497 ,33.0765},
        { 9.2885,29.5636},
        {17.497 ,44.4009},
        { 9.2885,40.6764}
      };
      assert(!g.IsConvex(points));
    }
  }


  if (verbose) TRACE("Convex shape, 2D, from error #3, point 0");
  {
    /*
        __--2
     1--    |
     |      |
     |      |
     |      |
     |      |
     |      3
     0

    */
    {
      const std::vector<Coordinat2D> points {
        { 9.2885,29.5636},
        { 9.2885,40.6764},
        {17.497 ,44.4009},
        {17.497 ,33.0765}
      };

      assert(g.IsConvex(points));
    }
  }

  if (verbose) TRACE("Convex shape, 2D, from error #3, point 5");
  {
    /*
            3
     0      |
     |      |
     |      |
     |      |
     |      |
     |  __--2
     1--

    */
    {
      const std::vector<Coordinat2D> points {
        { 9.2885,40.6764},
        { 9.2885,29.5636},
        {17.497 ,33.0765},
        {17.497 ,44.4009}
      };

      assert(g.IsConvex(points));
    }
  }

  if (verbose) TRACE("Convex shape, 2D, from error #3, point 5");
  {
    /*

    2-3
    |
    1-0

    */
    {
      const std::vector<Coordinat2D> points {
        {15.9835,631.923},
        {8.24075,628.579},
        {8.24075,679.58 },
        {15.9835,682.926}
      };

      assert(g.IsConvex(points));
    }
  }


  if (verbose) TRACE("Convex shape, 3D, points in Y=0 plane");
  {
    if (verbose) TRACE("Convex shape, 3D, points in Y=0 plane, Z shape");
    {
      /*
                  |####/
        3---2     |###/#
           /      +##+##
          /       |#/###
         /        |/####
        1---0   --+--+--
                 /|
      */
      const ApCoordinats3D points {
        ApCoordinat3D(1.0,0.0,0.0),
        ApCoordinat3D(0.0,0.0,0.0),
        ApCoordinat3D(1.0,0.0,1.0),
        ApCoordinat3D(0.0,0.0,1.0)
      };

      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    if (verbose) TRACE("Convex shape, 3D, points in Y=0 plane, C shape");
    {
      /*

        2---3 Z=1.0
        |
        |
        |
        1---0 Z=0.0

      */
      const ApCoordinats3D points {
        ApCoordinat3D(1.0,0.0,0.0),
        ApCoordinat3D(0.0,0.0,0.0),
        ApCoordinat3D(0.0,0.0,1.0),
        ApCoordinat3D(1.0,0.0,1.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, points in X=Y plane");
  {
    {
      /*
                  |    |/     _-
                  |  _-2    _-
        3---2     |_- /   _-
           /      3  /  _-
          /       | / _0
         /        |/_-
        1---0   --1-----
                 /|
      */
      const ApCoordinats3D points {
        ApCoordinat3D(1.0,1.0,0.0),
        ApCoordinat3D(0.0,0.0,0.0),
        ApCoordinat3D(1.0,1.0,1.0),
        ApCoordinat3D(0.0,0.0,1.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    //Convex shape, 3D, points in X=Y plane
    {
      /*

                  |    |/     _-
                  |  _-3    _-
        2---3     |_- /   _-
        |         2  /  _-
        |         | / _0
        |         |/_-
        1---0   --1-----
                 /|

      */
      const ApCoordinats3D points {
        ApCoordinat3D(1.0,1.0,0.0),
        ApCoordinat3D(0.0,0.0,0.0),
        ApCoordinat3D(0.0,0.0,1.0),
        ApCoordinat3D(1.0,1.0,1.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, points in 2X=Y plane, not at origin");
  {
    {
      const ApCoordinats3D points {
        ApCoordinat3D(2.0,4.0,0.0),
        ApCoordinat3D(1.0,1.0,0.0),
        ApCoordinat3D(2.0,4.0,1.0),
        ApCoordinat3D(1.0,1.0,1.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    {
      const ApCoordinats3D points {
        ApCoordinat3D(2.0,2.0,0.0),
        ApCoordinat3D(1.0,1.0,0.0),
        ApCoordinat3D(1.0,1.0,1.0),
        ApCoordinat3D(2.0,2.0,1.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, points in 2X=Y plane, above Z=0");
  {
    {
      const ApCoordinats3D points {
        ApCoordinat3D(2.0,4.0,1.0),
        ApCoordinat3D(1.0,1.0,1.0),
        ApCoordinat3D(2.0,4.0,2.0),
        ApCoordinat3D(1.0,1.0,2.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    {
      const ApCoordinats3D points {
        ApCoordinat3D(2.0,2.0,1.0),
        ApCoordinat3D(1.0,1.0,1.0),
        ApCoordinat3D(1.0,1.0,2.0),
        ApCoordinat3D(2.0,2.0,2.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }
  if (verbose) TRACE("Convex shape, 3D, from error");
  {
    {
      /*

        3---2 Z=6.0
           /
          /
         /
        1---0 Z=5.0

      */
      const ApCoordinats3D points {
        ApCoordinat3D(2.35114,3.23607,5.0),
        ApCoordinat3D(1.17557,2.35781,5.0),
        ApCoordinat3D(2.35114,3.23607,6.0),
        ApCoordinat3D(1.17557,2.35781,6.0)
      };
      assert(!g.IsConvex(points) && "This is an hourglass shape, so it is not convex");
    }
    {
      /*

        2---3 Z=6.0
        |
        |
        |
        1---0 Z=5.0

      */
      const ApCoordinats3D points {
        ApCoordinat3D(2.35114,3.23607,5.0),
        ApCoordinat3D(1.17557,2.35781,5.0),
        ApCoordinat3D(1.17557,2.35781,6.0),
        ApCoordinat3D(2.35114,3.23607,6.0)
      };
      assert(g.IsConvex(points) && "This is a corrected hourglass shape, so it is convex");
    }
  }

  if (verbose) TRACE("IsClockwise in three dimensions, points in XY plane");
  {
    /*

       Y
     3 |
       |
     2 | C-B
       | |/
     1 | A       (seen from above, Z = 1)
       |
     0 +------X
       0 1 2 3

    */

    const ApCoordinat3D a(1.0, 1.0, 1.0);
    const ApCoordinat3D b(2.0, 2.0, 1.0);
    const ApCoordinat3D c(1.0, 2.0, 1.0);
    const ApCoordinats3D coordinats { a,b,c };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const ApCoordinat3D above(x, y, 2.0);
        const ApCoordinat3D below(x, y,-1.0);
        assert(!g.IsClockwiseCartesian(coordinats,above));
        assert( g.IsClockwiseCartesian(coordinats,below));
        assert( g.IsCounterClockwiseCartesian(coordinats,above));
        assert(!g.IsCounterClockwiseCartesian(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise in three dimensions, points in XY plane");
  {
    /*

       Y
     3 |
       |
     2 | B-C
       | |/
     1 | A       (seen from above, Z = 1)
       |
     0 +------X
       0 1 2 3

    */
    const ApCoordinat3D a(1.0, 1.0, 1.0);
    const ApCoordinat3D b(1.0, 2.0, 1.0);
    const ApCoordinat3D c(2.0, 2.0, 1.0);
    const ApCoordinats3D coordinats { a,b,c };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const ApCoordinat3D above(x, y, 2.0);
        const ApCoordinat3D below(x, y,-1.0);
        assert( g.IsClockwiseCartesian(coordinats,above));
        assert(!g.IsClockwiseCartesian(coordinats,below));
        assert(!g.IsCounterClockwiseCartesian(coordinats,above));
        assert( g.IsCounterClockwiseCartesian(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise, clockwise, in three dimensions, four points in XY plane");
  {
    /*

   3.5 Y
     3 |
   2.5 |
     2 | D-C
   1.5 | | |
     1 | A-B     (seen from above, Z = 1)
   0.5 |
     0 +------X
       0 1 2 3

    */
    const ApCoordinat3D a(1.0, 1.0, 1.0);
    const ApCoordinat3D b(2.0, 1.0, 1.0);
    const ApCoordinat3D c(2.0, 2.0, 1.0);
    const ApCoordinat3D d(1.0, 2.0, 1.0);
    const ApCoordinats3D coordinats { a,b,c,d };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const ApCoordinat3D above(x, y, 2.0);
        const ApCoordinat3D below(x, y,-1.0);
        //Check CalcCenter
        {
          const auto center = g.CalcCenter(coordinats);
          const auto center_x = boost::geometry::get<0>(center);
          const auto center_y = boost::geometry::get<1>(center);
          const auto center_z = boost::geometry::get<2>(center);
          assert(center_x > 1.49 && center_x < 1.51);
          assert(center_y > 1.49 && center_y < 1.51);
          assert(center_z > 0.99 && center_z < 1.01);
        }
        assert(!g.IsClockwiseCartesianHorizontal(coordinats));
        assert( g.IsCounterClockwiseCartesianHorizontal(coordinats));
        assert(!g.IsClockwiseCartesian(coordinats,above));
        assert( g.IsClockwiseCartesian(coordinats,below));
        assert( g.IsCounterClockwiseCartesian(coordinats,above));
        assert(!g.IsCounterClockwiseCartesian(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise, counter-clockwise, in three dimensions, four points in XY plane");
  {
    /*
   3.5 Y
     3 |
   2.5 |
     2 | B-C
   1.5 | | |
     1 | A-D     (seen from above, Z = 1)
   0.5 |
     0 +------X
       0 1 2 3

    */
    const ApCoordinat3D a(1.0, 1.0, 1.0);
    const ApCoordinat3D b(1.0, 2.0, 1.0);
    const ApCoordinat3D c(2.0, 2.0, 1.0);
    const ApCoordinat3D d(2.0, 1.0, 1.0);
    const ApCoordinats3D coordinats { a,b,c,d };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const double x = static_cast<double>(i-1) * 5.0;
        const double y = static_cast<double>(j-1) * 5.0;
        const ApCoordinat3D above(x, y, 2.0);
        const ApCoordinat3D below(x, y,-1.0);
        assert( g.IsClockwiseCartesian(coordinats,above));
        assert(!g.IsClockwiseCartesian(coordinats,below));
        assert(!g.IsCounterClockwiseCartesian(coordinats,above));
        assert( g.IsCounterClockwiseCartesian(coordinats,below));
      }
    }
  }
  if (verbose) TRACE("IsClockwise, indetermined direction, in three dimensions, four points in XY plane");
  {
    /*
   3.5 Y
     3 |
   2.5 |
     2 | C-B
   1.5 |  x
     1 | A-D     (seen from above, Z = 1)
   0.5 |
     0 +------X
       0 1 2 3

    */
    const ApCoordinat3D a(1.0, 1.0, 1.0);
    const ApCoordinat3D b(2.0, 2.0, 1.0);
    const ApCoordinat3D c(1.0, 2.0, 1.0);
    const ApCoordinat3D d(2.0, 1.0, 1.0);
    const ApCoordinats3D coordinats { a,b,c,d };
    for (int i = 0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        const Apfloat x = static_cast<double>(i-1) * 5.0;
        const Apfloat y = static_cast<double>(j-1) * 5.0;
        const ApCoordinat3D above(x, y, 2.0);
        const ApCoordinat3D below(x, y,-1.0);
        assert(!g.IsClockwiseCartesian(coordinats,above));
        assert(!g.IsClockwiseCartesian(coordinats,below));
        assert(!g.IsCounterClockwiseCartesian(coordinats,above));
        assert(!g.IsCounterClockwiseCartesian(coordinats,below));
      }
    }
  }
  //IsPlane
  {
    const ApCoordinat3D a(-3.64472,-0.25,0.0);
    const ApCoordinat3D b(-4.52988,-0.25,0.0);
    const ApCoordinat3D c(-3.64472,-0.25,10.0);
    const ApCoordinat3D d(-4.52988,-0.25,10.0);
    const ApCoordinats3D v{a,b,c,d};
    assert(Geometry().IsPlane(v));
  }
  if (verbose) TRACE("Translate");
  {
    //Translate (0.5,1.0) to origin
    const auto house = g.CreateHouseShape();
    const auto translated_house = g.Translate(house,-0.5,-1.0);
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
  if (verbose) TRACE("Scale up twice, from origin");
  {
    //Scale twice up, from origin
    const auto house = g.CreateHouseShape();
    const auto rescaled_house = g.Rescale(house,2.0);
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
  if (verbose) TRACE("Scale up twice, from non-origin");
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
    const auto house = g.CreateHouseShape();
    const auto rescaled_house = g.Rescale(house,2.0,0.5,1.0);
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
  if (verbose) { TRACE("WktToSvg"); }
  {
    const std::string s
      = g.WktToSvg("POLYGON((0 0,0 1,1 0)),LINESTRING(0 0,0 1,1 0)",1.0)
    ;
    assert(!s.empty());
  }

  if (verbose) { TRACE("GetLineLineIntersections"); }
  #ifdef TODO_RICHEL
  {
    typedef boost::geometry::model::d2::point_xy<double> Point;
    typedef boost::geometry::model::linestring<Point> Line;
    typedef boost::geometry::model::box<Point> Rect;
    //Assume line segment (0,0)-(2,2) intersects line segment (2,0)-(0,2) at point (1,1)
    {
      const Line line1 = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Line line2 = CreateLine( std::vector<Point>( { Point(2.0,0.0), Point(0.0,2.0) } ));
      assert( GetLineLineIntersections(line1,line2).size() == 1);
      assert( fuzzy_equal_to()(GetLineLineIntersections(line1,line2)[0].x(),1.0) );
      assert( fuzzy_equal_to()(GetLineLineIntersections(line1,line2)[0].y(),1.0) );
    }
    //Lines are finite, however, as the line segment
    //(0,0)-(0.2,0.2) does not intersect line segment (2,0)-(0,2) at point (1,1)
    {
      const Line line1 = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(0.2,0.2) } ));
      const Line line2 = CreateLine( std::vector<Point>( { Point(2.0,0.0), Point(0.0,2.0) } ));
      assert( GetLineLineIntersections(line1,line2).size() == 0);
    }
    //Assume line segment (0,0)-(2,2) intersects with rectangle (1,0)-(3,9) at point (1,1)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Rect rect(Point(1.0,0.0), Point(3.0,3.9));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 1);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
    }
    //Assume line segment (0,0)-(2,2) intersects with rectangle (0,1)-(3,9) at point (1,1)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Rect rect(Point(0.0,1.0), Point(3.0,9.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 1);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
    }
    //Assume line segment (0,0)-(2,2) intersects with rectangle (1,1)-(3,3) at point (1,1) once
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(2.0,2.0) } ));
      const Rect rect(Point(1.0,1.0), Point(3.0,3.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 1);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
    }

    //Assume line segment (0,0)-(4,4) intersects with rectangle (1,0)-(3,9) at points (1,1) and (3,3)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(4.0,4.0) } ));
      const Rect rect(Point(1.0,0.0), Point(3.0,3.9));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 2);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
      assert( fuzzy_equal_to()(v[1].x(),3.0) );
      assert( fuzzy_equal_to()(v[1].y(),3.0) );
    }
    //Assume line segment (0,0)-(4,4) intersects with rectangle (0,1)-(3,9) at points (1,1) and (3,3)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(4.0,4.0) } ));
      const Rect rect(Point(0.0,1.0), Point(3.0,9.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 2);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
      assert( fuzzy_equal_to()(v[1].x(),3.0) );
      assert( fuzzy_equal_to()(v[1].y(),3.0) );
    }
    //Assume line segment (0,0)-(4,4) intersects with rectangle (1,1)-(3,3) at points (1,1) and (3,3)
    {
      const Line line = CreateLine( std::vector<Point>( { Point(0.0,0.0), Point(4.0,4.0) } ));
      const Rect rect(Point(1.0,1.0), Point(3.0,3.0));
      GetLineRectIntersections(line,rect);
      const std::vector<Point> v = GetLineRectIntersections(line,rect);
      assert(v.size() == 2);
      assert( fuzzy_equal_to()(v[0].x(),1.0) );
      assert( fuzzy_equal_to()(v[0].y(),1.0) );
      assert( fuzzy_equal_to()(v[1].x(),3.0) );
      assert( fuzzy_equal_to()(v[1].y(),3.0) );
    }
  }
  #endif //#ifdef TODO_RICHEL
  //WktToLinestring: open linestring to polygon
  {
    const auto p = g.WktToLinestring("LINESTRING(0 0 0 1 1 1 1 0)");
    assert(p.size() == 4);
  }
  //WktToPolygon: open linestring to polygon
  {
    const auto p = g.WktToPolygon("POLYGON((0 0 0 1 1 1 1 0))");
    assert(p.outer().size() == 4);
  }
  //ToPolygon: open linestring to polygon
  {
    /*

    |        |
    + 2-3    + 2-3
    | |   -> | | |
    + 1-0    + 1-0
    |        |
    +-+-+-   +-+-+-

    */
    const auto l = g.WktToLinestring("LINESTRING(2 1 1 1 1 2 2 2)");
    const auto p = g.ToPolygon(l);
    assert(p.outer().size() == 4);
  }
  //ToPolygon: closed linestring to polygon
  {
    /*

    |        |
    + 2-3    + 2-3
    | | | -> | | |
    + 1-0    + 1-0
    |        |
    +-+-+-   +-+-+-

    */
    const auto l = g.WktToLinestring("LINESTRING(2 1 1 1 1 2 2 2 2 1)");
    const auto p = g.ToPolygon(l);
    assert(p.outer().size() == 4);
  }
  TRACE("Finished ribi::Geometry::Test successfully");
}
#endif


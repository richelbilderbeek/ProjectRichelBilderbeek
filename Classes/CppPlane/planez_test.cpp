#include "planez.h"

#include <cassert>

#include "container.h"
#include "geometry.h"
#include "trace.h"

#ifndef NDEBUG
void ribi::PlaneZ::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PlaneZ::Test");
  using boost::geometry::get;
  const bool verbose = false;
  const auto series = GetTestSeries();

  if (verbose) { TRACE("Default construction"); }
  {
    const PlaneZ p;
    assert(!p.ToFunction().empty());
    assert(!p.GetCoefficients().empty());
  }

  if (verbose) TRACE("PlaneZ, Z = 5");
  {
    const Coordinat3D p1( 2.0, 3.0,5.0);
    const Coordinat3D p2( 7.0,11.0,5.0);
    const Coordinat3D p3(13.0,17.0,5.0);
    const PlaneZ p(p1,p2,p3);
    assert(
      !p.CalcProjection(
        {
          Coordinat3D(0.0,0.0,1.0),
          Coordinat3D(1.0,0.0,0.0),
          Coordinat3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }

  //IsInPlane for Z=0 plane
  if (verbose) TRACE("PlaneZ, preparation for Plane::CanCalcZ and Plane::IsInPlane, Z = 0 plane, from 1.0 coordinat");
  {
    const Coordinat3D p1(0.0,0.0,0.0);
    const Coordinat3D p2(0.0,1.0,0.0);
    const Coordinat3D p3(1.0,0.0,0.0);
    const PlaneZ p(p1,p2,p3);
    assert( p.IsInPlane(Coordinat3D( 0.0, 0.0,0.0)));
    assert( p.IsInPlane(Coordinat3D(-1.0,-1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D( 1.0,-1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D(-1.0, 1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D( 1.0, 1.0,0.0)));
  }
  if (verbose) TRACE("PlaneZ, preparation for Plane::CanCalcZ and Plane::IsInPlane, Z = 0 plane, from smallest possible coordinat");
  {
    const double i = std::numeric_limits<double>::denorm_min();
    assert(i > 0.0);
    const Coordinat3D p1(0.0,0.0,0.0);
    const Coordinat3D p2(0.0,  i,0.0);
    const Coordinat3D p3(  i,0.0,0.0);
    const PlaneZ p(p1,p2,p3);
    assert( p.IsInPlane(Coordinat3D( 0.0, 0.0,0.0)));
    assert( p.IsInPlane(Coordinat3D(-1.0,-1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D( 1.0,-1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D(-1.0, 1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D( 1.0, 1.0,0.0)));

  }
  if (verbose) TRACE("PlaneZ, preparation for Plane::CanCalcZ and Plane::IsInPlane, Z = 0 plane, from biggest possible coordinat");
  {
    const double i = std::numeric_limits<double>::max();
    assert(i > 0.0);
    const Coordinat3D p1(0.0,0.0,0.0);
    const Coordinat3D p2(0.0,  i,0.0);
    const Coordinat3D p3(  i,0.0,0.0);
    const PlaneZ p(p1,p2,p3);
    assert( p.IsInPlane(Coordinat3D( 0.0, 0.0,0.0)));
    assert( p.IsInPlane(Coordinat3D(-1.0,-1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D( 1.0,-1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D(-1.0, 1.0,0.0)));
    assert( p.IsInPlane(Coordinat3D( 1.0, 1.0,0.0)));
  }
  if (verbose) TRACE("PlaneZ, preparation for Plane::CanCalcZ and Plane::IsInPlane, Z = 0 plane, zooming in");
  {
    for (const double i:series)
    {
      if (i == 0.0) continue;
      assert(i != 0.0 && "Cannot express plane when all its coordinats are at origin");
      const Coordinat3D p1(0.0,0.0,0.0);
      const Coordinat3D p2(0.0,  i,0.0);
      const Coordinat3D p3(  i,0.0,0.0);
      const PlaneZ p(p1,p2,p3);
      for (const double j:series)
      {
        assert(p.IsInPlane(Coordinat3D(0.0,0.0,0.0)));
        assert(p.IsInPlane(Coordinat3D(  j,  j,0.0)));
        assert(p.IsInPlane(Coordinat3D(  j, -j,0.0)));
        assert(p.IsInPlane(Coordinat3D( -j,  j,0.0)));
        assert(p.IsInPlane(Coordinat3D( -j, -j,0.0)));
      }
    }
  }
  if (verbose) TRACE("CanCalcZ, Z = 1, zooming to smallest three points to determine a plane, point above origin");
  {
      for (double i = 1.0; i > 0.0; i/=10.0)
      {
        const Coordinat3D p1(0.0,0.0,1.0);
        const Coordinat3D p2(0.0,  i,1.0);
        const Coordinat3D p3(  i,0.0,1.0);
        const Coordinat3D p4(0.0,0.0,1.0);
        const PlaneZ p(p1,p2,p3);
        if (verbose)
        {
          TRACE("----------------------------");
          TRACE(i);
          TRACE(p.CalcMaxError(p4));
          TRACE(p.CalcError(p4));
          TRACE(p.GetFunctionA());
          TRACE(p.GetFunctionB());
          TRACE(p.GetFunctionC());
          TRACE(p.GetCoefficients()[0]);
          TRACE(p.GetCoefficients()[1]);
          TRACE(p.GetCoefficients()[2]);
          TRACE(p.GetCoefficients()[3]);
          TRACE(std::numeric_limits<double>::epsilon());
          TRACE(std::sqrt(std::numeric_limits<double>::epsilon()));
          TRACE(std::numeric_limits<double>::denorm_min());
        }
        assert(p.IsInPlane(p4));
      }
  }
  if (verbose) TRACE("CanCalcZ, Z = 1.0 plane, zooming in");
  {
    for (const double i:series)
    {
      if (i == 0.0) continue;
      assert(i != 0.0 && "Cannot express plane when all its coordinats are at origin");
      const Coordinat3D p1(0.0,0.0,1.0);
      const Coordinat3D p2(0.0,  i,1.0);
      const Coordinat3D p3(  i,0.0,1.0);
      const PlaneZ p(p1,p2,p3);
      for (const double j:series)
      {
        if (!p.IsInPlane(Coordinat3D(0.0,0.0,1.0)))
        {
          TRACE(i);
          TRACE(p.CalcMaxError(Coordinat3D(0.0,0.0,1.0)));
          TRACE(p.CalcError(Coordinat3D(0.0,0.0,1.0)));
        }
        assert(p.IsInPlane(Coordinat3D(0.0,0.0,1.0)));
        assert(p.IsInPlane(Coordinat3D(  j,  j,1.0)));
        assert(p.IsInPlane(Coordinat3D(  j, -j,1.0)));
        assert(p.IsInPlane(Coordinat3D( -j,  j,1.0)));
        assert(p.IsInPlane(Coordinat3D( -j, -j,1.0)));
      }
    }
  }

  /*

    |    /#/##########
    |   B#/###########
    |  /#/############
    | /#/#############
    |/#/##############
    A-------C--------- Z = z
    |/
  --O----------------- Z = 0
   /|


  */
  if (verbose) TRACE("PlaneZ, preparation for Plane::CanCalcZ and Plane::IsInPlane, Z = z plane, zooming in");
  {
    //The height of the plane
    for (const double z:series)
    {
      //The distance from the origin, will be used by the two construction points
      for (const double i:series)
      {
        if (i == 0.0) continue;
        assert(i != 0.0 && "Cannot express plane when all its coordinats are at origin");
        const Coordinat3D p1(0.0,0.0,z);
        const Coordinat3D p2(0.0,  i,z);
        const Coordinat3D p3(  i,0.0,z);
        const PlaneZ p(p1,p2,p3);
        //The distance (actually, half the Manhattan distance) from the origin,
        //will be used by points tested to be in this plane
        for (const double j:series)
        {
          if (!p.IsInPlane(Coordinat3D(j,j,z)))
          {
            std::stringstream s;
            s << "Warning: coordinat " << Geometry().ToStr(Coordinat3D(j,j,z))
              << " is determined not to be in a PlaneZ that was created from points "
              << Geometry().ToStr(p1) << ", "
              << Geometry().ToStr(p2) << " and "
              << Geometry().ToStr(p3) << "."
            ;
            TRACE(s.str());
            continue;
          }
          if (!p.IsInPlane(Coordinat3D(j,j,z)))
          {
            TRACE("ERROR");
            TRACE(z);
            TRACE(i);
            TRACE(j);
            TRACE(p.CalcError(Coordinat3D(j,j,z)));
            TRACE(p.CalcMaxError(Coordinat3D(j,j,z)));
            TRACE(p);

            TRACE("AGAIN");
            TRACE(z);
            TRACE(i);
            TRACE(j);
            TRACE(p.CalcError(Coordinat3D(j,j,z)));
            TRACE(p.CalcMaxError(Coordinat3D(j,j,z)));
            TRACE(p);

          }
          assert(p.IsInPlane(Coordinat3D(  j,  j,z)));
          assert(p.IsInPlane(Coordinat3D(  j, -j,z)));
          assert(p.IsInPlane(Coordinat3D( -j,  j,z)));
          assert(p.IsInPlane(Coordinat3D( -j, -j,z)));
        }
      }
    }
  }

  if (verbose) { TRACE("Check formulas"); }
  {
    const double p1_x { 1.0 };
    const double p1_y { 2.0 };
    const double p1_z { 3.0 };
    const double p2_x { 4.0 };
    const double p2_y { 6.0 };
    const double p2_z { 9.0 };
    const double p3_x {12.0 };
    const double p3_y {11.0 };
    const double p3_z { 9.0 };
    PlaneZ p(
      Coordinat3D(p1_x,p1_y,p1_z),
      Coordinat3D(p2_x,p2_y,p2_z),
      Coordinat3D(p3_x,p3_y,p3_z)
    );
    const auto t(Geometry().ToDouble(p.GetCoefficients()));
    assert(t.size() == 4);
    const auto a = t[0];
    const auto b = t[1];
    const auto c = t[2];
    const auto d = t[3];
    const auto a_expected =  30.0;
    const auto b_expected = -48.0;
    const auto c_expected =  17.0;
    const auto d_expected = -15.0;
    assert(std::abs(a - a_expected) < 0.001);
    assert(std::abs(b - b_expected) < 0.001);
    assert(std::abs(c - c_expected) < 0.001);
    assert(std::abs(d - d_expected) < 0.001);
    const auto d_p1_expected = (a * p1_x) + (b * p1_y) + (c * p1_z);
    const auto d_p2_expected = (a * p2_x) + (b * p2_y) + (c * p2_z);
    const auto d_p3_expected = (a * p3_x) + (b * p3_y) + (c * p3_z);
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
  if (verbose) { TRACE("CalcPlaneZ"); }
  {
    //CalcPlaneZ return the coefficients in the following form:
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
    const Coordinat3D p1(1.0,1.0,10.0);
    const Coordinat3D p2(1.0,2.0,13.0);
    const Coordinat3D p3(2.0,1.0,12.0);
    const PlaneZ p(p1,p2,p3);
    const auto t(Geometry().ToDouble(p.GetCoefficients()));
    const auto a = t[0];
    const auto b = t[1];
    const auto c = t[2];
    const auto d = t[3];
    const auto a_expected = -2.0;
    const auto b_expected = -3.0;
    const auto c_expected =  1.0;
    const auto d_expected =  5.0;
    assert(std::abs(a - a_expected) < 0.001);
    assert(std::abs(b - b_expected) < 0.001);
    assert(std::abs(c - c_expected) < 0.001);
    assert(std::abs(d - d_expected) < 0.001);
    const auto d_p1_expected = (a * 1.0) + (b * 1.0) + (c * 10.0);
    const auto d_p2_expected = (a * 1.0) + (b * 2.0) + (c * 13.0);
    const auto d_p3_expected = (a * 2.0) + (b * 1.0) + (c * 12.0);
    assert(std::abs(d - d_p1_expected) < 0.001);
    assert(std::abs(d - d_p2_expected) < 0.001);
    assert(std::abs(d - d_p3_expected) < 0.001);
  }
  if (verbose) { TRACE("CalcZ, diagonal plane"); }
  {
    const Coordinat3D p1(1.0,2.0,3.0);
    const Coordinat3D p2(2.0,5.0,8.0);
    const Coordinat3D p3(3.0,7.0,11.0);
    const PlaneZ p(p1,p2,p3);
    assert(abs(p.CalcZ(1.0,2.0)- 3.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(p.CalcZ(2.0,5.0)- 8.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(p.CalcZ(3.0,7.0)-11.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
  }
  if (verbose) { TRACE("CalcZ, horizontal plane Z = 5.0"); }
  /*

    |    /
    |   /#
    |  /##
    | /###
    |/####
 ---+-----
   /|
  / |
 /  |

  */
  {


    const Coordinat3D p1( 2.0, 3.0,5.0);
    const Coordinat3D p2( 7.0,11.0,5.0);
    const Coordinat3D p3(13.0,17.0,5.0);
    const PlaneZ p(p1,p2,p3);
    assert( abs(p.CalcZ(1.0,2.0)-5.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert( abs(p.CalcZ(3.0,5.0)-5.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert( abs(p.CalcZ(7.0,9.0)-5.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
  }
  if (verbose) { TRACE("ToFunction, 3 points and 4 points"); }
  {
    std::function<double(double,double)> f {
      [](const double x, const double y)
      {
        return (2.0 * x) + (3.0 * y) + 5.0;
      }
    };


    const double x1 =  2.0;
    const double y1 =  3.0;
    const double x2 =  5.0;
    const double y2 =  7.0;
    const double x3 = 11.0;
    const double y3 = 13.0;
    const double x4 = 17.0;
    const double y4 = 29.0;
    const Coordinat3D p1(x1,y1,f(x1,y1));
    const Coordinat3D p2(x2,y2,f(x2,y2));
    const Coordinat3D p3(x3,y3,f(x3,y3));
    const PlaneZ a(p1,p2,p3);
    //assert(a.ToFunction() == "z=(2*x) + (3*y) + 5");
    assert(!a.ToFunction().empty());

    const Coordinat3D p4(x4,y4,f(x4,y4));
    assert(a.ToFunction() == PlaneZ(p1,p2,p4).ToFunction());
    assert(a.ToFunction() == PlaneZ(p1,p3,p4).ToFunction());
    assert(a.ToFunction() == PlaneZ(p1,p4,p3).ToFunction());
    assert(a.ToFunction() == PlaneZ(p2,p1,p3).ToFunction());
    assert(a.ToFunction() == PlaneZ(p2,p1,p4).ToFunction());
    assert(a.ToFunction() == PlaneZ(p2,p3,p1).ToFunction());
    assert(a.ToFunction() == PlaneZ(p2,p3,p4).ToFunction());
    assert(a.ToFunction() == PlaneZ(p2,p4,p1).ToFunction());
    assert(a.ToFunction() == PlaneZ(p2,p4,p3).ToFunction());
    assert(a.ToFunction() == PlaneZ(p3,p1,p2).ToFunction());
    assert(a.ToFunction() == PlaneZ(p3,p1,p4).ToFunction());
    assert(a.ToFunction() == PlaneZ(p3,p2,p1).ToFunction());
    assert(a.ToFunction() == PlaneZ(p3,p2,p4).ToFunction());
    assert(a.ToFunction() == PlaneZ(p3,p4,p1).ToFunction());
    assert(a.ToFunction() == PlaneZ(p3,p4,p2).ToFunction());
    assert(a.ToFunction() == PlaneZ(p4,p1,p2).ToFunction());
    assert(a.ToFunction() == PlaneZ(p4,p1,p3).ToFunction());
    assert(a.ToFunction() == PlaneZ(p4,p2,p1).ToFunction());
    assert(a.ToFunction() == PlaneZ(p4,p2,p3).ToFunction());
    assert(a.ToFunction() == PlaneZ(p4,p3,p1).ToFunction());
    assert(a.ToFunction() == PlaneZ(p4,p3,p2).ToFunction());

  }
  if (verbose) { TRACE("GetProjection, for Z = 0 plane"); }
  {
    /*

    A: (0,0,1)                  A: (0,0)
    B: (1,0,0)                  B: (1,0)
    C: (1,1,0)                  C: (1,1)

    |    /
    |   /                       |
    A-----C                     |  C
    |\/  /      -> becomes ->   | /|
    |/\ /                       |/ |
    +--B---                     A--B-----

    */
    const std::vector<Coordinat2D> v {
      PlaneZ().CalcProjection(
        {
          Coordinat3D(0.0,0.0,1.0),
          Coordinat3D(1.0,0.0,0.0),
          Coordinat3D(1.0,1.0,0.0)
        }
      )
    };
    assert(v.size() == 3);
    assert(abs(get<0>(v[0]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[0]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[1]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[1]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[2]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[2]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace

  }
  if (verbose) { TRACE("CalcProjection, for Z = 2 plane"); }
  {
    /*

    A: (0,0,1+2)                  A: (0,0)
    B: (1,0,0+2)                  B: (1,0)
    C: (1,1,0+2)                  C: (1,1)

    |    /
    |   /                       |
    A-----C                     |  C
    |\/  /      -> becomes ->   | /|
    |/\ /                       |/ |
    +--B---                     A--B-----

    */
    const std::vector<Coordinat2D> v {
      PlaneZ(
        Coordinat3D(0.0,0.0,0.0+2.0),
        Coordinat3D(0.0,1.0,0.0+2.0),
        Coordinat3D(1.0,0.0,0.0+2.0)
      ).CalcProjection(
        {
          Coordinat3D(0.0,0.0,1.0+2.0),
          Coordinat3D(1.0,0.0,0.0+2.0),
          Coordinat3D(1.0,1.0,0.0+2.0)
        }
      )
    };
    assert(v.size() == 3);
    assert(abs(get<0>(v[0]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[0]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[1]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[1]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[2]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[2]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
  }

  TRACE("Finished ribi::PlaneZ::Test successfully");
}
#endif


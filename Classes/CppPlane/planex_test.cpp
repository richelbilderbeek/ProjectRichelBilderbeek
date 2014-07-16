//---------------------------------------------------------------------------
/*
Plane, 3D plane class
Copyright (C) 2013-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPlane.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "planex.h"

#include <cassert>

#include "container.h"
#include "geometry.h"
#include "planez.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::PlaneX::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PlaneX::Test");
  using boost::geometry::get;

  const bool verbose{false};
  if (verbose) TRACE("Default construction");
  {
    const PlaneX p;
    assert(!p.ToFunction().empty());
    assert(!p.GetCoefficients().empty());
  }
  /*
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
    PlaneX p(
      Point(p1_x,p1_y,p1_z),
      Point(p2_x,p2_y,p2_z),
      Point(p3_x,p3_y,p3_z)
    );
    const auto t(p.GetCoefficients());
    assert(t.size() == 4);
    const double a { t[0] };
    const double b { t[1] };
    const double c { t[2] };
    const double d { t[3] };
    const double a_expected {  30.0 };
    const double b_expected { -48.0 };
    const double c_expected {  17.0 };
    const double d_expected { -15.0 };
    assert(abs(a - a_expected) < 0.001);
    assert(abs(b - b_expected) < 0.001);
    assert(abs(c - c_expected) < 0.001);
    assert(abs(d - d_expected) < 0.001);
    const double d_p1_expected { (a * p1_x) + (b * p1_y) + (c * p1_z) };
    const double d_p2_expected { (a * p2_x) + (b * p2_y) + (c * p2_z) };
    const double d_p3_expected { (a * p3_x) + (b * p3_y) + (c * p3_z) };

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
    }
    assert(abs(d - d_p1_expected) < 0.001);
    assert(abs(d - d_p2_expected) < 0.001);
    assert(abs(d - d_p3_expected) < 0.001);
  }
  */
  //CalcPlaneX
  /*
  {
    //CalcPlaneX return the coefficients in the following form:
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


    const Point3D p1(1.0,1.0,10.0);
    const Point3D p2(1.0,2.0,13.0);
    const Point3D p3(2.0,1.0,12.0);
    PlaneX p(p1,p2,p3);
    const auto t(p.GetCoefficients());
    const double a { t[0] };
    const double b { t[1] };
    const double c { t[2] };
    const double d { t[3] };
    const double a_expected { -2.0 };
    const double b_expected { -3.0 };
    const double c_expected {  1.0 };
    const double d_expected {  5.0 };
    assert(abs(a - a_expected) < 0.001);
    assert(abs(b - b_expected) < 0.001);
    assert(abs(c - c_expected) < 0.001);
    assert(abs(d - d_expected) < 0.001);
    const double d_p1_expected { (a * 1.0) + (b * 1.0) + (c * 10.0) };
    const double d_p2_expected { (a * 1.0) + (b * 2.0) + (c * 13.0) };
    const double d_p3_expected { (a * 2.0) + (b * 1.0) + (c * 12.0) };
    assert(abs(d - d_p1_expected) < 0.001);
    assert(abs(d - d_p2_expected) < 0.001);
    assert(abs(d - d_p3_expected) < 0.001);
    TRACE(p.ToFunction());
  }
  */
  if (verbose) TRACE("CalcX, diagonal plane");
  {


    const Coordinat3D p1(1.0,2.0,3.0);
    const Coordinat3D p2(2.0,5.0,8.0);
    const Coordinat3D p3(3.0,7.0,11.0);
    PlaneX p(p1,p2,p3);
    assert( abs(p.CalcX(2.0, 3.0)- 1.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert( abs(p.CalcX(5.0, 8.0)- 2.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert( abs(p.CalcX(7.0,11.0)-3.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
  }
  if (verbose) TRACE("CalcX, vertical plane X = 2.0");
  /*

    |####/
    |###/
    |##/
    |#/
    |/
 ---+--------
   /|
  / |
 /  |

  */
  {


    const Coordinat3D p1(2.0, 3.0, 5.0);
    const Coordinat3D p2(2.0, 7.0,11.0);
    const Coordinat3D p3(2.0,13.0,17.0);
    PlaneX p(p1,p2,p3);
    assert( abs(p.CalcX(1.0,2.0)-2.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert( abs(p.CalcX(3.0,5.0)-2.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert( abs(p.CalcX(7.0,9.0)-2.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
  }
  if (verbose) TRACE("ToFunction, 3 points and 4 points");
  {
    std::function<double(double,double)> f {
      [](const double y, const double z)
      {
        return (2.0 * y) + (3.0 * z) + 5.0;
      }
    };


    const double y1 { 2.0 };
    const double z1 { 3.0 };
    const double y2 { 5.0 };
    const double z2 { 7.0 };
    const double y3 { 11.0 };
    const double z3 { 13.0 };
    const double y4 { 17.0 };
    const double z4 { 29.0 };
    const Coordinat3D p1(f(y1,z1),y1,z1);
    const Coordinat3D p2(f(y2,z2),y2,z2);
    const Coordinat3D p3(f(y3,z3),y3,z3);
    const PlaneX a(p1,p2,p3);
    //assert(a.ToFunction() == "x=(2*y) + (3*z) + 5");
    assert(!a.ToFunction().empty());
    const Coordinat3D p4(f(y4,z4),y4,z4);
    assert(a.ToFunction() == PlaneX(p1,p2,p4).ToFunction());
    assert(a.ToFunction() == PlaneX(p1,p3,p4).ToFunction());
    assert(a.ToFunction() == PlaneX(p1,p4,p3).ToFunction());
    assert(a.ToFunction() == PlaneX(p2,p1,p3).ToFunction());
    assert(a.ToFunction() == PlaneX(p2,p1,p4).ToFunction());
    assert(a.ToFunction() == PlaneX(p2,p3,p1).ToFunction());
    assert(a.ToFunction() == PlaneX(p2,p3,p4).ToFunction());
    assert(a.ToFunction() == PlaneX(p2,p4,p1).ToFunction());
    assert(a.ToFunction() == PlaneX(p2,p4,p3).ToFunction());
    assert(a.ToFunction() == PlaneX(p3,p1,p2).ToFunction());
    assert(a.ToFunction() == PlaneX(p3,p1,p4).ToFunction());
    assert(a.ToFunction() == PlaneX(p3,p2,p1).ToFunction());
    assert(a.ToFunction() == PlaneX(p3,p2,p4).ToFunction());
    assert(a.ToFunction() == PlaneX(p3,p4,p1).ToFunction());
    assert(a.ToFunction() == PlaneX(p3,p4,p2).ToFunction());
    assert(a.ToFunction() == PlaneX(p4,p1,p2).ToFunction());
    assert(a.ToFunction() == PlaneX(p4,p1,p3).ToFunction());
    assert(a.ToFunction() == PlaneX(p4,p2,p1).ToFunction());
    assert(a.ToFunction() == PlaneX(p4,p2,p3).ToFunction());
    assert(a.ToFunction() == PlaneX(p4,p3,p1).ToFunction());
    assert(a.ToFunction() == PlaneX(p4,p3,p2).ToFunction());
  }

  if (verbose) TRACE("IsInPlane, X = 1, zooming to smallest three points to determine a plane, point above origin");
  {
    for (double i = 1.0; i > 0.0; i/=10.0)
    {
      const Coordinat3D p1(1.0,0.0,0.0);
      const Coordinat3D p2(1.0,  i,0.0);
      const Coordinat3D p3(1.0,0.0,  i);
      const PlaneX p(p1,p2,p3);
      if (verbose)
      {
        TRACE("----------------------------");
        TRACE(i);
        TRACE(p.CalcMaxError(p1));
        TRACE(p.CalcError(p1));
        TRACE(p.CalcMaxError(p2));
        TRACE(p.CalcError(p2));
        TRACE(p.CalcMaxError(p3));
        TRACE(p.CalcError(p3));
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
      assert(p.IsInPlane(p1));
      assert(p.IsInPlane(p2));
      assert(p.IsInPlane(p3));
    }
  }

  if (verbose) TRACE("IsInPlane, for bug #228");
  {
    //Values copied literally, so no .0 on purpose
    const Coordinat3D p1(-5,-5,0);
    const Coordinat3D p2(-5,-0.999999999999999880,0);
    const Coordinat3D p3(-5,-5,10);
    const Coordinat3D p4(-5,-0.999999999999999880,10);
    const PlaneX p(p1,p2,p3);
    //if (verbose)
    {
      TRACE("----------------------------");
      TRACE(p.CalcMaxError(p1));
      TRACE(p.CalcError(p1));
      TRACE(p.CalcMaxError(p2));
      TRACE(p.CalcError(p2));
      TRACE(p.CalcMaxError(p3));
      TRACE(p.CalcError(p3));
      TRACE(p.CalcMaxError(p4));
      TRACE(p.CalcError(p4));
      TRACE(p.GetFunctionA());
      TRACE(p.GetFunctionB());
      TRACE(p.GetFunctionC());
      TRACE(p.GetCoefficients()[0]);
      TRACE(p.GetCoefficients()[1]);
      TRACE(p.GetCoefficients()[2]);
      TRACE(p.GetCoefficients()[3]);
    }
    assert(p.IsInPlane(p1));
    assert(p.IsInPlane(p2));
    assert(p.IsInPlane(p3));
    assert(p.IsInPlane(p4));
  }
  if (verbose) TRACE("GetProjection");
  {
    /*

    A: (0,0,1)                  A: ( 0,1)
    B: (1,0,0)                  B: ( 0,0)
    C: (1,1,0)                  C: (SQRT(2),0)

    |    /
    |   /                          |
    A-----C                        A
    |\/  /      -> becomes ->      |\
    |/\ /                          | \
  --+--B---                    ----B--C--
   /|                              |
  / |                              |
    */
    const std::vector<Coordinat2D> v {
      PlaneX().CalcProjection(
        {
          Coordinat3D(0.0,0.0,1.0),
          Coordinat3D(1.0,0.0,0.0),
          Coordinat3D(1.0,1.0,0.0)
        }
      )
    };
    assert(v.size() == 3);
    assert(abs(get<0>(v[0]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[0]) - 1.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[1]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[1]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[2]) - std::sqrt(2.0) ) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[2]) - 0.0 ) < 0.001); //no std:: , as apfloat puts abs in the global namespace

  }
  if (verbose) TRACE("GetProjection, for X = 2 plane");
  {
    /*

    A: (2,0,0)                  A: (0,0)
    B: (2,1,0)                  B: (1,0)
    C: (2,0,1)                  C: (0,1)

    |######/                 |
    C#####/                  C
    |\###/                   |\
    |#\#/                    | \
    |##B       -> becomes -> |  \
    |#/                      |   \
    |/                       |    \
 ---A--------             ---A-----B---
   /|                        |
  / |                        |
 /  |                        |

    */
    const std::vector<Coordinat2D> v {
      PlaneX(
        Coordinat3D(0.0+2.0,0.0,0.0),
        Coordinat3D(0.0+2.0,1.0,0.0),
        Coordinat3D(0.0+2.0,0.0,1.0)

      ).CalcProjection(
        {
          Coordinat3D(0.0+2.0,0.0,0.0),
          Coordinat3D(0.0+2.0,1.0,0.0),
          Coordinat3D(0.0+2.0,0.0,1.0)
        }
      )
    };
    assert(v.size() == 3);
    assert(abs(get<0>(v[0]) - 0.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[0]) - 0.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[1]) - 1.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[1]) - 0.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<0>(v[2]) - 0.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
    assert(abs(get<1>(v[2]) - 1.0) < 0.001); //no std:: , as apfloat puts abs in the global namespace
  }
  TRACE("Finished ribi::PlaneX::Test successfully");
}
#endif

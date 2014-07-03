#include "plane.h"

#include <cassert>

#include <boost/limits.hpp>
#include <boost/make_shared.hpp>

#include "container.h"
#include "geometry.h"
#include "planex.h"
#include "planey.h"
#include "planez.h"
#include "trace.h"

#ifndef NDEBUG
void ribi::Plane::Test() noexcept
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Plane::Test");
  const bool verbose = true;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Point3D;
  using boost::geometry::get;
  Container();
  Geometry();
  { const auto planex = boost::make_shared<PlaneX>(); assert(planex); }
  { const auto planey = boost::make_shared<PlaneY>(); assert(planey); }
  { const auto planez = boost::make_shared<PlaneZ>(); assert(planez); }

  if (verbose) TRACE("Plane that can be expressed in all three forms");
  {
    const Point3D p1( 1.0, 2.0,3.0);
    const Point3D p2( 4.0, 6.0,9.0);
    const Point3D p3(12.0,11.0,9.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcX());
    assert(p.CanCalcY());
    assert(p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );

  }
  if (verbose) TRACE("Plane X = 2");
  {
    const Point3D p1(2.0, 2.0,3.0);
    const Point3D p2(2.0, 6.0,9.0);
    const Point3D p3(2.0,11.0,9.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcX());
    assert(!p.CanCalcY());
    assert(!p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("Plane X = 123");
  {
    const Point3D p1(123.0, 2.0,3.0);
    const Point3D p2(123.0, 6.0,9.0);
    const Point3D p3(123.0,11.0,9.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcX());
    assert(!p.CanCalcY());
    assert(!p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("Plane Y = 3");
  {
    const Point3D p1( 2.0, 3.0, 5.0);
    const Point3D p2( 7.0, 3.0, 9.0);
    const Point3D p3(11.0,3.0,13.0);
    const Plane p(p1,p2,p3);

    assert(p.CanCalcY());
    assert(!p.CanCalcX());
    assert(!p.CanCalcZ());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("Plane Z = 5");
  {
    const Point3D p1( 2.0, 3.0,5.0);
    const Point3D p2( 7.0,11.0,5.0);
    const Point3D p3(13.0,17.0,5.0);
    const Plane p(p1,p2,p3);
    assert(p.CanCalcZ());
    assert(!p.CanCalcX());
    assert(!p.CanCalcY());
    assert(
      !p.CalcProjection(
        {
          Point3D(0.0,0.0,1.0),
          Point3D(1.0,0.0,0.0),
          Point3D(1.0,1.0,0.0)
        }
      ).empty()
    );
  }
  if (verbose) TRACE("IsInPlane, X = 0 plane");
  {
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,0.0,1.0);
    const Point3D p3(0.0,1.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D(0.0, 2.0, 2.0)));
    assert(p.IsInPlane(Point3D(0.0, 2.0,-2.0)));
    assert(p.IsInPlane(Point3D(0.0,-2.0, 2.0)));
    assert(p.IsInPlane(Point3D(0.0,-2.0,-2.0)));

    const double e = std::numeric_limits<double>::epsilon();

    assert(p.IsInPlane(Point3D(e, 2.0, 2.0)));
    assert(p.IsInPlane(Point3D(e, 2.0,-2.0)));
    assert(p.IsInPlane(Point3D(e,-2.0, 2.0)));
    assert(p.IsInPlane(Point3D(e,-2.0,-2.0)));
    const double f = 2.0 * e;
    assert(!p.IsInPlane(Point3D(f, 2.0, 2.0)));
    assert(!p.IsInPlane(Point3D(f, 2.0,-2.0)));
    assert(!p.IsInPlane(Point3D(f,-2.0, 2.0)));
    assert(!p.IsInPlane(Point3D(f,-2.0,-2.0)));
  }
  if (verbose) TRACE("IsInPlane, X = 0 plane, zooming in, #223");
  {
    const double i = boost::numeric::bounds<double>::smallest();
    assert(i > 0.0);
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,0.0,i);
    const Point3D p3(0.0,i,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D(0.0, 2.0, 2.0)));
    assert(p.IsInPlane(Point3D(0.0, 2.0,-2.0)));
    assert(p.IsInPlane(Point3D(0.0,-2.0, 2.0)));
    assert(p.IsInPlane(Point3D(0.0,-2.0,-2.0)));
  }
  if (verbose) TRACE("IsInPlane, Y = 0 plane");
  {
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,0.0,1.0);
    const Point3D p3(1.0,0.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D( 2.0,0.0, 2.0)));
    assert(p.IsInPlane(Point3D( 2.0,0.0,-2.0)));
    assert(p.IsInPlane(Point3D(-2.0,0.0, 2.0)));
    assert(p.IsInPlane(Point3D(-2.0,0.0,-2.0)));
    const double e = std::numeric_limits<double>::epsilon();
    //const double e = boost::numeric::bounds<double>::smallest();
    assert(p.IsInPlane(Point3D( 2.0,e, 2.0)));
    assert(p.IsInPlane(Point3D( 2.0,e,-2.0)));
    assert(p.IsInPlane(Point3D(-2.0,e, 2.0)));
    assert(p.IsInPlane(Point3D(-2.0,e,-2.0)));
    const double f = 2.0 * e;
    assert(!p.IsInPlane(Point3D( 2.0,f, 2.0)));
    assert(!p.IsInPlane(Point3D( 2.0,f,-2.0)));
    assert(!p.IsInPlane(Point3D(-2.0,f, 2.0)));
    assert(!p.IsInPlane(Point3D(-2.0,f,-2.0)));
  }
  if (verbose) TRACE("IsInPlane, Y = 0 plane, zooming in, #223");
  {
    const double i = boost::numeric::bounds<double>::smallest();
    assert(i > 0.0);
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,0.0,i);
    const Point3D p3(i,0.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D( 2.0,0.0, 2.0)));
    assert(p.IsInPlane(Point3D( 2.0,0.0,-2.0)));
    assert(p.IsInPlane(Point3D(-2.0,0.0, 2.0)));
    assert(p.IsInPlane(Point3D(-2.0,0.0,-2.0)));
  }
  if (verbose) TRACE("IsInPlane, Z = 0 plane");
  {
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,1.0,0.0);
    const Point3D p3(1.0,0.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D( 2.0, 2.0,0.0)));
    assert(p.IsInPlane(Point3D( 2.0,-2.0,0.0)));
    assert(p.IsInPlane(Point3D(-2.0, 2.0,0.0)));
    assert(p.IsInPlane(Point3D(-2.0,-2.0,0.0)));
    //const double e = boost::numeric::bounds<double>::smallest();
    const double e = std::numeric_limits<double>::epsilon();
    assert(p.IsInPlane(Point3D( 2.0, 2.0,e)));
    assert(p.IsInPlane(Point3D( 2.0,-2.0,e)));
    assert(p.IsInPlane(Point3D(-2.0, 2.0,e)));
    assert(p.IsInPlane(Point3D(-2.0,-2.0,e)));
    const double f = 2.0 * e;
    assert(!p.IsInPlane(Point3D( 1.0, 1.0,f)));
    assert(!p.IsInPlane(Point3D( 1.0,-1.0,f)));
    assert(!p.IsInPlane(Point3D(-1.0, 1.0,f)));
    assert(!p.IsInPlane(Point3D(-1.0,-1.0,f)));
  }
  if (verbose) TRACE("IsInPlane, Z = 0 plane, zooming in, #223");
  {
    const double i = boost::numeric::bounds<double>::smallest();
    assert(i > 0.0);
    const Point3D p1(0.0,0.0,0.0);
    const Point3D p2(0.0,i,0.0);
    const Point3D p3(i,0.0,0.0);
    const Plane p(p1,p2,p3);
    assert(p.IsInPlane(Point3D( 2.0, 2.0,0.0)));
    assert(p.IsInPlane(Point3D( 2.0,-2.0,0.0)));
    assert(p.IsInPlane(Point3D(-2.0, 2.0,0.0)));
    assert(p.IsInPlane(Point3D(-2.0,-2.0,0.0)));
  }
  //Create plane with different slopes
  /*
  |          /
  |         /
  |        /         __--D
  |       /      __--   /|
  |      /   __--      / |
  |     /__--         /  |
  |    B             /   +
  |   /         __--C   /
  |  /      __--    |  /
  | /   __--        | /
  |/__--            |/
  A-----------------+---------------

  A = p1 = Origin, fixed
  B = p2 = At y axis, fixed
  C = p3 = Above X axis, dependent on slope
  D = p4 = To be calculated
  */
  if (verbose) TRACE("IsInPlane, Slope");
  {
    for (const double slope: { 1.0, 0.1 } )
    {
      TRACE(slope);
      const double slope_less = slope * 0.9999999;
      const double slope_more = slope * 1.0000001;
      assert(slope_less < slope);
      assert(slope_more > slope);
      const Point3D p1(0.0,0.0,0.0);
      const Point3D p2(0.0,1.0,0.0);
      const Point3D p3(1.0,0.0,slope);
      const Plane p(p1,p2,p3);
      assert( p.IsInPlane(Point3D( 1.0, 1.0,slope)));
      assert(!p.IsInPlane(Point3D( 1.0, 1.0,slope_more)));
      assert(!p.IsInPlane(Point3D( 1.0, 1.0,slope_less)));
    }
  }
  //Create plane with different slopes
  /*
  |          /
  |         /
  |        /__-D
  |     __--   |
  | __-- /     |
  B-    /      |
  |    /       |
  |   /        |
  |  /      __-C
  | /   __--  /
  |/__--     /
  A---------+-----------------------

  A = p1 = Origin, fixed
  B = p2 = At y axis, fixed
  C = p3 = Above X axis, dependent on slope
  D = p4 = To be calculated
  */
  if (verbose) TRACE("IsInPlane, Slope, vertical plane");
  {
    typedef std::pair<double,double> Pair;
    for (const Pair co:
      {
        std::make_pair(    1.0,    1.0),
        std::make_pair(   10.0,   10.0),
        std::make_pair(  100.0,  100.0),
        std::make_pair( 1000.0, 1000.0),
        std::make_pair(10000.0,10000.0),
        std::make_pair(1.0,1.000),
        std::make_pair(1.0,0.100),
        std::make_pair(1.0,0.010),
        std::make_pair(1.0,0.001),
      }
    )
    {
      //TRACE("----------------------------------------------------------");
      //TRACE(co.first);
      //TRACE(co.second);
      const Point3D p1(0.0,0.0,0.0);
      const Point3D p2(0.0,0.0,1.0);
      const Point3D p3(co.first,co.second,0.0);
      const Plane p(p1,p2,p3);
      assert( p.IsInPlane(Point3D(co.first,co.second,1.0)));
    }
  }
  if (verbose) TRACE("CalcProjection, from a crash in the program");
  {
    const Point3D p1( 1.0,-0.0,0.0);
    const Point3D p2(-1.0, 0.0,0.0);
    const Point3D p3( 1.0,-0.0,1.0);
    const Point3D p4(-1.0, 0.0,1.0);
    const Plane p(p1,p2,p3);

    assert(p.CanCalcY());
    //assert(!p.ToFunctionY().empty());

    assert(!p.CanCalcX());
    //try { p.ToFunctionX(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }

    assert(!p.CanCalcZ());
    //try { p.ToFunctionZ(); assert(!"Should not get here"); } catch (std::logic_error&) { /* OK */ }
    assert(!p.CalcProjection( { p1,p2,p3,p4 } ).empty());
  }
  if (verbose) TRACE("IsInPlane, from #218");
  {
    const double x1 = -0.5500000000000004884981308350688777863979339599609375;
    const double y1 = 2.000000000000000444089209850062616169452667236328125;
    const double z1 = 0; //left out the '.0' intentionally
    const double x2 = -3.78623595505618038004058689693920314311981201171875;
    const double y2 = 2; //left out the '.0' intentionally
    const double z2 = 0; //left out the '.0' intentionally
    const double x3 = -0.5500000000000004884981308350688777863979339599609375;
    const double y3 = 2.000000000000000444089209850062616169452667236328125;
    const double z3 = 10; //left out the '.0' intentionally
    const double x4 = -3.78623595505618038004058689693920314311981201171875;
    const double y4 = 2; //left out the '.0' intentionally
    const double z4 = 10; //left out the '.0' intentionally

    const Point3D p1(x1,y1,z1);
    const Point3D p2(x2,y2,z2);
    const Point3D p3(x3,y3,z3);
    const Point3D p4(x4,y4,z4);
    const Plane p(p1,p2,p3);
    try
    {
      const bool must_be_true = p.IsInPlane(p4);
      assert(must_be_true);
    }
    catch (std::exception&)
    {
      TRACE("ERROR");
      std::stringstream s;
      s
        << std::setprecision(99)
        << p << '\n'
        << Container().ToStr(p.GetCoefficientsX()) << '\n'
        << Container().ToStr(p.GetCoefficientsY()) << '\n'
        << Container().ToStr(p.GetCoefficientsZ()) << '\n'
      ;
      TRACE(s.str());
      TRACE("BREAK");
    }
    assert(p.IsInPlane(p4));
  }
  if (verbose) TRACE("IsInPlane, from >#220");
  {
    const double x1 = 0.0004035051226622692510832834944523028752882964909076690673828125;
    const double y1 = 0.00023296416881187433805568132161312178141088224947452545166015625;
    const double z1 = 0; //left out the '.0' intentionally

    const double x2 = 0.000403505141811931846741734464245610070065595209598541259765625;
    const double y2 = 0.00023296414405748076185791173298156309101614169776439666748046875;
    const double z2 = 0; //left out the '.0' intentionally

    const double x3 = 0.0004035051226622692510832834944523028752882964909076690673828125;
    const double y3 = 0.00023296416881187433805568132161312178141088224947452545166015625;
    const double z3 = 0.00025000000000000000520417042793042128323577344417572021484375;

    const double x4 = 0.000403505141811931846741734464245610070065595209598541259765625;
    const double y4 = 0.00023296414405748076185791173298156309101614169776439666748046875;
    const double z4 = 0.00025000000000000000520417042793042128323577344417572021484375;

    const Point3D p1(x1,y1,z1);
    const Point3D p2(x2,y2,z2);
    const Point3D p3(x3,y3,z3);
    const Point3D p4(x4,y4,z4);
    const Plane p(p1,p2,p3);
    try
    {
      assert(p.IsInPlane(p4));
    }
    catch (std::exception&)
    {
      TRACE("ERROR");
      std::stringstream s;
      s
        << std::setprecision(99)
        << p << '\n'
        << Container().ToStr(p.GetCoefficientsX()) << '\n'
        << Container().ToStr(p.GetCoefficientsY()) << '\n'
        << Container().ToStr(p.GetCoefficientsZ()) << '\n'
      ;
      TRACE(s.str());
      TRACE("BREAK");
    }
    assert(p.IsInPlane(p4));
  }
  TRACE("Finished ribi::Plane::Test successfully");
}
#endif

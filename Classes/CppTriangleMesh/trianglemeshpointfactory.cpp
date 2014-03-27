#include "trianglemeshpointfactory.h"

#include <cassert>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshwindings.h"
#include "trace.h"

ribi::trim::PointFactory::PointFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
/*
///Create a Point with an undetermined Z coordinat
const boost::shared_ptr<ribi::trim::Point> ribi::trim::PointFactory::CreateFromXy(
  const double x, const double y
) const noexcept
{
  const boost::shared_ptr<const ConstCoordinat2D> coordinat {
    new ConstCoordinat2D(x,y)
  };
  assert(coordinat);
  return Create(coordinat);
}
*/
#endif

boost::shared_ptr<ribi::trim::Point> ribi::trim::PointFactory::Create(
  const boost::shared_ptr<const Coordinat2D> coordinat
) const noexcept
{
  PROFILE_FUNC();
  //Give every Point some index at creation
  static int cnt = 1;
  const int n = cnt;
  ++cnt;


  const boost::shared_ptr<Point> point(
    new Point(
      coordinat,
      n,
      *this
    )
  );
  assert(point);
  return point;
}

std::vector<boost::shared_ptr<ribi::trim::Point>>
  ribi::trim::PointFactory::CreateTestInvalid() const noexcept
{
  //1: -1  0 0
  //2:  1 -0 1
  //7:  1 -0 0
  //3: -1  0 1
  const boost::shared_ptr<Coordinat2D> co_a { new Coordinat2D(-1.0, 0.0) };
  const boost::shared_ptr<Coordinat2D> co_b { new Coordinat2D( 1.0,-0.0) };
  const boost::shared_ptr<Coordinat2D> co_c { new Coordinat2D( 1.0,-0.0) };
  const boost::shared_ptr<Coordinat2D> co_d { new Coordinat2D(-1.0, 0.0) };
  const auto a(PointFactory().Create(co_a));
  const auto b(PointFactory().Create(co_b));
  const auto c(PointFactory().Create(co_c));
  const auto d(PointFactory().Create(co_d));
  a->SetZ(0.0 * boost::units::si::meter);
  b->SetZ(1.0 * boost::units::si::meter);
  c->SetZ(0.0 * boost::units::si::meter);
  d->SetZ(1.0 * boost::units::si::meter);
  a->SetIndex(1);
  b->SetIndex(2);
  c->SetIndex(3);
  d->SetIndex(4);
  const std::vector<boost::shared_ptr<Point>> square { a,b,c,d };
  return square;
}

std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::PointFactory::CreateTestPrism() const noexcept
{
  const boost::shared_ptr<Coordinat2D> co_a { new Coordinat2D(0.0,0.0) };
  const boost::shared_ptr<Coordinat2D> co_b { new Coordinat2D(1.0,0.0) };
  const boost::shared_ptr<Coordinat2D> co_c { new Coordinat2D(0.0,1.0) };
  const boost::shared_ptr<Coordinat2D> co_d { new Coordinat2D(0.0,0.0) };
  const boost::shared_ptr<Coordinat2D> co_e { new Coordinat2D(1.0,0.0) };
  const boost::shared_ptr<Coordinat2D> co_f { new Coordinat2D(0.0,1.0) };

  const auto a(PointFactory().Create(co_a));
  const auto b(PointFactory().Create(co_b));
  const auto c(PointFactory().Create(co_c));
  const auto d(PointFactory().Create(co_d));
  const auto e(PointFactory().Create(co_e));
  const auto f(PointFactory().Create(co_f));
  a->SetZ(0.0 * boost::units::si::meter);
  b->SetZ(0.0 * boost::units::si::meter);
  c->SetZ(0.0 * boost::units::si::meter);
  d->SetZ(1.0 * boost::units::si::meter);
  e->SetZ(1.0 * boost::units::si::meter);
  f->SetZ(1.0 * boost::units::si::meter);
  a->SetIndex(1);
  b->SetIndex(2);
  c->SetIndex(3);
  d->SetIndex(4);
  e->SetIndex(5);
  f->SetIndex(6);
  const std::vector<boost::shared_ptr<Point>> prism {
    a,b,c,d,e,f
  };
  return prism;
}

std::vector<boost::shared_ptr<ribi::trim::Point>>
  ribi::trim::PointFactory::CreateTestSquare(
  const ribi::trim::Winding winding
) const noexcept
{
  /*

    Clockwise:

    0 1 2
  0 +-+-+-X
    |
  1 + 0-1  where Z = 1.0 for all points
    | | |
  2 + 3-2
    |
    Y

    Counter-clockwise:

    0 1 2
  0 +-+-+-X
    |
  1 + 0-3 where Z = 1.0 for all points
    | | |
  2 + 1-2
    |
    Y

    Indeterminate:

    0  1  2
  0 +--+--+-X
    |
    |
  1 +  0--3 where Z = 1.0 for all points
    |   \/
    |   /\
  2 +  2--1
    |
    Y

  */
  const boost::shared_ptr<Coordinat2D> co_a {
    new Coordinat2D(1.0,1.0)
  };
  boost::shared_ptr<Coordinat2D> co_b {
    new Coordinat2D(2.0,1.0)
  };
  boost::shared_ptr<Coordinat2D> co_c {
    new Coordinat2D(2.0,2.0)
  };
  boost::shared_ptr<Coordinat2D> co_d {
    new Coordinat2D(1.0,2.0)
  };

  if (winding == Winding::counter_clockwise)
  {
    std::swap(co_b,co_d);
  }
  else if (winding == Winding::indeterminate)
  {
    std::swap(co_b,co_c);
    std::swap(co_c,co_d);
  }

  const boost::shared_ptr<Point> a { PointFactory().Create(co_a) };
  const boost::shared_ptr<Point> b { PointFactory().Create(co_b) };
  const boost::shared_ptr<Point> c { PointFactory().Create(co_c) };
  const boost::shared_ptr<Point> d { PointFactory().Create(co_d) };

  a->SetIndex(1);
  b->SetIndex(2);
  c->SetIndex(3);
  d->SetIndex(3);
  a->SetZ(1.0 * boost::units::si::meter);
  b->SetZ(1.0 * boost::units::si::meter);
  c->SetZ(1.0 * boost::units::si::meter);
  d->SetZ(1.0 * boost::units::si::meter);
  const std::vector<boost::shared_ptr<Point>> square { a,b,c,d };
  #ifndef NDEBUG

  if(Helper().CalcWindingHorizontal(AddConst(square)) != winding)
  {
    TRACE("ERROR");
    TRACE(*a);
    TRACE(*b);
    TRACE(*c);
    TRACE(Windings().ToStr(winding));
    TRACE(Helper().IsClockwiseHorizontal(square));
    TRACE("BREAK");
  }
  #endif
  assert(Helper().CalcWindingHorizontal(AddConst(square)) == winding);
  return square;
}

std::vector<boost::shared_ptr<ribi::trim::Point>>
  ribi::trim::PointFactory::CreateTestTriangle(
  const ribi::trim::Winding winding
) const noexcept
{
  assert( (winding == Winding::clockwise || winding == Winding::counter_clockwise)
    && "It is impossible to create a triangle with an indeterminate winding");

  /*

    Clockwise:

    0 1 2
  0 +-+-+-X
    |
  1 + 0   where Z = 1.0 for all points
    | |\
  2 + 2-1
    |
    Y

    Counter-clockwise:

    0 1 2
  0 +-+-+-X
    |
  1 + 0   where Z = 1.0 for all points
    | |\
  2 + 1-2
    |
    Y

  */

  const boost::shared_ptr<Coordinat2D> co_a {
    new Coordinat2D(1.0,1.0)
  };
  boost::shared_ptr<Coordinat2D> co_b {
    new Coordinat2D(2.0,2.0)
  };
  boost::shared_ptr<Coordinat2D> co_c {
    new Coordinat2D(1.0,2.0)
  };

  if (winding == Winding::counter_clockwise) { std::swap(co_b,co_c); }

  const boost::shared_ptr<Point> a {
    PointFactory().Create(co_a)
  };
  const boost::shared_ptr<Point> b {
    PointFactory().Create(co_b)
  };
  const boost::shared_ptr<Point> c {
    PointFactory().Create(co_c)
  };

  a->SetIndex(1);
  b->SetIndex(2);
  c->SetIndex(3);
  a->SetZ(1.0 * boost::units::si::meter);
  b->SetZ(1.0 * boost::units::si::meter);
  c->SetZ(1.0 * boost::units::si::meter);
  const std::vector<boost::shared_ptr<Point>> triangle { a,b,c };
  #ifndef NDEBUG
  if (!(Helper().IsClockwiseHorizontal(triangle)   == (winding == Winding::clockwise)))
  {
    TRACE("ERROR");
    TRACE(*a);
    TRACE(*b);
    TRACE(*c);
    TRACE(Windings().ToStr(winding));
    TRACE(Helper().IsClockwiseHorizontal(triangle));
    TRACE("BREAK");
  }
  #endif
  assert(Helper().IsClockwiseHorizontal(triangle)   == (winding == Winding::clockwise));
  return triangle;
}

#ifndef NDEBUG
void ribi::trim::PointFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::PointFactory::Test");
  {
    const std::vector<boost::shared_ptr<Point>> prism {
      PointFactory().CreateTestPrism()
    };
    assert(prism.size() == 6 && "A prism has 6 points");
  }
  for (Winding winding: { Winding::clockwise, Winding::counter_clockwise } )
  {
    assert(
      Helper().CalcWindingHorizontal(
        AddConst(PointFactory().CreateTestTriangle(winding))
      ) == winding
    );
  }
  TRACE("Finished ribi::trim::PointFactory::Test successfully");
}
#endif

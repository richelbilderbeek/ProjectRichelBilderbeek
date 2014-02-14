#include "trianglemeshpointfactory.h"

#include <cassert>

#include "Shiny.h"

#include "coordinat3d.h"
#include "trianglemeshpoint.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trace.h"

ribi::trim::PointFactory::PointFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::trim::Point> ribi::trim::PointFactory::Create(
  const boost::shared_ptr<const ribi::ConstCoordinat2D> coordinat
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

const std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::PointFactory::CreateTestPrism() const noexcept
{
  const std::vector<boost::shared_ptr<Point>> points {
    Point::CreateTestPrism()
  };
  const std::vector<boost::shared_ptr<Point>> points_bottom { points[0], points[1], points[2] };
  const std::vector<boost::shared_ptr<Point>> points_top    { points[3], points[4], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_a      { points[0], points[1], points[4] };
  const std::vector<boost::shared_ptr<Point>> points_b      { points[0], points[3], points[4] };
  const std::vector<boost::shared_ptr<Point>> points_c      { points[1], points[2], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_d      { points[1], points[4], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_e      { points[0], points[2], points[3] };
  const std::vector<boost::shared_ptr<Point>> points_f      { points[2], points[3], points[5] };

  const boost::shared_ptr<Point> bottom {
    PointFactory().Create(points_top,PointOrientation::horizontal, {})
  };
  const boost::shared_ptr<Point> top {
    PointFactory().Create(points_top,PointOrientation::horizontal,bottom)
  };
  const boost::shared_ptr<Point> a {
    PointFactory().Create(points_a,PointOrientation::vertical, {})
  };
  const boost::shared_ptr<Point> b {
    PointFactory().Create(points_b,PointOrientation::vertical, {})
  };
  const boost::shared_ptr<Point> c {
    PointFactory().Create(points_c,PointOrientation::vertical, {})
  };
  const boost::shared_ptr<Point> d {
    PointFactory().Create(points_d,PointOrientation::vertical, {})
  };
  const boost::shared_ptr<Point> e {
    PointFactory().Create(points_e,PointOrientation::vertical, {})
  };
  const boost::shared_ptr<Point> f {
    PointFactory().Create(points_f,PointOrientation::vertical, {})
  };
  assert(bottom);
  assert(top);
  assert(a);
  assert(b);
  assert(c);
  assert(d);
  assert(e);
  assert(f);
  bottom->SetIndex(1);
  top->SetIndex(2);
  a->SetIndex(3);
  b->SetIndex(4);
  c->SetIndex(5);
  d->SetIndex(6);
  e->SetIndex(7);
  f->SetIndex(8);
  const std::vector<boost::shared_ptr<Point>> prism {
    top,bottom,a,b,c,d,e,f
  };
  return prism;
}

const std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::PointFactory::CreateTestPrism() noexcept
{
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_a {
    new ribi::ConstCoordinat2D(0.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_b {
    new ribi::ConstCoordinat2D(1.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_c {
    new ribi::ConstCoordinat2D(0.0,1.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_d {
    new ribi::ConstCoordinat2D(0.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_e {
    new ribi::ConstCoordinat2D(1.0,0.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_f {
    new ribi::ConstCoordinat2D(0.0,1.0)
  };

  const boost::shared_ptr<Point> a {
    new Point(co_a)
  };
  const boost::shared_ptr<Point> b {
    new Point(co_b)
  };
  const boost::shared_ptr<Point> c {
    new Point(co_c)
  };
  const boost::shared_ptr<Point> d {
    new Point(co_d)
  };
  const boost::shared_ptr<Point> e {
    new Point(co_e)
  };
  const boost::shared_ptr<Point> f {
    new Point(co_f)
  };
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

#ifndef NDEBUG
void ribi::trim::PointFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::PointFactory::Test");
  TRACE("Finished ribi::trim::PointFactory::Test successfully");
}
#endif

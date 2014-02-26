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
    PointFactory().Create(co_a)
  };
  const boost::shared_ptr<Point> b {
    PointFactory().Create(co_b)
  };
  const boost::shared_ptr<Point> c {
    PointFactory().Create(co_c)
  };
  const boost::shared_ptr<Point> d {
    PointFactory().Create(co_d)
  };
  const boost::shared_ptr<Point> e {
    PointFactory().Create(co_e)
  };
  const boost::shared_ptr<Point> f {
    PointFactory().Create(co_f)
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

const std::vector<boost::shared_ptr<ribi::trim::Point>> ribi::trim::PointFactory::CreateTestTriangle() const noexcept
{
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_a {
    new ribi::ConstCoordinat2D(1.0,2.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_b {
    new ribi::ConstCoordinat2D(2.0,1.0)
  };
  const boost::shared_ptr<ribi::ConstCoordinat2D> co_c {
    new ribi::ConstCoordinat2D(1.0,1.0)
  };

  const boost::shared_ptr<Point> a {
    PointFactory().Create(co_a)
  };
  const boost::shared_ptr<Point> b {
    PointFactory().Create(co_b)
  };
  const boost::shared_ptr<Point> c {
    PointFactory().Create(co_c)
  };

  a->SetZ(1.0 * boost::units::si::meter);
  b->SetZ(1.0 * boost::units::si::meter);
  c->SetZ(1.0 * boost::units::si::meter);
  a->SetIndex(1);
  b->SetIndex(2);
  c->SetIndex(3);
  const std::vector<boost::shared_ptr<Point>> triangle { a,b,c };
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
  const std::vector<boost::shared_ptr<Point>> prism {
    PointFactory().CreateTestPrism()
  };
  assert(prism.size() == 6 && "A prism has 6 points");
  TRACE("Finished ribi::trim::PointFactory::Test successfully");
}
#endif

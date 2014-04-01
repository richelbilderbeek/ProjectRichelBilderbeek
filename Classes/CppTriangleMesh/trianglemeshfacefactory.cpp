#include "trianglemeshfacefactory.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshwinding.h"
#include "trianglemeshwindings.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::trim::FaceFactory::FaceFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::trim::Face> ribi::trim::FaceFactory::Create(
  std::vector<boost::shared_ptr<Point>> points,
  const FaceOrientation any_orientation
) const noexcept
{
  PROFILE_FUNC();
  //Give every Cell some index at creation
  static int cnt = 1;
  const int n = cnt;
  ++cnt;

  assert(points.size() == 3 || points.size() == 4);
  assert(std::count(points.begin(),points.end(),nullptr) == 0);
  #ifndef NDEBUG
  if(!Helper().IsPlane(points))
  {
    TRACE("ERROR");
  }
  #endif

  assert(Helper().IsPlane(points));

  if (!Helper().IsConvex(points))
  {
    TRACE("ERROR");
  }

  #ifndef FIX_ISSUE_168
  assert(Helper().IsConvex(points)
    && "FaceFactory must be called by a sorted and convex collection of points"
    //&& "That way, the incorrect caller can be found"
    //Just use Helper().MakeConvex
  );
  #endif
  /*
  if (!Helper().IsConvex(points))
  {
    #ifndef NDEBUG
    //for (auto p: points) TRACE(*p);
    #endif
    std::sort(points.begin(),points.end());
    while (std::next_permutation(points.begin(),points.end()))
    {
      if (Helper().IsConvex(points))
      {
        TRACE("CONVEX!");
        break;
      }
    }
  }


  #ifndef NDEBUG
  if(!Helper().IsConvex(points))
  {
    TRACE("ERROR: NOT CONVEX");
    //for (auto p: points) TRACE(*p);
    //TRACE("BREAK");
  }
  #endif
  assert(Helper().IsConvex(points));
  */

  const boost::shared_ptr<Face> face(
    new Face(
      points,
      any_orientation,
      n,
      *this
    )
  );
  assert(face);
  for (auto point: face->GetPoints())
  {
    assert(point);
    point->AddConnected(face);
  }

  return face;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrism(
  const CreateVerticalFacesStrategy strategy
) const noexcept
{
  switch (strategy)
  {
    case CreateVerticalFacesStrategy::one_face_per_square : return CreateTestPrismOneFacePerVerticalFace();
    case CreateVerticalFacesStrategy::two_faces_per_square: return CreateTestPrismTwoFacesPerVerticalFace();
  }
  assert(!"FaceFactory::CreateTestPrism: Should not get here");
  throw std::logic_error("FaceFactory::CreateTestPrism: Should not get here");
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrismOneFacePerVerticalFace() const noexcept
{
  const std::vector<boost::shared_ptr<Point>> points {
    PointFactory().CreateTestPrism()
  };
  const std::vector<boost::shared_ptr<Point>> points_bottom { points[0], points[2], points[1] };
  const std::vector<boost::shared_ptr<Point>> points_top    { points[3], points[4], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_a      { points[0], points[1], points[4], points[3] };
  const std::vector<boost::shared_ptr<Point>> points_b      { points[1], points[2], points[5], points[4] };
  const std::vector<boost::shared_ptr<Point>> points_c      { points[2], points[0], points[3], points[5] };

  assert(!Helper().IsClockwiseHorizontal(points_bottom) && "Clockwise from the inside");
  assert(Helper().IsClockwiseHorizontal(points_top));
  assert(Helper().IsConvex(points_bottom));
  assert(Helper().IsConvex(points_top));
  assert(Helper().IsConvex(points_a));
  assert(Helper().IsConvex(points_b));
  assert(Helper().IsConvex(points_c));
  const auto bottom(FaceFactory().Create(points_bottom,FaceOrientation::horizontal));
  const auto top(FaceFactory().Create(points_top,FaceOrientation::horizontal));
  const auto a(FaceFactory().Create(points_a,FaceOrientation::vertical));
  const auto b(FaceFactory().Create(points_b,FaceOrientation::vertical));
  const auto c(FaceFactory().Create(points_c,FaceOrientation::vertical));
  assert(bottom);
  assert(top);
  assert(a);
  assert(b);
  assert(c);
  bottom->SetIndex(1);
  top->SetIndex(2);
  a->SetIndex(3);
  b->SetIndex(4);
  c->SetIndex(5);
  const std::vector<boost::shared_ptr<Face>> prism {
    top,bottom,a,b,c
  };
  return prism;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrismTwoFacesPerVerticalFace() const noexcept
{
  const std::vector<boost::shared_ptr<Point>> points {
    PointFactory().CreateTestPrism()
  };
        std::vector<boost::shared_ptr<Point>> points_bottom { points[0], points[1], points[2] };
        std::vector<boost::shared_ptr<Point>> points_top    { points[3], points[4], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_a      { points[0], points[1], points[4] };
  const std::vector<boost::shared_ptr<Point>> points_b      { points[0], points[3], points[4] };
  const std::vector<boost::shared_ptr<Point>> points_c      { points[1], points[2], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_d      { points[1], points[4], points[5] };
  const std::vector<boost::shared_ptr<Point>> points_e      { points[0], points[2], points[3] };
  const std::vector<boost::shared_ptr<Point>> points_f      { points[2], points[3], points[5] };

  if (!Helper().IsClockwiseHorizontal(points_bottom))
  {
    std::reverse(points_bottom.begin(),points_bottom.end());
  }
  if (!Helper().IsClockwiseHorizontal(points_top))
  {
    std::reverse(points_top.begin(),points_top.end());
  }

  const auto bottom(FaceFactory().Create(points_bottom,FaceOrientation::horizontal));
  const auto top(FaceFactory().Create(points_top,FaceOrientation::horizontal));
  const auto a(FaceFactory().Create(points_a,FaceOrientation::vertical));
  const auto b(FaceFactory().Create(points_b,FaceOrientation::vertical));
  const auto c(FaceFactory().Create(points_c,FaceOrientation::vertical));
  const auto d(FaceFactory().Create(points_d,FaceOrientation::vertical));
  const auto e(FaceFactory().Create(points_e,FaceOrientation::vertical));
  const auto f(FaceFactory().Create(points_f,FaceOrientation::vertical));
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
  const std::vector<boost::shared_ptr<Face>> prism {
    top,bottom,a,b,c,d,e,f
  };
  return prism;
}

boost::shared_ptr<ribi::trim::Face> ribi::trim::FaceFactory::CreateTestSquare(const Winding winding) const noexcept
{


  const std::vector<boost::shared_ptr<Point>> points {
    PointFactory().CreateTestSquare(winding)
  };
  assert(points.size() == 4);

  const boost::shared_ptr<Face> square {
    FaceFactory().Create(
      { points[0],points[1],points[2],points[3] },
      FaceOrientation::horizontal)
  };
  assert(square);
  square->SetIndex(1);
  return square;
}

#ifndef NDEBUG
void ribi::trim::FaceFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::FaceFactory::Test");
  const bool verbose = true;
  if (verbose) TRACE("Create a testing prism");
  for (auto strategy: CreateVerticalFacesStrategies().GetAll())
  {
    const std::vector<boost::shared_ptr<Face>> prism {
      FaceFactory().CreateTestPrism(strategy)
    };
    switch (strategy)
    {
      case CreateVerticalFacesStrategy::one_face_per_square:
        assert(prism.size() == 5 && "A prism has 5 faces (when the vertical faces are kept as squares)");
        break;
      case CreateVerticalFacesStrategy::two_faces_per_square:
        assert(prism.size() == 8 && "A prism has 8 faces (as the vertical faces are split into 2 triangle)");
        break;
    }
  }
  if (verbose) TRACE("Check that incorrect Faces cannot be constructed");
  //(as this test is done in each Face its contructor)
  for (Winding winding: Windings().GetAll())
  {
    const std::vector<boost::shared_ptr<Point>> points {
      PointFactory().CreateTestSquare(winding)
    };
    assert(points.size() == 4);
    assert(Helper().IsConvex(points)
      == (winding == Winding::clockwise || winding == Winding::counter_clockwise)
    );
  }
  if (verbose) TRACE("Check that incorrect Faces cannot be constructed");
  //(as this test is done in each Face its contructor)
  {
    const std::vector<boost::shared_ptr<Point>> points {
      PointFactory().CreateTestInvalid()
    };
    assert(points.size() == 4);
    assert(!Helper().IsConvex(points));
  }
  if (verbose) TRACE("IsConvex, issue 168");
  {
    typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
    boost::shared_ptr<Coordinat2D> c_0(new Coordinat2D(2.35114,3.23607));
    boost::shared_ptr<Coordinat2D> c_1(new Coordinat2D(1.17557,2.35781));
    boost::shared_ptr<Coordinat2D> c_2(new Coordinat2D(2.35114,3.23607));
    boost::shared_ptr<Coordinat2D> c_3(new Coordinat2D(1.17557,2.35781));
    boost::shared_ptr<Point> p0(PointFactory().Create(c_0));
    boost::shared_ptr<Point> p1(PointFactory().Create(c_1));
    boost::shared_ptr<Point> p2(PointFactory().Create(c_2));
    boost::shared_ptr<Point> p3(PointFactory().Create(c_3));
    p0->SetZ(5 * boost::units::si::meter); //Add no comma on purpose
    p1->SetZ(5 * boost::units::si::meter); //Add no comma on purpose
    p2->SetZ(6 * boost::units::si::meter); //Add no comma on purpose
    p3->SetZ(6 * boost::units::si::meter); //Add no comma on purpose
    std::vector<boost::shared_ptr<Point>> points { p0, p1, p2, p3 };
    assert(points.size() == 4);
    assert(!Helper().IsConvex(points) && "This a Z shape and thus not convex");
    Helper().MakeConvex(points);
    assert(Helper().IsConvex(points) && "FaceFactory only accepts convex points");
    const auto face(
      FaceFactory().Create(points,FaceOrientation::vertical)
    );
    assert(face && "But when creating a Face, the points are ordered");
    assert(face->GetIndex() > 0);
    //Shuffle these more often:
    //For every order, it must be possibleto be made convex
    for (int i=0; i!=256; ++i)
    {
      std::random_shuffle(points.begin(),points.end());
      Helper().MakeConvex(points);
      assert(Helper().IsConvex(points));
    }
  }

  if (verbose) TRACE("IsConvex, issue 168");
  {
    typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
    boost::shared_ptr<Coordinat2D> c_0(new Coordinat2D(1.17557,2.35781));
    boost::shared_ptr<Coordinat2D> c_1(new Coordinat2D(2.35114,3.23607));
    boost::shared_ptr<Coordinat2D> c_2(new Coordinat2D(1.17557,2.35781));
    boost::shared_ptr<Coordinat2D> c_3(new Coordinat2D(2.35114,3.23607));
    boost::shared_ptr<Point> p0(PointFactory().Create(c_0));
    boost::shared_ptr<Point> p1(PointFactory().Create(c_1));
    boost::shared_ptr<Point> p2(PointFactory().Create(c_2));
    boost::shared_ptr<Point> p3(PointFactory().Create(c_3));
    p0->SetZ(5 * boost::units::si::meter); //Add no comma on purpose
    p1->SetZ(6 * boost::units::si::meter); //Add no comma on purpose
    p2->SetZ(6 * boost::units::si::meter); //Add no comma on purpose
    p3->SetZ(5 * boost::units::si::meter); //Add no comma on purpose
    std::vector<boost::shared_ptr<Point>> points { p0, p1, p2, p3 };
    assert(points.size() == 4);
    assert(!Helper().IsConvex(points) && "This a Z shape and thus not convex");
    Helper().MakeConvex(points);
    assert(Helper().IsConvex(points) && "FaceFactory only accepts convex points");
    const auto face(
      FaceFactory().Create(points,FaceOrientation::vertical)
    );
    assert(face && "But when creating a Face, the points are ordered");
    assert(face->GetIndex() > 0);
    //Shuffle these more often:
    //For every order, it must be possibleto be made convex
    for (int i=0; i!=256; ++i)
    {
      std::random_shuffle(points.begin(),points.end());
      Helper().MakeConvex(points);
      assert(Helper().IsConvex(points));
    }
  }
  assert("issue 168");
  TRACE("Finished ribi::trim::FaceFactory::Test successfully");
}
#endif


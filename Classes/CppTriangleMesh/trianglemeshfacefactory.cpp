#include "trianglemeshfacefactory.h"

#include <cassert>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshpoint.h"
#include "trianglemeshedge.h"
#include "trianglemeshedgefactory.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshwinding.h"
#include "trianglemeshwindings.h"
#include "trace.h"

ribi::trim::FaceFactory::FaceFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::trim::Face> ribi::trim::FaceFactory::Create(
  const std::vector<boost::shared_ptr<Edge>>& edges,
  const FaceOrientation any_orientation
) const noexcept
{
  std::vector<boost::shared_ptr<Point>> points;
  assert(edges.size() == 3 || edges.size() == 4);
  for (auto edge: edges)
  {
    points.push_back(edge->GetFrom());
    points.push_back(edge->GetTo());
  }
  std::sort(points.begin(),points.end());
  points.erase(std::unique(points.begin(),points.end()),points.end());

  assert(ribi::Geometry().IsPlane(Helper().PointsToCoordinats3D(AddConst(points))));
  return Create(points,any_orientation);
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
    std::sort(points.begin(),points.end());
    while (std::next_permutation(points.begin(),points.end()))
    {
      if (Helper().IsConvex(points))
      {
        break;
      }
    }
  }

  #ifndef NDEBUG
  if(!Helper().IsConvex(points))
  {
    TRACE("ERROR");
  }
  #endif
  assert(Helper().IsConvex(points));

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

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrism() const noexcept
{
  const std::vector<boost::shared_ptr<Edge>> edges {
    EdgeFactory().CreateTestPrism()
  };
  assert(edges.size() == 12);
        std::vector<boost::shared_ptr<Edge>> edges_0 { edges[0], edges[ 1], edges[ 2] };
        std::vector<boost::shared_ptr<Edge>> edges_1 { edges[3], edges[ 4], edges[ 5] };
  const std::vector<boost::shared_ptr<Edge>> edges_2 { edges[0], edges[ 7], edges[ 8] };
  const std::vector<boost::shared_ptr<Edge>> edges_3 { edges[3], edges[ 6], edges[ 7] };
  const std::vector<boost::shared_ptr<Edge>> edges_4 { edges[1], edges[ 9], edges[10] };
  const std::vector<boost::shared_ptr<Edge>> edges_5 { edges[4], edges[ 8], edges[ 9] };
  const std::vector<boost::shared_ptr<Edge>> edges_6 { edges[2], edges[ 6], edges[11] };
  const std::vector<boost::shared_ptr<Edge>> edges_7 { edges[5], edges[10], edges[11] };

  const Coordinat3D center { Helper().CalcCenter(edges) };
  assert(Geometry().IsEqual(center,Helper().CalcCenter(edges)));
  assert(Geometry().IsEqual(center,Helper().CalcCenter(edges)));
  assert(Geometry().IsEqual(center,Helper().CalcCenter(edges)));

  #ifndef NDEBUG
  const auto edgeses { edges_0,edges_1,edges_2,edges_3,edges_4,edges_5,edges_6,edges_7 };
  for (const auto my_edges: edgeses)
  {
    assert(Helper().IsPlane(AddConst(my_edges)));
    const bool a(Helper().IsClockwise(AddConst(my_edges),center));
    const bool b(Helper().IsClockwise(AddConst(my_edges),center));
    assert(a == b);
  }
  #endif

  if (Helper().CalcWindingHorizontal(AddConst(edges_0)) != Winding::clockwise)
  {
    Helper().SetWindingHorizontal(edges_0,Winding::clockwise);
  }
  assert(Helper().CalcWindingHorizontal(AddConst(edges_0)) == Winding::clockwise);
  assert( Helper().IsClockwise(AddConst(edges_0),center));
  //assert(!Helper().IsCounterClockwise(AddConst(edges_0),center));

  if (Helper().CalcWindingHorizontal(AddConst(edges_1)) != Winding::counter_clockwise)
  {
    Helper().SetWindingHorizontal(edges_1,Winding::counter_clockwise);
  }

  //When viewed from above:
  assert(Helper().CalcWindingHorizontal(AddConst(edges_1)) == Winding::counter_clockwise);

  //When viewed from center/below:
  assert(Helper().IsClockwise(AddConst(edges_1),center));

  #ifndef NDEBUG
  for (const auto my_edges: edgeses)
  {
    assert(Helper().IsPlane(AddConst(my_edges)));
    const bool a(Helper().IsClockwise(AddConst(my_edges),center));
    const bool b(Helper().IsClockwise(AddConst(my_edges),center));
    assert(a == b);
  }
  #endif

  const auto bottom(FaceFactory().Create(edges_0,FaceOrientation::horizontal));
  const boost::shared_ptr<Face> top {
    FaceFactory().Create(edges_1,FaceOrientation::horizontal)
  };
  const auto a(FaceFactory().Create(edges_2,FaceOrientation::vertical));
  const boost::shared_ptr<Face> b {
    FaceFactory().Create(edges_3,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> c {
    FaceFactory().Create(edges_4,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> d {
    FaceFactory().Create(edges_5,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> e {
    FaceFactory().Create(edges_6,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> f {
    FaceFactory().Create(edges_7,FaceOrientation::vertical)
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
  const std::vector<boost::shared_ptr<Face>> prism {
    top,bottom,a,b,c,d,e,f
  };
  return prism;
}

std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrismFromPoints() const noexcept
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

  const boost::shared_ptr<Face> bottom {
    FaceFactory().Create(points_bottom,FaceOrientation::horizontal)
  };
  const boost::shared_ptr<Face> top {
    FaceFactory().Create(points_top,FaceOrientation::horizontal)
  };
  const boost::shared_ptr<Face> a {
    FaceFactory().Create(points_a,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> b {
    FaceFactory().Create(points_b,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> c {
    FaceFactory().Create(points_c,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> d {
    FaceFactory().Create(points_d,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> e {
    FaceFactory().Create(points_e,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> f {
    FaceFactory().Create(points_f,FaceOrientation::vertical)
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
  //Create a testing prism
  {
    const std::vector<boost::shared_ptr<Face>> prism {
      FaceFactory().CreateTestPrism()
    };
    assert(prism.size() == 8 && "A prism has 8 faces (as the vertical faces are split into 2 triangle)");
  }
  //Check that incorrect Faces cannot be constructed
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
  //Check that incorrect Faces cannot be constructed
  //(as this test is done in each Face its contructor)
  {
    const std::vector<boost::shared_ptr<Point>> points {
      PointFactory().CreateTestInvalid()
    };
    assert(points.size() == 4);
    assert(!Helper().IsConvex(points));
  }
  //Bug found
  {
    const std::vector<boost::shared_ptr<Edge>> edges {
      EdgeFactory().CreateTestPrism()
    };
    assert(edges.size() == 12);
    const Coordinat3D center { Helper().CalcCenter(edges) };
    std::vector<boost::shared_ptr<Edge>> edges_1 { edges[3], edges[ 4], edges[ 5] };
    if (Helper().CalcWindingHorizontal(AddConst(edges_1)) != Winding::counter_clockwise)
    {
      Helper().SetWindingHorizontal(edges_1,Winding::counter_clockwise);
    }
    TRACE(Geometry().ToStr(center));
    for (const auto edge: edges_1) { TRACE(*edge); }

    //When viewed from above:
    assert(Helper().CalcWindingHorizontal(AddConst(edges_1)) == Winding::counter_clockwise);

    //When viewed from center:
    assert(Helper().IsClockwise(AddConst(edges_1),center));
  }
  TRACE("Finished ribi::trim::FaceFactory::Test successfully");
}
#endif

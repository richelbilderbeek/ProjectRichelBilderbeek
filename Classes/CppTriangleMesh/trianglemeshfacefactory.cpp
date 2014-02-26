#include "trianglemeshfacefactory.h"

#include <cassert>

#include "Shiny.h"

#include "coordinat3d.h"
#include "trianglemeshpoint.h"
#include "trianglemeshedge.h"
#include "trianglemeshedgefactory.h"
#include "trianglemeshface.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshwinding.h"
#include "trace.h"

ribi::trim::FaceFactory::FaceFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::trim::Face> ribi::trim::FaceFactory::Create(
  const std::vector<boost::shared_ptr<Edge>>& edges,
  const FaceOrientation any_orientation
) const noexcept
{
  std::vector<boost::shared_ptr<Point>> points;
  for (auto edge: edges)
  {
    points.push_back(edge->GetFrom());
    points.push_back(edge->GetTo());
  }
  std::sort(points.begin(),points.end());
  points.erase(std::unique(points.begin(),points.end()),points.end());
  return Create(points,any_orientation);
}

const boost::shared_ptr<ribi::trim::Face> ribi::trim::FaceFactory::Create(
  const std::vector<boost::shared_ptr<Point>>& points,
  const FaceOrientation any_orientation
) const noexcept
{
  PROFILE_FUNC();
  //Give every Cell some index at creation
  static int cnt = 1;
  const int n = cnt;
  ++cnt;


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

const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrism() const noexcept
{
  const std::vector<boost::shared_ptr<Edge>> edges {
    EdgeFactory().CreateTestPrism()
  };
  assert(edges.size() == 12);
        std::vector<boost::shared_ptr<Edge>> edges_bottom { edges[0], edges[ 1], edges[ 2] };
        std::vector<boost::shared_ptr<Edge>> edges_top    { edges[3], edges[ 4], edges[ 5] };
  const std::vector<boost::shared_ptr<Edge>> edges_a      { edges[0], edges[ 7], edges[ 8] };
  const std::vector<boost::shared_ptr<Edge>> edges_b      { edges[4], edges[ 7], edges[ 8] };
  const std::vector<boost::shared_ptr<Edge>> edges_c      { edges[2], edges[ 9], edges[10] };
  const std::vector<boost::shared_ptr<Edge>> edges_d      { edges[4], edges[ 8], edges[ 9] };
  const std::vector<boost::shared_ptr<Edge>> edges_e      { edges[2], edges[ 6], edges[11] };
  const std::vector<boost::shared_ptr<Edge>> edges_f      { edges[5], edges[10], edges[11] };

  if (CalcWindingHorizontal(AddConst(edges_bottom)) != Winding::clockwise)
  {
    SetWindingHorizontal(edges_bottom,Winding::clockwise);
  }
  if (CalcWindingHorizontal(AddConst(edges_top)) != Winding::counter_clockwise)
  {
    SetWindingHorizontal(edges_top,Winding::counter_clockwise);
  }
  /*
  if (!IsClockwiseHorizontal(edges_bottom))
  {
    std::reverse(edges_bottom.begin(),edges_bottom.end());
  }
  if (!IsClockwiseHorizontal(edges_top))
  {
    std::reverse(edges_top.begin(),edges_top.end());
  }
  */

  const boost::shared_ptr<Face> bottom {
    FaceFactory().Create(edges_bottom,FaceOrientation::horizontal)
  };
  const boost::shared_ptr<Face> top {
    FaceFactory().Create(edges_top,FaceOrientation::horizontal)
  };
  const boost::shared_ptr<Face> a {
    FaceFactory().Create(edges_a,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> b {
    FaceFactory().Create(edges_b,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> c {
    FaceFactory().Create(edges_c,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> d {
    FaceFactory().Create(edges_d,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> e {
    FaceFactory().Create(edges_e,FaceOrientation::vertical)
  };
  const boost::shared_ptr<Face> f {
    FaceFactory().Create(edges_f,FaceOrientation::vertical)
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

const std::vector<boost::shared_ptr<ribi::trim::Face>> ribi::trim::FaceFactory::CreateTestPrismFromPoints() const noexcept
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

  if (!IsClockwiseHorizontal(points_bottom))
  {
    std::reverse(points_bottom.begin(),points_bottom.end());
  }
  if (!IsClockwiseHorizontal(points_top))
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

#ifndef NDEBUG
void ribi::trim::FaceFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::FaceFactory::Test");
  const std::vector<boost::shared_ptr<Face>> prism {
    FaceFactory().CreateTestPrism()
  };
  assert(prism.size() == 8 && "A prism has 8 faces (as the vertical faces are split into 2 triangle)");
  TRACE("Finished ribi::trim::FaceFactory::Test successfully");
}
#endif

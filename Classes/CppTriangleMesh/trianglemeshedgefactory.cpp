#include "trianglemeshedgefactory.h"

#include <cassert>

#include "Shiny.h"

#include "coordinat3d.h"
#include "trianglemeshpoint.h"
#include "trianglemeshedge.h"
#include "trianglemeshedgefactory.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshhelper.h"
#include "trace.h"

ribi::trim::EdgeFactory::EdgeFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

const boost::shared_ptr<ribi::trim::Edge> ribi::trim::EdgeFactory::Create(
  const std::array<boost::shared_ptr<Point>,2>& points
) const noexcept
{
  PROFILE_FUNC();
  //Give every Cell some index at creation
  static int cnt = 1;
  const int n = cnt;
  ++cnt;


  const boost::shared_ptr<Edge> edge(
    new Edge(
      points,
      n,
      *this
    )
  );
  assert(edge);
  for (auto point: edge->GetPoints())
  {
    assert(point);
    point->AddBelongsTo(edge);
  }

  return edge;
}

const std::vector<boost::shared_ptr<ribi::trim::Edge>> ribi::trim::EdgeFactory::CreateTestPrism() const noexcept
{
  const std::vector<boost::shared_ptr<Point>> points {
    PointFactory().CreateTestPrism()
  };
  const std::array<boost::shared_ptr<Point>,2> points_1 { points[0], points[1] };
  const std::array<boost::shared_ptr<Point>,2> points_2 { points[1], points[2] };
  const std::array<boost::shared_ptr<Point>,2> points_3 { points[2], points[0] };
  const std::array<boost::shared_ptr<Point>,2> points_4 { points[3], points[4] };
  const std::array<boost::shared_ptr<Point>,2> points_5 { points[4], points[5] };
  const std::array<boost::shared_ptr<Point>,2> points_6 { points[5], points[0] };
  const std::array<boost::shared_ptr<Point>,2> points_7 { points[0], points[3] };
  const std::array<boost::shared_ptr<Point>,2> points_8 { points[0], points[4] };
  const std::array<boost::shared_ptr<Point>,2> points_9 { points[1], points[4] };
  const std::array<boost::shared_ptr<Point>,2> points_a { points[1], points[5] };
  const std::array<boost::shared_ptr<Point>,2> points_b { points[2], points[5] };
  const std::array<boost::shared_ptr<Point>,2> points_c { points[2], points[3] };
  const boost::shared_ptr<Edge> edge_1 { EdgeFactory().Create(points_1) };
  const boost::shared_ptr<Edge> edge_2 { EdgeFactory().Create(points_2) };
  const boost::shared_ptr<Edge> edge_3 { EdgeFactory().Create(points_3) };
  const boost::shared_ptr<Edge> edge_4 { EdgeFactory().Create(points_4) };
  const boost::shared_ptr<Edge> edge_5 { EdgeFactory().Create(points_5) };
  const boost::shared_ptr<Edge> edge_6 { EdgeFactory().Create(points_6) };
  const boost::shared_ptr<Edge> edge_7 { EdgeFactory().Create(points_7) };
  const boost::shared_ptr<Edge> edge_8 { EdgeFactory().Create(points_8) };
  const boost::shared_ptr<Edge> edge_9 { EdgeFactory().Create(points_9) };
  const boost::shared_ptr<Edge> edge_a { EdgeFactory().Create(points_a) };
  const boost::shared_ptr<Edge> edge_b { EdgeFactory().Create(points_b) };
  const boost::shared_ptr<Edge> edge_c { EdgeFactory().Create(points_c) };
  assert(edge_1);
  assert(edge_2);
  assert(edge_3);
  assert(edge_4);
  assert(edge_5);
  assert(edge_6);
  assert(edge_7);
  assert(edge_8);
  assert(edge_9);
  assert(edge_a);
  assert(edge_b);
  assert(edge_c);
  edge_1->SetIndex(1);
  edge_2->SetIndex(2);
  edge_3->SetIndex(3);
  edge_4->SetIndex(4);
  edge_5->SetIndex(5);
  edge_6->SetIndex(6);
  edge_7->SetIndex(7);
  edge_8->SetIndex(8);
  edge_9->SetIndex(9);
  edge_a->SetIndex(10);
  edge_b->SetIndex(11);
  edge_c->SetIndex(12);
  const std::vector<boost::shared_ptr<Edge>> prism {
    edge_1,
    edge_2,
    edge_3,
    edge_4,
    edge_5,
    edge_6,
    edge_7,
    edge_8,
    edge_9,
    edge_a,
    edge_b,
    edge_c
  };
  return prism;
}

#ifndef NDEBUG
void ribi::trim::EdgeFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::EdgeFactory::Test");
  const std::vector<boost::shared_ptr<Edge>> prism {
    EdgeFactory().CreateTestPrism()
  };
  assert(prism.size() == 12 && "A prism has 12 edges (as the vertical faces are split into 2 triangle)");
  assert(1==2);
  TRACE("Finished ribi::trim::EdgeFactory::Test successfully");
}
#endif

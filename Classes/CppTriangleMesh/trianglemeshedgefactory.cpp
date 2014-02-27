#include "trianglemeshedgefactory.h"

#include <cassert>
#include <stdexcept>

#include "Shiny.h"

#include "coordinat3d.h"
#include "trianglemeshpoint.h"
#include "trianglemeshedge.h"
#include "trianglemeshedgefactory.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshwindings.h"
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
  //Let the Points know they belong to the Edge
  edge->GetFrom()->AddBelongsTo(edge);
  edge->GetTo()->AddBelongsTo(edge);
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
  const std::array<boost::shared_ptr<Point>,2> points_6 { points[5], points[3] };
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

const std::vector<boost::shared_ptr<ribi::trim::Edge>> ribi::trim::EdgeFactory::CreateTestTriangle(
  const Winding winding) const noexcept
{
  assert(winding != Winding::n_types);


  const std::vector<boost::shared_ptr<Point>> points {
    PointFactory().CreateTestTriangle(winding == Winding::indeterminate ? Winding::clockwise : winding)
  };

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

  assert(std::count(points.begin(),points.end(),nullptr) == 0);
  //clockwise        : 0->1, 1->2, 2->0
  //counter_clockwise: 0->1, 1->2, 2->0
  //indeterminate    : 0->1, 2->1, 2->0

  assert(winding != Winding::clockwise
    || Helper().IsClockwiseHorizontal( {points[0],points[1],points[2]} )
  );
  assert(winding != Winding::counter_clockwise
    || !Helper().IsClockwiseHorizontal( {points[0],points[1],points[2]} )
  );

  const std::array<boost::shared_ptr<Point>,2> points_1{ {points[0], points[1]} };
  assert(points_1[0]);
  assert(points_1[1]);
  std::array<boost::shared_ptr<Point>,2> points_2 {{}};
  switch (winding)
  {
    case Winding::clockwise        :
    case Winding::counter_clockwise: points_2 = { points[1], points[2] }; break;
    case Winding::indeterminate    : points_2 = { points[2], points[1] }; break;
    case Winding::n_types:
      assert(!"Should not get here");
      throw std::logic_error("ribi::trim::EdgeFactory::CreateTestTriangle: invalid Winding");
  }
  assert(points_2[0]);
  assert(points_2[1]);
  const std::array<boost::shared_ptr<Point>,2> points_3 {{points[2], points[0]}};
  assert(points_3[0]);
  assert(points_3[1]);
  const boost::shared_ptr<Edge> edge_1 { EdgeFactory().Create(points_1) };
  const boost::shared_ptr<Edge> edge_2 { EdgeFactory().Create(points_2) };
  const boost::shared_ptr<Edge> edge_3 { EdgeFactory().Create(points_3) };
  assert(edge_1);
  assert(edge_2);
  assert(edge_3);
  edge_1->SetIndex(1);
  edge_2->SetIndex(2);
  edge_3->SetIndex(3);
  const std::vector<boost::shared_ptr<Edge>> triangle {
    edge_1,
    edge_2,
    edge_3
  };
  assert(Helper().CalcWindingHorizontal(AddConst(triangle)) == winding);
  return triangle;
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
  {
    for (const Winding winding: Windings().GetAll())
    {
      const std::vector<boost::shared_ptr<Edge>> triangle {
        EdgeFactory().CreateTestTriangle(winding)
      };
      assert(Helper().CalcWindingHorizontal(AddConst(triangle)) == winding);
    }
  }
  {
    const std::vector<boost::shared_ptr<Edge>> prism {
      EdgeFactory().CreateTestPrism()
    };
    assert(prism.size() == 12 && "A prism has 12 edges (as the vertical faces are split into 2 triangle)");
  }
  TRACE("Finished ribi::trim::EdgeFactory::Test successfully");
}
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshhelper.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>

#include "Shiny.h"

#include "constcoordinat2d.h"
#include "coordinat2d.h"
#include "coordinat3d.h"
#include "geometry.h"
#include "trace.h"
#include "trianglemeshedge.h"
#include "trianglemeshface.h"
#include "trianglemeshpoint.h"

#pragma GCC diagnostic pop

const ribi::Coordinat3D ribi::trim::CalcCenter(const std::vector<boost::shared_ptr<Edge>>& edges) noexcept
{
  Coordinat3D sum;
  for (const auto edge: edges)
  {
    assert(edge);
    assert(edge->GetFrom());
    assert(edge->GetTo());
    Coordinat3D from(
      edge->GetFrom()->GetCoordinat()->GetX(),
      edge->GetFrom()->GetCoordinat()->GetY(),
      edge->GetFrom()->GetZ().value()
    );
    sum += from;
    Coordinat3D to(
      edge->GetTo()->GetCoordinat()->GetX(),
      edge->GetTo()->GetCoordinat()->GetY(),
      edge->GetTo()->GetZ().value()
    );
    sum += to;
  }
  const double n { static_cast<double>(2 * edges.size()) }; //multipled by two, because every edge has two points
  const Coordinat3D center(
    sum.GetX() / n,
    sum.GetY() / n,
    sum.GetZ() / n
  );
  return center;
}

ribi::trim::Winding ribi::trim::CalcWindingHorizontal(const std::vector<boost::shared_ptr<const Edge>>& edges)
{
  //Are Edges nicely ordered
  // 0: A->B (edge[0] has A at its m_points[0] and has B at its m_points[1])
  // 1: B->C (edge[1] has B at its m_points[0] and has C at its m_points[1])
  // 2: C->A (edge[2] has C at its m_points[0] and has A at its m_points[1])
  const int n_edges { static_cast<int>(edges.size()) };

  //Check for indeterminate ordering
  for (int i=0; i!=n_edges; ++i)
  {
    const int j { (i + 1) % n_edges };
    assert(i < static_cast<int>(edges.size()));
    assert(j < static_cast<int>(edges.size()));
    if (edges[i]->GetTo() != edges[j]->GetFrom())
    {
      return Winding::indeterminate;
    }
  }
  //Extract the points
  std::vector<Coordinat3D> points;
  for (int i=0; i!=n_edges; ++i)
  {
    Coordinat3D co(
      edges[i]->GetFrom()->GetCoordinat()->GetX(),
      edges[i]->GetFrom()->GetCoordinat()->GetY(),
      edges[i]->GetFrom()->GetZ().value()
    );
    points.push_back(co);
  }
  assert(points.size() == edges.size());

  return Geometry().IsClockwiseHorizontal(points)
    ? Winding::clockwise
    : Winding::counter_clockwise
  ;
}

double ribi::trim::GetAngle(const boost::shared_ptr<const Point> point) noexcept
{
  return Geometry().GetAngle(point->GetCoordinat()->GetX(),point->GetCoordinat()->GetY());
}

bool ribi::trim::IsClockwiseHorizontal(
  const boost::shared_ptr<const Edge> edge,
  const Coordinat3D& center
  ) noexcept
{
  const bool is_clockwise {
    Geometry().IsClockwise(
      Geometry().GetAngle(
        edge->GetFrom()->GetCoordinat()->GetX() - center.GetX(),
        edge->GetFrom()->GetCoordinat()->GetY() - center.GetY()
      ),
      Geometry().GetAngle(
        edge->GetTo()->GetCoordinat()->GetX() - center.GetX(),
        edge->GetTo()->GetCoordinat()->GetY() - center.GetY()
      )
    )
  };
  return is_clockwise;
}

bool ribi::trim::IsClockwiseHorizontal(const std::vector<boost::shared_ptr<Point>>& points) noexcept
{
  assert(points.size() == 3);
  double center_x = 0.0;
  double center_y = 0.0;
  for (const auto point: points)
  {
    center_x += point->GetCoordinat()->GetX();
    center_y += point->GetCoordinat()->GetY();
  }
  center_x /= static_cast<double>(points.size());
  center_y /= static_cast<double>(points.size());

  //const double pi  = boost::math::constants::pi<double>();
  //const double tau = boost::math::constants::two_pi<double>();
  const bool a {
    Geometry().IsClockwise(
      Geometry().GetAngle(
        points[0]->GetCoordinat()->GetX() - center_x,
        points[0]->GetCoordinat()->GetY() - center_y
      ),
      Geometry().GetAngle(
        points[1]->GetCoordinat()->GetX() - center_x,
        points[1]->GetCoordinat()->GetY() - center_y
      )
    )
  };
  const bool b {
    Geometry().IsClockwise(
      Geometry().GetAngle(
        points[1]->GetCoordinat()->GetX() - center_x,
        points[1]->GetCoordinat()->GetY() - center_y
      ),
      Geometry().GetAngle(
        points[2]->GetCoordinat()->GetX() - center_x,
        points[2]->GetCoordinat()->GetY() - center_y
      )
    )
  };
  //TRACE(a);
  //TRACE(b);
  const bool is_clockwise { a && b };
  //TRACE(is_clockwise);
  return is_clockwise;
}

void ribi::trim::SetWindingHorizontal(std::vector<boost::shared_ptr<Edge>>& edges,const Winding winding)
{
  assert(CalcWindingHorizontal(AddConst(edges)) != winding);
  switch(winding)
  {
    case Winding::indeterminate:
    {
      edges[1]->Reverse();
    }
    break;
    case Winding::clockwise:
    {
      assert(edges.size() == 3 && "Otherwise I am not sure this will work");
      const Coordinat3D center { CalcCenter(edges) };
      const int n_edges { static_cast<int>(edges.size()) };
      for (int i=0; i!=n_edges; ++i)
      {
        //Fix winding
        if (!IsClockwiseHorizontal(edges[i],center)) { edges[i]->Reverse(); }
        assert(IsClockwiseHorizontal(edges[i],center));
        //Fix ordering of elements
        if (edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo()) continue;
        //Try to swap the next element's order
        assert(i + 1 < n_edges);
        if (edges[i+1]->GetFrom() != edges[i]->GetTo()) { edges[i+1]->Reverse(); }
        if (edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo()) continue;
        //Swap the next and its next elements
        assert(i + 2 < n_edges);
        if (edges[i+1]->GetFrom() != edges[i]->GetTo()) { std::swap(edges[i+1],edges[i+2]); }
        if (edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo()) continue;
        //Try to swap the next element's order
        if (edges[i+1]->GetFrom() != edges[i]->GetTo()) { edges[i+1]->Reverse(); }
        assert(edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo());
      }
    }
    break;
    case Winding::counter_clockwise:
    {
      assert(edges.size() == 3 && "Otherwise I am not sure this will work");
      const Coordinat3D center { CalcCenter(edges) };
      const int n_edges { static_cast<int>(edges.size()) };
      for (int i=0; i!=n_edges; ++i)
      {
        //Fix winding
        if (IsClockwiseHorizontal(edges[i],center)) { edges[i]->Reverse(); }
        assert(!IsClockwiseHorizontal(edges[i],center));
        //Fix ordering of elements
        if (edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo()) continue;
        //Try to swap the next element's order
        assert(i + 1 < n_edges);
        if (edges[i+1]->GetFrom() != edges[i]->GetTo()) { edges[i+1]->Reverse(); }
        if (edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo()) continue;
        //Swap the next and its next elements
        assert(i + 2 < n_edges);
        if (edges[i+1]->GetFrom() != edges[i]->GetTo()) { std::swap(edges[i+1],edges[i+2]); }
        if (edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo()) continue;
        //Try to swap the next element's order
        if (edges[i+1]->GetFrom() != edges[i]->GetTo()) { edges[i+1]->Reverse(); }
        assert(edges[(i+1) % n_edges]->GetFrom() == edges[i]->GetTo());
      }
    }
    break;
  }
  assert(CalcWindingHorizontal(AddConst(edges)) == winding);
}

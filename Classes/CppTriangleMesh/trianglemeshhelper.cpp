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
#include "trianglemeshpointfactory.h"

#pragma GCC diagnostic pop

ribi::trim::Helper::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}


const ribi::Coordinat3D ribi::trim::Helper::CalcCenter(
  const std::vector<boost::shared_ptr<Edge>>& edges
) const noexcept
{
  std::vector<boost::shared_ptr<Point>> points;
  for (const auto edge: edges)
  {
    points.push_back(edge->GetFrom());
    points.push_back(edge->GetTo());
  }
  return CalcCenter(points);
}

const ribi::Coordinat3D ribi::trim::Helper::CalcCenter(const std::vector<boost::shared_ptr<Point>>& points) const noexcept
{
  Coordinat3D sum;
  for (const auto point: points)
  {
    assert(point);
    Coordinat3D coordinat(
      point->GetCoordinat()->GetX(),
      point->GetCoordinat()->GetY(),
      point->CanGetZ() ? point->GetZ().value() : 0.0
    );
    sum += coordinat;
  }
  const double n { static_cast<double>(points.size()) };
  const Coordinat3D center(
    sum.GetX() / n,
    sum.GetY() / n,
    sum.GetZ() / n
  );
  return center;

}

const ribi::Coordinat3D ribi::trim::Helper::CalcNormal(
  const std::vector<boost::shared_ptr<Edge>>& edges
) const noexcept
{
  assert(edges.size() == 3);
  assert(edges[0]->GetTo() == edges[1]->GetFrom());
  assert(edges[1]->GetTo() == edges[2]->GetFrom());
  assert(edges[2]->GetTo() == edges[0]->GetFrom());

  return ::ribi::CalcNormal(
    Coordinat3D(
      edges[0]->GetFrom()->GetCoordinat()->GetX(),
      edges[0]->GetFrom()->GetCoordinat()->GetY(),
      edges[0]->GetFrom()->CanGetZ() ? edges[0]->GetFrom()->GetZ().value() : 0.0
    ),
    Coordinat3D(
      edges[1]->GetFrom()->GetCoordinat()->GetX(),
      edges[1]->GetFrom()->GetCoordinat()->GetY(),
      edges[1]->GetFrom()->CanGetZ() ? edges[1]->GetFrom()->GetZ().value() : 0.0
    ),
    Coordinat3D(
      edges[2]->GetFrom()->GetCoordinat()->GetX(),
      edges[2]->GetFrom()->GetCoordinat()->GetY(),
      edges[2]->GetFrom()->CanGetZ() ? edges[2]->GetFrom()->GetZ().value() : 0.0
    )
  );
}


ribi::trim::Winding ribi::trim::Helper::CalcWindingHorizontal(
  const std::vector<boost::shared_ptr<const Edge>>& edges
) const noexcept
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
    //TRACE(co);
    points.push_back(co);
  }

  assert(points.size() == edges.size());

  //return Geometry().IsClockwise(points, Co`ordinat3D(0.0,0.0,1.0))
  return Geometry().IsClockwiseHorizontal(points)
    ? Winding::clockwise
    : Winding::counter_clockwise
  ;
}

const std::set<ribi::Coordinat3D> ribi::trim::Helper::ExtractCoordinats(
  const std::vector<boost::shared_ptr<Point>>& points
)
{
  PROFILE_FUNC();
  std::set<ribi::Coordinat3D> s;
  for (const auto point: points)
  {
    if (!point->CanGetZ())
    {
      TRACE("Extract these coordinats later: the Face must be assigned to a Layer first");
    }
    assert(point->CanGetZ());
    const ribi::Coordinat3D c(
      point->GetCoordinat()->GetX(),
      point->GetCoordinat()->GetY(),
      point->GetZ().value()
    );
    s.insert(s.begin(),c);
  }

  return s;
}

const std::set<ribi::Coordinat3D> ribi::trim::Helper::ExtractCoordinats(const ribi::trim::Face& face)
{
  face.DoExtractCoordinats();
  return face.GetCoordinats();
}

double ribi::trim::Helper::GetAngle(const boost::shared_ptr<const Point> point) const noexcept
{
  return Geometry().GetAngle(point->GetCoordinat()->GetX(),point->GetCoordinat()->GetY());
}

bool ribi::trim::Helper::IsClockwise(
  const std::vector<boost::shared_ptr<const Edge>>& edges,
  const Coordinat3D& observer
) const noexcept
{
  std::vector<Coordinat3D> coordinats;
  for (auto edge: edges)
  {
    Coordinat3D coordinat(
      edge->GetFrom()->GetCoordinat()->GetX(),
      edge->GetFrom()->GetCoordinat()->GetY(),
      edge->GetFrom()->GetZ().value()
    );
    coordinats.push_back(coordinat);
  }
  return Geometry().IsClockwise(coordinats,observer);
}

bool ribi::trim::Helper::IsClockwise(
  const std::vector<boost::shared_ptr<const Point>>& points,
  const Coordinat3D& observer) const noexcept
{
  std::vector<Coordinat3D> coordinats;
  for (auto point: points)
  {
    Coordinat3D coordinat(
      point->GetCoordinat()->GetX(),
      point->GetCoordinat()->GetY(),
      point->CanGetZ() ? point->GetZ().value() : 0.0
    );
    coordinats.push_back(coordinat);
  }
  return Geometry().IsClockwise(coordinats,observer);
}

bool ribi::trim::Helper::IsClockwiseHorizontal(
  const boost::shared_ptr<const Edge> edge,
  const Coordinat3D& observer
  ) const noexcept
{
  const bool is_clockwise {
    Geometry().IsClockwise(
      Geometry().GetAngle(
        edge->GetFrom()->GetCoordinat()->GetX() - observer.GetX(),
        edge->GetFrom()->GetCoordinat()->GetY() - observer.GetY()
      ),
      Geometry().GetAngle(
        edge->GetTo()->GetCoordinat()->GetX() - observer.GetX(),
        edge->GetTo()->GetCoordinat()->GetY() - observer.GetY()
      )
    )
  };
  return is_clockwise;
}

bool ribi::trim::Helper::IsClockwiseHorizontal(
  const std::vector<boost::shared_ptr<Point>>& points
) const noexcept
{
  assert(points.size() == 3);
  const Coordinat3D center { CalcCenter(points) };
  const double center_x { center.GetX() };
  const double center_y { center.GetY() };

  //const double pi  = boost::math::constants::pi<double>();
  //const double tau = boost::math::constants::two_pi<double>();
  const std::vector<double> angles {
    Geometry().GetAngle(
      points[0]->GetCoordinat()->GetX() - center_x,
      points[0]->GetCoordinat()->GetY() - center_y
    ),
    Geometry().GetAngle(
      points[1]->GetCoordinat()->GetX() - center_x,
      points[1]->GetCoordinat()->GetY() - center_y
    ),
    Geometry().GetAngle(
      points[2]->GetCoordinat()->GetX() - center_x,
      points[2]->GetCoordinat()->GetY() - center_y
    )
  };
  const bool a { Geometry().IsClockwise(angles[0],angles[1]) };
  const bool b { Geometry().IsClockwise(angles[1],angles[2]) };
  const bool is_clockwise { a && b };
  return is_clockwise;
}

bool ribi::trim::Helper::IsHorizontal(const ribi::trim::Face& face) noexcept
{
  const bool answer_1 = face.GetOrientation() == FaceOrientation::horizontal;

  const std::set<ribi::Coordinat3D> coordinats { ExtractCoordinats(face) };

  typedef std::set<ribi::Coordinat3D>::iterator Iterator;
  typedef std::pair<Iterator,Iterator> Pair;
  const Pair xs {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const ribi::Coordinat3D& lhs,const ribi::Coordinat3D& rhs)
      {
        return lhs.GetX() < rhs.GetX();
      }
    )
  };

  const double dx { std::abs((*xs.first).GetX() - (*xs.second).GetX()) };

  const Pair ys {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const ribi::Coordinat3D& lhs,const ribi::Coordinat3D& rhs)
      {
        return lhs.GetY() < rhs.GetY();
      }
    )
  };

  const double dy { std::abs((*ys.first).GetY() - (*ys.second).GetY()) };

  const Pair zs {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const ribi::Coordinat3D& lhs,const ribi::Coordinat3D& rhs)
      {
        return lhs.GetZ() < rhs.GetZ();
      }
    )
  };
  const double dz { std::abs((*zs.first).GetZ() - (*zs.second).GetZ()) };

  const bool answer_2 { dz * 1000.0 < dx && dz * 1000.0 < dy };

  assert(answer_1 == answer_2);
  return answer_1;
}

bool ribi::trim::Helper::IsVertical(const ribi::trim::Face& face) noexcept
{
  const bool answer_1 = face.GetOrientation() == FaceOrientation::vertical;
  const bool answer_2 = !IsHorizontal(face);
  assert(answer_1 == answer_2);
  return answer_1;
}

void ribi::trim::Helper::SetWindingHorizontal(
  std::vector<boost::shared_ptr<Edge>>& edges,
  const Winding winding
) const noexcept
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
    case Winding::n_types:
      assert(!"Should never get here");
      throw std::logic_error("ribi::trim::Helper::SetWindingHorizontal: unknown Winding");
  }
  assert(CalcWindingHorizontal(AddConst(edges)) == winding);
}

#ifndef NDEBUG
void ribi::trim::Helper::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Helper::Point::Test");
  //CalcCenter
  //CalcWindingHorizontal
  //GetAngle
  const Helper h;
  const double pi { boost::math::constants::pi<double>() };
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(0.0,-1.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle = h.GetAngle(point); //North
    const double expected = 0.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(1.0,-1.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //North-East
    const double expected = 0.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(1.0,0.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //East
    const double expected = 0.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(1.0,1.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //South-East
    const double expected = 0.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(0.0,1.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //South
    const double expected = 1.0 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(-1.0,1.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //South-West
    const double expected = 1.25 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(-1.0,0.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //West
    const double expected = 1.5 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  {
    const boost::shared_ptr<const ConstCoordinat2D> coordinat {
      new ConstCoordinat2D(-1.0,-1.0)
    };
    const boost::shared_ptr<Point> point {
      PointFactory().Create(coordinat)
    };
    const double angle =  h.GetAngle(point); //North-West
    const double expected = 1.75 * pi;
    assert(std::abs(angle-expected) < 0.01);
  }
  //IsClockwiseHorizontal 1
  //IsClockwiseHorizontal 2
  //IsClockwiseVertical
  //SetWindingHorizontal
  //
  TRACE("Finished ribi::trim::Helper::Point::Test successfully");
}
#endif

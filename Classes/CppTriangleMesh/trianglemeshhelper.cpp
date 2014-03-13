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

//
#include "geometry.h"
#include "trace.h"
#include "trianglemeshedge.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshpointfactory.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::trim::Helper::Helper::Helper()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Helper::CalcCenter(
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

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Helper::CalcCenter(
  const std::vector<boost::shared_ptr<Point>>& points
) const noexcept
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Value;
  using boost::geometry::get;

  assert(!points.empty());
  Value sum(0.0,0.0,0.0);
  for (const auto point: points)
  {
    assert(point);
    assert(point->GetCoordinat());
    assert(!std::isnan( get<0>(*point->GetCoordinat())));
    assert(!std::isnan( get<1>(*point->GetCoordinat())));
    assert(!point->CanGetZ() || !std::isnan(point->GetZ().value()));
    const Value coordinat(
      get<0>(*point->GetCoordinat()),
      get<1>(*point->GetCoordinat()),
      point->CanGetZ() ? point->GetZ().value() : 0.0
    );
    sum += coordinat;
  }
  const double n { static_cast<double>(points.size()) };
  return sum / n;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Helper::CalcNormal(
  const std::vector<boost::shared_ptr<Edge>>& edges
) const noexcept
{
  using boost::geometry::get;
  assert(edges.size() == 3);
  assert(edges[0]->GetTo() == edges[1]->GetFrom());
  assert(edges[1]->GetTo() == edges[2]->GetFrom());
  assert(edges[2]->GetTo() == edges[0]->GetFrom());

  return Geometry().CalcNormal(
    Coordinat3D(
      get<0>(*edges[0]->GetFrom()->GetCoordinat()),
      get<1>(*edges[0]->GetFrom()->GetCoordinat()),
      edges[0]->GetFrom()->CanGetZ() ? edges[0]->GetFrom()->GetZ().value() : 0.0
    ),
    Coordinat3D(
      get<0>(*edges[1]->GetFrom()->GetCoordinat()),
      get<1>(*edges[1]->GetFrom()->GetCoordinat()),
      edges[1]->GetFrom()->CanGetZ() ? edges[1]->GetFrom()->GetZ().value() : 0.0
    ),
    Coordinat3D(
      get<0>(*edges[2]->GetFrom()->GetCoordinat()),
      get<1>(*edges[2]->GetFrom()->GetCoordinat()),
      edges[2]->GetFrom()->CanGetZ() ? edges[2]->GetFrom()->GetZ().value() : 0.0
    )
  );
}

ribi::trim::Winding ribi::trim::Helper::CalcWindingHorizontal(
  const std::vector<boost::shared_ptr<const Point>>& points
) const noexcept
{
  using boost::geometry::get;

  const int n_points { static_cast<int>(points.size()) };

  //Extract the points
  std::vector<Coordinat3D> coordinats;
  for (int i=0; i!=n_points; ++i)
  {
    Coordinat3D co(
      get<0>(*points[i]->GetCoordinat()),
      get<1>(*points[i]->GetCoordinat()),
      points[i]->GetZ().value()
    );
    //TRACE(co);
    coordinats.push_back(co);
  }

  assert(coordinats.size() == coordinats.size());

  const bool a { Geometry().IsClockwiseHorizontal(coordinats) };
  const bool b { Geometry().IsCounterClockwiseHorizontal(coordinats) };
  if ( a && !b) return Winding::clockwise;
  if (!a &&  b) return Winding::counter_clockwise;
  return Winding::indeterminate;
}

ribi::trim::Winding ribi::trim::Helper::CalcWindingHorizontal(
  const std::vector<boost::shared_ptr<const Edge>>& edges
) const noexcept
{
  using boost::geometry::get;

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
  std::vector<Coordinat3D> coordinats;
  for (int i=0; i!=n_edges; ++i)
  {
    Coordinat3D co(
      get<0>(*edges[i]->GetFrom()->GetCoordinat()),
      get<1>(*edges[i]->GetFrom()->GetCoordinat()),
      edges[i]->GetFrom()->GetZ().value()
    );
    //TRACE(co);
    coordinats.push_back(co);
  }

  assert(coordinats.size() == edges.size());

  const bool a { Geometry().IsClockwiseHorizontal(coordinats) };
  const bool b { Geometry().IsCounterClockwiseHorizontal(coordinats) };
  if ( a && !b) return Winding::clockwise;
  if (!a &&  b) return Winding::counter_clockwise;
  return Winding::indeterminate;
}

std::set<
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>,
  std::function<
    bool(
      boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>,
      boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>
    )
  >
>
  ribi::trim::Helper::ExtractCoordinats(
  const std::vector<boost::shared_ptr<Point>>& points
)
{
  PROFILE_FUNC();
  using boost::geometry::get;

  std::set<Coordinat3D,std::function<bool(Coordinat3D,Coordinat3D)>> s(
    [](const Coordinat3D& lhs, const Coordinat3D& rhs)
    {
      return ribi::trim::Less(lhs,rhs);
    }
  );
  for (const auto point: points)
  {
    if (!point->CanGetZ())
    {
      TRACE("Extract these coordinats later: the Face must be assigned to a Layer first");
    }
    assert(point->CanGetZ());
    const Coordinat3D c(
      get<0>(*point->GetCoordinat()),
      get<1>(*point->GetCoordinat()),
      point->GetZ().value()
    );
    s.insert(s.begin(),c);
  }

  return s;
}


ribi::trim::Helper::Coordinat3dSet ribi::trim::Helper::ExtractCoordinats(const ribi::trim::Face& face)
{
  face.DoExtractCoordinats();
  return face.GetCoordinats();
}

double ribi::trim::Helper::GetAngle(const boost::shared_ptr<const Point> point) const noexcept
{
  return Geometry().GetAngle(
    boost::geometry::get<0>(*point->GetCoordinat()),
    boost::geometry::get<1>(*point->GetCoordinat())
  );
}

bool ribi::trim::Helper::IsClockwise(
  const std::vector<boost::shared_ptr<const Edge>>& edges,
  const Coordinat3D& observer
) const noexcept
{
  using boost::geometry::get;
  std::vector<Coordinat3D> coordinats;
  for (auto edge: edges)
  {
    Coordinat3D coordinat(
      get<0>(*edge->GetFrom()->GetCoordinat()),
      get<1>(*edge->GetFrom()->GetCoordinat()),
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
  using boost::geometry::get;
  std::vector<Coordinat3D> coordinats;
  for (auto point: points)
  {
    Coordinat3D coordinat(
      get<0>(*point->GetCoordinat()),
      get<1>(*point->GetCoordinat()),
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
  using boost::geometry::get;
  const auto observer_x(boost::geometry::get<0>(observer));
  const auto observer_y(boost::geometry::get<1>(observer));
  const auto is_clockwise(
    Geometry().IsClockwise(
      Geometry().GetAngle(
        get<0>(*edge->GetFrom()->GetCoordinat()) - observer_x,
        get<1>(*edge->GetFrom()->GetCoordinat()) - observer_y
      ),
      Geometry().GetAngle(
        get<0>(*edge->GetTo()->GetCoordinat()) - observer_x,
        get<1>(*edge->GetTo()->GetCoordinat()) - observer_y
      )
    )
  );
  return is_clockwise;
}

bool ribi::trim::Helper::IsClockwiseHorizontal(
  const std::vector<boost::shared_ptr<Point>>& points
) const noexcept
{
  using boost::geometry::get;
  assert(points.size() == 3);
  assert(points[0]);
  assert(points[1]);
  assert(points[2]);
  assert(points[0]->GetCoordinat());
  assert(points[1]->GetCoordinat());
  assert(points[2]->GetCoordinat());
  const Coordinat3D center(CalcCenter(points));
  const auto center_x(boost::geometry::get<0>(center));
  const auto center_y(boost::geometry::get<1>(center));
  assert(!std::isnan(center_x));
  assert(!std::isnan(center_y));

  //const double pi  = boost::math::constants::pi<double>();
  //const double tau = boost::math::constants::two_pi<double>();
  const std::vector<double> angles {
    Geometry().GetAngle(
      get<0>(*points[0]->GetCoordinat()) - center_x,
      get<1>(*points[0]->GetCoordinat()) - center_y
    ),
    Geometry().GetAngle(
      get<0>(*points[1]->GetCoordinat()) - center_x,
      get<1>(*points[1]->GetCoordinat()) - center_y
    ),
    Geometry().GetAngle(
      get<0>(*points[2]->GetCoordinat()) - center_x,
      get<1>(*points[2]->GetCoordinat()) - center_y
    )
  };
  const bool a = Geometry().IsClockwise(angles[0],angles[1]);
  const bool b = Geometry().IsClockwise(angles[1],angles[2]);
  const bool is_clockwise { a && b };
  return is_clockwise;
}

bool ribi::trim::Helper::IsHorizontal(const ribi::trim::Face& face) noexcept
{
  using boost::geometry::get;
  const bool answer_1 = face.GetOrientation() == FaceOrientation::horizontal;

  const auto coordinats(ExtractCoordinats(face));

  typedef std::set<Coordinat3D>::iterator Iterator;
  typedef std::pair<Iterator,Iterator> Pair;
  const Pair xs(
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const Coordinat3D& lhs,const Coordinat3D& rhs)
      {
        return get<0>(lhs) < get<0>(rhs);
      }
    )
  );

  const double dx = std::abs(get<0>(*xs.first) - get<0>(*xs.second));

  const Pair ys {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const Coordinat3D& lhs,const Coordinat3D& rhs)
      {
        return get<1>(lhs) < get<1>(rhs);
      }
    )
  };

  const double dy = std::abs(get<1>(*ys.first) - get<1>(*ys.second));

  const Pair zs {
    std::minmax_element(coordinats.begin(),coordinats.end(),
      [](const Coordinat3D& lhs,const Coordinat3D& rhs)
      {
        return get<2>(lhs) < get<2>(rhs);
      }
    )
  };

  const double dz = std::abs(get<2>(*zs.first) - get<2>(*zs.second));
  //const double dz { std::abs((*zs.first).GetZ() - (*zs.second).GetZ()) };

  const bool answer_2
    = dz == 0.0 || (dz * 1000.0 < dx && dz * 1000.0 < dy);

  if (answer_1 != answer_2)
  {
    TRACE("ERROR");
  }

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
  typedef boost::geometry::model::d2::point_xy<double> ConstCoordinat2D;
  using boost::geometry::get;

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

std::string ribi::trim::Helper::ToXml(const boost::geometry::model::d2::point_xy<double>& p) const noexcept
{
  using boost::geometry::get;
  std::stringstream s;
  s
    << ribi::xml::ToXml("0",get<0>(p))
    << ribi::xml::ToXml("1",get<1>(p))
  ;

  std::stringstream t;
  t << ribi::xml::ToXml("Coordinat2D",s.str());
  return t.str();
}

bool ribi::trim::operator<(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs) noexcept
{
  using boost::geometry::get;
  if (get<0>(lhs) < get<0>(rhs)) return true;
  if (get<0>(lhs) > get<0>(rhs)) return false;

  if (get<1>(lhs) < get<1>(rhs)) return true;
  if (get<1>(lhs) > get<1>(rhs)) return false;

  return get<2>(lhs) < get<2>(rhs);
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::operator+(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  typedef std::remove_const<std::remove_reference<decltype(lhs)>::type>::type R_t;
  using boost::geometry::get;
  return R_t(
    get<0>(lhs) + get<0>(rhs),
    get<1>(lhs) + get<1>(rhs),
    get<2>(lhs) + get<2>(rhs)
  );
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& ribi::trim::operator+=(
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  lhs = lhs + rhs;
  return lhs;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& ribi::trim::operator/=(
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p,
  const double factor
) noexcept
{
  p = p / factor;
  return p;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::operator/(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p,
  const double factor
) noexcept
{
  typedef std::remove_const<std::remove_reference<decltype(p)>::type>::type R_t;
  using boost::geometry::get;
  return R_t(
    get<0>(p) / factor,
    get<1>(p) / factor,
    get<2>(p) / factor
  );
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Add(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept { return lhs + rhs; }

bool ribi::trim::Less(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  return ribi::trim::operator <(lhs,rhs);
  //return lhs < rhs;
}

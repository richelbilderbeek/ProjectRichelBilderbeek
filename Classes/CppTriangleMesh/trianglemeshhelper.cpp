#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglemeshhelper.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/math/constants/constants.hpp>


#include "geometry.h"
#include "trace.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshpointfactory.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::trim::Helper::Helper::Helper() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Helper::CalcCenter(
  const std::vector<boost::shared_ptr<Point>>& points
) const noexcept
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Value;
  using boost::geometry::get;

  assert(!points.empty());
  Value sum(0.0,0.0,0.0);
  for (const auto& point: points)
  {
    assert(point);
    assert(point->GetCoordinat());
    assert(!std::isnan( get<0>(*point->GetCoordinat())));
    assert(!std::isnan( get<1>(*point->GetCoordinat())));
    assert(!point->CanGetZ() || !std::isnan(point->GetZ().value()));
    sum += point->GetCoordinat3D();
  }
  const double n { static_cast<double>(points.size()) };
  return sum / n;
}

std::vector<ribi::trim::Helper::Coordinat2D> ribi::trim::Helper::CalcProjection(
  const std::vector<boost::shared_ptr<const ribi::trim::Point>>& v) const
{
  
  return Geometry().CalcProjection(PointsToCoordinats3D(v));
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
    coordinats.push_back(co);
  }

  assert(coordinats.size() == coordinats.size());

  const bool a { Geometry().IsClockwiseCartesianHorizontal(coordinats) };
  const bool b { Geometry().IsCounterClockwiseCartesianHorizontal(coordinats) };
  if ( a && !b) return Winding::clockwise;
  if (!a &&  b) return Winding::counter_clockwise;
  return Winding::indeterminate;
}

ribi::trim::Helper::FaceSet ribi::trim::Helper::CreateEmptyFaceSet() const noexcept
{
  ribi::trim::Helper::FaceSet s(OrderByIndex());
  return s;
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
  const std::vector<boost::shared_ptr<const Point>>& points
) const noexcept
{
  
  using boost::geometry::get;

  std::set<Coordinat3D,std::function<bool(Coordinat3D,Coordinat3D)>> s(
    [](const Coordinat3D& lhs, const Coordinat3D& rhs)
    {
      return ribi::trim::Less(lhs,rhs);
    }
  );
  for (const auto& point: points)
  {
    if (!point->CanGetZ())
    {
      TRACE("Extract these coordinats later: the Face must be assigned to a Layer first");
    }
    assert(point->CanGetZ());
    const Coordinat3D c(
      point->GetCoordinat3D()
    );
    s.insert(s.begin(),c);
  }
  return s;
}

ribi::trim::Helper::Coordinat3dSet ribi::trim::Helper::ExtractCoordinats(const ribi::trim::Face& face) const noexcept
{
  face.DoExtractCoordinats();
  return face.GetCoordinats();
}

/*
double ribi::trim::Helper::GetAngle(const boost::shared_ptr<const Point> point) const noexcept
{
  
  return Geometry().GetAngle(
    boost::geometry::get<0>(*point->GetCoordinat()),
    boost::geometry::get<1>(*point->GetCoordinat())
  );
}
*/

std::vector<std::vector<int>> ribi::trim::Helper::GetPermutations(std::vector<int> v) const noexcept
{
  std::sort(std::begin(v),std::end(v));
  std::vector<std::vector<int>> w;
  w.push_back(v);
  while(std::next_permutation(std::begin(v),std::end(v)))
  {
    w.push_back(v);
  }
  return w;
}

bool ribi::trim::Helper::IsClockwise(
  const std::vector<boost::shared_ptr<const Point>>& points,
  const Coordinat3D& observer) const noexcept
{
  
  std::vector<Coordinat3D> coordinats;
  for (const auto& point: points)
  {
    assert(point);
    coordinats.push_back(point->GetCoordinat3D());
  }
  assert(Geometry().IsPlane(coordinats));
  return Geometry().IsClockwiseCartesian(coordinats,observer);
}

bool ribi::trim::Helper::IsClockwise(
  const std::vector<boost::shared_ptr<Point>>& points,
  const Coordinat3D& observer) const noexcept
{
  return IsClockwise(AddConst(points),observer);
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

  const std::vector<double> angles {
    Geometry().GetAngleClockCartesian(
      get<0>(*points[0]->GetCoordinat()) - center_x,
      get<1>(*points[0]->GetCoordinat()) - center_y
    ),
    Geometry().GetAngleClockCartesian(
      get<0>(*points[1]->GetCoordinat()) - center_x,
      get<1>(*points[1]->GetCoordinat()) - center_y
    ),
    Geometry().GetAngleClockCartesian(
      get<0>(*points[2]->GetCoordinat()) - center_x,
      get<1>(*points[2]->GetCoordinat()) - center_y
    )
  };
  const bool a = Geometry().IsClockwise(angles[0],angles[1]);
  const bool b = Geometry().IsClockwise(angles[1],angles[2]);
  const bool is_clockwise { a && b };
  return is_clockwise;
}

bool ribi::trim::Helper::IsConvex(const std::vector<boost::shared_ptr<const ribi::trim::Point>>& points) const noexcept
{
  
  const std::vector<Coordinat3D> coordinats3d
    = PointsToCoordinats3D(points);
  return Geometry().IsConvex(coordinats3d);
}

bool ribi::trim::Helper::IsConvex(const std::vector<boost::shared_ptr<ribi::trim::Point>>& points) const noexcept
{
  const bool verbose{false};
  if (points.size() == 3)
  {
    if (verbose) { TRACE("Three points are always convex"); }
    return true;
  }

  #ifndef NDEBUG
  assert(points.size() == 4);
  if (verbose)
  {
    std::stringstream s;
    s << "{";
    for (const auto& point3d: points)
    {
      assert(point3d);
      s << (*point3d) << ",";
    }
    std::string po_str(s.str());
    po_str[po_str.size() - 1] = '}';
    TRACE(po_str);
  }
  #endif

  const auto const_points(AddConst(points));

  assert(points.size() == const_points.size());
  assert(boost::geometry::get<0>(*points[0]->GetCoordinat()) == boost::geometry::get<0>(*const_points[0]->GetCoordinat()));
  assert(boost::geometry::get<1>(*points[0]->GetCoordinat()) == boost::geometry::get<1>(*const_points[0]->GetCoordinat()));
  assert(points[0]->GetZ() == const_points[0]->GetZ());
  assert(boost::geometry::get<0>(*points[1]->GetCoordinat()) == boost::geometry::get<0>(*const_points[1]->GetCoordinat()));
  assert(boost::geometry::get<1>(*points[1]->GetCoordinat()) == boost::geometry::get<1>(*const_points[1]->GetCoordinat()));
  assert(points[1]->GetZ() == const_points[1]->GetZ());
  assert(boost::geometry::get<0>(*points[2]->GetCoordinat()) == boost::geometry::get<0>(*const_points[2]->GetCoordinat()));
  assert(boost::geometry::get<1>(*points[2]->GetCoordinat()) == boost::geometry::get<1>(*const_points[2]->GetCoordinat()));
  assert(points[2]->GetZ() == const_points[2]->GetZ());
  assert(boost::geometry::get<0>(*points[3]->GetCoordinat()) == boost::geometry::get<0>(*const_points[3]->GetCoordinat()));
  assert(boost::geometry::get<1>(*points[3]->GetCoordinat()) == boost::geometry::get<1>(*const_points[3]->GetCoordinat()));
  assert(points[3]->GetZ() == const_points[3]->GetZ());

  #ifndef NDEBUG
  for (const auto& point: const_points) { assert(point); }
  #endif
  return IsConvex(const_points);
}

bool ribi::trim::Helper::IsCounterClockwise(
  const std::vector<boost::shared_ptr<const Point>>& points,
  const Coordinat3D& observer) const noexcept
{
  
  assert(Geometry().IsPlane(PointsToCoordinats3D(points)));
  return Geometry().IsCounterClockwiseCartesian(PointsToCoordinats3D(points),observer);
}

bool ribi::trim::Helper::IsCounterClockwise(
  const std::vector<boost::shared_ptr<Point>>& points,
  const Coordinat3D& observer) const noexcept
{
  return IsCounterClockwise(AddConst(points),observer);
  //assert(Geometry().IsPlane(PointsToCoordinats3D(AddConst(points))));
  //return Geometry().IsCounterClockwise(PointsToCoordinats3D(AddConst(points)),observer);
}

bool ribi::trim::Helper::IsHorizontal(const ribi::trim::Face& face) const noexcept
{
  const bool answer = face.GetOrientation() == FaceOrientation::horizontal;
  return answer;
}

bool ribi::trim::Helper::IsPlane(
  const std::vector<boost::shared_ptr<const ribi::trim::Point>>& points
) const noexcept
{
  
  return Geometry().IsPlane(PointsToCoordinats3D(points));
}

bool ribi::trim::Helper::IsPlane(
  const std::vector<boost::shared_ptr<ribi::trim::Point>>& points
) const noexcept
{
  
  return Geometry().IsPlane(PointsToCoordinats3D(AddConst(points)));
}

bool ribi::trim::Helper::IsVertical(const ribi::trim::Face& face) const noexcept
{
  const bool answer_1 = face.GetOrientation() == FaceOrientation::vertical;
  #ifndef NDEBUG
  const bool answer_2 = !IsHorizontal(face);
  assert(answer_1 == answer_2);
  #endif
  return answer_1;
}

void ribi::trim::Helper::MakeConvex(
  std::vector<boost::shared_ptr<ribi::trim::Point>>& points
) const noexcept
{
  const bool verbose{false};
  #ifndef NDEBUG
  for (const auto& p: points) { assert(p); }
  assert(!points.empty());
  assert(points.size() == 4);
  #endif

  if (verbose)
  {
    TRACE(Helper().ToStr(AddConst(points)));
    for (const auto& p: points) { std::cerr << (*p) << std::endl; }
    TRACE("BREAK");
  }

  if (IsConvex(points))
  {
    if (verbose) { TRACE("MakeConvex: points were convex at start"); }
    return;
  }

  std::sort(points.begin(),points.end(),OrderByX());

  #ifndef NDEBUG
  const int max_i = (4*3*2*1) + 4; //Number of permutations, plus four to be sure
  for (int i=0; i!=max_i; ++i)
  #else
  while (1)
  #endif
  {
    #ifndef NDEBUG
    if (i == max_i-1)
    {
      TRACE("ERROR");
      TRACE(Helper().ToStr(AddConst(points)));
      for (const auto& p: points) { TRACE(*p); }
      TRACE("BREAK");
    }
    assert(i!=max_i-1 && "There must be a permutation of the points that renders them convex");
    #endif

    if (IsConvex(points))
    {
      break;
    }

    #ifndef NDEBUG
    const auto before = points;
    #endif

    std::next_permutation(points.begin(),points.end(),OrderByX());

    #ifndef NDEBUG
    const auto after = points;
    assert(before != after);
    #endif
  }

  #ifndef NDEBUG
  if(!IsConvex(points))
  {
    TRACE("ERROR");
    for (int i=0; i!=26; ++i)
    {
      std::next_permutation(points.begin(),points.end(),OrderByX());
      {
        std::stringstream s;
        assert(points.size() == 4);
        assert(points[0]); assert(points[1]); assert(points[2]); assert(points[3]);
        s << (IsConvex(points) ? "Convex" : "Not convex")
          << ": "
          << Geometry().ToStr(points[0]->GetCoordinat3D()) << "->"<< points[0]->GetIndex() << ","
          << Geometry().ToStr(points[1]->GetCoordinat3D()) << "->"<< points[1]->GetIndex() << ","
          << Geometry().ToStr(points[2]->GetCoordinat3D()) << "->"<< points[2]->GetIndex() << ","
          << Geometry().ToStr(points[3]->GetCoordinat3D()) << "->"<< points[3]->GetIndex() << '\n'
        ;
        TRACE(s.str());
      }
      {
        std::stringstream t;
        const std::vector<Coordinat2D> projected_points(CalcProjection(AddConst(points)));
        assert(projected_points.size() == 4);
        t << (IsConvex(points) ? "Convex" : "Not convex")
          << ": "
          << Geometry().ToStr(projected_points[0]) << ","
          << Geometry().ToStr(projected_points[1]) << ","
          << Geometry().ToStr(projected_points[2]) << ","
          << Geometry().ToStr(projected_points[3])
        ;
        TRACE(t.str());
      }
    }
  }
  #endif

  assert(Helper().IsConvex(points));
  return;
}

void ribi::trim::Helper::MakeCounterClockwise(
  std::vector<boost::shared_ptr<Point>>& points,
  const Coordinat3D& observer) const noexcept
{
  //Sure, will be repeated later, but perhaps the points are already ordered by a smart client
  if (IsCounterClockwise(points,observer)) return;

  assert(points.size() == 3 || points.size() == 4);

  const std::vector<boost::shared_ptr<Point>> original{points};

  assert(original == points);

  const int n_points{static_cast<int>(points.size())};
  const std::vector<int> indices{
    n_points == 3 ? std::vector<int>({0,1,2}) : std::vector<int>({0,1,2,3})
  };

  for (const auto& sequence: GetPermutations(indices))
  {
    for (int i{0}; i!=n_points; ++i)
    {
      points[i] = original[ sequence[i] ];
    }
    if (IsCounterClockwise(points,observer)) return;
  }

  TRACE("ERROR: failed making these points counterclockwards:");
  for (const auto& point: original) { TRACE(Geometry().ToStr(point->GetCoordinat3D())); }
  TRACE(Geometry().ToStr(observer));
  TRACE(IsCounterClockwise(original,observer));
  TRACE(IsPlane(original));
  TRACE(IsConvex(original));
  TRACE("Let's try again");
  for (const auto& point: points) { TRACE(Geometry().ToStr(point->GetCoordinat3D())); }
  TRACE(IsCounterClockwise(points,observer));

  for (const auto& sequence: GetPermutations(indices))
  {
    for (int i{0}; i!=n_points; ++i)
    {
      points[i] = original[ sequence[i] ];
    }
    for (const auto& point: points) { TRACE(Geometry().ToStr(point->GetCoordinat3D())); }
    TRACE(IsCounterClockwise(points,observer));
  }

  assert(!"Should not get here");
  assert(IsCounterClockwise(points,observer));
}

std::function<
    bool(
      const boost::shared_ptr<const ribi::trim::Face>& lhs,
      const boost::shared_ptr<const ribi::trim::Face>& rhs
    )
  >
  ribi::trim::Helper::OrderByIndex() const noexcept
{
  return [](const boost::shared_ptr<const Face>& lhs, const boost::shared_ptr<const Face>& rhs)
  {
    using boost::geometry::get;
    assert(lhs);
    assert(rhs);
    return lhs->GetIndex() < rhs->GetIndex();
  };

}

std::function<
    bool(
      const boost::shared_ptr<const ribi::trim::Point>& lhs,
      const boost::shared_ptr<const ribi::trim::Point>& rhs
    )
  >
  ribi::trim::Helper::OrderByX() const noexcept
{
  return [](const boost::shared_ptr<const Point>& lhs, const boost::shared_ptr<const Point>& rhs)
  {
    using boost::geometry::get;
    assert(lhs);
    assert(rhs);
    assert(lhs->GetCoordinat());
    assert(rhs->GetCoordinat());
    const auto lhs_coordinat = lhs->GetCoordinat();
    const auto rhs_coordinat = rhs->GetCoordinat();
    assert(lhs_coordinat);
    assert(rhs_coordinat);
    if (get<0>(*lhs_coordinat) < get<0>(*rhs_coordinat)) return true;
    if (get<0>(*lhs_coordinat) > get<0>(*rhs_coordinat)) return false;
    if (get<1>(*lhs_coordinat) < get<1>(*rhs_coordinat)) return true;
    if (get<1>(*lhs_coordinat) > get<1>(*rhs_coordinat)) return false;
    assert(lhs->CanGetZ());
    assert(rhs->CanGetZ());
    return lhs->GetZ() < rhs->GetZ();
  };
}

std::vector<boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>>
  ribi::trim::Helper::PointsToCoordinats3D(
    const std::vector<boost::shared_ptr<const ribi::trim::Point>>& points
) const noexcept
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  std::vector<Coordinat3D> v;
  for (const auto& p: points)
  {
    assert(p);
    assert(p->GetCoordinat());
    v.push_back(p->GetCoordinat3D());
  }
  return v;
}



std::string ribi::trim::Helper::ToStr(
  const std::vector<boost::shared_ptr<const Point>>& points
  ) const noexcept
{
  std::stringstream s;
  s << " {";
  for (const auto& point:points) { s << point->GetIndex() << ","; }
  std::string t(s.str());
  t[ t.size() - 1] = '}';
  return t;
}

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
  using boost::geometry::get;
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> result(
    get<0>(lhs) + get<0>(rhs),
    get<1>(lhs) + get<1>(rhs),
    get<2>(lhs) + get<2>(rhs)
  );
  assert(std::abs(get<0>(result) - (get<0>(lhs) + get<0>(rhs))) < 0.001);
  assert(std::abs(get<1>(result) - (get<1>(lhs) + get<1>(rhs))) < 0.001);
  assert(std::abs(get<2>(result) - (get<2>(lhs) + get<2>(rhs))) < 0.001);
  return result;
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
  using boost::geometry::get;
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> result(
    get<0>(p) / factor,
    get<1>(p) / factor,
    get<2>(p) / factor
  );
  assert(std::abs(get<0>(result) - (get<0>(p) / factor)) < 0.001);
  assert(std::abs(get<1>(result) - (get<1>(p) / factor)) < 0.001);
  assert(std::abs(get<2>(result) - (get<2>(p) / factor)) < 0.001);
  return result;
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
}


#include "trianglemeshface.h"

#include <algorithm>
#include <fstream>
#include <set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include "Shiny.h"

#include "geometry.h"
#include "trianglemeshcell.h"
#include "trianglemeshpoint.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::trim::Face::Face(
  const std::vector<boost::shared_ptr<Point>>& any_points,
  const FaceOrientation any_orientation,
  const int index,
  const FaceFactory&
  )
  : m_belongs_to{},
    m_coordinats{},
    m_index{index},
    m_orientation(any_orientation),
    m_points(any_points),
    m_type{}
{
  #ifndef NDEBUG
  Test();
  #endif
  PROFILE_FUNC();
  #ifndef NDEBUG
  if (!ribi::Geometry().IsPlane(Helper().PointsToCoordinats(AddConst(m_points))))
  {
    TRACE(*this);
    TRACE("ERROR");
  }
  assert(ribi::Geometry().IsPlane(Helper().PointsToCoordinats(AddConst(m_points))));
  if (m_orientation == FaceOrientation::horizontal)
  {
    const int n_points = static_cast<int>(m_points.size());
    assert(n_points > 2);
    for (int i=0; i!=n_points; ++i)
    {
      assert(m_points[i]);
    }
    if (m_points[0]->CanGetZ())
    {
      const auto z = m_points[0]->GetZ();
      for (const auto p: m_points)
      {
        assert(p->CanGetZ());
        assert(z == p->GetZ());
      }
    }
  }
  #endif
}

void ribi::trim::Face::AddBelongsTo(boost::weak_ptr<const Cell> cell) const
{
  assert(cell.lock());
  m_belongs_to.push_back(cell);
  assert(m_belongs_to.size() <= 2);
  assert(
       (m_belongs_to.size() == 1)
    || (m_belongs_to.size() == 2 && m_belongs_to[0].lock() != m_belongs_to[1].lock())
  );
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Face::CalcCenter() const noexcept
{
  using boost::geometry::get;
  const auto sum(
    std::accumulate(m_points.begin(),m_points.end(),
      Coordinat3D(),
      [](const Coordinat3D& init, const boost::shared_ptr<const Point>& point)
      {
        return init + Coordinat3D(
          get<0>(*point->GetCoordinat()),
          get<1>(*point->GetCoordinat()),
          point->GetZ().value()
        );
      }
    )
  );
  return sum / static_cast<double>(m_points.size());
}

int ribi::trim::Face::CalcPriority() const noexcept
{
  assert(GetOwner());
  return std::max(
    GetOwner()->GetIndex(),
    GetNeighbour() ? GetNeighbour()->GetIndex() : -1
  );
}

bool ribi::trim::Face::CanExtractCoordinats() const noexcept
{
  for (const auto point: m_points)
  {
    if (!point->CanGetZ()) return false;
  }
  return true;
}

void ribi::trim::Face::CheckOrientation() const
{
  assert(std::count(m_points.begin(),m_points.end(),nullptr) == 0);
  std::set<double> zs;
  for (auto point: m_points)
  {
    if (point->CanGetZ()) { zs.insert(zs.begin(),point->GetZ().value()); }
  }
  if (zs.size() > 1)
  {
    assert(m_orientation == FaceOrientation::vertical
      && "Only a vertical face has multiple Z values");
  }
}

void ribi::trim::Face::DoExtractCoordinats() const
{
  PROFILE_FUNC();
  assert(CanExtractCoordinats());
  //assert(m_coordinats.empty()); //This is done multiple times in debugging
  m_coordinats = Helper().ExtractCoordinats(AddConst(m_points));
}

boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetNeighbour() const noexcept
{
  PROFILE_FUNC();
  assert(m_belongs_to.size() <= 2);
  m_belongs_to.erase(
    std::remove_if(
      m_belongs_to.begin(),m_belongs_to.end(),
      [](const boost::weak_ptr<const Cell> cell)
      {
        return !cell.lock();
      }
    ),
    m_belongs_to.end()
  );
  boost::shared_ptr<const Cell> p;
  if (m_belongs_to.size() < 2) return p;

  assert(m_belongs_to[0].lock() != m_belongs_to[1].lock());

  p = m_belongs_to[1].lock();
  assert(p);
  return p;
}

boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetOwner() const noexcept
{
  PROFILE_FUNC();
  assert(m_belongs_to.size() <= 2);
  m_belongs_to.erase(
    std::remove_if(
      m_belongs_to.begin(),m_belongs_to.end(),
      [](const boost::weak_ptr<const Cell> cell)
      {
        return !cell.lock();
      }
    ),
    m_belongs_to.end()
  );
  if (m_belongs_to.empty())
  {
    return nullptr;
  }
  assert(!m_belongs_to.empty());
  boost::shared_ptr<const Cell> p {
    m_belongs_to[0].lock()
  };
  assert(p);
  return p;
}


boost::shared_ptr<const ribi::trim::Point> ribi::trim::Face::GetPoint(const int index) const noexcept
{
  PROFILE_FUNC();
  assert(index >= 0);
  assert(index < static_cast<int>(GetPoints().size()));
  return GetPoints()[index];
}

void ribi::trim::Face::SetCorrectWinding() noexcept
{
  PROFILE_FUNC();
  assert(m_points.size() == 3 || m_points.size() == 4);
  assert( (m_belongs_to.size() == 1 || m_belongs_to.size() == 2)
    && "A Face its winding can only be set if it belongs to a cell"
  );
  std::sort(m_points.begin(),m_points.end()); //For std::next_permutation

  const boost::shared_ptr<const Cell> observer(
    !GetNeighbour()
    ? GetOwner()
    : GetOwner()->GetIndex() < GetNeighbour()->GetIndex() ? GetOwner() : GetNeighbour()
  );
  assert(observer);
  assert(Geometry().IsPlane(Helper().PointsToCoordinats(AddConst(m_points))));
  static int cnt = 0;
  cnt = 0;
  while (std::next_permutation(m_points.begin(),m_points.end()))
  {
    TRACE(cnt);
    TRACE(Geometry().ToStr(observer->CalculateCenter()));
    assert(std::count(m_points.begin(),m_points.end(),nullptr) == 0);
    if (Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()))
    {
      TRACE("OK");
      assert(std::count(m_points.begin(),m_points.end(),nullptr) == 0);
      TRACE(Geometry().ToStr(observer->CalculateCenter()));
      assert(Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()));
      TRACE(Geometry().ToStr(observer->CalculateCenter()));
      assert(Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()));
      TRACE(Geometry().ToStr(observer->CalculateCenter()));
      assert(Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()));
      TRACE(Geometry().ToStr(observer->CalculateCenter()));
      assert(Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()));
      TRACE(Geometry().ToStr(observer->CalculateCenter()));
      break;
    }
    ++cnt;
  }
  TRACE(cnt);
  #ifndef NDEBUG
  if (!Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()))
  {
    TRACE(m_points.size());
    for (const auto point: m_points) TRACE(Geometry().ToStr(point->GetCoordinat3D()));
    TRACE(Geometry().ToStr(observer->CalculateCenter()));
  }
  #endif
  assert(Helper().IsClockwise(AddConst(m_points),observer->CalculateCenter()));
}

#ifndef NDEBUG
void ribi::trim::Face::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Face::Test");
  const std::vector<boost::shared_ptr<Face>> faces {
    FaceFactory().CreateTestPrism()
  };
  for (auto face: faces)
  {
    assert(!(face->GetOwner().get()) && "Faces obtain an owner when being added to a Cell");
    assert(!(face->GetNeighbour().get()) && "Faces obtain a neighbour when beging added to a Cell twice");
    //face->SetCorrectWinding(); //Cannot! A Face must belong to a Cell for this to work
  }
  TRACE("Finished ribi::trim::Face::Test successfully");
}
#endif

bool ribi::trim::operator==(const ribi::trim::Face& lhs, const ribi::trim::Face& rhs) noexcept
{
  return
       lhs.GetPoints() == rhs.GetPoints()
    && lhs.GetOrientation() == rhs.GetOrientation()
  ;
}

bool ribi::trim::operator!=(const ribi::trim::Face& lhs, const ribi::trim::Face& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::trim::operator<<(std::ostream& os, const ribi::trim::Face& f)
{
  os
    << ribi::xml::ToXml("face_index",f.GetIndex())
    << ribi::xml::ToXml("orientation",static_cast<int>(f.GetOrientation()))
  ;

  {
    std::stringstream s;
    const int n_points { static_cast<int>(f.GetPoints().size()) };
    for (int i=0; i!=n_points; ++i)
    {
      s << ribi::xml::ToXml("point" + boost::lexical_cast<std::string>(i),*f.GetPoint(i));
    }
    os << ribi::xml::ToXml("points",s.str());
  }

  return os;
}

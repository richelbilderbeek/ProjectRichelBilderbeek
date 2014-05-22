#include "trianglemeshface.h"

#include <algorithm>
#include <fstream>
#include <set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>

#include "geometry.h"
#include "trianglemeshcell.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#include "trianglemeshpoint.h"
#include "trianglemeshfacefactory.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpointfactory.h"
#include "trianglemeshwinding.h"
#include "trianglemeshwindings.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

std::set<const ribi::trim::Face*> ribi::trim::Face::sm_faces;

ribi::trim::Face::Face(
  const std::vector<boost::shared_ptr<Point>>& any_points,
  const FaceOrientation any_orientation,
  const int index,
  const FaceFactory&
  )
  :
    #ifdef TRIANGLEMESH_USE_SIGNALS2
    m_signal_destroyed{},
    #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
    m_belongs_to{},
    m_coordinats{},
    m_index{index},
    m_orientation{any_orientation},
    m_points{any_points},
    m_type{}
{
  #ifndef NDEBUG
  Test();
  
  assert(m_points == any_points);
  assert(!m_points.empty());
  assert(  m_points[0].use_count() >= 2);
  assert(any_points[0].use_count() >= 2);
  
  assert(Helper().IsPlane(m_points));
  if (!Helper().IsConvex(m_points))
  {
    TRACE("ERROR");
    for (auto point: m_points) TRACE(point->ToStr());
  }
  assert(sm_faces.count(this) == 0);
  sm_faces.insert(this);

  assert(Helper().IsConvex(m_points));

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

ribi::trim::Face::~Face() noexcept
{
  assert(sm_faces.count(this) == 1);
  sm_faces.erase(this);
  assert(sm_faces.count(this) == 0);

  #ifdef TRIANGLEMESH_USE_SIGNALS2
  m_signal_destroyed(this);
  #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
}

#ifdef TRIANGLEMESH_USE_SIGNALS2
void ribi::trim::Face::AddBelongsTo(boost::shared_ptr<const Cell> cell)
{
  assert(cell);
  m_belongs_to.push_back(cell);
  assert(m_belongs_to.size() <= 2);
  assert(
       (m_belongs_to.size() == 1)
    || (m_belongs_to.size() == 2 && m_belongs_to[0] != m_belongs_to[1])
  );
  cell->m_signal_destroyed.connect(
    boost::bind(&ribi::trim::Face::OnCellDestroyed,this,boost::lambda::_1)
  );
}
#else
void ribi::trim::Face::AddBelongsTo(boost::weak_ptr<const Cell> cell)
{
  assert(cell.lock());
  m_belongs_to.push_back(cell);
  assert(m_belongs_to.size() <= 2);
  assert(
       (m_belongs_to.size() == 1)
    || (m_belongs_to.size() == 2 && m_belongs_to[0].lock() != m_belongs_to[1].lock())
  );
}
#endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::trim::Face::CalcCenter() const noexcept
{
  assert(!m_points.empty());
  using boost::geometry::get;
  
  const Coordinat3D sum(
    std::accumulate(m_points.begin(),m_points.end(),
      Geometry().CreatePoint(0.0,0.0,0.0),
      [](const Coordinat3D& init, const boost::shared_ptr<const Point>& point)
      {
        assert(point);
        return init + point->GetCoordinat3D();
      }
    )
  );
  const Coordinat3D center(
    sum / static_cast<double>(m_points.size())
  );
  return center;
}

int ribi::trim::Face::CalcPriority() const noexcept
{
  assert(GetConstOwner());
  return GetConstOwner()->GetIndex();
  //return std::max(
  //  GetOwner()->GetIndex(),
  //  GetNeighbour() ? GetNeighbour()->GetIndex() : -1
  //);
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
  
  assert(CanExtractCoordinats());
  //assert(m_coordinats.empty()); //This is done multiple times in debugging
  
  m_coordinats = Helper().ExtractCoordinats(AddConst(m_points));
}

boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetNeighbour() const noexcept
{
  
  assert(m_belongs_to.size() <= 2);
  m_belongs_to.erase(
    std::remove_if(
      m_belongs_to.begin(),m_belongs_to.end(),
      #ifdef TRIANGLEMESH_USE_SIGNALS2
      [](const boost::shared_ptr<const Cell> cell) { return !cell; }
      #else
      [](const boost::weak_ptr<const Cell> cell) { return !cell.lock(); }
      #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
    ),
    m_belongs_to.end()
  );
  boost::shared_ptr<const Cell> p;
  if (m_belongs_to.size() < 2) return p;

  #ifdef TRIANGLEMESH_USE_SIGNALS2
  assert(m_belongs_to[0] != m_belongs_to[1]);
  p = m_belongs_to[1];
  assert(p);
  return p;
  #else
  assert(m_belongs_to[0].lock() != m_belongs_to[1].lock());
  p = m_belongs_to[1].lock();
  assert(p);
  return p;
  #endif //#ifdef TRIANGLEMESH_USE_SIGNALS2
}

boost::shared_ptr<ribi::trim::Cell> ribi::trim::Face::GetNonConstNeighbour() noexcept
{
  const boost::shared_ptr<const ribi::trim::Cell> const_cell
    = const_cast<const ribi::trim::Face*>(this)->GetNeighbour();
  return boost::const_pointer_cast<Cell>(const_cell);
}

boost::shared_ptr<const ribi::trim::Cell> ribi::trim::Face::GetConstOwner() const noexcept
{
  //TODO: This is the slowest function
  assert(m_belongs_to.size() <= 2);
  m_belongs_to.erase(
    std::remove_if(
      m_belongs_to.begin(),m_belongs_to.end(),
      #ifdef TRIANGLEMESH_USE_SIGNALS2
      [](const boost::shared_ptr<const Cell> cell) { return !cell; }
      #else
      [](const boost::weak_ptr<const Cell> cell) { return !cell.lock(); }
      #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
    ),
    m_belongs_to.end()
  );
  if (m_belongs_to.empty())
  {
    return nullptr;
  }
  assert(!m_belongs_to.empty());
  boost::shared_ptr<const Cell> p {
    m_belongs_to[0]
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::trim::Cell> ribi::trim::Face::GetNonConstOwner() noexcept
{
  const boost::shared_ptr<const ribi::trim::Cell> const_cell
    = const_cast<const ribi::trim::Face*>(this)->GetConstOwner();
  return boost::const_pointer_cast<Cell>(const_cell);
}

boost::shared_ptr<const ribi::trim::Point> ribi::trim::Face::GetPoint(const int index) const noexcept
{
  
  assert(index >= 0);
  assert(index < static_cast<int>(GetPoints().size()));
  return GetPoints()[index];
}

void ribi::trim::Face::OnCellDestroyed(const Cell* const cell) noexcept
{
  assert(1==2);
  #ifdef TRIANGLEMESH_USE_SIGNALS2
  const auto new_end = std::remove_if(m_belongs_to.begin(),m_belongs_to.end(),
    [cell](const boost::shared_ptr<const Cell>& belongs_to) { return belongs_to.get() == cell; }
  );
  #else
  const auto new_end = std::remove_if(m_belongs_to.begin(),m_belongs_to.end(),
    [cell](const boost::weak_ptr<const Cell>& belongs_to) { return belongs_to.lock().get() == cell; }
  );
  #endif //~#ifdef TRIANGLEMESH_USE_SIGNALS2
  m_belongs_to.erase(new_end,m_belongs_to.end());
}

void ribi::trim::Face::SetCorrectWinding() noexcept
{
  
  
  assert(m_points.size() == 3 || m_points.size() == 4);
  assert( (m_belongs_to.size() == 1 || m_belongs_to.size() == 2)
    && "A Face its winding can only be set if it belongs to a cell"
  );
  assert(Helper().IsPlane(m_points));
  assert(Helper().IsConvex(m_points));

  const boost::shared_ptr<const Cell> observer(
    !GetNeighbour()
    ? GetConstOwner()
    : GetConstOwner()->GetIndex() < GetNeighbour()->GetIndex() ? GetConstOwner() : GetNeighbour()
  );
  assert(observer);
  assert(Helper().IsPlane(m_points));

  if (!Helper().IsCounterClockwise(m_points,observer->CalculateCenter()))
  {
    std::sort(m_points.begin(),m_points.end(),Helper().OrderByX()); //For std::next_permutation
    //Must be ordered counter-clockwise (although the documentation says otherwise?)
    while (std::next_permutation(m_points.begin(),m_points.end(),Helper().OrderByX()))
    {
      assert(std::count(m_points.begin(),m_points.end(),nullptr) == 0);
      if (
        Helper().IsCounterClockwise(m_points,observer->CalculateCenter())
        && Helper().IsConvex(m_points)
      )
      {
        assert(std::count(m_points.begin(),m_points.end(),nullptr) == 0);
        break;
      }
    }
  }

  #ifndef NDEBUG
  if (!Helper().IsCounterClockwise(AddConst(m_points),observer->CalculateCenter()))
  {
    TRACE(m_points.size());
    
    for (const auto point: m_points) TRACE(Geometry().ToStr(point->GetCoordinat3D()));
    TRACE(Geometry().ToStr(observer->CalculateCenter()));
  }
  #endif
  assert(Helper().IsCounterClockwise(m_points,observer->CalculateCenter()));
  assert(Helper().IsPlane(m_points));
  assert(Helper().IsConvex(m_points));
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
  //Check that a Face has no owner nor neighbour when not added to a Cell
  for (auto strategy: CreateVerticalFacesStrategies().GetAll())
  {
    const std::vector<boost::shared_ptr<Face>> faces {
      FaceFactory().CreateTestPrism(strategy)
    };
    for (auto face: faces)
    {
      assert(!(face->GetConstOwner().get()) && "Faces obtain an owner when being added to a Cell");
      assert(!(face->GetNeighbour().get()) && "Faces obtain a neighbour when beging added to a Cell twice");
      //face->SetCorrectWinding(); //Cannot! A Face must belong to a Cell for this to work
    }
  }
  //Check that incorrect Faces cannot be constructed
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
  TRACE("Finished ribi::trim::Face::Test successfully");
}
#endif

void ribi::trim::Face::TransferOwnership() noexcept
{
  assert(m_belongs_to.size() == 2);
  std::swap(m_belongs_to[0],m_belongs_to[1]);
}

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

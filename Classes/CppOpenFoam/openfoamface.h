#ifndef RIBI_OPENFOAMFACE_H
#define RIBI_OPENFOAMFACE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#include "openfoamfwd.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace foam {

///An OpenFOAM face:
///- has a collection of points/vertices/coordinats
///- has a/no neighbouring cell
///- has a/no cell owning this face
struct Face
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  explicit Face(
    const boost::shared_ptr<Cell>& neighbour,
    const boost::shared_ptr<Cell>& owner,
    const std::vector<boost::shared_ptr<Coordinat3D>>& points
  ) noexcept;

  Face(const Face&) = delete;
  Face& operator=(const Face&) = delete;

  ///Can only assign once
  void AssignNeighbour(const boost::shared_ptr<Cell> neighbour) noexcept;

  ///Can only assign once
  void AssignOwner(const boost::shared_ptr<Cell> owner) noexcept;

  boost::shared_ptr<const Cell> GetNeighbour() const noexcept { return m_neighbour; }

  boost::shared_ptr<const Cell> GetOwner() const noexcept { return m_owner; }
  boost::shared_ptr<      Cell> GetOwner()       noexcept;

        std::vector<boost::shared_ptr<const Coordinat3D>> GetPoints() const noexcept;
  const std::vector<boost::shared_ptr<      Coordinat3D>>&GetPoints()       noexcept { return m_points; }
  private:
  ///If this Face has no Neighbour, this is nullptr
  boost::shared_ptr<Cell> m_neighbour;

  ///If this Face has no Owner, this is nullptr
  boost::shared_ptr<Cell> m_owner;

  ///The points/vertices/coordinats this face consists of
  const std::vector<boost::shared_ptr<Coordinat3D>> m_points;

  friend std::ostream& operator<<(std::ostream& os, const Face& face) noexcept;
};

///Calculate the center of the Face
boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> CalcCenter(const Face& face) noexcept;

std::ostream& operator<<(std::ostream& os, const Face& face) noexcept;

//bool operator<(const boost::shared_ptr<const Face>& lhs, const boost::shared_ptr<      Face>& rhs) = delete;
//bool operator<(const boost::shared_ptr<const Face>& lhs, const boost::shared_ptr<const Face>& rhs) = delete;
//bool operator<(const boost::shared_ptr<      Face>& lhs, const boost::shared_ptr<      Face>& rhs) = delete;
//bool operator<(const boost::shared_ptr<      Face>& lhs, const boost::shared_ptr<const Face>& rhs) = delete;

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMFACE_H

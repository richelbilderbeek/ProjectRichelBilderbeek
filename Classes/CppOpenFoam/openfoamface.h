#ifndef OPENFOAMFACE_H
#define OPENFOAMFACE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
//#include "openfoamcellindex.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace foam {

///An OpenFOAM face:
///- has a collection of points/vertices/coordinats
///- has a/no neighbouring cell
///- has a/no cell owning this face
struct Face
{
  Face(
    const boost::shared_ptr<Cell> neighbour,
    const boost::shared_ptr<Cell> owner,
    const std::vector<boost::shared_ptr<ribi::Coordinat3D> >& points
  );

  Face(const Face&) = delete;
  Face& operator=(const Face&) = delete;

  ///Can only assign once
  void AssignNeighbour(const boost::shared_ptr<Cell> neighbour) noexcept;

  ///Can only assign once
  void AssignOwner(const boost::shared_ptr<Cell> owner) noexcept;

  const boost::shared_ptr<const Cell> GetNeighbour() const noexcept { return m_neighbour; }

  const boost::shared_ptr<const Cell> GetOwner() const noexcept { return m_owner; }
  const boost::shared_ptr<      Cell> GetOwner()       noexcept;

  const std::vector<boost::shared_ptr<const ribi::Coordinat3D> > GetPoints() const noexcept;
  const std::vector<boost::shared_ptr<      ribi::Coordinat3D> >&GetPoints()       noexcept { return m_points; }

  private:
  ///If this Face has no Neighbour, this is nullptr
  boost::shared_ptr<Cell> m_neighbour;

  ///If this Face has no Owner, this is nullptr
  boost::shared_ptr<Cell> m_owner;

  ///The points/vertices/coordinats this face consists of
  const std::vector<boost::shared_ptr<ribi::Coordinat3D> > m_points;

  friend std::ostream& operator<<(std::ostream& os, const Face& face);
};

///Calculate the center of the Face
ribi::Coordinat3D CalcCenter(const Face& face) noexcept;

std::ostream& operator<<(std::ostream& os, const Face& face);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFACE_H

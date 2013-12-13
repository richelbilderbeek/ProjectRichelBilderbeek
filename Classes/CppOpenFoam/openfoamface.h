#ifndef OPENFOAMFACE_H
#define OPENFOAMFACE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#include "openfoamcellindex.h"
//#include "openfoampoint.h"
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

  void AssignOwner(const boost::shared_ptr<Cell> owner) noexcept;

  const boost::shared_ptr<Cell> GetOwner() noexcept;

  private:
  ///If this Face has no Neighbour, this is nullptr
  boost::shared_ptr<Cell> m_neighbour;

  ///If this Face has no Owner, this is nullptr
  boost::shared_ptr<Cell> m_owner;

  ///The points/vertices/coordinats this face consists of
  const std::vector<boost::shared_ptr<ribi::Coordinat3D> > m_points;
};

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFACE_H

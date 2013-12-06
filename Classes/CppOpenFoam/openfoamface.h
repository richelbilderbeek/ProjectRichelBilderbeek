#ifndef OPENFOAMFACE_H
#define OPENFOAMFACE_H

#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamcellindex.h"
#include "openfoampoint.h"
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
    const boost::shared_ptr<CellIndex> neighbour = nullptr,
    const boost::shared_ptr<CellIndex> owner = nullptr,
    const std::vector<Point>& points = {}
  );

  ///If this Face has no Neighbour, this is nullptr
  const boost::shared_ptr<CellIndex> m_neighbour;

  ///If this Face has no Owner, this is nullptr
  const boost::shared_ptr<CellIndex> m_owner;

  ///The points/vertices/coordinats this face consists of
  const std::vector<Point> m_points;
};

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFACE_H

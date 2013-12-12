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
    //const boost::shared_ptr<Cell> neighbour = nullptr,
    //const boost::shared_ptr<Cell> owner = nullptr,
    const std::vector<boost::shared_ptr<Point> >& points = {}
  );

  Face(const Face&) = delete;
  Face& operator=(const Face&) = delete;

  ///If this Face has no Neighbour, this is nullptr
  //const boost::shared_ptr<CellIndex> m_neighbour;

  ///If this Face has no Owner, this is nullptr
  //const boost::shared_ptr<CellIndex> m_owner;

  ///The points/vertices/coordinats this face consists of
  const std::vector<boost::shared_ptr<Point> > m_points;
};

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFACE_H

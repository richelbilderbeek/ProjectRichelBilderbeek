#ifndef OPENFOAMMESH_H
#define OPENFOAMMESH_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace foam {

///Mesh contains the mesh of an OpenFOAM mesh in an indexless way
///A Mesh can be converted to a Files and vice versa
struct Mesh
{
  ///Step #0
  ///Create Points so these can be shared over the Faces
  ///Create Cells so these can be shared over the Faces
  Mesh(const Files& files) : Mesh(files,CreatePoints(files)) {}

  ///Write the Mesh to a Files
  Files CreateFiles() const noexcept;

  private:

  ///Step #1
  ///Create Faces so these can be shared over Boundary and Cell
  Mesh(const Files& files,
    const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points);

  ///Step #2
  ///Seperate these Faces into Boundary and Cell instances
  //Mesh(const Files& files, const std::vector<boost::shared_ptr<Face>>& faces);

  static const std::vector<boost::shared_ptr<Boundary> > CreateBoundaries(
    const Files& files, const std::vector<boost::shared_ptr<Face>>& faces);

  ///Create empty Cells, as much as needed
  static const std::vector<boost::shared_ptr<Cell> > CreateEmptyCells(
    const Files& files);

  ///Create the Faces from the points, but cannot initialize Owner and Neighbour
  static const std::vector<boost::shared_ptr<Face> > CreateFacesWithPoints(
    const Files& files,const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points);

  static const std::vector<boost::shared_ptr<ribi::Coordinat3D> > CreatePoints(const Files& files);


  std::vector<boost::shared_ptr<Boundary> > m_boundaries;
  std::vector<boost::shared_ptr<Cell> > m_cells;

};

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMMESH_H

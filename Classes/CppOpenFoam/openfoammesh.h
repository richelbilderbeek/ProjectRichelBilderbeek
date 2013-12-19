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

  Mesh(
    const std::vector<boost::shared_ptr<Boundary>>& boundaries,
    const std::vector<boost::shared_ptr<Cell>>& cells,
    const std::vector<boost::shared_ptr<Face>>& faces,
    const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points
  );

  ///Write the Mesh to a Files
  Files CreateFiles() const noexcept;

  const boost::shared_ptr<const Face> FindMostSimilarFace(
    const std::vector<ribi::Coordinat3D>& coordinats
  ) const;

  int GetNumberOfBoundaries() const noexcept;
  int GetNumberOfCells() const noexcept;
  int GetNumberOfFaces() const noexcept;
  int GetNumberOfPoints() const noexcept;

  const std::vector<boost::shared_ptr<Boundary> >& GetBoundaries() noexcept { return m_boundaries; }
  const std::vector<boost::shared_ptr<Cell> >& GetCells() noexcept { return  m_cells; }
  const std::vector<boost::shared_ptr<      Face> >& GetFaces()       noexcept { return m_faces; }
  const std::vector<boost::shared_ptr<const Face> >  GetFaces() const noexcept;
  const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& GetPoints() noexcept { return m_points; }

  private:

  ///Order is not important
  std::vector<boost::shared_ptr<Boundary> > m_boundaries;

  ///Order is not important
  std::vector<boost::shared_ptr<Cell> > m_cells;

  ///Order is important for ReorderFaces only
  std::vector<boost::shared_ptr<Face> > m_faces;

  ///Order is not important
  std::vector<boost::shared_ptr<ribi::Coordinat3D>> m_points;

  ///Step #1
  ///Create Faces so these can be shared over Boundary and Cell
  Mesh(const Files& files,
    const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points);

  ///Checks if the Faces their indices are adjacent
  ///when they belong to the
  ///same Boundary
  bool AreFacesOrdered() const noexcept;

  static double CalcSimilarity(
    const std::vector<ribi::Coordinat3D>& v,
    const std::vector<ribi::Coordinat3D>& w) noexcept;

  static double CalcSimilarity(
    const std::vector<boost::shared_ptr<const ribi::Coordinat3D> >& v,
    const std::vector<ribi::Coordinat3D>& w) noexcept;

  static const std::vector<boost::shared_ptr<Boundary> > CreateBoundaries(
    const Files& files, const std::vector<boost::shared_ptr<Face>>& faces);

  const boost::shared_ptr<BoundaryFile> CreateBoundary() const noexcept;

  ///Create empty Cells, as much as needed
  static const std::vector<boost::shared_ptr<Cell> > CreateEmptyCells(
    const Files& files);

  const boost::shared_ptr<FacesFile> CreateFaces() const noexcept;

  ///Create the Faces from the points, but cannot initialize Owner and Neighbour
  static const std::vector<boost::shared_ptr<Face> > CreateFacesWithPoints(
    const Files& files,
    const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points);

  const boost::shared_ptr<NeighbourFile> CreateNeighbour() const noexcept;
  const boost::shared_ptr<OwnerFile> CreateOwner() const noexcept;
  const boost::shared_ptr<PointsFile> CreatePoints() const noexcept;

  static const std::vector<boost::shared_ptr<ribi::Coordinat3D> > CreatePoints(const Files& files);

  ///This member function is called to reorder the faces in such a way
  ///that indices in m_faces are adjacent when they belong to the
  ///same Boundary
  ///
  ///For example, consider the following boundary file:
  ///
  ///2
  ///(
  ///  boundary_left
  ///  {
  ///    type            patch;
  ///    nFaces          2;
  ///    startFace       0;
  ///  }
  ///  boundary_right
  ///  {
  ///    type            patch;
  ///    nFaces          2;
  ///    startFace       2;
  ///  }
  ///)
  ///
  ///ReorderFaces will put the faces belonging to 'boundary_left'
  ///at indices 0 and 1, and the faces belonging to 'boundary_right'
  ///at indices 2 and 3.
  ///
  ///These ordering of Faces in m_faces is unimportant, except for this
  void ReorderFaces();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh);
};

std::ostream& operator<<(std::ostream& os, const Mesh& mesh);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMMESH_H

#include "openfoammesh.h"

#include <cassert>

#include "openfoamboundaryindex.h"
#include "openfoamboundary.h"
#include "openfoamcell.h"
#include "openfoamfiles.h"
#include "openfoamfacesfile.h"
#include "openfoamboundaryfile.h"

ribi::foam::Mesh::Mesh(
  const Files& files,
  const std::vector<boost::shared_ptr<Point>>& points
  )
  : m_boundaries{},
    m_cells{}
{
  //Create Faces
  std::vector<boost::shared_ptr<Face> > faces { CreateFaces(files,points) };

  //Create empty Cells
  files.GetNeighbour()->GetMaxCellIndex()
  m_cells;
}

const std::vector<boost::shared_ptr<ribi::foam::Boundary> > ribi::foam::Mesh::CreateBoundaries(
  const Files& files,
  const std::vector<boost::shared_ptr<Face>>& all_faces
  )
{
  assert(files.GetFaces()->GetMaxFaceIndex().Get() == static_cast<int>(all_faces.size()));

  std::vector<boost::shared_ptr<ribi::foam::Boundary>> boundaries;

  const BoundaryIndex n_boundaries = files.GetBoundary()->GetMaxBoundaryIndex();
  for (BoundaryIndex i = BoundaryIndex(0); i!=n_boundaries; ++i)
  {
    const BoundaryFileItem& item { files.GetBoundary()->GetItem(i) };
    const std::string name = item.GetName();
    const std::string type = item.GetType();

    std::vector<boost::shared_ptr<Face> > faces;
    const FaceIndex end_face { item.GetEndFace() } ;
    for (FaceIndex face_index = item.GetStartFace(); face_index!=end_face; ++face_index)
    {
      const int fi = face_index.Get();
      assert(fi >= 0);
      assert(fi < static_cast<int>(all_faces.size()));
      faces.push_back(all_faces[fi]);
    }

    //Face belongs to Boundary
    const boost::shared_ptr<Boundary> boundary {
      new Boundary(
        faces,
        name,
        type
      )
    };
    boundaries.push_back(boundary);
  }
  return boundaries;
}

/*
const std::vector<boost::shared_ptr<ribi::foam::Cell> > ribi::foam::Mesh::CreateCells(
  const Files& files)
{
  std::vector<boost::shared_ptr<ribi::foam::Cell> > cells;
  ///cell[0] has no neighbour
  {
    boost::shared_ptr<ribi::foam::Cell> p {
      new Cell(

  return cells;
}
*/

/*
const std::vector<boost::shared_ptr<ribi::foam::Cell> > ribi::foam::Mesh::CreateCells(
  const Files& files,
  const std::vector<boost::shared_ptr<Face>>& all_faces
  )
{
  assert(files.GetFaces()->GetMaxFaceIndex().Get() == static_cast<int>(all_faces.size()));

  const FaceIndex n_faces = files.GetFaces()->GetMaxFaceIndex();
  for (FaceIndex i = FaceIndex(0); i!=n_faces; ++i)
  {
    //A Face belongs to either a Boundary or a Cell
    if (files.GetBoundary()->IsBoundary(i))
    {
      //Face belongs to Boundary
      //Skip
    }
    else
    {
      //Face belongs to Cell
      const boost::shared_ptr<Cell> cell {
        new Cell(

        )
      };
      m_cells.push_back(cell);
    }
  }

}
*/

const std::vector<boost::shared_ptr> ribi::foam::Mesh:CreateFaces(
  const Files& files,const std::vector<boost::shared_ptr<Point>>& points)
{
  const FaceIndex n_faces { files.GetFaces()->GetMaxFaceIndex() };

  std::vector<boost::shared_ptr> faces;
  for (FaceIndex i = FaceIndex(0); i!=n_faces; ++i)
  {

  }
}


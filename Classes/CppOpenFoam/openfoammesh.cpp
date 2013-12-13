#include "openfoammesh.h"

#include <cassert>
#include <map>

#include "openfoamboundary.h"
#include "openfoamboundaryfile.h"
#include "openfoamboundaryindex.h"
#include "openfoamcell.h"
#include "openfoamface.h"
#include "openfoamfacesfile.h"
#include "openfoamfiles.h"
#include "openfoamneighbourfile.h"
#include "openfoamownerfile.h"
#include "openfoampoint.h"
#include "openfoampointsfile.h"
#include "trace.h"

ribi::foam::Mesh::Mesh(
  const Files& files,
  const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points
  )
  : m_boundaries{},
    m_cells{CreateEmptyCells(files)}
{

  //Create Faces from their Points
  std::vector<boost::shared_ptr<Face> > faces { CreateFacesWithPoints(files,points) };

  //Add Cell owner to Faces
  {
    const FaceIndex n_faces = files.GetFaces()->GetMaxFaceIndex();
    for (FaceIndex i = FaceIndex(0); i!=n_faces; ++i)
    {
      const CellIndex owner_cell_index { files.GetOwner()->GetItem(i).GetCellIndex() };
      #ifndef NDEBUG
      if (owner_cell_index.Get() >= static_cast<int>(m_cells.size()))
      {
        TRACE("ERROR");
        TRACE(owner_cell_index);
        TRACE(m_cells.size());
      }
      #endif
      assert(owner_cell_index.Get() >= 0);
      assert(owner_cell_index.Get() < static_cast<int>(m_cells.size()));
      boost::shared_ptr<Cell> owner { m_cells[ owner_cell_index.Get() ] };
      assert(owner);
      faces[i.Get()]->AssignOwner(owner);
    }
  }

  //Add owned Faces to Cells
  {
    std::map<boost::shared_ptr<Cell>,std::vector<boost::shared_ptr<Face>>> m;
    for (const boost::shared_ptr<Face> face: faces)
    {
      assert(face);
      const boost::shared_ptr<Cell> owner { face->GetOwner() };
      if (!owner) continue;
      if (m.find(owner) == m.end()) { m.insert(std::make_pair(owner, std::vector<boost::shared_ptr<Face>>() ) ); }
      assert(m.find(owner) != m.end());
      (*m.find(owner)).second.push_back(face);
    }
    for (auto p: m)
    {
      p.first->AssignOwnedFaces(p.second);
    }
  }

  //Add ? to Faces
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


const std::vector<boost::shared_ptr<ribi::foam::Cell> > ribi::foam::Mesh::CreateEmptyCells(
  const Files& files)
{
  std::vector<boost::shared_ptr<ribi::foam::Cell> > cells;
  const CellIndex n_cells = files.GetNeighbour()->FindMaxCellIndex();
  for (CellIndex i=CellIndex(0); i!=n_cells; ++i)
  {
    boost::shared_ptr<Cell> cell(
      new Cell
    );
    cells.push_back(cell);
  }
  return cells;
}


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

const std::vector<boost::shared_ptr<ribi::foam::Face>> ribi::foam::Mesh::CreateFacesWithPoints(
  const Files& files,
  const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& all_points)
{
  const FaceIndex n_faces { files.GetFaces()->GetMaxFaceIndex() };

  std::vector<boost::shared_ptr<Face>> faces;
  for (FaceIndex i = FaceIndex(0); i!=n_faces; ++i)
  {
    const std::vector<PointIndex> point_indices {
      files.GetFaces()->GetItem(i).GetPointIndices()
    };
    std::vector<boost::shared_ptr<ribi::Coordinat3D>> points;
    for (const PointIndex& point_index: point_indices)
    {
      assert(point_index.Get() >= 0);
      assert(point_index.Get() < static_cast<int>(all_points.size()));
      points.push_back(all_points[point_index.Get() ]);
    }
    const boost::shared_ptr<Face> face(
      new Face(
        nullptr,
        nullptr,
        points
      )
    );
    assert(face);
    faces.push_back(face);
  }
  return faces;
}

ribi::foam::Files ribi::foam::Mesh::CreateFiles() const noexcept
{
  Files f;
  return f;
}

const std::vector<boost::shared_ptr<ribi::Coordinat3D> >
  ribi::foam::Mesh::CreatePoints(const Files& files)
{
  std::vector<boost::shared_ptr<ribi::Coordinat3D> > v;
  for (const PointsFileItem& item: files.GetPoints()->GetItems())
  {
    //PointsFileItem == Point
    const boost::shared_ptr<ribi::Coordinat3D> p {
      new ribi::Coordinat3D(item.GetCoordinat())

    };
    assert(p);
    v.push_back(p);
  }
  return v;
}

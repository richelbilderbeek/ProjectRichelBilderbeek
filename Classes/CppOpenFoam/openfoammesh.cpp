#include "openfoammesh.h"

#include <cassert>
#include <map>

#include "openfoamboundary.h"
#include "openfoamboundaryfile.h"
#include "openfoamboundaryfileitem.h"
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
    m_cells{CreateEmptyCells(files)},
    m_faces{CreateFacesWithPoints(files,points)},
    m_points(points)
{

  //Add Cell owner to Faces
  assert(!m_cells.empty());
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
      assert(m_cells[ owner_cell_index.Get() ]);
      const boost::shared_ptr<Cell> owner { m_cells[ owner_cell_index.Get() ] };
      assert(owner);
      assert(!m_faces[i.Get()]->GetOwner() );
      m_faces[i.Get()]->AssignOwner(owner);
      assert( m_faces[i.Get()]->GetOwner() );
    }
  }
  #ifndef NDEBUG
  for (const boost::shared_ptr<Face> face: m_faces) { assert(face); assert(face->GetOwner()); }
  #endif

  //Add owned Faces to Cells
  {
    std::map<boost::shared_ptr<Cell>,std::vector<boost::shared_ptr<Face>>> m;
    for (const boost::shared_ptr<Face> face: m_faces)
    {
      assert(face);
      const boost::shared_ptr<Cell> owner { face->GetOwner() };
      assert(owner);
      //if (!owner) continue;
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
  m_boundaries = CreateBoundaries(files,m_faces);

  //Check
  #ifndef NDEBUG
  if (GetNumberOfBoundaries() != files.GetBoundary()->GetMaxBoundaryIndex().Get())
  {
    TRACE("ERROR");
    TRACE(GetNumberOfBoundaries());
    TRACE(files.GetBoundary()->GetMaxBoundaryIndex());
  }
  #endif
  assert(GetNumberOfBoundaries() == files.GetBoundary()->GetMaxBoundaryIndex().Get());

  /*
  #ifndef NDEBUG
  if (!
       ( files.GetNeighbour()->GetItems().empty()
         && GetNumberOfCells() == 0
       )
    || (!files.GetNeighbour()->GetItems().empty()
         && GetNumberOfCells() == files.GetNeighbour()->CountNumberOfCells().Get()
       )
  )
  {
    TRACE("ERROR");
    TRACE(GetNumberOfCells());
    TRACE(files.GetNeighbour()->GetItems().size());
    if (!files.GetNeighbour()->GetItems().empty()) TRACE(files.GetNeighbour()->CountNumberOfCells());
  }
  #endif
  assert(
       ( files.GetNeighbour()->GetItems().empty()
         && GetNumberOfCells() == 0
       )
    || (!files.GetNeighbour()->GetItems().empty()
         && GetNumberOfCells() == files.GetNeighbour()->CountNumberOfCells().Get()
       )
  );

  #ifndef NDEBUG
  if (GetNumberOfPoints() != static_cast<int>(files.GetPoints()->GetItems().size()))
  {
    TRACE("ERROR");
    TRACE(GetNumberOfPoints());
    TRACE(files.GetPoints()->GetItems().size());
  }
  #endif
  assert(GetNumberOfPoints() == static_cast<int>(files.GetPoints()->GetItems().size()));

  #ifndef NDEBUG
  if (GetNumberOfFaces() != files.GetFaces()->GetMaxFaceIndex().Get())
  {
    TRACE("ERROR");
    TRACE(GetNumberOfFaces());
    TRACE(files.GetFaces()->GetMaxFaceIndex());
  }
  #endif
  */
  assert(GetNumberOfFaces() == files.GetFaces()->GetMaxFaceIndex().Get());
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

const boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Mesh::CreateBoundary() const noexcept
{
  std::vector<BoundaryFileItem> items;

  FaceIndex n_start_face(0);
  for (const boost::shared_ptr<Boundary> boundary: m_boundaries)
  {
    const int n_faces {
      static_cast<int>(boundary->GetFaces().size())
    };
    const BoundaryFileItem item(
      boundary->GetName(),
      boundary->GetType(),
      n_faces,
      n_start_face
    );
    items.push_back(item);
    n_start_face += FaceIndex(n_faces);
  }

  boost::shared_ptr<BoundaryFile> f {
    new BoundaryFile(
      BoundaryFile::GetDefaultHeader(),
      items
    )
  };
  assert(f);
  return f;
}

const std::vector<boost::shared_ptr<ribi::foam::Cell> > ribi::foam::Mesh::CreateEmptyCells(
  const Files& files)
{
  std::vector<boost::shared_ptr<ribi::foam::Cell> > cells;
  //assert(files.GetNeighbour()->GetNumberOfItems() > 0);

  const CellIndex n_cells = files.GetNeighbour()->CountNumberOfCells();
  assert(n_cells > CellIndex(0));
  for (CellIndex i=CellIndex(0); i!=n_cells; ++i)
  {
    const boost::shared_ptr<Cell> cell(
      new Cell
    );
    cells.push_back(cell);
  }
  assert(!cells.empty());
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

const boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Mesh::CreateFaces() const noexcept
{
  std::vector<FacesFileItem> items;

  //std::vector<boost::shared_ptr<const ribi::foam::Face>> faces;
  std::transform(
    m_faces.begin(),
    m_faces.end(),
    std::back_inserter(items),
    [this](const boost::shared_ptr<const Face> face)
    {
      assert(face);
      const std::vector<boost::shared_ptr<const ribi::Coordinat3D> > points {
        face->GetPoints()
      };
      std::vector<PointIndex> point_indices;
      std::transform(points.begin(),points.end(),
        std::back_inserter(point_indices),
        [this](boost::shared_ptr<const ribi::Coordinat3D> coordinat)
        {
          const std::vector<boost::shared_ptr<ribi::Coordinat3D>>::const_iterator iter {
            std::find(m_points.begin(),m_points.end(),coordinat)
          };
          assert(iter != m_points.end());
          const int index {
            std::distance(m_points.begin(),iter)
          };
          assert(index >= 0);
          assert(index < static_cast<int>(m_points.size()));
          return PointIndex(index);
        }
      );
      return FacesFileItem(point_indices);
    }
  );

  const boost::shared_ptr<FacesFile> f {
    new FacesFile(
      FacesFile::GetDefaultHeader(),
      items
    )
  };
  assert(f);
  return f;
}

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
  assert(faces.size() == files.GetFaces()->GetItems().size());
  return faces;
}

ribi::foam::Files ribi::foam::Mesh::CreateFiles() const noexcept
{
  boost::shared_ptr<BoundaryFile> boundary {
    CreateBoundary()
  };
  assert(boundary);
  boost::shared_ptr<FacesFile> faces {
    CreateFaces()
  };
  assert(faces);
  boost::shared_ptr<NeighbourFile> neighbour {
    CreateNeighbour()
  };
  assert(neighbour);
  boost::shared_ptr<OwnerFile> owner {
    CreateOwner()
  };
  assert(owner);
  boost::shared_ptr<PointsFile> points {
    CreatePoints()
  };
  assert(points);
  const Files f(
    boundary,
    faces,
    neighbour,
    owner,
    points
  );
  return f;
}

const boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Mesh::CreateNeighbour() const noexcept
{
  std::vector<NeighbourFileItem> v;
  for (boost::shared_ptr<Cell> cell: m_cells)
  {
    const boost::shared_ptr<const ribi::foam::Cell> neighbour { cell->GetNeighbour() };
    assert(neighbour);
    assert(std::find(m_cells.begin(),m_cells.end(),neighbour) != m_cells.end());

    const int index
      = std::distance(
        m_cells.begin(),
        std::find(m_cells.begin(),m_cells.end(),neighbour)
      );

    assert(index >= 0);
    assert(index < static_cast<int>(m_cells.size()));
    const CellIndex cell_index(index);
    const NeighbourFileItem item(cell_index);
    v.push_back(item);
  }

  const boost::shared_ptr<ribi::foam::NeighbourFile> p {
    new NeighbourFile(
      NeighbourFile::GetDefaultHeader(),
      v
    )
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Mesh::CreateOwner() const noexcept
{
  std::vector<OwnerFileItem> items;

  std::transform(
    m_faces.begin(),
    m_faces.end(),
    std::back_inserter(items),
    [this](const boost::shared_ptr<Face> face)
    {
      assert(face);
      const boost::shared_ptr<Cell> owner = face->GetOwner();
      assert(owner);
      const auto iter = std::find(m_cells.begin(),m_cells.end(),owner);
      assert(iter != m_cells.end());
      const int index = static_cast<int>(std::distance(m_cells.begin(),iter));
      assert(index >= 0);
      assert(index < static_cast<int>(m_cells.size()));
      const CellIndex cell_index(index);
      return OwnerFileItem(cell_index);
    }
  );

  const boost::shared_ptr<OwnerFile> p {
    new OwnerFile(
      OwnerFile::GetDefaultHeader(),
      items
    )
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Mesh::CreatePoints() const noexcept
{
  std::vector<PointsFileItem> items;
  std::transform(
    m_points.begin(),
    m_points.end(),
    std::back_inserter(items),
    [](const boost::shared_ptr<ribi::Coordinat3D> point)
    {
      assert(point);
      return PointsFileItem(*point);
    }
  );

  const boost::shared_ptr<PointsFile> p {
    new PointsFile(
      PointsFile::GetDefaultHeader(),
      items
    )
  };
  assert(p);
  return p;
}

const std::vector<boost::shared_ptr<ribi::Coordinat3D> >
  ribi::foam::Mesh::CreatePoints(const Files& files)
{
  std::vector<boost::shared_ptr<ribi::Coordinat3D> > v;
  for (const PointsFileItem& item: files.GetPoints()->GetItems())
  {
    static_assert(std::is_same<PointsFileItem,Point>(),
      "Point is a typedef for PointsFileItem"
    );
    const boost::shared_ptr<ribi::Coordinat3D> p {
      new ribi::Coordinat3D(item.GetCoordinat())

    };
    assert(p);
    v.push_back(p);
  }
  return v;
}

int ribi::foam::Mesh::GetNumberOfBoundaries() const noexcept
{
  return static_cast<int>(this->m_boundaries.size());
}

int ribi::foam::Mesh::GetNumberOfCells() const noexcept
{
  return static_cast<int>(m_cells.size());
}

int ribi::foam::Mesh::GetNumberOfFaces() const noexcept
{
  return static_cast<int>(m_faces.size());
}

int ribi::foam::Mesh::GetNumberOfPoints() const noexcept
{
  return static_cast<int>(m_points.size());
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const ribi::foam::Mesh& mesh)
{
  TRACE("Smallest: points");
  os << "Points: ";
  for (boost::shared_ptr<ribi::Coordinat3D> point: mesh.m_points)
  {
    assert(point);
    os << "* " << *point << '\n';
  }
  TRACE("Small: faces");
  os << "Faces:\n";
  for (boost::shared_ptr<Face> face: mesh.m_faces)
  {
    os
      << "* Neighbour: " << face->GetNeighbour() << '\n'
      << "* Owner: " << face->GetOwner() << '\n'
      << "* Coordinats: ";
    for(boost::shared_ptr<const ribi::Coordinat3D> coordinat: face->GetPoints())
    {
      os << coordinat << ' ';
    }
    os << '\n';
  }
  TRACE("Bigger: boundaries");
  os << "Boundary:\n";
  for (boost::shared_ptr<Boundary> boundary: mesh.m_boundaries)
  {
    os
      << "* Name: " << boundary->GetName() << '\n'
      << "* Type: " << boundary->GetType() << '\n'
      << "* Faces: ";
    for (const boost::shared_ptr<const Face> face: boundary->GetFaces())
    {
      os << face << ' ';
    }
    os << '\n';
  }

  TRACE("Biggest: cells");
  os << "Cells:\n";
  for (const boost::shared_ptr<Cell> cell: mesh.m_cells)
  {
    os << "* Neighbour: " << cell->GetNeighbour() << '\n'
       << "* Faces: ";
    for (boost::shared_ptr<const ribi::foam::Face> face: cell->GetOwnedFaces())
    {
      os << face << ' ';
    }
    os << '\n';
  }

  return os;
}

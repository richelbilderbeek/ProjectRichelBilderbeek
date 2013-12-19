#include "openfoammesh.h"

#include <cassert>
#include <ostream>
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
  const std::vector<boost::shared_ptr<Boundary>>& boundaries,
  const std::vector<boost::shared_ptr<Cell>>& cells,
  const std::vector<boost::shared_ptr<Face>>& faces,
  const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points
  )
  : m_boundaries(boundaries),
    m_cells(cells),
    m_faces(faces),
    m_points(points)
{
  #ifndef NDEBUG
  Test();
  for (const boost::shared_ptr<Face> face: m_faces)
  {
    assert(face);
    assert(face->GetOwner());
    assert( (face->GetNeighbour() || !face->GetNeighbour() )
      && "internalMesh faces have a neighbour, defaultWall faces don't"
    );
  }
  #endif

  if (!AreFacesOrdered())
  {
    ReorderFaces();
  }

  #ifndef NDEBUG
  assert(AreFacesOrdered());
  const Files f(this->CreateFiles());
  assert(f.GetFaces()->GetItems().size() == faces.size());
  assert(f.GetBoundary()->GetItems().size() == boundaries.size());
  assert(f.GetPoints()->GetItems().size() == points.size());
  #endif

}

ribi::foam::Mesh::Mesh(
  const Files& files,
  const std::vector<boost::shared_ptr<ribi::Coordinat3D>>& points
  )
  : m_boundaries{},
    m_cells{CreateEmptyCells(files)},
    m_faces{CreateFacesWithPoints(files,points)},
    m_points(points)
{
  #ifndef NDEBUG
  Test();
  #endif
  //Add Cell owner to Faces
  {
    assert(!m_cells.empty());
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
  //Add neighbours to Cells
  {
    const int n_faces = static_cast<int>(m_faces.size());
    for (int i=0; i!=n_faces; ++i)
    {
      const FaceIndex index(i);
      assert(files.GetNeighbour());
      //Not all Faces have a neighbour
      if (!files.GetNeighbour()->CanGetItem(index)) continue;
      assert(files.GetNeighbour()->CanGetItem(index));
      const CellIndex neighbour_index {
        files.GetNeighbour()->GetItem(index).GetCellIndex()
      };
      assert(i < static_cast<int>(m_faces.size()));
      assert(neighbour_index.Get() < static_cast<int>(m_cells.size()));
      assert(!m_faces[i]->GetNeighbour());
      m_faces[i]->AssignNeighbour( m_cells[ neighbour_index.Get() ] );
      assert(m_faces[i]->GetNeighbour());
    }
  }

  //Assign boundaries
  m_boundaries = CreateBoundaries(files,m_faces);

  //Check
  #ifndef NDEBUG
  for (boost::shared_ptr<Cell> cell: m_cells)
  {
    assert(cell);
    //assert( (cell->GetNeighbour() || !cell->GetNeighbour())
    //  && "Not all cells have a neighbour, for example in a 1x1x1 mesh");
  }

  if (GetNumberOfBoundaries() != files.GetBoundary()->GetMaxBoundaryIndex().Get())
  {
    TRACE("ERROR");
    TRACE(GetNumberOfBoundaries());
    TRACE(files.GetBoundary()->GetMaxBoundaryIndex());
  }
  #endif
  assert(GetNumberOfBoundaries() == files.GetBoundary()->GetMaxBoundaryIndex().Get());

  assert(GetNumberOfFaces() == files.GetFaces()->GetMaxFaceIndex().Get());
}

bool ribi::foam::Mesh::AreFacesOrdered() const noexcept
{
  for (const boost::shared_ptr<Boundary> boundary: m_boundaries)
  {
    assert(!boundary->GetFaces().empty());
    #ifndef NDEBUG
    const int n_faces {
      static_cast<int>(boundary->GetFaces().size())
    };
    assert(n_faces > 0);
    #endif
    //Determine the start face: at which indices are the Faces in m_faces?
    std::vector<int> indices;
    std::transform(boundary->GetFaces().begin(),boundary->GetFaces().end(),std::back_inserter(indices),
      [this](const boost::shared_ptr<Face> face)
      {
        const std::vector<boost::shared_ptr<Face>>::const_iterator iter {
          std::find(m_faces.begin(),m_faces.end(),face)
        };
        assert(iter != m_faces.end());
        const int index = std::distance(m_faces.begin(),iter);
        assert(index >= 0);
        assert(index < static_cast<int>(m_faces.size()));
        return index;
      }
    );
    assert(!indices.empty());
    assert(indices.size() == boundary->GetFaces().size());
    std::sort(indices.begin(),indices.end());
    const std::size_t n_indices = indices.size();
    if (n_indices > 1)
    {
      for (std::size_t i=1; i!=n_indices; ++i)
      {
        assert(indices[i-1] != indices[i]  && "All face indices must be unique");
        if (indices[i-1] + 1 != indices[i])
        {
          return false;
        }
      }
    }
  }
  return true;
}


double ribi::foam::Mesh::CalcSimilarity(
  const std::vector<ribi::Coordinat3D>& v,
  const std::vector<ribi::Coordinat3D>& w) noexcept
{
  if (v.size() != w.size()) return std::numeric_limits<double>::max();
  const double distance {
    std::accumulate(v.begin(),v.end(),0.0,
      [w](const double init,const ribi::Coordinat3D& c)
      {
        //Find the closest coordinat in w to c
        const std::vector<ribi::Coordinat3D>::const_iterator closest {
          std::min_element(w.begin(),w.end(),
            [c](const ribi::Coordinat3D& lhs, const ribi::Coordinat3D& rhs)
            {
              return Distance(lhs,c) < Distance(rhs,c);
            }
          )
        };
        return init + Distance(c,*closest);
      }
    )
  };
  return distance;
}

double ribi::foam::Mesh::CalcSimilarity(
  const std::vector<boost::shared_ptr<const ribi::Coordinat3D> >& v,
  const std::vector<ribi::Coordinat3D>& w) noexcept
{
  if (v.size() != w.size()) return std::numeric_limits<double>::max();
  const double distance {
    std::accumulate(v.begin(),v.end(),0.0,
      [w](const double init,const boost::shared_ptr<const ribi::Coordinat3D>& c)
      {
        //Find the closest coordinat in w to c
        const std::vector<ribi::Coordinat3D>::const_iterator closest {
          std::min_element(w.begin(),w.end(),
            [c](const ribi::Coordinat3D& lhs, const ribi::Coordinat3D& rhs)
            {
              return Distance(lhs,*c) < Distance(rhs,*c);
            }
          )
        };
        return init + Distance(*c,*closest);
      }
    )
  };
  return distance;
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


  for (const boost::shared_ptr<Boundary> boundary: m_boundaries)
  {
    assert(!boundary->GetFaces().empty());
    const int n_faces {
      static_cast<int>(boundary->GetFaces().size())
    };
    assert(n_faces > 0);
    //Determine the start face: at which indices are the Faces in m_faces?
    std::vector<int> indices;
    std::transform(boundary->GetFaces().begin(),boundary->GetFaces().end(),std::back_inserter(indices),
      [this](const boost::shared_ptr<Face> face)
      {
        const std::vector<boost::shared_ptr<Face>>::const_iterator iter {
          std::find(m_faces.begin(),m_faces.end(),face)
        };
        assert(iter != m_faces.end());
        const int index = std::distance(m_faces.begin(),iter);
        assert(index >= 0);
        assert(index < static_cast<int>(m_faces.size()));
        return index;
      }
    );
    assert(!indices.empty());
    assert(indices.size() == boundary->GetFaces().size());
    std::sort(indices.begin(),indices.end());
    #ifndef NDEBUG
    const std::size_t n_indices = indices.size();
    if (n_indices > 1)
    {
      for (std::size_t i=1; i!=n_indices; ++i)
      {
        assert(indices[i-1] != indices[i]
          && "All face indices must be unique");
        if (indices[i-1] + 1 != indices[i])
        {
          TRACE("ERROR");
        }
        assert(indices[i-1] + 1 == indices[i]
          && "All face indices must be adjacent");
      }
    }
    #endif

    const FaceIndex n_start_face = FaceIndex(indices[0]);
    //TRACE(n_start_face);
    const BoundaryFileItem item(
      boundary->GetName(),
      boundary->GetType(),
      n_faces,
      n_start_face
    );
    items.push_back(item);
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
  for (boost::shared_ptr<Face> face: m_faces)
  {
    assert(face);
    const boost::shared_ptr<const ribi::foam::Cell> neighbour { face->GetNeighbour() };

    assert( (neighbour || !neighbour)
      && "Not all cells have a neighbour, for example in a 1x1x1 mesh");
    if (!neighbour) continue;

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

const boost::shared_ptr<const ribi::foam::Face> ribi::foam::Mesh::FindMostSimilarFace(
  const std::vector<ribi::Coordinat3D>& coordinats
  ) const
{
  ///Obtain the distance from focal coordindat to each face its coordinat
  std::vector<double> distances;
  const std::size_t sz = coordinats.size();
  for (std::size_t i=0; i!=sz; ++i)
  {
    const double distance = CalcSimilarity(
      m_faces[i]->GetPoints(),
      coordinats
    );
    distances.push_back(distance);
  }

  //Find the most similar
  const int index {
    std::distance(
      distances.begin(),
      std::min_element(distances.begin(),distances.end())
    )
  };

  //Return the face
  const boost::shared_ptr<const ribi::foam::Face> p {
    m_faces[index]
  };
  assert(p);
  return p;
}

const std::vector<boost::shared_ptr<const ribi::foam::Face> > ribi::foam::Mesh::GetFaces() const noexcept
{
  std::vector<boost::shared_ptr<const ribi::foam::Face> > v;
  std::transform(
    m_faces.begin(),m_faces.end(),
    std::back_inserter(v),
    [](boost::shared_ptr<ribi::foam::Face> old_face)
    {
      const boost::shared_ptr<const ribi::foam::Face> new_face(old_face);
      assert(old_face == new_face);
      return new_face;
    }
  );
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

void ribi::foam::Mesh::ReorderFaces()
{
  assert(!this->AreFacesOrdered());

  const std::size_t n_boundaries = m_boundaries.size();
  std::size_t new_face_index = 0; //The index to put the next Face at
  for (std::size_t i=0; i!=n_boundaries; ++i)
  {
    const boost::shared_ptr<Boundary> boundary = m_boundaries[i];
    const std::size_t n_faces = boundary->GetFaces().size();
    for (std::size_t j=0; j!=n_faces; ++j)
    {
      assert(j < boundary->GetFaces().size());
      const std::vector<boost::shared_ptr<Face> >::iterator here {
        std::find(m_faces.begin(),m_faces.end(),boundary->GetFaces()[j])
      };
      assert(here != m_faces.end());
      const std::size_t old_face_index = std::distance(m_faces.begin(),here);
      assert(old_face_index >= new_face_index);
      std::swap(m_faces[old_face_index],m_faces[new_face_index]);
      ++new_face_index;
    }
  }


  assert(this->AreFacesOrdered());
}


#ifndef NDEBUG
void ribi::foam::Mesh::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::Mesh::Test");
  //Check if the number of boundary faces is correct
  {
    const std::vector<boost::shared_ptr<ribi::foam::Files>> v { Files::CreateTestFiles() };
    assert(v.size() == 6);
    const std::vector<int> n_internal_mesh_faces_expected { 0,0,1,4,12,133 };
    assert(v.size() == n_internal_mesh_faces_expected.size());
    const int n_meshes = static_cast<int>(v.size());
    for (int mesh_index = 0; mesh_index != n_meshes; ++mesh_index)
    {
      const Mesh mesh(*v[mesh_index]);
      const std::vector<boost::shared_ptr<const Face> > mesh_faces {
        mesh.GetFaces()
      };
      const int n_internal {
        std::count_if(mesh_faces.begin(),mesh_faces.end(),
          [](const boost::shared_ptr<const Face> face)
          {
            assert(face);
            assert(face->GetOwner());
            return face->GetNeighbour(); //internal faces have a neighbour
          }
        )
      };
      assert(n_internal == n_internal_mesh_faces_expected[mesh_index]
        && "Must have as much internal faces as expected"
      );
    }
  }
  //Find most similar Faces
  {
    //Handcraft Faces, put these in mesh

    //Points as log 12 page 48
    const boost::shared_ptr<ribi::Coordinat3D> p0 { new ribi::Coordinat3D(0.0,0.0,0.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p1 { new ribi::Coordinat3D(1.0,0.0,0.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p2 { new ribi::Coordinat3D(1.0,1.0,0.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p3 { new ribi::Coordinat3D(0.0,1.0,0.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p4 { new ribi::Coordinat3D(0.0,0.0,1.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p5 { new ribi::Coordinat3D(1.0,0.0,1.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p6 { new ribi::Coordinat3D(1.0,1.0,1.0) };
    const boost::shared_ptr<ribi::Coordinat3D> p7 { new ribi::Coordinat3D(0.0,1.0,1.0) };
    assert(p0); assert(p1); assert(p2); assert(p3);
    assert(p4); assert(p5); assert(p6); assert(p7);
    const boost::shared_ptr<Cell> cell { new Cell };
    const std::vector<boost::shared_ptr<Cell>> cells { cell };

    const boost::shared_ptr<Cell> n0; //No neighbours in a 1x1 mesh
    const boost::shared_ptr<Cell> n1; //No neighbours in a 1x1 mesh
    const boost::shared_ptr<Cell> n2; //No neighbours in a 1x1 mesh
    const boost::shared_ptr<Cell> n3; //No neighbours in a 1x1 mesh
    const boost::shared_ptr<Cell> n4; //No neighbours in a 1x1 mesh
    const boost::shared_ptr<Cell> n5; //No neighbours in a 1x1 mesh
    const boost::shared_ptr<Cell> own0 { cell }; //The only Cell owns all Faces
    const boost::shared_ptr<Cell> own1 { cell }; //The only Cell owns all Faces
    const boost::shared_ptr<Cell> own2 { cell }; //The only Cell owns all Faces
    const boost::shared_ptr<Cell> own3 { cell }; //The only Cell owns all Faces
    const boost::shared_ptr<Cell> own4 { cell }; //The only Cell owns all Faces
    const boost::shared_ptr<Cell> own5 { cell }; //The only Cell owns all Faces

    const std::vector<boost::shared_ptr<ribi::Coordinat3D>> points { p0,p1,p2,p3,p4,p5,p6,p7 };
    const boost::shared_ptr<Face> f0 { new Face(n0,own0, { p0, p2, p3, p1 } ) };
    const boost::shared_ptr<Face> f1 { new Face(n1,own1, { p0, p4, p6, p2 } ) };
    const boost::shared_ptr<Face> f2 { new Face(n2,own2, { p0, p1, p5, p4 } ) };
    const boost::shared_ptr<Face> f3 { new Face(n3,own3, { p1, p3, p7, p5 } ) };
    const boost::shared_ptr<Face> f4 { new Face(n4,own4, { p2, p6, p7, p3 } ) };
    const boost::shared_ptr<Face> f5 { new Face(n5,own5, { p4, p5, p7, p6 } ) };

    const std::vector<boost::shared_ptr<Face>> faces { f0,f1,f2,f3,f4,f5,f6 };
    cell->AssignOwnedFaces( { f0,f1,f2,f3,f4,f5,f6 } );

    boost::shared_ptr<Boundary> boundary { new Boundary(  {f0,f1,f2,f3,f4,f5,f6 },"defaultFaces","patch" ) };
    const std::vector<boost::shared_ptr<Boundary>> boundaries { boundary };

    const Mesh m(
      boundaries,
      cells,
      faces,
      points
    );
    for (const boost::shared_ptr<Face> face: faces)
    {
      //For every Face, extract the coordinats
      //FindMostSimilar should find back the original Face
      assert(m.FindMostSimilarFace(face->GetPoints()) == face);
    }
  }
  TRACE("Finished ribi::foam::Mesh::Test successfully");
}
#endif


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
    os
       //<< "* Neighbour: " << cell->GetNeighbour() << '\n'
       << "* Faces: ";
    for (boost::shared_ptr<const ribi::foam::Face> face: cell->GetOwnedFaces())
    {
      os << face << ' ';
    }
    os << '\n';
  }

  return os;
}

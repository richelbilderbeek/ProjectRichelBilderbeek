#include "openfoamfiles.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QFile>

#include "fileio.h"
#include "filename.h"
#include "openfoamboundaryfile.h"
#include "openfoamfacesfile.h"
#include "openfoamneighbourfile.h"
#include "openfoamownerfile.h"
#include "openfoamfilenames.h"
#include "openfoampointsfile.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::foam::Files::Files(const std::string& folder_name)
  : m_boundary(CreateBoundary(folder_name)),
    m_faces(CreateFaces(folder_name)),
    m_neighbour(CreateNeighbour(folder_name)),
    m_owner(CreateOwner(folder_name)),
    m_points(CreatePoints(folder_name))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(ribi::fileio::IsFolder(folder_name));
  assert(m_boundary);
  assert(m_faces);
  assert(m_neighbour);
  assert(m_owner);
  assert(m_points);
}

ribi::foam::Files::Files(
  const boost::shared_ptr<BoundaryFile> boundary,
  const boost::shared_ptr<FacesFile> faces,
  const boost::shared_ptr<NeighbourFile> neighbour,
  const boost::shared_ptr<OwnerFile> owner,
  const boost::shared_ptr<PointsFile> points
)
  : m_boundary(boundary),
    m_faces(faces),
    m_neighbour(neighbour),
    m_owner(owner),
    m_points(points)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_boundary);
  assert(m_faces);
  assert(m_neighbour);
  assert(m_owner);
  assert(m_points);
}

const boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Files::CreateBoundary(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetBoundary().Get()
  );
  assert(fileio::IsRegularFile(filename));
  std::ifstream is(filename.Get().c_str());
  boost::shared_ptr<ribi::foam::BoundaryFile> p {
    new ribi::foam::BoundaryFile(is)
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Files::CreateDefaultBoundary() noexcept
{
  const boost::shared_ptr<BoundaryFile> p {
    new BoundaryFile
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Files::CreateDefaultFaces() noexcept
{
  const boost::shared_ptr<FacesFile> p {
    new FacesFile
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Files::CreateDefaultNeighbour() noexcept
{
  const boost::shared_ptr<NeighbourFile> p {
    new NeighbourFile
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Files::CreateDefaultOwner() noexcept
{
  const boost::shared_ptr<OwnerFile> p {
    new OwnerFile
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Files::CreateDefaultPoints() noexcept
{
  const boost::shared_ptr<PointsFile> p {
    new PointsFile
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Files::CreateFaces(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetFaces().Get()
  );
  std::ifstream is(filename.Get().c_str());
  boost::shared_ptr<ribi::foam::FacesFile> p {
    new ribi::foam::FacesFile(is)
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::Filenames> ribi::foam::Files::CreateFilenames() noexcept
{
  const boost::shared_ptr<ribi::foam::Filenames> p {
    new Filenames
  };
  assert(p);
  return p;
}

void ribi::foam::Files::CreateFolders(const std::string& folder_name)
{
  {
    const std::string s { fileio::GetPathSeperator() };
    const std::string f { folder_name + s + std::string("constant") };
    if (!fileio::IsFolder(f)) { fileio::CreateFolder(f); }
    assert(fileio::IsFolder(f));
  }
  {
    const std::string s { fileio::GetPathSeperator() };
    const std::string f { folder_name + s + std::string("constant") + s + std::string("polyMesh") };
    if (!fileio::IsFolder(f)) { fileio::CreateFolder(f); }
    assert(fileio::IsFolder(f));
  }
}

const boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Files::CreateNeighbour(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetNeighbour().Get()
  );
  std::ifstream is(filename.Get().c_str());
  boost::shared_ptr<ribi::foam::NeighbourFile> p {
    new ribi::foam::NeighbourFile(is)
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Files::CreateOwner(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetOwner().Get()
  );
  std::ifstream is(filename.Get().c_str());
  boost::shared_ptr<ribi::foam::OwnerFile> p {
    new ribi::foam::OwnerFile(is)
  };
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Files::CreatePoints(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetPoints().Get()
  );
  std::ifstream is(filename.Get().c_str());
  boost::shared_ptr<ribi::foam::PointsFile> p {
    new ribi::foam::PointsFile(is)
  };
  assert(p);
  return p;
}

void ribi::foam::Files::CreateTestFiles(const std::string& folder_name)
{
  CreateFolders(folder_name);

  //Read from testing file
  for (const std::string filename:
    {
      BoundaryFile::GetDefaultHeader().GetObject(),
      FacesFile::GetDefaultHeader().GetObject(),
      NeighbourFile::GetDefaultHeader().GetObject(),
      OwnerFile::GetDefaultHeader().GetObject(),
      PointsFile::GetDefaultHeader().GetObject()
    }
  )
  {
    const std::string resources_path { ":/CppOpenFoam/files/" + filename };
    const std::string destination_path {
      folder_name
      + fileio::GetPathSeperator()
      + "constant"
      + fileio::GetPathSeperator()
      + "polyMesh"
      + fileio::GetPathSeperator()
      + filename
    };
    QFile f(resources_path.c_str());
    f.copy(destination_path.c_str());
    assert(fileio::IsRegularFile(destination_path));
  }
}

void ribi::foam::Files::SetOwner(const boost::shared_ptr<ribi::foam::OwnerFile>& owner) noexcept
{
  assert(owner);
  m_owner = owner;
}

void ribi::foam::Files::Swap(const ribi::foam::FaceIndex& lhs, const ribi::foam::FaceIndex& rhs)
{
  assert(lhs != rhs);
  //Boundary
  {
    //Cleanest interface I could think of
    //m_boundary->Swap(lhs,rhs);
    /*

    boost::shared_ptr<int> lhs_n_faces;
    if (m_boundary->CanGetItem(lhs))
    {
      lhs_n_faces.reset(new int(m_boundary->Find(lhs).GetNfaces()));
    }
    boost::shared_ptr<int> rhs_n_faces;
    {

    }
    const BoundaryIndex lhs_boundary_index = m_boundary->GetItem(lhs).GetCellIndex();
    const BoundaryIndex rhs_boundary_index = m_owner->GetItem(rhs).GetCellIndex();

    //Set swapped
    m_owner->SetItem(lhs,OwnerFileItem(rhs_cell_index));
    m_owner->SetItem(rhs,OwnerFileItem(lhs_cell_index));
   */
  }
  //Neighbour
  {
    //Can only swap two cellIndices when either both of them are absent
    //(both cells are boundary cells)
    //or both of them are present
    //(both cells are non-boundary cells)
    const bool lhs_is_boundary = m_neighbour->CanGetItem(lhs);
    const bool rhs_is_boundary = m_neighbour->CanGetItem(rhs);
    assert(lhs_is_boundary == rhs_is_boundary
      && "Can only swap two boundary or two non-boundary faces");

    if (lhs_is_boundary)
    {
      assert(rhs_is_boundary);
      //Done! Boundary cells have no neighbours
    }
    else
    {
      const CellIndex lhs_cell_index = m_neighbour->GetItem(lhs).GetCellIndex();
      const CellIndex rhs_cell_index = m_neighbour->GetItem(rhs).GetCellIndex();

      //Set swapped
      m_neighbour->SetItem(lhs,NeighbourFileItem(rhs_cell_index));
      m_neighbour->SetItem(rhs,NeighbourFileItem(lhs_cell_index));
    }
  }
  //Owner
  {
    const CellIndex lhs_cell_index = m_owner->GetItem(lhs).GetCellIndex();
    const CellIndex rhs_cell_index = m_owner->GetItem(rhs).GetCellIndex();

    //Set swapped
    m_owner->SetItem(lhs,OwnerFileItem(rhs_cell_index));
    m_owner->SetItem(rhs,OwnerFileItem(lhs_cell_index));
  }
}

#ifndef NDEBUG
void ribi::foam::Files::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::foam::Files::Test");
  //operator==
  {
    const Files f;
    assert(f == f);
    const Files g;
    assert(f == g);
    assert(g == f);
    assert(g == g);
  }
  //operator==
  {
    const Files f;
    assert(f == f);
    const Files g;
    assert(f == g);
    assert(g == f);
    assert(g == g);
  }
  //operator!=
  {
    Files f;
    Files g;
    assert(f == g);
    const std::vector<OwnerFileItem> items_1 {
      OwnerFileItem(CellIndex(0)),
      OwnerFileItem(CellIndex(1)),
      OwnerFileItem(CellIndex(2))
    };
    const std::vector<OwnerFileItem> items_2 {
      OwnerFileItem(CellIndex(0)),
      OwnerFileItem(CellIndex(1)),
      OwnerFileItem(CellIndex(4))
    };
    const boost::shared_ptr<OwnerFile> owner_1 {
      new OwnerFile(OwnerFile::GetDefaultHeader(),items_1)
    };
    const boost::shared_ptr<OwnerFile> owner_2 {
      new OwnerFile(OwnerFile::GetDefaultHeader(),items_2)
    };
    assert(*owner_1 != *owner_2);
    f.SetOwner(owner_1);
    assert(f != g);
    g.SetOwner(owner_2);
    assert(f != g);
    f.SetOwner(owner_2);
    assert(f == g);
  }
  //Swap faces
  {
    const std::string temp_folder = "tmp_folder";
    CreateTestFiles(temp_folder);

    const Files f(temp_folder);
    assert(f == f);
    Files g(temp_folder);
    assert(f == g);
    assert(g == f);
    assert(g == g);
    const FaceIndex i(1);
    const FaceIndex j(11);
    g.Swap(i,j);
    assert(g != f);
    assert(f != g);
    g.Swap(i,j);
    assert(f == g);
  }
  TRACE("Finished ribi::foam::Files::Test successfully");
}
#endif

bool ribi::foam::operator==(const ribi::foam::Files& lhs, const ribi::foam::Files& rhs)
{
  return
       ((*lhs.GetBoundary())  == (*rhs.GetBoundary()))
    && ((*lhs.GetFaces())     == (*rhs.GetFaces()))
    && ((*lhs.GetNeighbour()) == (*rhs.GetNeighbour()))
    && ((*lhs.GetOwner())     == (*rhs.GetOwner()))
    && ((*lhs.GetPoints())    == (*rhs.GetPoints()));
}

bool ribi::foam::operator!=(const ribi::foam::Files& lhs, const ribi::foam::Files& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const Files& files)
{
  os
    << (*files.GetBoundary()) << '\n'
    << (*files.GetFaces())    << '\n'
    << (*files.GetNeighbour()) << '\n'
    << (*files.GetOwner())     << '\n'
    << (*files.GetPoints())
  ;
  return os;
}

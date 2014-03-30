#include "openfoamfiles.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>

#include <QFile>

#include "fileio.h"

#include "openfoamboundaryfile.h"
#include "openfoamfacesfile.h"
#include "openfoamneighbourfile.h"
#include "openfoamownerfile.h"
#include "openfoamfilenames.h"
#include "openfoampointsfile.h"
#include "trace.h"
#pragma GCC diagnostic pop

/*
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
  assert(ribi::fileio::FileIo().IsFolder(folder_name));
  assert(m_boundary);
  assert(m_faces);
  assert(m_neighbour);
  assert(m_owner);
  assert(m_points);
}
*/

ribi::foam::Files::Files(
  const boost::shared_ptr<BoundaryFile> boundary,
  const boost::shared_ptr<FacesFile> faces,
  const boost::shared_ptr<NeighbourFile> neighbour,
  const boost::shared_ptr<OwnerFile> owner,
  const boost::shared_ptr<PointsFile> points
) : m_boundary(boundary),
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

  #ifndef NDEBUG
  CheckMe();
  #endif

}

ribi::foam::Files::Files(const Files& other)
  : m_boundary(boost::make_shared<BoundaryFile>(*other.m_boundary)),
    m_faces(boost::make_shared<FacesFile>(*other.m_faces)),
    m_neighbour(boost::make_shared<NeighbourFile>(*other.m_neighbour)),
    m_owner(boost::make_shared<OwnerFile>(*other.m_owner)),
    m_points(boost::make_shared<PointsFile>(*other.m_points))
{

  #ifndef NDEBUG
  Test();
  #endif
  assert(m_boundary);
  assert(m_faces);
  assert(m_neighbour);
  assert(m_owner);
  assert(m_points);

  assert(*m_boundary == *other.m_boundary && "Must be a copy");
  assert( m_boundary !=  other.m_boundary && "Must be a deep copy");
  assert(*m_faces == *other.m_faces && "Must be a copy");
  assert( m_faces !=  other.m_faces && "Must be a deep copy");

  assert(*m_neighbour == *other.m_neighbour && "Must be a copy");
  assert( m_neighbour !=  other.m_neighbour && "Must be a deep copy");

  assert(*m_owner == *other.m_owner && "Must be a copy");
  assert( m_owner !=  other.m_owner && "Must be a deep copy");

  assert(*m_points == *other.m_points && "Must be a copy");
  assert( m_points !=  other.m_points && "Must be a deep copy");

  #ifndef NDEBUG
  CheckMe();
  #endif
}

void ribi::foam::Files::CheckMe() const
{
  TRACE_FUNC();
  assert(m_faces);
  assert(m_points);
  const FaceIndex n_faces { FaceIndex(static_cast<int>(this->m_faces->GetItems().size())) };
  const PointIndex n_points { PointIndex(static_cast<int>(this->m_points->GetItems().size())) };

  TRACE("CheckMe: 'boundary' file individuals items");
  for (const BoundaryFileItem& item: m_boundary->GetItems())
  {
    std::stringstream s;
    s << "Error in 'boundary' file in this item:\n"
      << '\n'
      << item << '\n'
      << '\n';
    if (item.GetNfaces() <= 0)
    {
      s << "nFaces (" << item.GetNfaces() << ") must be a positive non-zero value";
      throw std::logic_error(s.str());
    }
    if (item.GetStartFace() > n_faces)
    {
      s << "startFace (" << item.GetStartFace() << ") beyond number of faces (" << n_faces << ")";
      throw std::logic_error(s.str());
    }
    if (item.GetStartFace() + FaceIndex(item.GetNfaces()) > n_faces)
    {
      s << "startFace (" << item.GetStartFace() << ")"
        << " + nFaces (" << n_faces << ")"
        << " = " << (item.GetStartFace() + FaceIndex(item.GetNfaces()))
        << " is beyond number of faces (" << n_faces << ")"
        ;
      throw std::logic_error(s.str());
    }
  }
  TRACE("CheckMe: 'boundary' file: no ranges should overlap");
  const int n_boundary_items { static_cast<int>(m_boundary->GetItems().size()) };
  for (int i=0; i!=n_boundary_items; ++i)
  {
    const BoundaryFileItem item_i = m_boundary->GetItems()[i];
    const FaceIndex first_i = item_i.GetStartFace();
    assert(first_i.Get() >= 0);
    assert(item_i.GetNfaces() >= 0);
    const FaceIndex last_i = first_i + FaceIndex(item_i.GetNfaces());
    for (int j=0; j!=n_boundary_items; ++j)
    {
      if (i == j) continue;
      const BoundaryFileItem item_j = m_boundary->GetItems()[j];
      const FaceIndex first_j = item_j.GetStartFace();
      assert(item_j.GetNfaces() >= 0);
      const FaceIndex last_j = first_j + FaceIndex(item_j.GetNfaces());
      if ( (first_i >= first_j && first_i < last_j)
        || (last_i  >  first_j && last_i  < last_j)
        || (first_j >= first_i && first_j < last_i)
        || (last_j  >  first_i && last_j  < last_i)
      )
      {
        TRACE(*m_boundary);
        std::stringstream s;
        s << "Error in 'boundary' file in these items:\n"
          << '\n'
          << item_i << '\n'
          << '\n'
          << item_j << '\n'
          << '\n'
          << "Face index ranges overlap: "
          << "[" << first_i << "," << last_i << "> and "
          << "[" << first_j << "," << last_j << ">";
        throw std::logic_error(s.str());
      }
    }
  }
  //
  TRACE("CheckMe: 'faces' files: point indices must be valid");
  for (const FacesFileItem& item: m_faces->GetItems())
  {
    for (const PointIndex& index: item.GetPointIndices())
    {
      assert(index.Get() >= 0);
      if (index >= n_points)
      {
        std::stringstream s;
        s << "Error in 'faces' file in this item:\n"
          << '\n'
          << item << '\n'
          << '\n'
          << "point index (" << index << ") beyond number of points (" << n_points << ")"
        ;
        throw std::logic_error(s.str());

      }
    }
  }
  const bool do_check_doubles = false;
  if (do_check_doubles)
  {
    TRACE("CheckMe: 'faces' files: detect doublures: START");
    {
      for (FaceIndex i = FaceIndex(0); i!=n_faces; ++i)
      {
        std::vector<PointIndex> v_i { m_faces->GetItem(i).GetPointIndices() };
        std::sort(v_i.begin(),v_i.end());
        for (FaceIndex j = FaceIndex(0); j!=n_faces; ++j)
        {
          if (i == j) continue;
          std::vector<PointIndex> v_j { m_faces->GetItem(j).GetPointIndices() };
          std::sort(v_j.begin(),v_j.end());
          if (v_i == v_j)
          {
            std::stringstream s;
            s << "Error in 'faces' file in these items:\n"
              << "\n"
              << "Item " << i << ": " << m_faces->GetItem(i) << '\n'
              << "Item " << j << ": " << m_faces->GetItem(j) << '\n'
              << "\n"
              << "Faces at index " << i << " and " << j << " consist of the same Point indices";
            ;
            throw std::logic_error(s.str());

          }
        }

      }
    }
  }
  else
  {
    TRACE("CheckMe: 'faces' files: detect doublures: SKIP");
  }

  TRACE("CheckMe: 'owner' files");
  if (m_owner->GetItems().size() != m_faces->GetItems().size())
  {
    std::stringstream s;
    s << "The file 'owner' has a different amount of faces than 'faces':\n"
      << "'faces' has " << m_faces->GetItems().size()
      << ", where 'owner' has " << m_owner->GetItems().size()
      << '\n'
    ;
    throw std::logic_error(s.str());
  }

  #ifdef SURE_THIS_CODE_CANNOT_BE_REUSED_20131212
  //Faces that have the same owner (which is a cell index) are member of the same cell
  //Each point index of all faces must be present at least one times: at least three faces are
  //needed at each vertex to form an enclosing/non-leaking cell surface, yet not all faces
  //are owned by each cell
  //Because each point index must be present once, it has no use collecting these
  {
    std::map<CellIndex,std::multiset<PointIndex>> m;
    for (FaceIndex face_index = FaceIndex(0); face_index!=n_faces; ++face_index)
    {
      //Find the point indices of this face
      const std::vector<PointIndex> p { m_faces->GetItem(face_index).GetPointIndices() };

      //Find the owner of this face
      const CellIndex c { m_owner->GetItem(face_index).GetCellIndex() };

      //Add the combination to m
      if (m.find(c) == m.end()) { m.insert(std::make_pair(c,std::multiset<PointIndex>())); }
      assert(m.find(c) != m.end());
      std::copy(p.begin(),p.end(),std::inserter(m.find(c)->second,m.find(c)->second.begin()));
    }
    //Check that each point index is present at least twice
    for (const std::pair<CellIndex,std::multiset<PointIndex>>& s: m)
    {
      for (const PointIndex& i: s.second)
      {
        const int count = s.second.count(i);
        if (count < 2)
        {
          TRACE(*m_owner);
          TRACE(*m_faces);
          std::stringstream str;
          str
            << "Error in 'owner' and 'faces' file combination:\n"
            << "The file 'owner' has faces owned by the same cell,"
            << "of which these faces do not cover each vertex with at least two times\n"
            << '\n'
            << "In this case, cell index " << s.first
            << " its faces have a point index " << i << " that is only a member of "
            << count << " faces"
          ;
          throw std::logic_error(str.str());

        }
      }
    }
  }
  #endif
  TRACE("CheckMe finished successfully");
}

boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Files::CreateBoundary(
  const std::string& folder_name)
{
  std::cout << (__func__) << std::endl;

  assert(ribi::fileio::FileIo().IsFolder(folder_name));

  const std::string filename(
    (folder_name.empty() ? folder_name : folder_name + fileio::FileIo().GetPathSeperator())
    + CreateFilenames()->GetBoundary()
  );
  #ifndef NDEBUG
  if (!fileio::FileIo().IsRegularFile(filename))
  {
    TRACE(filename);
    TRACE("BREAK");
  }
  #endif

  assert(fileio::FileIo().IsRegularFile(filename));

  std::ifstream is(filename.c_str());

  try
  {

    const boost::shared_ptr<ribi::foam::BoundaryFile> p {
      new ribi::foam::BoundaryFile(filename)
    };

    assert(p);
    return p;
  }
  catch(std::runtime_error& e)
  {

    std::stringstream s;
    s << "File '" << filename << "' is not an OpenFOAM 'boundary' file: "
      << e.what();
    throw std::runtime_error(s.str());
  }
}

void ribi::foam::Files::CreateCopy(
  const ribi::foam::Files& files,
  const std::string copy_folder_name) noexcept
{
  #ifndef NDEBUG
  if (fileio::FileIo().IsFolder(copy_folder_name))
  {
    TRACE(copy_folder_name);
  }
  #endif
  assert(!fileio::FileIo().IsFolder(copy_folder_name)
    && "Cannot make a copy in an existing folder");

  CreateFolders(copy_folder_name);
  //boundary
  {
    const std::string destination_path {
        copy_folder_name
      + fileio::FileIo().GetPathSeperator()
      + BoundaryFile::GetDefaultHeader().GetLocation()
      + fileio::FileIo().GetPathSeperator()
      + BoundaryFile::GetDefaultHeader().GetObject()
    };
    std::ofstream f(destination_path.c_str());
    f << *files.GetBoundary();
  }
  //faces
  {
    const std::string destination_path {
        copy_folder_name
      + fileio::FileIo().GetPathSeperator()
      + FacesFile::GetDefaultHeader().GetLocation()
      + fileio::FileIo().GetPathSeperator()
      + FacesFile::GetDefaultHeader().GetObject()
    };
    std::ofstream f(destination_path.c_str());
    f << *files.GetFaces();
  }
  //neighbour
  {
    const std::string destination_path {
        copy_folder_name
      + fileio::FileIo().GetPathSeperator()
      + NeighbourFile::GetDefaultHeader().GetLocation()
      + fileio::FileIo().GetPathSeperator()
      + NeighbourFile::GetDefaultHeader().GetObject()
    };
    std::ofstream f(destination_path.c_str());
    f << *files.GetNeighbour();
  }
  //owner
  {
    const std::string destination_path {
        copy_folder_name
      + fileio::FileIo().GetPathSeperator()
      + OwnerFile::GetDefaultHeader().GetLocation()
      + fileio::FileIo().GetPathSeperator()
      + OwnerFile::GetDefaultHeader().GetObject()
    };
    std::ofstream f(destination_path.c_str());
    f << *files.GetOwner();
  }
  //points
  {
    const std::string destination_path {
        copy_folder_name
      + fileio::FileIo().GetPathSeperator()
      + PointsFile::GetDefaultHeader().GetLocation()
      + fileio::FileIo().GetPathSeperator()
      + PointsFile::GetDefaultHeader().GetObject()
    };
    std::ofstream f(destination_path.c_str());
    f << *files.GetPoints();
  }


  try
  {
    assert(Files(copy_folder_name) == files
      && "Resulting Files must be same");
  }
  catch (std::runtime_error& e)
  {
    TRACE(e.what());
    assert(!"Resulting Files must be same");
  }
}

boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Files::CreateDefaultBoundary() noexcept
{
  const boost::shared_ptr<BoundaryFile> p {
    new BoundaryFile
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Files::CreateDefaultFaces() noexcept
{
  const boost::shared_ptr<FacesFile> p {
    new FacesFile
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Files::CreateDefaultNeighbour() noexcept
{
  const boost::shared_ptr<NeighbourFile> p {
    new NeighbourFile
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Files::CreateDefaultOwner() noexcept
{
  const boost::shared_ptr<OwnerFile> p {
    new OwnerFile
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Files::CreateDefaultPoints() noexcept
{
  const boost::shared_ptr<PointsFile> p {
    new PointsFile
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Files::CreateFaces(
  const std::string& folder_name)
{
  std::cout << (__func__) << std::endl;
  assert(ribi::fileio::FileIo().IsFolder(folder_name));
  const std::string filename(
    (folder_name.empty() ? folder_name : folder_name + fileio::FileIo().GetPathSeperator())
    + CreateFilenames()->GetFaces()
  );
  //std::ifstream is(filename.c_str());
  boost::shared_ptr<ribi::foam::FacesFile> p {
    new ribi::foam::FacesFile(filename)
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::Filenames> ribi::foam::Files::CreateFilenames() noexcept
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
    const std::string s { fileio::FileIo().GetPathSeperator() };
    const std::string f { folder_name + s + "constant" };
    if (!fileio::FileIo().IsFolder(f)) { fileio::FileIo().CreateFolder(f); }
    assert(fileio::FileIo().IsFolder(f));
  }
  {
    const std::string s { fileio::FileIo().GetPathSeperator() };
    const std::string f { folder_name + s + "constant" + s + "polyMesh" };
    if (!fileio::FileIo().IsFolder(f)) { fileio::FileIo().CreateFolder(f); }
    assert(fileio::FileIo().IsFolder(f));
  }
}

boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Files::CreateNeighbour(
  const std::string& folder_name)
{
  std::cout << (__func__) << std::endl;
  assert(ribi::fileio::FileIo().IsFolder(folder_name));
  const std::string filename(
    (folder_name.empty() ? folder_name : folder_name + fileio::FileIo().GetPathSeperator())
    + CreateFilenames()->GetNeighbour()
  );
  //std::ifstream is(filename.c_str());
  boost::shared_ptr<ribi::foam::NeighbourFile> p {
    new ribi::foam::NeighbourFile(filename)
  };
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Files::CreateOwner(
  const std::string& folder_name)
{
  std::cout << (__func__) << std::endl;
  assert(ribi::fileio::FileIo().IsFolder(folder_name));
  const std::string filename(
    (folder_name.empty() ? folder_name : folder_name + fileio::FileIo().GetPathSeperator())
    + CreateFilenames()->GetOwner()
  );

  const boost::shared_ptr<ribi::foam::OwnerFile> p {
    new ribi::foam::OwnerFile(filename)
  };
  //std::ifstream is(filename.c_str());
  //const boost::shared_ptr<ribi::foam::OwnerFile> p {
  //  new ribi::foam::OwnerFile(is)
  //};
  assert(p);
  return p;
}

boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Files::CreatePoints(
  const std::string& folder_name)
{
  std::cout << (__func__) << std::endl;
  assert(ribi::fileio::FileIo().IsFolder(folder_name));
  const std::string filename(
    (folder_name.empty() ? folder_name : folder_name + fileio::FileIo().GetPathSeperator())
    + CreateFilenames()->GetPoints()
  );
  //std::ifstream is(filename.c_str());
  boost::shared_ptr<ribi::foam::PointsFile> p {
    new ribi::foam::PointsFile(filename)
  };
  assert(p);
  return p;
}

std::vector<boost::shared_ptr<ribi::foam::Files>> ribi::foam::Files::CreateTestFiles() noexcept
{
  std::vector<boost::shared_ptr<ribi::foam::Files>> v;
  //Empty
  {
    const boost::shared_ptr<Files> files {
      new Files
    };
    assert(files);
    v.push_back(files);
  }
  //Complex from resources
  for (int i=0; i!=5; ++i)
  {
    const std::string folder_name = ribi::fileio::FileIo().GetTempFolderName();
    CreateTestFiles(folder_name,i);
    const boost::shared_ptr<Files> files {
      new Files(folder_name)
    };
    assert(files);
    v.push_back(files);
    ribi::fileio::FileIo().DeleteFolder(folder_name);
  }
  return v;
}

void ribi::foam::Files::CreateTestFiles(const std::string& folder_name, const int test_index)
{
  assert(test_index >= 0 && test_index < 5);

  CreateFolders(folder_name);

  //Read from testing file
  for (const std::string filename_base:
    {
      BoundaryFile::GetDefaultHeader().GetObject(),
      FacesFile::GetDefaultHeader().GetObject(),
      NeighbourFile::GetDefaultHeader().GetObject(),
      OwnerFile::GetDefaultHeader().GetObject(),
      PointsFile::GetDefaultHeader().GetObject()
    }
  )
  {
    std::string filename_appendix;
    switch (test_index)
    {
      case 0: filename_appendix = "_1x1x1"; break;
      case 1: filename_appendix = "_1x1x2"; break;
      case 2: filename_appendix = "_1x2x2"; break;
      case 3: filename_appendix = "_2x2x2"; break;
      case 4: filename_appendix = "_3x4x5"; break;
      default: assert(!"Should never get here");
        throw std::logic_error("foam::Files::CreateTestFiles: unknown test index");
    }
    assert(!filename_appendix.empty());
    const std::string filename = filename_base + filename_appendix;
    const std::string resources_path { ":/CppOpenFoam/files/" + filename };
    const std::string destination_path {
      folder_name
      + fileio::FileIo().GetPathSeperator()
      + "constant"
      + fileio::FileIo().GetPathSeperator()
      + "polyMesh"
      + fileio::FileIo().GetPathSeperator()
      + filename_base
    };
    QFile f(resources_path.c_str());
    f.copy(destination_path.c_str());
    assert(fileio::FileIo().IsRegularFile(destination_path));
  }
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
    /*
    const bool lhs_is_boundary = m_neighbour->CanGetItem(lhs);
    const bool rhs_is_boundary = m_neighbour->CanGetItem(rhs);
    assert(lhs_is_boundary == rhs_is_boundary
      && "Can only swap two boundary or two non-boundary faces");

    if (lhs_is_boundary != rhs_is_boundary)
    {
      throw std::logic_error("Can only swap two boundary or two non-boundary faces");
    }

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
    */
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
    const std::vector<boost::shared_ptr<ribi::foam::Files>> v { Files::CreateTestFiles() };
    const std::size_t sz = v.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      for (std::size_t j=0; j!=sz; ++j)
      {
        if (i == j) { assert(v[i] == v[j]); }
        if (i != j) { assert(v[i] != v[j]); }
      }
    }
  }
  //CreateCopy
  for (int test_index=0; test_index!=5; ++test_index)
  {
    const std::string temp_folder_source = ribi::fileio::FileIo().GetTempFolderName();
    {
      assert(!ribi::fileio::FileIo().IsFolder(temp_folder_source));
      CreateTestFiles(temp_folder_source,test_index);
    }
    const Files source(temp_folder_source);
    const std::string temp_folder_target = ribi::fileio::FileIo().GetTempFolderName();
    Files::CreateCopy(source,temp_folder_target);
    const Files target(temp_folder_target);
    assert(source == target);
    ribi::fileio::FileIo().DeleteFolder(temp_folder_source);
    ribi::fileio::FileIo().DeleteFolder(temp_folder_target);
  }
  //Swap faces
  {
    const std::string temp_folder = ribi::fileio::FileIo().GetTempFolderName();
    assert(!ribi::fileio::FileIo().IsFolder(temp_folder));
    CreateTestFiles(temp_folder,3); //3 = 2x2x2 cubes
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
    ribi::fileio::FileIo().DeleteFolder(temp_folder);
    assert(!ribi::fileio::FileIo().IsFolder(temp_folder));

  }
  TRACE("Finished ribi::foam::Files::Test successfully");
}
#endif

bool ribi::foam::operator==(const ribi::foam::Files& lhs, const ribi::foam::Files& rhs) noexcept
{
  //Split function for ease in debugging
  if (*lhs.GetBoundary()!= *rhs.GetBoundary())
  {
    //TRACE("Boundaries differ:");
    //TRACE(*lhs.GetBoundary());
    //TRACE(*rhs.GetBoundary());
    return false;
  }
  if (*lhs.GetFaces() != *rhs.GetFaces())
  {
    //TRACE("Faces differ:");
    //TRACE(*lhs.GetFaces());
    //TRACE(*rhs.GetFaces());
    return false;
  }
  if (*lhs.GetNeighbour() != *rhs.GetNeighbour())
  {
    //TRACE("Neighbours differ:");
    //TRACE(*lhs.GetNeighbour());
    //TRACE(*rhs.GetNeighbour());
    return false;
  }
  if (*lhs.GetOwner() != *rhs.GetOwner())
  {
    //TRACE("Owners differ:");
    //TRACE(*lhs.GetOwner());
    //TRACE(*rhs.GetOwner());
    return false;
  }
  if (*lhs.GetPoints() != *rhs.GetPoints())
  {
    //TRACE("Points differ:");
    //TRACE(*lhs.GetPoints());
    //TRACE(*rhs.GetPoints());
    return false;
  }
  return true;
}

bool ribi::foam::operator!=(const ribi::foam::Files& lhs, const ribi::foam::Files& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::foam::operator<<(std::ostream& os, const Files& files) noexcept
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

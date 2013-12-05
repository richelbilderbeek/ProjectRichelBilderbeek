#include "openfoamfiles.h"

#include <cassert>
#include <iostream>

#include "fileio.h"

#include "openfoamfilenames.h"

ribi::foam::Files::Files(const std::string& folder_name)
  : m_boundary(CreateBoundary(folder_name)),
    m_faces(CreateFaces(folder_name)),
    m_neighbour(CreateNeighbour(folder_name)),
    m_owner(CreateOwner(folder_name)),
    m_points(CreatePoints(folder_name))
{
  assert(ribi::fileio::IsFolder(folder_name));
}


const boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Files::CreateBoundary(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetBoundary().Get()
  );
  boost::shared_ptr<ribi::foam::BoundaryFile> p;
  if (fileio::IsRegularFile(filename))
  {
    std::istream is(filename.Get().c_str());
    p.reset(new ribi::foam::BoundaryFile(is));
  }
  return p;
}

const boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Files::CreateFaces(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetFaces().Get()
  );
  boost::shared_ptr<ribi::foam::FacesFile> p;
  if (fileio::IsRegularFile(filename))
  {
    std::istream is(filename.Get().c_str());
    p.reset(new ribi::foam::FacesFile(is));
  }
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

const boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Files::CreateNeighbour(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetNeighbour().Get()
  );
  boost::shared_ptr<ribi::foam::NeighbourFile> p;
  if (fileio::IsRegularFile(filename))
  {
    std::istream is(filename.Get().c_str());
    p.reset(new ribi::foam::NeighbourFile(is));
  }
  return p;
}

const boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Files::CreateOwner(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetOwner().Get()
  );
  boost::shared_ptr<ribi::foam::OwnerFile> p;
  if (fileio::IsRegularFile(filename))
  {
    std::istream is(filename.Get().c_str());
    p.reset(new ribi::foam::OwnerFile(is));
  }
  return p;
}

const boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Files::CreatePoints(
  const std::string& folder_name)
{
  assert(ribi::fileio::IsFolder(folder_name));
  const ribi::fileio::Filename filename(
    folder_name + fileio::GetPathSeperator() + CreateFilenames()->GetPoints().Get()
  );
  boost::shared_ptr<ribi::foam::PointsFile> p;
  if (fileio::IsRegularFile(filename))
  {
    std::istream is(filename.Get().c_str());
    p.reset(new ribi::foam::PointsFile(is));
  }
  return p;
}

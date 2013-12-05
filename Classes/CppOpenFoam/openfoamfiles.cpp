#include "openfoamfiles.h"

#include "fileio.h"

ribi::foam::Files::Files(const std::string& folder_name)
  : m_boundary(CreateBoundaryFile(folder_name)),
    m_faces(CreateFacesFile(folder_name)),
    m_neighbour(CreateNeighbourFile(folder_name)),
    m_owner(CreateOwnerFile(folder_name),
    m_points(CreatePointsFile(folder_name))
{
  assert(ribi::fileio::IsFolder(folder_name));
}


const boost::shared_ptr<ribi::foam::BoundaryFile> ribi::foam::Files::CreateBoundary(
  const std::string& folder_name)
{

}

const boost::shared_ptr<ribi::foam::FacesFile> ribi::foam::Files::CreateFaces(
  const std::string& folder_name)
{

}

const boost::shared_ptr<ribi::foam::NeighbourFile> ribi::foam::Files::CreateNeighbour(
  const std::string& folder_name)
{

}

const boost::shared_ptr<ribi::foam::OwnerFile> ribi::foam::Files::CreateOwner(
  const std::string& folder_name)
{

}

const boost::shared_ptr<ribi::foam::PointsFile> ribi::foam::Files::CreatePoints(
  const std::string& folder_name)
{

}

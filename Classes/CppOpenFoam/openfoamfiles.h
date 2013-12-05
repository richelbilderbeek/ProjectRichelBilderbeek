#ifndef OPENFOAMFILES_H
#define OPENFOAMFILES_H

#include <vector>
#include <iosfwd>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace foam {

///Files contains all files in an OpenFOAM folder
class Files
{
  Files(const std::string& folder_name);

  private:
  const boost::shared_ptr<BoundaryFile> m_boundary;
  const boost::shared_ptr<FacesFile> m_faces;
  const boost::shared_ptr<NeighbourFile> m_neighbour;
  const boost::shared_ptr<OwnerFile> m_owner;
  const boost::shared_ptr<PointsFile> m_points;


  static const boost::shared_ptr<BoundaryFile> CreateBoundary(const std::string& folder_name);
  static const boost::shared_ptr<FacesFile> CreateFaces(const std::string& folder_name);
  static const boost::shared_ptr<Filenames> CreateFilenames() noexcept;
  static const boost::shared_ptr<NeighbourFile> CreateNeighbour(const std::string& folder_name);
  static const boost::shared_ptr<OwnerFile> CreateOwner(const std::string& folder_name);
  static const boost::shared_ptr<PointsFile> CreatePoints(const std::string& folder_name);
};

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFILES_H

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

///Files contains the info of all files in an OpenFOAM folder
///This info can be used to create a Mesh
///After creating a Files, these files can be deleted
///Use CreateCopy to let these files be recreated again
struct Files
{
  ///Builds up Files from the current or any folder
  ///Use an empty string to build up from current folder
  explicit Files(const std::string& folder_name)
    : Files(
        CreateBoundary(folder_name),
        CreateFaces(folder_name),
        CreateNeighbour(folder_name),
        CreateOwner(folder_name),
        CreatePoints(folder_name)
      ) { }

  ///Builds up a Files from its information or from nothing
  explicit Files(
    const boost::shared_ptr<BoundaryFile> boundary = CreateDefaultBoundary(),
    const boost::shared_ptr<FacesFile> faces = CreateDefaultFaces(),
    const boost::shared_ptr<NeighbourFile> neighbour = CreateDefaultNeighbour(),
    const boost::shared_ptr<OwnerFile> owner = CreateDefaultOwner(),
    const boost::shared_ptr<PointsFile> points = CreateDefaultPoints()
  );
  Files(const Files&) = delete;
  Files& operator=(const Files&) = delete;

  ///Create a copy of the complete file structure of Files in the copy folder name
  static void CreateCopy(const Files& files, const std::string copy_folder_name) noexcept;

  ///Create test files in the correct OpenFOAM folder structure
  ///These files are obtained from the /Classes/CppOpenFoam/CppOpenFoam.qrc resources file
  static void CreateTestFiles(const std::string& folder_name);

  ///Create valid test Files
  static const std::vector<boost::shared_ptr<Files>> CreateTestFiles() noexcept;

  const boost::shared_ptr<const BoundaryFile> GetBoundary() const noexcept { return m_boundary; }
  const boost::shared_ptr<const FacesFile> GetFaces() const noexcept { return m_faces; }
  const boost::shared_ptr<const NeighbourFile> GetNeighbour() const noexcept { return m_neighbour; }
  const boost::shared_ptr<const OwnerFile> GetOwner() const noexcept { return m_owner; }
  const boost::shared_ptr<const PointsFile> GetPoints() const noexcept { return m_points; }

  void Swap(const FaceIndex& lhs, const FaceIndex& rhs);

  private:
  const boost::shared_ptr<BoundaryFile> m_boundary;
  const boost::shared_ptr<FacesFile> m_faces;
  const boost::shared_ptr<NeighbourFile> m_neighbour;
  const boost::shared_ptr<OwnerFile> m_owner;
  const boost::shared_ptr<PointsFile> m_points;

  ///Checks this class for correctless
  ///Throws std::logic_error if there are incorrectnesses
  void CheckMe() const;

  static const boost::shared_ptr<BoundaryFile> CreateBoundary(const std::string& folder_name);
  static const boost::shared_ptr<BoundaryFile> CreateDefaultBoundary() noexcept;
  static const boost::shared_ptr<FacesFile> CreateDefaultFaces() noexcept;
  static const boost::shared_ptr<NeighbourFile> CreateDefaultNeighbour() noexcept;
  static const boost::shared_ptr<OwnerFile> CreateDefaultOwner() noexcept;
  static const boost::shared_ptr<PointsFile> CreateDefaultPoints() noexcept;
  static const boost::shared_ptr<FacesFile> CreateFaces(const std::string& folder_name);

  ///Creates the folder structure needed by OpenFOAM
  static void CreateFolders(const std::string& folder_name);

  static const boost::shared_ptr<Filenames> CreateFilenames() noexcept;
  static const boost::shared_ptr<NeighbourFile> CreateNeighbour(const std::string& folder_name);
  static const boost::shared_ptr<OwnerFile> CreateOwner(const std::string& folder_name);
  static const boost::shared_ptr<PointsFile> CreatePoints(const std::string& folder_name);


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

///Write all info to a single stream. Use CreateCopy to write all info
///to an OpenFOAM folder structure with multiple files
std::ostream& operator<<(std::ostream& os, const Files& files);

bool operator==(const Files& lhs, const Files& rhs);
bool operator!=(const Files& lhs, const Files& rhs);

} //~namespace foam
} //~namespace ribi

#endif // OPENFOAMFILES_H

#ifndef TRIANGLEMESHBUILDER_H
#define TRIANGLEMESHBUILDER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <string>
#include <boost/shared_ptr.hpp>
#include "openfoamfwd.h"
#include "openfoampatchfieldtype.h"
#include "trianglemeshfwd.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///TriangleMeshBuilder creates all files needed by OpenFOAM
///(in the correct folder) from a collection of Cells
///These Cells can be created by TriangleMeshCellCreator
///The Cells' Faces are assigned a Boundary, but these
///may be reassigned before feeding the cells to TriangleMeshBuilder
struct TriangleMeshBuilder
{
  TriangleMeshBuilder(
    const std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells,
    const std::string& mesh_filename,
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function,
    const CreateVerticalFacesStrategy strategy
  );

  private:
  std::vector<boost::shared_ptr<Cell>> m_cells;
  std::vector<boost::shared_ptr<Face>> m_faces;
  const std::vector<boost::shared_ptr<Point>> m_points;

  std::string CreateBoundary(
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
  ) const noexcept;
  std::pair<std::string,std::string> CreateCells() const noexcept;
  std::string CreateFaces() const noexcept;
  std::string CreateHeader() const noexcept;
  std::string CreateNodes() const noexcept;

  std::string CreateOpenFoamFaces() const noexcept;
  std::string CreateOpenFoamHeader(
    const std::string& class_name,
    const std::string& object,
    const std::string& location,
    const std::string& note = "") const noexcept;

  std::string CreateOpenFoamK() const noexcept;
  std::string CreateOpenFoamMut() const noexcept;
  std::string CreateOpenFoamNodes() const noexcept;
  std::string CreateOpenFoamPin() const noexcept;
  std::string CreateOpenFoamPout() const noexcept;
  std::string CreateOpenFoamRasProperties() const noexcept;
  std::string CreateOpenFoamT() const noexcept;

  static std::vector<boost::shared_ptr<Face>> ExtractFaces(
    const std::vector<boost::shared_ptr<Cell>>& cells
  ) noexcept;

  static std::vector<boost::shared_ptr<Point>> ExtractPoints(
    const std::vector<boost::shared_ptr<Cell>>& cells
  ) noexcept;

  std::vector<std::string> GetAllFolders() const noexcept;

  static std::string Implode(
    const std::string& seperator,
    const std::vector<ribi::foam::PointIndex>& v) noexcept;

  static std::string Implode(
    const std::string& seperator,
    const std::vector<int>& v) noexcept;

  static std::vector<boost::shared_ptr<Face>> SortByBoundary(
    std::vector<boost::shared_ptr<Face>> faces,
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHBUILDER_H

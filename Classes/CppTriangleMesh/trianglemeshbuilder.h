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
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
  );

  private:
  std::vector<boost::shared_ptr<Cell>> m_cells;
  std::vector<boost::shared_ptr<Face>> m_faces;
  const std::vector<boost::shared_ptr<Point>> m_points;

  const std::string CreateBoundary(
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
    ) const noexcept;
  const std::pair<std::string,std::string> CreateCells() const noexcept;
  const std::string CreateFaces() const noexcept;
  const std::string CreateHeader() const noexcept;
  const std::string CreateNodes() const noexcept;

  const std::string CreateOpenFoamAlphat() const noexcept;
  const std::string CreateOpenFoamControlDict() const noexcept;
  const std::string CreateOpenFoamDecomposeParDict() const noexcept;

  const std::string CreateOpenFoamEpsilon() const noexcept;
  const std::string CreateOpenFoamFaces() const noexcept;
  const std::string CreateOpenFoamFvSchemes() const noexcept;
  const std::string CreateOpenFoamFvSolution() const noexcept;
  const std::string CreateOpenFoamHeader(
    const std::string& class_name,
    const std::string& object,
    const std::string& location,
    const std::string& note = "") const noexcept;

  const std::string CreateOpenFoamK() const noexcept;
  const std::string CreateOpenFoamMut() const noexcept;
  const std::string CreateOpenFoamNodes() const noexcept;
  //const std::string CreateOpenFoamP() const noexcept;
  const std::string CreateOpenFoamPin() const noexcept;
  const std::string CreateOpenFoamPout() const noexcept;
  const std::string CreateOpenFoamRasProperties() const noexcept;
  const std::string CreateOpenFoamT() const noexcept;
  //const std::string CreateOpenFoamThermoPhysicalProperties() const noexcept;
  const std::string CreateOpenFoamTurbulenceProperties() const noexcept;
  const std::string CreateOpenFoamU() const noexcept;


  static const std::vector<boost::shared_ptr<Face>> ExtractFaces(
    const std::vector<boost::shared_ptr<Cell>>& cells
  ) noexcept;

  static const std::vector<boost::shared_ptr<Point>> ExtractPoints(
    const std::vector<boost::shared_ptr<Cell>>& cells
  ) noexcept;

  const std::vector<std::string> GetAllFolders() const noexcept;

  static const std::string Implode(
    const std::string& seperator,
    const std::vector<ribi::foam::PointIndex>& v) noexcept;

  static const std::string Implode(
    const std::string& seperator,
    const std::vector<int>& v) noexcept;

  static const std::vector<boost::shared_ptr<Face>> SortByBoundary(
    std::vector<boost::shared_ptr<Face>> faces
  ) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHBUILDER_H

#ifndef TRIANGLEMESHBUILDERIMPL_H
#define TRIANGLEMESHBUILDERIMPL_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "openfoamfwd.h"
#include "openfoampatchfieldtype.h"
#include "trianglemeshfwd.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

struct TriangleMeshBuilderImpl
{
  explicit TriangleMeshBuilderImpl(
    const std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells,
    const std::string& mesh_filename,
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function,
    const CreateVerticalFacesStrategy strategy,
    const bool verbose
  );
  ~TriangleMeshBuilderImpl();
  int CountCells() const noexcept;
  int CountFaces() const noexcept;

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

  ///no_patch_field comes first, name comes second
  static bool OrderByPatchFieldType(
    const std::string lhs_name, const std::string rhs_name,
    const ribi::foam::PatchFieldType lhs_type, const ribi::foam::PatchFieldType rhs_type
  ) noexcept;

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

#endif // TRIANGLEMESHBUILDERIMPL_H

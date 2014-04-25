#ifndef TESTTRIANGLEMESHMAINDIALOG_H
#define TESTTRIANGLEMESHMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>

#include "openfoampatchfieldtype.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace trim { struct Cell; }

struct TestTriangleMeshMainDialog
{
  TestTriangleMeshMainDialog(
    const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
    const int n_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const ::ribi::trim::CreateVerticalFacesStrategy strategy,
    const double quality,
    const std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>& sculpt_function,
    const std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>& assign_boundary_function
  );

  static std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> CreateDefaultAssignBoundaryFunction() noexcept;

  static std::function<ribi::foam::PatchFieldType(const std::string&)> CreateDefaultBoundaryToPatchFieldTypeFunction() noexcept;

  static std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> CreateSculptFunctionNone() noexcept;
  static std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> CreateSculptFunctionRemoveRandom(const double p) noexcept;

  ///Obtain the filename of the created mesh
  std::string GetFilename() const noexcept { return m_filename_result_mesh; }

  private:

  const std::string m_filename_result_mesh;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTTRIANGLEMESHMAINDIALOG_H

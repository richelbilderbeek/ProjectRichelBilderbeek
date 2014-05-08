//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm
//---------------------------------------------------------------------------
#ifndef RIBI_TRIANGLEMESHCREATORMAINDIALOG_H
#define RIBI_TRIANGLEMESHCREATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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

struct TriangleMeshCreatorMainDialog
{
  TriangleMeshCreatorMainDialog(
    const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
    const int n_cell_layers,
    const boost::units::quantity<boost::units::si::length> layer_height,
    const ::ribi::trim::CreateVerticalFacesStrategy strategy,
    const double triangle_area,
    const double triangle_quality,
    const std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>& sculpt_function,
    const std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>& assign_boundary_function,
    const std::function<ribi::foam::PatchFieldType(const std::string&)>& boundary_to_patch_field_type_function,
    const bool verbose
  );

  static std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> CreateDefaultAssignBoundaryFunction() noexcept;
  static std::function<ribi::foam::PatchFieldType(const std::string&)> CreateDefaultBoundaryToPatchFieldTypeFunction() noexcept;

  void CreateDefaultControlDict() const noexcept;
  void CreateDefaultPressureField() const noexcept;
  void CreateDefaultTemperatureField() const noexcept;
  void CreateDefaultVelocityField() const noexcept;

  static std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> CreateSculptFunctionNone() noexcept;
  static std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> CreateSculptFunctionRemoveRandom(const double p) noexcept;

  ///Obtain the filename of the created mesh
  std::string GetFilename() const noexcept { return m_filename_result_mesh; }

  int GetNcells() const noexcept { return m_n_cells; }
  int GetNfaces() const noexcept { return m_n_faces; }

  private:

  const std::string m_filename_result_mesh;
  int m_n_cells;
  int m_n_faces;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_TRIANGLEMESHCREATORMAINDIALOG_H

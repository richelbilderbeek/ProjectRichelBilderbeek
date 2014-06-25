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
#ifndef RIBI_TRIANGLEMESHDIALOG_H
#define RIBI_TRIANGLEMESHDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include "openfoampatchfieldtype.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

namespace ribi {

struct TriangleFile;

namespace trim {

struct Cell;


///Facade
///
///              SetTriangleParameters()                          SetMeshParameters()
///                CreateTriangleMesh()                              Create3DMesh()
/// SetShapes() ------------------------> GetTriangleMesh()      --------------------> Get3dMesh()
/// GetShapesAsSvg()                      GetTriangleMeshAsSvg()
/// GetShapesAsWkt()                      GetTriangleMeshAsWkt()
///
///1) SetShapes, CanGetShapes, GetShapes,
///   Initially, the Dialog contains no shapes, which is a valid state
///2) SetTriangleParameters, CanGetTriangleMesh, m_are_triangle_parameters_set
///3) SetMeshParameters, CanGet3dMesh, m_are_3d_mesh_parameters_set
///4) Create3dMesh
///
/*

  Shapes:  Triangle:  Mesh:

  *-----*  *---+-*    *---+-*
  |     |  |\ / /|    |\ / /|\
  | *-* |  | *-* |    | *-* | \
  |     |  |/ \ \|    |/ \ \|  \
  *-----*  *---+-*    *---+-*   *
                       \   \ \  |
                        \   \ \ |
                         \   \ \|
                          *-----*
*/
struct Dialog
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef boost::geometry::model::linestring<Coordinat> Linestring;
  typedef std::vector<Polygon> Polygons;
  typedef std::vector<Linestring> Linestrings;
  typedef std::pair<Polygons,Linestrings> Shapes;

  ///Path is only used for CheckMesh
  Dialog();

  ///Uses OpenFOAM's checkMesh to check the 3D mesh
  void Check3dMesh(const std::string& full_path_of_executable) const noexcept;

  void CreateTriangleMesh() noexcept;
  void Create3dMesh() noexcept;

  static std::function<void(std::vector<boost::shared_ptr<Cell>>&)> CreateDefaultAssignBoundaryFunction() noexcept;
  static std::function<::ribi::foam::PatchFieldType(const std::string&)> CreateDefaultBoundaryToPatchFieldTypeFunction() noexcept;

  void CreateDefaultControlDict() const noexcept;
  void CreateDefaultPressureField() const noexcept;
  void CreateDefaultTemperatureField() const noexcept;
  void CreateDefaultVelocityField() const noexcept;

  static std::function<void(std::vector<boost::shared_ptr<Cell>>&)> CreateSculptFunctionNone() noexcept;
  static std::function<void(std::vector<boost::shared_ptr<Cell>>&)> CreateSculptFunctionRemoveRandom(const double p) noexcept;

  ///The content of the .ply file created by Create3dMesh()
  const std::string& Get3dMesh() const noexcept { return m_3dmesh_output_ply; }

  ///Obtain the filename of the created mesh
  //std::string Get3dMeshFilename() const noexcept { return m_3dmesh_filename_result; }

  int GetNcells() const noexcept { return m_n_cells; }
  int GetNfaces() const noexcept { return m_n_faces; }

  ///Shapes are the input shapes
  const Shapes& GetShapes() const noexcept { return m_shapes; }
  std::string GetShapesAsSvg(const double line_width = 0.1) const noexcept;
  std::string GetShapesAsWkt() const noexcept;

  ///Obtain the content of the .poly file used as input for Triangle
  const std::string& GetTriangleInput() const noexcept { return m_triangle_input_poly; }
  ///TriangleMesh is the 2D mesh generated by Triangle
  const Shapes& GetTriangleMesh() const noexcept { return m_triangle_shapes; }
  ///TriangleMesh is the 2D mesh generated by Triangle
  std::string GetTriangleMeshAsSvg(const double line_width = 0.1) const noexcept;
  ///TriangleMesh is the 2D mesh generated by Triangle
  std::string GetTriangleMeshAsWkt() const noexcept;
  ///Obtain the content of the .ele file that Triangle wrote part of its output to
  const std::string& GetTriangleOutputEle() const noexcept { return m_triangle_output_ele; }
  ///Obtain the content of the .node file that Triangle wrote part of its output to
  const std::string& GetTriangleOutputNode() const noexcept { return m_triangle_output_node; }
  ///Obtain the content of the .poly file that Triangle wrote part of its output to
  const std::string& GetTriangleOutputPoly() const noexcept { return m_triangle_output_poly; }


  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Step 3
  void Set3dMeshParameters(
    const int n_cell_layers,
    const Length layer_height,
    const ::ribi::trim::CreateVerticalFacesStrategy strategy,
    const std::function<void(std::vector<boost::shared_ptr<Cell>>&)>& sculpt_function,
    const std::function<void(std::vector<boost::shared_ptr<Cell>>&)>& assign_boundary_function,
    const std::function<::ribi::foam::PatchFieldType(const std::string&)>& boundary_to_patch_field_type_function,
    const bool verbose
  ) noexcept;

  ///Step 1
  void SetShapes(const Shapes& shapes) noexcept;
  void SetShapes(const std::string& wkt) noexcept;

  ///Step 2
  void SetTriangleParameters(
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose
  ) noexcept;


  ///Show the 3D mesh result in MeshLab
  void Show3dMesh() const noexcept;

  private:
  std::function<void(std::vector<boost::shared_ptr<Cell>>&)> m_3dmesh_assign_boundary_function;
  std::function<::ribi::foam::PatchFieldType(const std::string&)> m_3dmesh_boundary_to_patch_field_type_function;
  Length m_3dmesh_layer_height;
  int m_3dmesh_n_cell_layers;
  ///The text put in a .ply file as output of TriangleMesh
  std::string m_3dmesh_output_ply;
  std::function<void(std::vector<boost::shared_ptr<Cell>>&)> m_3dmesh_sculpt_function;
  CreateVerticalFacesStrategy m_3dmesh_strategy;
  bool m_3dmesh_verbose;

  int m_n_cells;
  int m_n_faces;

  Shapes m_shapes; //The input shapes

  //boost::shared_ptr<TriangleFile> m_triangle_file;

  ///The text put in a .poly file as input for Triangle.exe
  std::string m_triangle_input_poly;

  Area m_triangle_max_area;
  Angle m_triangle_min_angle;

  ///The text put in a .ele file as output of Triangle.exe
  std::string m_triangle_output_ele;
  ///The text put in a .node file as output of Triangle.exe
  std::string m_triangle_output_node;
  ///The text put in a .poly file as output of Triangle.exe
  std::string m_triangle_output_poly;

  Shapes m_triangle_shapes; //The shapes generated by Triangle
  bool m_triangle_verbose;


  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace trim
} //~namespace ribi

#endif // RIBI_TRIANGLEMESHDIALOG_H

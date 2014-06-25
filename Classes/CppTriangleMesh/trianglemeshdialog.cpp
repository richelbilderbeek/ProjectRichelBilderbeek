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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglemeshdialog.h"

#include <fstream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/systems/si.hpp>

#include "fileio.h"
#include "geometry.h"
#include "openfoamcontroldictfile.h"
#include "openfoamfilenames.h"
#include "openfoamfvschemesfile.h"
#include "openfoamfvsolutionfile.h"
#include "openfoampressurefile.h"
#include "openfoamtemperaturefile.h"
#include "openfoamthermophysicalpropertiesfile.h"
#include "openfoamvelocityfieldfile.h"
#include "polyfile.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshbuilder.h"
#include "trianglemeshcell.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshtemplate.h"
#include "trianglemeshcreateverticalfacesstrategies.h"
#pragma GCC diagnostic pop

ribi::trim::Dialog::Dialog()
  : m_3dmesh_assign_boundary_function{CreateDefaultAssignBoundaryFunction()},
    m_3dmesh_boundary_to_patch_field_type_function{CreateDefaultBoundaryToPatchFieldTypeFunction()},
    m_3dmesh_layer_height{0.0 * boost::units::si::meter},
    m_3dmesh_n_cell_layers{0},
    m_3dmesh_output_ply{},
    m_3dmesh_sculpt_function{CreateSculptFunctionNone()},
    m_3dmesh_strategy{CreateVerticalFacesStrategy::one_face_per_square},
    m_3dmesh_verbose{false},
    m_n_cells{0},
    m_n_faces{0},
    m_shapes{},
    m_triangle_input_poly{},
    m_triangle_max_area(boost::numeric::bounds<double>::highest() * boost::units::si::square_meter),
    m_triangle_min_angle(Angle( (20.0 * boost::math::constants::two_pi<double>() / 360.0) * boost::units::si::radians)),
    m_triangle_output_ele{},
    m_triangle_output_node{},
    m_triangle_output_poly{},
    m_triangle_shapes{},
    m_triangle_verbose{false}
{
  #ifndef NDEBUG
  Test();
  #endif

  CreateTriangleMesh();
  Create3dMesh();
}

void ribi::trim::Dialog::Check3dMesh() const noexcept
{
  const std::string ply_filename = fileio::FileIo().GetTempFileName(".ply");

  {
    std::ofstream f(ply_filename.c_str());
    f << m_3dmesh_output_ply;
  }

  const auto verbose = m_3dmesh_verbose;
  const std::string checkMesh_command(
    std::string(
      R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat )")
    + R"("WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""" )"
    //  // Changing to drive D is important...
    //+ "&& D: "
    //  // ...although this also indicates the drive
    //+ "&& cd " + ribi::fileio::FileIo().GetPath(path) + " "
    //+ "&& cd .. "
    //+ (verbose ? "&& dir " : "")
    + "&& checkMesh"
  );
  if (verbose) { TRACE(checkMesh_command); }
  const int error = std::system(checkMesh_command.c_str());

  ribi::fileio::FileIo().DeleteFile(ply_filename);

  if (error)
  {
    TRACE("WARNING");
    TRACE(error);
    TRACE("BREAK");
  }
  assert(!error);
}

std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>
  ribi::trim::Dialog::CreateDefaultAssignBoundaryFunction() noexcept
{
  return [](std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells)
  {
    std::vector<boost::shared_ptr<ribi::trim::Face>> faces;
    for (const boost::shared_ptr<ribi::trim::Cell>& cell: cells)
    {
      const std::vector<boost::shared_ptr<ribi::trim::Face>> w { cell->GetFaces() };
      std::copy(w.begin(),w.end(),std::back_inserter(faces));
    }
    for (boost::shared_ptr<ribi::trim::Face> face: faces)
    {
      if (face->GetNeighbour())
      {
        assert(face->GetConstOwner());
        face->SetBoundaryType("inside");
        continue;
      }
      else
      {
        assert(face->GetConstOwner());
        assert(!face->GetNeighbour());
        //If Owner its center has a higher Z coordinat, this is a bottom face
        if (face->GetOrientation() == ribi::trim::FaceOrientation::horizontal)
        {
          const double owner_z = boost::geometry::get<2>(face->GetConstOwner()->CalculateCenter());
          const double face_z = face->GetPoint(0)->GetZ().value();
          if (face_z < owner_z)
          {
            face->SetBoundaryType("bottom");
          }
          else
          {
            face->SetBoundaryType("top");
          }
        }
        else
        {
          assert(face->GetOrientation() == ribi::trim::FaceOrientation::vertical);
          const auto center(face->CalcCenter());
          const double center_x = boost::geometry::get<0>(center);
          const double center_y = boost::geometry::get<1>(center);
          if (center_x < 0.0)
          {
            if (center_y < 0.0)
            {
              face->SetBoundaryType("front");
            }
            else
            {
              face->SetBoundaryType("back");
            }
          }
          else
          {
            if (center_y < 0.0)
            {
              face->SetBoundaryType("left");
            }
            else
            {
              face->SetBoundaryType("right");
            }
          }
        }
        continue;
      }
    }
  }
  ;
}

std::function<ribi::foam::PatchFieldType(const std::string&)>
  ribi::trim::Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction() noexcept
{
  const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function
    = [](const std::string& patch_name)
    {
      if (patch_name == "inside") return ribi::foam::PatchFieldType::no_patch_field;
      if (patch_name == "top") return ribi::foam::PatchFieldType::zeroGradient;
      if (patch_name == "bottom") return ribi::foam::PatchFieldType::zeroGradient;
      if (patch_name == "front") return ribi::foam::PatchFieldType::zeroGradient;
      if (patch_name == "back") return ribi::foam::PatchFieldType::zeroGradient;
      if (patch_name == "left") return ribi::foam::PatchFieldType::zeroGradient;
      if (patch_name == "right") return ribi::foam::PatchFieldType::zeroGradient;
      //if (patch_name == "defaultFaces") return ribi::foam::PatchFieldType::wall;
      TRACE(patch_name);
      assert(!"CreateDefaultBoundaryToPatchFieldTypeFunction: unknown patch name");
      throw std::logic_error("CreateDefaultBoundaryToPatchFieldTypeFunction: unknown patch name");
    }
  ;
  return boundary_to_patch_field_type_function;
}

void ribi::trim::Dialog::CreateDefaultControlDict() const noexcept
{
  std::ofstream f(ribi::foam::Filenames().GetControlDict().c_str());
  ribi::foam::ControlDictFile file;
  file.SetAdjustTimeStep(false);
  file.SetApplication("sonicFoam");
  file.SetDeltaT(1.0);
  file.SetEndTime(10.0);
  file.SetPurgeWrite(0);
  file.SetRunTimeModifiable(true);
  file.SetStartFrom("latestTime");
  file.SetStartTime(0.0);
  file.SetStopAt("endTime");
  file.SetTimeFormat("general");
  file.SetTimePrecision(6);
  file.SetWriteCompression("uncompressed");
  file.SetWriteControl("adjustableRunTime");
  file.SetWriteFormat("ascii");
  file.SetWriteInterval(1.0);
  file.SetWritePrecision(6);
  f << file;
}

void ribi::trim::Dialog::CreateDefaultPressureField() const noexcept
{
  std::ofstream f(ribi::foam::Filenames().GetPressureField().c_str());
  ribi::foam::PressureFile file;
  //std::vector<std::pair<std::string,foam::PatchFieldType>> v;
  //v.push_back(std::make_pair("top",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("bottom",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("front",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("back",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("left",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("right",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("defaultFaces",foam::PatchFieldType::zeroGradient));
  //file.SetBoundaryField(v);
  file.SetBoundaryField(
    "  top\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }\n"
    "  bottom\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }\n"
    "  front\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }\n"
    "  back\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }\n"
    "  left\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }\n"
    "  right\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }\n"
    "  \n"
    "  defaultFaces\n"
    "  {\n"
    "    type zeroGradient;\n"
    "  }"
  );
  file.SetDimensions( {1,-1,-2,0,0,0,0} );
  file.SetInternalField("uniform 1.7e5");
  f << file;
}

void ribi::trim::Dialog::CreateDefaultTemperatureField() const noexcept
{
  std::ofstream f(ribi::foam::Filenames().GetTemperatureField().c_str());
  ribi::foam::TemperatureFile file;
  file.SetBoundaryField(
    "top\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "bottom\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "front\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "back\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "left\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "right\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
  );

  file.SetDimensions( {0,0,0,1,0,0,0} );
  file.SetInternalField("uniform 293");
  f << file;
}

void ribi::trim::Dialog::CreateDefaultVelocityField() const noexcept
{
  ribi::foam::VelocityFieldFile file;
  file.SetDimensions( {0,1,-1,0,0,0,0} );
  file.SetInternalField("uniform (0 0 0)");
  file.SetBoundaryField(
    "inside\n"
    "{\n"
    "  type slip;\n"
    "}\n"
    "\n"
    "top\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "bottom\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "front\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "back\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "left\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
    "right\n"
    "{\n"
    "  type zeroGradient;\n"
    "}\n"
  );
  std::ofstream f(ribi::foam::Filenames().GetVelocityField().c_str());
  f << file;
}

std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>
  ribi::trim::Dialog::CreateSculptFunctionNone() noexcept
{
  return [](std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells)
  {
    std::random_shuffle(cells.begin(),cells.end());
  }
  ;
}

std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)>
  ribi::trim::Dialog::CreateSculptFunctionRemoveRandom(const double p) noexcept
{
  assert(p >= 0.0);
  assert(p <= 1.0);
  return [p](std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells)
  {
    std::random_shuffle(cells.begin(),cells.end());
    std::reverse(cells.begin(),cells.end());
    std::random_shuffle(cells.begin(),cells.end());
    cells.resize(static_cast<int>(static_cast<double>(cells.size()) * p));
  }
  ;
}

void ribi::trim::Dialog::CreateTriangleMesh() noexcept
{
  const auto verbose = m_triangle_verbose;
  if (verbose) { std::clog << "Write some geometries, let Triangle.exe work on it" << std::endl; }

  m_triangle_input_poly = "";
  m_triangle_shapes = Shapes();
  m_triangle_output_ele = "";
  m_triangle_output_node = "";
  m_triangle_output_poly = "";

  try
  {
    if (verbose) { std::clog << "Create Triangle.exe input" << std::endl; }

    const auto file = boost::make_shared<TriangleFile>(m_shapes);

    if (verbose) { std::clog << "Store the Triangle.exe input" << std::endl; }

    m_triangle_input_poly = file->GetTriangleInputPoly();

    std::string filename_node;
    std::string filename_ele;
    std::string filename_poly;

    if (verbose) { std::clog << "Calling Triangle.exe" << std::endl; }

    file->ExecuteTriangleExe(
      filename_node,
      filename_ele,
      filename_poly,
      m_triangle_min_angle,
      m_triangle_max_area,
      verbose
    );

    if (verbose) { std::clog << "Saving Triangle.exe output" << std::endl; }

    m_triangle_output_ele = fileio::FileIo().FileToStr(filename_ele);
    m_triangle_output_node = fileio::FileIo().FileToStr(filename_node);
    m_triangle_output_poly = fileio::FileIo().FileToStr(filename_poly);

    if (verbose) { std::clog << "Read data from Triangle.exe output" << std::endl; }

    const boost::shared_ptr<const ribi::trim::Template> t(
      //= boost::make_shared<ribi::trim::Template>(
      new ribi::trim::Template(
        filename_node,
        filename_ele
      )
    );
    assert(t);

    if (verbose) { std::clog << "Convert Triangle.exe output to polygons" << std::endl; }

    for (const boost::shared_ptr<trim::Face> face: t->GetFaces())
    {
      std::vector<Coordinat> coordinats;
      for (const boost::shared_ptr<trim::Point> point: face->GetPoints())
      {
        coordinats.push_back(*point->GetCoordinat());
      }
      Polygon polygon;
      boost::geometry::append(polygon, coordinats);
      m_triangle_shapes.first.push_back(polygon);
    }

    if (verbose) { std::clog << "Delete Triangle.exe output" << std::endl; }
    fileio::FileIo().DeleteFile(filename_ele);
    fileio::FileIo().DeleteFile(filename_node);
    fileio::FileIo().DeleteFile(filename_poly);
  }
  catch (std::exception& e)
  {
    std::stringstream s;
    s << "ribi::trim::Dialog::Dialog: "
      << "Triangle.exe failed: " << e.what();
    TRACE(s.str());
    //throw std::runtime_error(s.str());
  }
}

void ribi::trim::Dialog::Create3dMesh() noexcept
{
  const auto verbose = m_3dmesh_verbose;

  if (verbose) { std::clog << "Read data from Triangle.exe output" << std::endl; }

  std::vector<boost::shared_ptr<ribi::trim::Cell>> cells;
  {
    const std::string filename_ele = fileio::FileIo().GetTempFileName(".ele");
    const std::string filename_node = fileio::FileIo().GetTempFileName(".node");

    { std::ofstream f(filename_ele.c_str()); f << m_triangle_output_ele; }
    { std::ofstream f(filename_node.c_str()); f << m_triangle_output_node; }

    const boost::shared_ptr<const ribi::trim::Template> t(
      new ribi::trim::Template(
        filename_node,
        filename_ele
      )
    );
    assert(t);

    fileio::FileIo().DeleteFile(filename_ele);
    fileio::FileIo().DeleteFile(filename_node);

    //Create cells from this template
    {
      const ribi::trim::CellsCreatorFactory cells_creator_factory;
      assert(t);
      const boost::shared_ptr<ribi::trim::CellsCreator> c
        = cells_creator_factory.Create(
          t,
          m_3dmesh_n_cell_layers,
          m_3dmesh_layer_height,
          m_3dmesh_strategy
      );
      assert(c);
      cells = c->GetCells();
      #ifndef NDEBUG
      for (const auto cell:cells) { assert(cell); }
      #endif
    }

    //Sculpting
    if (verbose) { std::clog << "Number of cells before sculpting: " << cells.size() << std::endl; }
    m_3dmesh_sculpt_function(cells);

    m_n_cells = static_cast<int>(cells.size());
    if (verbose) { std::clog << "Number of cells after sculpting: " << m_n_cells << std::endl; }

    //Remove weak faces
    {
      std::vector<boost::shared_ptr<ribi::trim::Face>> faces;
      for (const boost::shared_ptr<ribi::trim::Cell>& cell: cells)
      {
        const std::vector<boost::shared_ptr<ribi::trim::Face>> w { cell->GetFaces() };
        std::copy(w.begin(),w.end(),std::back_inserter(faces));
      }
      if (verbose) { std::clog << "Number of weak faces: " << faces.size() << std::endl; }
      assert(std::unique(faces.begin(),faces.end()) == faces.end());
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);
      //Clean all weakened faces
      faces.erase(
        std::remove_if(faces.begin(),faces.end(),
          [](const boost::shared_ptr<const ribi::trim::Face> face)
          {
            return !face->GetConstOwner();
          }
        ),
        faces.end()
      );
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);

      m_n_faces = static_cast<int>(faces.size());
      if (verbose) { std::clog << "Number of strong faces: " << m_n_faces << std::endl; }
      //const ribi::trim::Helper helper;
      std::sort(faces.begin(),faces.end(),ribi::trim::Helper().OrderByIndex());
      const auto new_end = std::unique(faces.begin(),faces.end());
      faces.erase(new_end,faces.end());
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);
    }

    //Assign boundaries to the strong faces
    m_3dmesh_assign_boundary_function(cells);
  }

  if (verbose) { std::clog << "Checking the cells" << std::endl; }
  {
    for (const auto cell: cells)
    {
      assert(cell);
      for (const auto face: cell->GetFaces())
      {
        assert(face);
        for (const auto point: face->GetPoints())
        {
          assert(point);
        }
      }
    }
  }

  if (verbose) { std::clog << "Build the OpenFOAM files" << std::endl; }
  {
    std::string filename_result_mesh = fileio::FileIo().GetTempFileName(".ply");

    const boost::shared_ptr<ribi::trim::TriangleMeshBuilder> builder(
      new ribi::trim::TriangleMeshBuilder(
        cells,
        filename_result_mesh,
        m_3dmesh_boundary_to_patch_field_type_function,
        m_3dmesh_strategy,
        m_3dmesh_verbose
      )
    );
    assert(builder);

    m_3dmesh_output_ply = fileio::FileIo().FileToStr(filename_result_mesh);

    fileio::FileIo().DeleteFile(filename_result_mesh);
  }
}

std::string ribi::trim::Dialog::GetShapesAsSvg(const double line_width) const noexcept
{
  return Geometry().ToSvg(m_shapes,line_width);
}

std::string ribi::trim::Dialog::GetShapesAsWkt() const noexcept
{
  return Geometry().ToWkt(m_shapes);
}

std::string ribi::trim::Dialog::GetTriangleMeshAsSvg(const double line_width) const noexcept
{
  return Geometry().ToSvg(m_triangle_shapes,line_width);
}

std::string ribi::trim::Dialog::GetTriangleMeshAsWkt() const noexcept
{
  return Geometry().ToWkt(m_triangle_shapes);
}

std::string ribi::trim::Dialog::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::trim::Dialog::GetVersionHistory() noexcept
{
  return {
    "2014-06-24: version 1.0: initial version"
  };
}

void ribi::trim::Dialog::Set3dMeshParameters(
  const int n_cell_layers,
  const Length layer_height,
  const ::ribi::trim::CreateVerticalFacesStrategy strategy,
  const std::function<void(std::vector<boost::shared_ptr<Cell>>&)>& sculpt_function,
  const std::function<void(std::vector<boost::shared_ptr<Cell>>&)>& assign_boundary_function,
  const std::function<::ribi::foam::PatchFieldType(const std::string&)>& boundary_to_patch_field_type_function,
  const bool verbose
) noexcept
{
  m_3dmesh_assign_boundary_function = assign_boundary_function;
  m_3dmesh_boundary_to_patch_field_type_function = boundary_to_patch_field_type_function;
  m_3dmesh_layer_height = layer_height;
  m_3dmesh_n_cell_layers = n_cell_layers;
  m_3dmesh_sculpt_function = sculpt_function;
  m_3dmesh_strategy = strategy;
  m_3dmesh_verbose = verbose;

}


void ribi::trim::Dialog::SetShapes(const Shapes& shapes) noexcept
{
  m_shapes = shapes;
}

void ribi::trim::Dialog::SetShapes(const std::string& wkt) noexcept
{
  SetShapes(Geometry().WktToShapes(wkt));
}

void ribi::trim::Dialog::SetTriangleParameters(
  const Angle triangle_min_angle,
  const Area triangle_max_area,
  const bool verbose
) noexcept
{
  m_triangle_min_angle = triangle_min_angle;
  m_triangle_max_area = triangle_max_area;
  m_triangle_verbose = verbose;

}

void ribi::trim::Dialog::Show3dMesh() const noexcept
{
  const std::string filename = fileio::FileIo().GetTempFileName(".ply");

  //Create file for MeshLab
  {
    std::ofstream f(filename.c_str());
    f << m_3dmesh_output_ply;
  }

  assert(ribi::fileio::FileIo().IsRegularFile(filename));
  std::stringstream s;
  s
    #ifdef _WIN32
    << "C:\\Progra~1\\VCG\\Meshlab\\meshlab.exe "
    #else
    << "meshlab "
    #endif
    << filename
  ;
  const int error = std::system(s.str().c_str());
  if (error)
  {
    std::cout << "WARNING: cannot display mesh" << '\n';
    TRACE("BREAK");
  }

  ribi::fileio::FileIo().DeleteFile(filename);
  assert(!ribi::fileio::FileIo().IsRegularFile(filename));
}

#ifndef NDEBUG
void ribi::trim::Dialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::trim::Dialog::Test");
  //typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> Coordinat2D;
  ribi::trim::CellsCreatorFactory();
  //Flow of Dialog
  {
    Dialog d;
    d.CreateTriangleMesh();
    d.Create3dMesh();
    assert(!d.Get3dMesh().empty());
  }
  {
    ribi::trim::CellsCreatorFactory().Create(
      ribi::trim::Template::CreateTest(0),
      2,
      1.0 * boost::units::si::meter,
      ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
    );
  }

  //Create a simple mesh
  /*
  for (::ribi::trim::CreateVerticalFacesStrategy strategy: ribi::trim::CreateVerticalFacesStrategies().GetAll())
  {
    try
    {
      const double pi { boost::math::constants::pi<double>() };
      const Polygons polygons {
        Geometry().CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
      };
      const Linestrings linestrings = {};
      const Shapes shapes(polygons,linestrings);
      const Angle triangle_min_angle
        = 20.0 //Default used by Triangle, in degrees
        * (boost::math::constants::two_pi<double>() / 360.0)
        * boost::units::si::radian
      ;
      const Area triangle_max_area = 1.0 * boost::units::si::square_meter;
      const int n_cell_layers = 1;
      const bool verbose = false;
      const ribi::trim::Dialog d(
        shapes,
        n_cell_layers,
        1.0 * boost::units::si::meter,
        strategy,
        triangle_min_angle,
        triangle_max_area,
        Dialog::CreateSculptFunctionRemoveRandom(0.75),
        Dialog::CreateDefaultAssignBoundaryFunction(),
        Dialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
        verbose
      );
    }
    catch (std::exception& e)
    {
      assert(!"Should not get here");
    }
    catch (...)
    {
      assert(!"Should not get here");
    }
  }
  */
  TRACE("Finished ribi::trim::Dialog::Test successfully");
}
#endif

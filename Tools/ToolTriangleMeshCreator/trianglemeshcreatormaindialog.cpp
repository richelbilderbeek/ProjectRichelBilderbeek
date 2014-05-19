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
#include "trianglemeshcreatormaindialog.h"

#include <fstream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/systems/si.hpp>



#include "fileio.h"
#include "openfoamcontroldictfile.h"
#include "openfoamfilenames.h"
#include "openfoamfvschemesfile.h"
#include "openfoamfvsolutionfile.h"
#include "openfoampressurefile.h"
#include "openfoamtemperaturefile.h"
#include "openfoamthermophysicalpropertiesfile.h"
#include "openfoamvelocityfieldfile.h"
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

ribi::TriangleMeshCreatorMainDialog::TriangleMeshCreatorMainDialog(
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
)
  : m_filename_result_mesh(ribi::fileio::FileIo().GetTempFileName(".ply")),
    m_n_cells{0},
    m_n_faces{0}
{
  
  #ifndef NDEBUG
  Test();
  #endif

  if (verbose) { std::clog << "Write some geometries, let Triangle.exe work on it" << std::endl; }
  std::string filename_node;
  std::string filename_ele;
  std::string filename_poly;
  {
    ribi::TriangleFile f(shapes);
    //const double area = 2.0;
    f.ExecuteTriangleExe(
      filename_node,
      filename_ele,
      filename_poly,
      triangle_quality,
      triangle_area
    );
  }

  if (verbose) { std::clog << "Read data from Triangle.exe output" << std::endl; }

  std::vector<boost::shared_ptr<ribi::trim::Cell>> cells;
  {
    const boost::shared_ptr<const ribi::trim::Template> t
      = boost::make_shared<ribi::trim::Template>(
        filename_node,
        filename_ele
    );
    assert(t);

    //Create cells from this template
    {
      const ribi::trim::CellsCreatorFactory cells_creator_factory;
      assert(t);
      const boost::shared_ptr<ribi::trim::CellsCreator> c
        = cells_creator_factory.Create(
          t,
          n_cell_layers,
          layer_height,
          strategy
      );
      assert(c);
      cells = c->GetCells();
      #ifndef NDEBUG
      for (auto cell:cells) { assert(cell); }
      #endif
    }

    //Sculpting
    if (verbose) { std::clog << "Number of cells before sculpting: " << cells.size() << std::endl; }
    sculpt_function(cells);

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
    assign_boundary_function(cells);
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
    const boost::shared_ptr<ribi::trim::TriangleMeshBuilder> builder(
      new ribi::trim::TriangleMeshBuilder(
        cells,
        m_filename_result_mesh,
        boundary_to_patch_field_type_function,
        strategy,
        verbose
      )
    );
    assert(builder);
  }
}


std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> ribi::TriangleMeshCreatorMainDialog::CreateDefaultAssignBoundaryFunction() noexcept
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
  ribi::TriangleMeshCreatorMainDialog::CreateDefaultBoundaryToPatchFieldTypeFunction() noexcept
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

void ribi::TriangleMeshCreatorMainDialog::CreateDefaultControlDict() const noexcept
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

void ribi::TriangleMeshCreatorMainDialog::CreateDefaultPressureField() const noexcept
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

void ribi::TriangleMeshCreatorMainDialog::CreateDefaultTemperatureField() const noexcept
{
  std::ofstream f(ribi::foam::Filenames().GetTemperatureField().c_str());
  ribi::foam::TemperatureFile file;
  //std::vector<std::pair<std::string,foam::PatchFieldType>> v;
  //v.push_back(std::make_pair("top",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("bottom",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("front",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("back",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("left",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("right",foam::PatchFieldType::zeroGradient));
  //file.SetBoundaryField(v);

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

void ribi::TriangleMeshCreatorMainDialog::CreateDefaultVelocityField() const noexcept
{
  ribi::foam::VelocityFieldFile file;
  file.SetDimensions( {0,1,-1,0,0,0,0} );
  file.SetInternalField("uniform (0 0 0)");
  //std::vector<std::pair<std::string,foam::PatchFieldType>> v;
  //v.push_back(std::make_pair("inside",foam::PatchFieldType::slip));
  //v.push_back(std::make_pair("top",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("bottom",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("front",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("back",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("left",foam::PatchFieldType::zeroGradient));
  //v.push_back(std::make_pair("right",foam::PatchFieldType::zeroGradient));
  //file.SetBoundaryField(v);
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
  ribi::TriangleMeshCreatorMainDialog::CreateSculptFunctionNone() noexcept
{
  return [](std::vector<boost::shared_ptr<ribi::trim::Cell>>& cells)
  {
    std::random_shuffle(cells.begin(),cells.end());
  }
  ;
}

std::function<void(std::vector<boost::shared_ptr<ribi::trim::Cell>>&)> ribi::TriangleMeshCreatorMainDialog::CreateSculptFunctionRemoveRandom(const double p) noexcept
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

#ifndef NDEBUG
void ribi::TriangleMeshCreatorMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TriangleMeshCreatorMainDialog::Test");
  typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> Coordinat2D;
  ribi::trim::CellsCreatorFactory();

  //Create a simple mesh
  for (::ribi::trim::CreateVerticalFacesStrategy strategy: ribi::trim::CreateVerticalFacesStrategies().GetAll())
  {
    try
    {
      const double pi { boost::math::constants::pi<double>() };
      const std::vector<Coordinat2D> shapes {
        ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
      };
      const double triangle_quality = 5.0;
      const double triangle_area = 2.0;
      const int n_cell_layers = 1;
      const bool verbose = false;
      const ribi::TriangleMeshCreatorMainDialog d(
        shapes,
        n_cell_layers,
        1.0 * boost::units::si::meter,
        strategy,
        triangle_quality,
        triangle_area,
        TriangleMeshCreatorMainDialog::CreateSculptFunctionRemoveRandom(0.75),
        TriangleMeshCreatorMainDialog::CreateDefaultAssignBoundaryFunction(),
        TriangleMeshCreatorMainDialog::CreateDefaultBoundaryToPatchFieldTypeFunction(),
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
  TRACE("Finished ribi::TriangleMeshCreatorMainDialog::Test successfully");
}
#endif

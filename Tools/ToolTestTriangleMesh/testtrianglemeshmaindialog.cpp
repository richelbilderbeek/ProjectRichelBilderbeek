#include "testtrianglemeshmaindialog.h"

#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/systems/si.hpp>

#include "Shiny.h"

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
#include "trianglemeshedgefactory.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#include "trianglemeshpoint.h"
#include "trianglemeshtemplate.h"
#pragma GCC diagnostic pop

ribi::TestTriangleMeshMainDialog::TestTriangleMeshMainDialog(
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
  const bool show_mesh,
  const int n_layers,
  const ::ribi::trim::CreateVerticalFacesStrategy strategy,
  const std::string& renumberMesh_command
)
{
  PROFILE_FUNC();

  const auto filename_result_mesh(ribi::fileio::FileIo().GetTempFileName(".ply"));

  //Write some geometries, let Triangle.exe work on it
  std::string filename_node;
  std::string filename_ele;
  std::string filename_poly;
  {
    ribi::TriangleFile f(shapes);
    const double quality = 5.0;
    const double area = 2.0;
    f.ExecuteTriangle(
      filename_node,
      filename_ele,
      filename_poly,
      quality,
      area
    );
  }

  //Read data from Triangle.exe output
  std::vector<boost::shared_ptr<ribi::trim::Cell>> cells;
  {
    const boost::shared_ptr<const ribi::trim::Template> t(
      new ribi::trim::Template(
        filename_node,
        filename_ele
      )
    );
    assert(t);

    //Create cells from this template
    {
      const boost::units::quantity<boost::units::si::length> layer_height(
        1.0 * boost::units::si::meter
      );

      const auto c(
        ribi::trim::CellsCreatorFactory().Create(
          t,
          n_layers,
          layer_height,
          strategy
        )
      );
      assert(c);
      cells = c->GetCells();
      #ifndef NDEBUG
      for (auto cell:cells) { assert(cell); }
      #endif
    }
    //Remove some random cells
    std::clog << "Number of cells before sculpting: " << cells.size() << std::endl;
    //std::random_shuffle(cells.begin(),cells.end());
    //std::reverse(cells.begin(),cells.end());
    //std::random_shuffle(cells.begin(),cells.end());
    //cells.resize(cells.size() * 3 / 4);

    std::clog << "Number of cells after sculpting: " << cells.size() << std::endl;

    //Assign boundaries to the faces
    {
      std::vector<boost::shared_ptr<ribi::trim::Face>> faces;
      for (const boost::shared_ptr<ribi::trim::Cell>& cell: cells)
      {
        const std::vector<boost::shared_ptr<ribi::trim::Face>> w { cell->GetFaces() };
        std::copy(w.begin(),w.end(),std::back_inserter(faces));
      }
      std::clog << "Number of weak faces: " << faces.size() << std::endl;
      assert(std::unique(faces.begin(),faces.end()) == faces.end());
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);
      //Clean all weakened faces
      faces.erase(
        std::remove_if(faces.begin(),faces.end(),
          [](const boost::shared_ptr<const ribi::trim::Face> face)
          {
            return !face->GetOwner();
          }
        ),
        faces.end()
      );
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);
      std::clog << "Number of strong faces: " << faces.size() << std::endl;
      std::sort(faces.begin(),faces.end(),ribi::trim::Helper().OrderByIndex());
      const auto new_end = std::unique(faces.begin(),faces.end());
      faces.erase(new_end,faces.end());
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);
      int n_internal = 0;
      int n_external = 0;
      for (boost::shared_ptr<ribi::trim::Face> face: faces)
      {
        if (face->GetNeighbour())
        {
          assert(face->GetOwner());
          face->SetBoundaryType("inside");
          ++n_internal;
          continue;
        }
        else
        {
          assert(face->GetOwner());
          assert(!face->GetNeighbour());
          ++n_external;
          if (face->GetOrientation() == ribi::trim::FaceOrientation::horizontal)
          {
            if (face->GetPoint(0)->GetZ() < 0.5 * boost::units::si::meter)
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
      std::clog << "internal faces: " << n_internal << std::endl;
      std::clog << "external faces: " << n_external << std::endl;
    }

    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
  }

  {
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function {
      [](const std::string& patch_name)
      {
        if (patch_name == "inside") return ribi::foam::PatchFieldType::no_patch_field;
        if (patch_name == "top") return ribi::foam::PatchFieldType::zeroGradient;
        if (patch_name == "bottom") return ribi::foam::PatchFieldType::zeroGradient;
        if (patch_name == "front") return ribi::foam::PatchFieldType::zeroGradient;
        if (patch_name == "back") return ribi::foam::PatchFieldType::zeroGradient;
        if (patch_name == "left") return ribi::foam::PatchFieldType::zeroGradient;
        if (patch_name == "right") return ribi::foam::PatchFieldType::zeroGradient;
        assert(!"Should not get here");
        throw std::logic_error("boundary_to_patch_field_type: unknown patch name");
      }
    };

    //Build the OpenFOAM files
    const ribi::trim::TriangleMeshBuilder builder(
      cells,
      filename_result_mesh,
      boundary_to_patch_field_type_function,
      strategy
    );
    TRACE_FUNC();
  }

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

  {
    std::ofstream f(ribi::foam::Filenames().GetFvSchemes().c_str());
    ribi::foam::FvSchemesFile file;
    f << file;
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetFvSolution().c_str());
    ribi::foam::FvSolutionFile file;
    f << file;
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetPressureField().c_str());
    ribi::foam::PressureFile file;
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

  {
    std::ofstream f(ribi::foam::Filenames().GetThermophysicalProperties().c_str());
    ribi::foam::ThermophysicalPropertiesFile file;
    file.SetMixture("air 1 28.9 717 0 1.458e-6 110.4");
    file.SetThermoType("ePsiThermo<pureMixture<sutherlandTransport<specieThermo<eConstThermo<perfectGas>>>>>");
    f << file;

  }

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

  std::clog << std::endl;
  std::cout << std::endl;

  std::system(renumberMesh_command.c_str());

  if (show_mesh)
  {
    std::stringstream s;
    s
      << "C:\\Progra~1\\VCG\\Meshlab\\meshlab.exe "
      << filename_result_mesh;
    const int error = std::system(s.str().c_str());
    if (error) std::cout << "WARNING: cannot display mesh" << '\n';
  }

}

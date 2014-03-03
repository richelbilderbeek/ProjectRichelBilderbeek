#include "testtrianglemeshmaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/systems/si.hpp>

#include "Shiny.h"

#include "fileio.h"
#include "openfoamfilenames.h"
#include "openfoamcontroldictfile.h"
#include "openfoamfvschemesfile.h"
#include "openfoamfvsolutionfile.h"
#include "openfoamvelocityfieldfile.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshcell.h"
#include "trianglemeshedgefactory.h"
#include "trianglemeshface.h"
#include "trianglemeshbuilder.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshtemplate.h"
#pragma GCC diagnostic pop

ribi::TestTriangleMeshMainDialog::TestTriangleMeshMainDialog(
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
  const bool show_mesh,
  const int n_layers
  )
{
  PROFILE_FUNC();

  const std::string filename_result_mesh { ribi::fileio::GetTempFileName(".ply") };

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
    const boost::shared_ptr<const ribi::trim::Template> t {
      new ribi::trim::Template(
        filename_node,
        filename_ele
      )
    };

    //Create cells from this template
    {
      const boost::units::quantity<boost::units::si::length> layer_height(
        1.0 * boost::units::si::meter
      );

      const boost::shared_ptr<ribi::trim::CellsCreator> c {
        ribi::trim::CellsCreatorFactory().Create(t,n_layers,layer_height)
      };

      cells = c->GetCells();
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
      std::sort(faces.begin(),faces.end());
      const auto new_end = std::unique(faces.begin(),faces.end());
      faces.erase(new_end,faces.end());
      assert(std::count(faces.begin(),faces.end(),nullptr) == 0);
      int n_internal = 0;
      int n_default = 0;
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
          face->SetBoundaryType("outside");
          ++n_default;
          continue;
        }
      }
      std::clog << "internal faces: " << n_internal << std::endl;
      std::clog << "external faces: " << n_default << std::endl;
    }

    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
  }

  {
    const std::function<ribi::foam::PatchFieldType(const std::string&)> boundary_to_patch_field_type_function {
      [](const std::string& patch_name)
      {
        if (patch_name == "inside") return ribi::foam::PatchFieldType::slip;
        if (patch_name == "outside") return ribi::foam::PatchFieldType::zeroGradient;
        assert(!"Should not get here");
        throw std::logic_error("boundary_to_patch_field_type: unknown patch name");
      }
    };

    //Build the OpenFOAM files
    const ribi::trim::TriangleMeshBuilder builder(
      cells,
      filename_result_mesh,
      boundary_to_patch_field_type_function
    );
    TRACE_FUNC();
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetControlDict().Get().c_str());
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
    std::ofstream f(ribi::foam::Filenames().GetFvSchemes().Get().c_str());
    ribi::foam::FvSchemesFile file;
    f << file;
  }

  {
    std::ofstream f(ribi::foam::Filenames().GetFvSolution().Get().c_str());
    ribi::foam::FvSolutionFile file;
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
      "outside\n"
      "{\n"
      "  type zeroGradient;\n"
      "}\n"
    );
    std::ofstream f(ribi::foam::Filenames().GetVelocityField().Get().c_str());
    f << file;
  }

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

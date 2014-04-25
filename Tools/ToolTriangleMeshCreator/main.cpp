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
#include <string>

#include <boost/math/constants/constants.hpp>

#include "Shiny.h"

#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "trianglemeshcreatormaindialog.h"
#include "trace.h"
#include "trianglefile.h"
#include "trianglemeshcellscreator.h"
#include "trianglemeshcellscreatorfactory.h"
#include "trianglemeshface.h"
#include "trianglemeshhelper.h"
#pragma GCC diagnostic pop

int main(int, char* argv[])
{
  START_TRACE();
  PROFILE_FUNC();
  typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> Coordinat2D;
  {
    const ribi::Geometry geometry;
    const std::unique_ptr<ribi::Plane> plane(
      new ribi::Plane(
        geometry.CreatePoint(0.0,0.0,0.0),
        geometry.CreatePoint(0.0,1.0,0.0),
        geometry.CreatePoint(1.0,0.0,0.0)
      )
    );
    assert(plane);
  }

  const ::ribi::trim::CreateVerticalFacesStrategy strategy {
    ::ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
    //::ribi::trim::CreateVerticalFacesStrategy::two_faces_per_square
  };

  const bool verbose = true;

  const std::string checkMesh_command(
    std::string(
      R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat )")
    + R"("WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""" )"
      // Changing to drive D is important...
    + "&& D: "
      // ...although this also indicates the drive
    + "&& cd " + ribi::fileio::FileIo().GetPath(argv[0]) + " "
    + "&& cd .. "
    + (verbose ? "&& dir " : "")
    + "&& checkMesh"
  );

  //Test
  #ifndef NDEBUG
  const bool test_smaller_mesh = false;
  if (test_smaller_mesh)
  {
    try
    {
      const double pi = boost::math::constants::pi<double>();
      const std::vector<Coordinat2D> shapes {
        ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
      };
      const int n_layers = 3;
      const boost::units::quantity<boost::units::si::length> layer_height(
        1.0 * boost::units::si::meter
      );
      const double quality = 5.0;
      const ribi::TriangleMeshCreatorMainDialog d(
        shapes,
        n_layers,
        layer_height,
        strategy,
        quality,
        ribi::TriangleMeshCreatorMainDialog::CreateSculptFunctionRemoveRandom(0.75),
        ribi::TriangleMeshCreatorMainDialog::CreateDefaultAssignBoundaryFunction(),
        ribi::TriangleMeshCreatorMainDialog::CreateDefaultBoundaryToPatchFieldTypeFunction()
      );
      TRACE(checkMesh_command);
      std::system(checkMesh_command.c_str());
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
  #endif

  try
  {
    const double pi = boost::math::constants::pi<double>();
    const bool show_mesh = true;
    const std::vector<Coordinat2D> shapes {
      ribi::TriangleFile::CreateShapePolygon( 3,pi * 0.0 / 6.0,  1.0), //1 prism
      ribi::TriangleFile::CreateShapePolygon( 3,pi * 0.0 / 6.0,  2.0), //3 prisms
      ribi::TriangleFile::CreateShapePolygon( 5,pi * 0.0 / 6.0,  4.0),
      ribi::TriangleFile::CreateShapePolygon(11,pi * 0.0 / 6.0,  6.0),
      ribi::TriangleFile::CreateShapePolygon(21,pi * 0.0 / 6.0,  8.0)
    };
    const int n_layers = 5;
    const boost::units::quantity<boost::units::si::length> layer_height(
      10.0 * boost::units::si::meter / static_cast<double>(n_layers)
    );

    const double quality = 5.0;

    const ribi::TriangleMeshCreatorMainDialog d(
      shapes,
      n_layers,
      layer_height,
      strategy,
      quality,
      ribi::TriangleMeshCreatorMainDialog::CreateSculptFunctionRemoveRandom(0.75),
      ribi::TriangleMeshCreatorMainDialog::CreateDefaultAssignBoundaryFunction(),
      ribi::TriangleMeshCreatorMainDialog::CreateDefaultBoundaryToPatchFieldTypeFunction()
    );
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    if (show_mesh)
    {
      std::stringstream s;
      s
        << "C:\\Progra~1\\VCG\\Meshlab\\meshlab.exe "
        << d.GetFilename();
      const int error = std::system(s.str().c_str());
      if (error) std::cout << "WARNING: cannot display mesh" << '\n';
    }

    TRACE(checkMesh_command);
    std::system(checkMesh_command.c_str());
    return 0;
  }
  catch (std::exception& e)
  {
    std::cerr << "ERROR: Exception caught: " << e.what() << std::endl;
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown exception caught!" << std::endl;
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    return 1;
  }
}

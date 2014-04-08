#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <string>

#include <boost/math/constants/constants.hpp>

#include "Shiny.h"

#include "fileio.h"
#include "geometry.h"
#include "plane.h"
#include "testtrianglemeshmaindialog.h"
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
  {
    const std::unique_ptr<ribi::Plane> plane(
      new ribi::Plane(
        ribi::Geometry().CreatePoint(0.0,0.0,0.0),
        ribi::Geometry().CreatePoint(0.0,1.0,0.0),
        ribi::Geometry().CreatePoint(1.0,0.0,0.0)
      )
    );
    assert(plane);
  }

  const ::ribi::trim::CreateVerticalFacesStrategy strategy {
    ::ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
    //::ribi::trim::CreateVerticalFacesStrategy::two_faces_per_square
  };

  try
  {
    const double pi { boost::math::constants::pi<double>() };
    const bool show_mesh { false };
    const std::string renumberMesh_command(
      std::string(
        R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat )")
      + R"("WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""")"
        // Changing to drive D is important...
      + " && D: "
        // ...although this also indicates the drive
      + " && cd " + ribi::fileio::FileIo().GetPath(argv[0])
      + " && cd .. && dir && renumberMesh"
    );
    const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes {
      //ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
      ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,0.5), //? cube
      //ribi::TriangleFile::CreateShapePolygon(3,pi * 0.0 / 6.0,1.0) //1 prism
      ribi::TriangleFile::CreateShapePolygon(3,pi * 0.0 / 6.0,2.0), //3 prisms
      ribi::TriangleFile::CreateShapePolygon(5,pi * 0.0 / 6.0,4.0)
    };


    ribi::TestTriangleMeshMainDialog d(
      shapes,
      show_mesh,
      100,
      strategy,
      renumberMesh_command
    );
    std::cout << d.GetTicks() << std::endl;
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    //checkMesh
    {
      std::stringstream cmd;
      cmd
        << R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat )"
        << R"("WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""")"
        // Changing to drive D is important...
        << " && D: "
        // ...although this also indicates the drive
        << " && cd " << ribi::fileio::FileIo().GetPath(argv[0])
        << " && cd .. && dir && checkMesh"
      ;
      TRACE(cmd.str());
      std::system(cmd.str().c_str());
    }
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

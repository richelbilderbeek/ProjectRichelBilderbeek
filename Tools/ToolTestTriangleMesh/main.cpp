#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <string>

#include <boost/math/constants/constants.hpp>

#include "Shiny.h"
#include "testtrianglemeshmaindialog.h"

#include "fileio.h"
#include "trianglefile.h"
#include "trace.h"
#include "plane.h"
#pragma GCC diagnostic pop


int main(int, char* argv[])
{

  START_TRACE();
  PROFILE_FUNC();
  ribi::Plane( {0.0,0.0,0.0},{0.0,1.0,0.0},{1.0,0.0,0.0} );

  const ::ribi::trim::CreateVerticalFacesStrategy strategy {
    ::ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
    //::ribi::trim::CreateVerticalFacesStrategy::two_faces_per_square
  };

  try
  {
    const double pi { boost::math::constants::pi<double>() };
    const bool show_mesh { true };
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
    ribi::TestTriangleMeshMainDialog(
      {
        //ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,1.0) //1 cube
        ribi::TriangleFile::CreateShapePolygon(4,pi * 0.125,0.5), //? cube
        //ribi::TriangleFile::CreateShapePolygon(3,pi * 0.0 / 6.0,1.0) //1 prism
        //ribi::TriangleFile::CreateShapePolygon(3,pi * 0.0 / 6.0,2.0), //3 prisms
        ribi::TriangleFile::CreateShapePolygon(5,pi * 0.0 / 6.0,4.0)
      },
      show_mesh,
      10,
      strategy,
      renumberMesh_command
    );
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

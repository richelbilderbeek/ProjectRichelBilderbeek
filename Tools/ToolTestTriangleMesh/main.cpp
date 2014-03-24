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
    const bool show_mesh { false };
    ribi::TestTriangleMeshMainDialog(
      {
        ribi::TriangleFile::CreateShapePolygon(4,pi * 0.25,1.0)
        //ribi::TriangleFile::CreateShapePolygon(3,tau * 0.0 / 6.0,2.0)
      },
      show_mesh,
      2,
      strategy
    );
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
    {
      std::stringstream cmd;
      cmd
        << R"(C:\cfd\blueCFD-SingleCore-2.1\OpenFOAM-2.1\etc\batchrc.bat )"
        << R"("WM_COMPILER=mingw-w32" "WM_PRECISION_OPTION=DP" "WM_MPLIB=""")"
        // Changing to drive D is important...
        << " && D: "
        // ...although this also indicates the drive
        //<< R"( && cd D:\Projects\Test\ToolOpenFoamErrorOpenCellsFoundCorrected)"
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

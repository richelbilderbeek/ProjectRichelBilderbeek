#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <string>

#include <boost/math/constants/constants.hpp>

#include "Shiny.h"
#include "testtrianglemeshmaindialog.h"

#include "trianglefile.h"
#include "trace.h"
#include "plane.h"
#pragma GCC diagnostic pop


int main()
{
  START_TRACE();
  PROFILE_FUNC();
  ribi::Plane();

  const ::ribi::trim::CreateVerticalFacesStrategy strategy {
    ::ribi::trim::CreateVerticalFacesStrategy::one_face_per_square
  };

  try
  {
    const double tau { boost::math::constants::two_pi<double>() };
    const bool show_mesh { true };
    ribi::TestTriangleMeshMainDialog(
      {
        ribi::TriangleFile::CreateShapePolygon(4,tau * 0.0 / 6.0,1.0)
        //, ribi::TriangleFile::CreateShapePolygon(3,tau * 0.0 / 6.0,2.0)
      },
      show_mesh,
      2,
      strategy
    );
    PROFILER_UPDATE();
    PROFILER_OUTPUT("shiny_output.txt");
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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <string>

#include "Shiny.h"
#include "testtrianglemeshmaindialog.h"
#include "trianglefile.h"
#include "trace.h"
#pragma GCC diagnostic pop


int main()
{
  START_TRACE();
  PROFILE_FUNC();
  try
  {

    ribi::TestTriangleMeshMainDialog(
      {
        ribi::TriangleFile::CreateShapeTriangle(1.0)
        //ribi::TriangleFile::CreateShapeHeart(1.0),
        //ribi::TriangleFile::CreateShapeHeart(1.5)
      },
      true,
      2
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

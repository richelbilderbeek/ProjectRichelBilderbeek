#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testtrianglemenudialog.h"
#pragma GCC diagnostic pop

//#221
//--WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --triangle_max_area 0.001 --triangle_min_angle 20.0 --profile

//TestTriangleConsole --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --triangle_max_area 10.0 --triangle_min_angle 20.0 --profile
int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  ribi::TestTriangleMenuDialog d;
  return d.Execute(args);

}

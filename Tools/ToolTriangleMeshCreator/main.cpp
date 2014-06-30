#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglemeshcreatormenudialog.h"
#pragma GCC diagnostic pop

//Easy, about 5 seconds
//TriangleMeshCreator --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 10.0 --triangle_min_angle 20.0 --profile

//Medium, about 100 seconds
//TriangleMeshCreator --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 1.0 --triangle_min_angle 20.0 --show_mesh --verbose

// Issue 221:
// --layer_height 1 --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --strategy 1 --n_layers 10 --fraction 0.9 --triangle_max_area 0.1 --triangle_min_angle 20.0 --profile --show_mesh
//
int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::TriangleMeshCreatorMenuDialog().Execute(args);
}

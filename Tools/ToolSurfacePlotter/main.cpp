#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "surfaceplottermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char* argv[])
{
  START_TRACE();
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::SurfacePlotterMenuDialog().Execute(args);
}

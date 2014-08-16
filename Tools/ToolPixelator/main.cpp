#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "pixelatormenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  const std::vector<std::string> args {
    ribi::PixelatorMenuDialog::ConvertArguments(argc,argv)
  };
  ribi::PixelatorMenuDialog d;
  return d.Execute(args);
}

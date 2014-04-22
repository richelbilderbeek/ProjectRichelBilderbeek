#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "imagerotatermenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  const std::vector<std::string> args {
    ribi::ImageRotaterMenuDialog::ConvertArguments(argc,argv)
  };
  ribi::ImageRotaterMenuDialog d;
  return d.Execute(args);
}

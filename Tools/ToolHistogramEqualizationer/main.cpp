#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "toolgaborfiltermenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  const std::vector<std::string> args {
    ribi::ToolGaborFilterMenuDialog::ConvertArguments(argc,argv)
  };
  ribi::ToolGaborFilterMenuDialog d;
  return d.Execute(args);
}

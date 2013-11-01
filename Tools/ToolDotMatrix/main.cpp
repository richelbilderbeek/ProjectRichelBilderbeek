
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "tooldotmatrixmenudialog.h"

#pragma GCC diagnostic pop

int main(int argc, char* argv[])
{
  ribi::ToolDotMatrixMenuDialog d;
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return d.Execute(args);

}

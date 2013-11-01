//#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
//#include <boost/lexical_cast.hpp>

#include "toolgraycodermenudialog.h"
//#include "toolgraycodermaindialog.h"

#pragma GCC diagnostic pop

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::GrayCoderMenuDialog::ConvertArguments(argc,argv) };
  ribi::GrayCoderMenuDialog d;
  return d.Execute(args);
}

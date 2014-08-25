#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <iostream>
#include "createglossarymenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::CreateGlossaryMenuDialog().Execute(args);
}


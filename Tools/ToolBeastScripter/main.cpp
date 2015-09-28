#include "beastscriptermenudialog.h"

#include <iostream>
#include <iterator>

int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  ribi::BeastScripterMenuDialog d;
  return d.Execute(args);
}

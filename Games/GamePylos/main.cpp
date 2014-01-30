#include <iostream>

#include "pylosmenudialog.h"

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::pylos::MenuDialog().Execute(args);
}

#include <iostream>

#include "daswahreschlagerfestmenudialog.h"

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::dws::DasWahreSchlagerfestMenuDialog().Execute(args);
}

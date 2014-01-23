#include <iostream>

#include "k3opeenrijmenudialog.h"

int main(int argc, char * argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::K3OpEenRijMenuDialog().Execute(args);
}

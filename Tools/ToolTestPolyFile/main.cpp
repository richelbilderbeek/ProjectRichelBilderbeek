#include "testpolyfilemenudialog.h"

int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::TestPolyFileMenuDialog().Execute(args);
}

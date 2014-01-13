#include "testmulticanvasmenudialog.h"
#include "trace.h"
#include "xml.h"

int main(int argc, char* argv[])
{
  START_TRACE();
  ribi::xml::Test();
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::TestMultiCanvasMenuDialog().Execute(args);
}

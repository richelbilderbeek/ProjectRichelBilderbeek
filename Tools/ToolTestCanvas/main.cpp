#include "tooltestcanvasmenudialog.h"
#include "trace.h"

int main(int argc, char* argv[])
{
  START_TRACE();
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::ToolTestCanvasMenuDialog().Execute(args);
}

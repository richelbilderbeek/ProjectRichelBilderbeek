#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <QDir>
#include <QFile>
#include <QFileInfoList>

#include "staircasecardcreatormenudialog.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

int main(int argc, char* argv[])
{
  START_TRACE();
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::scc::MenuDialog().Execute(args);
}

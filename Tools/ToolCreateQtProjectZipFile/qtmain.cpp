//---------------------------------------------------------------------------
/*
CreateQtProjectZipFile, tool to create a zip file from a Qt project
Copyright (C) 2012-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>

#include <csignal>
#include <iostream>

#include "qtcreateqtprojectzipfilemenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

void OnAbort(int)
{
  std::cout << "Abort" << std::endl;
}

int main(int argc, char *argv[])
{
  std::signal(SIGABRT,OnAbort);
  QApplication a(argc, argv);
  START_TRACE();
  ribi::QtCreateQtProjectZipFileMenuDialog w;
  w.show();
  return a.exec();
}


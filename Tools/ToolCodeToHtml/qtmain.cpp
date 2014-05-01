//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2014  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <csignal>
#include <iostream>

#include <QApplication>

#include "codetohtml.h"
#include "qtcreatorprofile.h"
#include "qtcodetohtmlmenudialog.h"
#include "codetohtmldialog.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

/*
void OnAbort(int)
{
  std::cerr << "Application called OnAbort" << std::endl;
  std::exit(1);
}
*/

int main(int argc, char *argv[])
{
  //Connect the abort signal to the OnAbort, to obtain informative
  //screen output with 'Projects | Run | Run in terminal' unchecked
  //std::signal(SIGABRT,OnAbort);

  QApplication a(argc, argv);
  try
  {
    START_TRACE();
    #ifndef _WIN32
    assert(ribi::c2h::IsTidyInstalled() && "I really want to be sure that tidy is installed");
    #endif

    #ifndef NDEBUG
    ribi::fileio::FileIo();
    assert( ribi::fileio::FileIo().IsRegularFile(argv[0]));
    assert(!ribi::fileio::FileIo().IsFolder(argv[0]));
    #endif

    ribi::c2h::QtCodeToHtmlMenuDialog w;
    w.show();
    return a.exec();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception thrown: " << e.what() << std::endl;
    return 1;
  }
}

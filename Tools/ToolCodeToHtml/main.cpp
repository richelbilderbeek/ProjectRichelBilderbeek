//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2011  Richel Bilderbeek

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
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <QDir>
#include <QFile>
#include <QFileInfoList>

#include "codetohtmlinfo.h"
#include "codetohtmlmenudialog.h"
#include "fileio.h"
#include "trace.h"
#pragma GCC diagnostic pop

//From http://www.richelbilderbeek.nl/CppGetCurrentFolder.htm
const std::string GetCurrentFolder(const std::string& s)
{
  return ribi::fileio::GetPath(s);
}

int main(int argc, char* argv[])
{
  START_TRACE();
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  return ribi::c2h::CodeToHtmlMenuDialog().Execute(args);
}

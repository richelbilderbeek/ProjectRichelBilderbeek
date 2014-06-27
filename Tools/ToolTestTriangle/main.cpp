//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestTriangle.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testtrianglemenudialog.h"
#pragma GCC diagnostic pop

//#221
//--WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --triangle_max_area 0.001 --triangle_min_angle 20.0 --profile

//TestTriangleConsole --WKT "POLYGON((10 10,10 -10,-10 -10,-10 10))" --triangle_max_area 10.0 --triangle_min_angle 20.0 --profile
int main(int argc, char* argv[])
{
  const std::vector<std::string> args { ribi::MenuDialog::ConvertArguments(argc,argv) };
  ribi::TestTriangleMenuDialog d;
  return d.Execute(args);

}

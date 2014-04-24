//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2014 Richel Bilderbeek

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
#ifndef CODETOHTMLFILETYPE_H
#define CODETOHTMLFILETYPE_H

namespace ribi {
namespace c2h {

///The type of file
enum class FileType
{
  cpp,          //.cpp file
  license_txt,  //license.txt file
  png,          //.png image file
  pri,          //.pri file
  pro,          //.pro file
  py,           //.py file
  sh,           //.sh file
  txt,          //.txt file, to be renamed to txt
  n_types       //Used for debugging
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLFILETYPE_H

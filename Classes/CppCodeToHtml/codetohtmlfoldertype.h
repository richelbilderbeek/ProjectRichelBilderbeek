//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
#ifndef CODETOHTMLFOLDERTYPE_H
#define CODETOHTMLFOLDERTYPE_H

namespace ribi {
namespace c2h {

///The type of folder content:



enum class FolderType
{
  foam, ///an OpenFOAM project
  pro,  ///a Qt Creator project
  txt   ///a collection of text files
};

} //~namespace ribi
} //~namespace c2h

#endif // CODETOHTMLFOLDERTYPE_H

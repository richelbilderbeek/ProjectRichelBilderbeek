//---------------------------------------------------------------------------
/*
Lazy_init. Class to postpone constructor call upon first use.
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppLazy_init.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "lazy_init.h"

const std::string Lazy_initVersion::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> Lazy_initVersion::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-02-11: version 1.0: initial version");
  return v;
}


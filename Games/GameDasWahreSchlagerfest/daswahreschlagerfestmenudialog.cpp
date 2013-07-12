
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2012 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "daswahreschlagerfestmenudialog.h"

DasWahreSchlagerfestMenuDialog::DasWahreSchlagerfestMenuDialog()
{

}

const About DasWahreSchlagerfestMenuDialog::GetAbout()
{
  return About(
    "Richel Bilderbeek",
    "Das Wahre Schlagerfest",
    "a simple game",
    "the 9th of August 2012",
    "2003-2012",
    "http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm",
    GetVersion(),
    GetVersionHistory());

}

const std::string DasWahreSchlagerfestMenuDialog::GetVersion()
{
  return "2.2";
}

const std::vector<std::string> DasWahreSchlagerfestMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2003-09-30: version 1.1: Windows-only version");
  v.push_back("2012-07-21: version 2.0: ported to cross-platform");
  v.push_back("2012-07-29: version 2.1: changed graphics to old-school");
  v.push_back("2012-08-09: version 2.2: changed graphics, changed new tile selection (rendering the eat-it all tile) obsolete");
  return v;
}


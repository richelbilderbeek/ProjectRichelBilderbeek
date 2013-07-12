//---------------------------------------------------------------------------
/*
StateObserver, tool to examine state observers
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolStateObserver.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "stateobservermenudialog.h"

#include "trace.h"
#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "integeralphafilter.h"
#include "integerstateobserver.h"
#include "integersymmetricalphafilter.h"
#include "multialphafilter.h"
#include "multiintegerstateobserver.h"

const About StateObserverMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "StateObserver",
    "tool to examine state observers",
    "the 12th of July 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolStateObserver.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("AlphaFilter version: " + AlphaFilter::GetVersion());
  a.AddLibrary("AlphaBetaFilter version: " + AlphaBetaFilter::GetVersion());
  a.AddLibrary("AlphaBetaGammaFilter version: " + AlphaBetaGammaFilter::GetVersion());
  a.AddLibrary("IntegerAlphaFilter version: " + IntegerAlphaFilter::GetVersion());
  a.AddLibrary("IntegerStateObserver version: " + IntegerStateObserver::GetVersion());
  a.AddLibrary("IntegerSymmetricalAlphaFilter version: " + IntegerSymmetricalAlphaFilter::GetVersion());
  a.AddLibrary("MultiAlphaFilter version: " + MultiAlphaFilter::GetVersion());
  a.AddLibrary("MultiIntegerStateObserver version: " + MultiIntegerStateObserver::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string StateObserverMenuDialog::GetVersion()
{
  return "1.2";
}

const std::vector<std::string> StateObserverMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-05-25: version 1.0: initial version");
  v.push_back("2013-06-04: version 1.1: added more state observers, allow plotting of subset of state observers");
  v.push_back("2013-06-17: version 1.1: improved menu screen");
  v.push_back("2013-07-12: version 1.2: transitioned to Qt5 and Boost 1.54.0");
  return v;
}

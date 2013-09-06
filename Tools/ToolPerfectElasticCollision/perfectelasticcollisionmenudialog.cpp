//---------------------------------------------------------------------------
/*
PerfectElasticCollision, tool to investigate a perfect elastic collision
Copyright (C) 2010 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm
//---------------------------------------------------------------------------


#include "perfectelasticcollisionmenudialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

const About PerfectElasticCollisionMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "PerfectElasticCollision",
    "tool to investigate a perfect elastic collision",
    "the 7th of March 2012",
    "2010-2012",
    "http://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  return a;
}

const std::string PerfectElasticCollisionMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> PerfectElasticCollisionMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-08-14: version 1.0: initial version.");
  v.push_back("2012-03-07: version 1.1: added versioning. Added menu screen.");
  return v;
}


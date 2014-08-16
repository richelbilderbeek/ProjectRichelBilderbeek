//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "UnitResults.h"
//---------------------------------------------------------------------------
#include <string>
#include "Assert.h"
//---------------------------------------------------------------------------
const std::auto_ptr<Results> Results::mpInstance(new Results);
//---------------------------------------------------------------------------
Results::Results()
{

}
//---------------------------------------------------------------------------
Results::~Results()
{

}
//---------------------------------------------------------------------------
Results* Results::instance()
{
  Assert(mpInstance.get()!=0);
  return mpInstance.get();
}
//---------------------------------------------------------------------------
void Results::log(const std::string& s)
{
  mLog.push_back(s);
}
//---------------------------------------------------------------------------
void Results::log(const char* s)
{
  mLog.push_back(s);
}
//---------------------------------------------------------------------------
void Results::reset()
{
  mNsingleFemales.resize(0);
  mNsingleMales.resize(0);
  mNcouples.resize(0);
  mNmigrants.resize(0);
  mNdead.resize(0);
  mLog.resize(0);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)

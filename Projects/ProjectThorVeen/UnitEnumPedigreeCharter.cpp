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

#include "UnitEnumPedigreeCharter.h"

//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <assert>
//---------------------------------------------------------------------------
const std::auto_ptr<EnumPedigreeCharterConverter> EnumPedigreeCharterConverter::mpInstance(new EnumPedigreeCharterConverter);
//---------------------------------------------------------------------------
EnumPedigreeCharterConverter * EnumPedigreeCharterConverter::instance()
{
  assert(mpInstance.get()!=0);
  return mpInstance.get();
}
//---------------------------------------------------------------------------
EnumPedigreeCharterConverter::EnumPedigreeCharterConverter()
{
  mMap[pedigreeCharterNone] = "pedigreeCharterNone";
  mMap[pedigreeCharterAll] = "pedigreeCharterAll";
}
//---------------------------------------------------------------------------
EnumPedigreeCharter EnumPedigreeCharterConverter::toEnum(const std::string& myString) const
{
  for(mIter = mMap.begin(); mIter!=mMap.end(); ++mIter)
  {
    if ((*mIter).second==myString) return ((*mIter).first);
  }
  assert(!"Unknown string");
  std::exit(1);
  return pedigreeCharterNone;
}
//---------------------------------------------------------------------------
std::string EnumPedigreeCharterConverter::toString(const EnumPedigreeCharter& myEnumPedigreeCharter) const
{
  return mMap.operator [](myEnumPedigreeCharter);
}
//---------------------------------------------------------------------------
void EnumPedigreeCharterConverter::cout(const EnumPedigreeCharter& myEnumPedigreeCharter) const
{
  std::cout << toString(myEnumPedigreeCharter) << std::endl;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

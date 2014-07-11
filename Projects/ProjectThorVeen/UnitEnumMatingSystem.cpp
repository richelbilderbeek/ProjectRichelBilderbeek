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

#include "UnitEnumMatingSystem.h"

//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <assert>
//---------------------------------------------------------------------------
const std::auto_ptr<EnumMatingSystemConverter> EnumMatingSystemConverter::mpInstance(new EnumMatingSystemConverter);
//---------------------------------------------------------------------------
EnumMatingSystemConverter * EnumMatingSystemConverter::instance()
{
  assert(mpInstance.get()!=0);
  return mpInstance.get();
}
//---------------------------------------------------------------------------
EnumMatingSystemConverter::EnumMatingSystemConverter()
{
  mMap[monogamy] = "monogamy";
  mMap[polygyny] = "polygyny";
}
//---------------------------------------------------------------------------
EnumMatingSystem EnumMatingSystemConverter::toEnum(const std::string& myString) const
{
  for(mIter = mMap.begin(); mIter!=mMap.end(); ++mIter)
  {
    if ((*mIter).second==myString) return ((*mIter).first);
  }
  assert(!"Unknown string");
  std::exit(1);
  return monogamy;
}
//---------------------------------------------------------------------------
std::string EnumMatingSystemConverter::toString(const EnumMatingSystem& myEnumMatingSystem) const
{
  return mMap.operator [](myEnumMatingSystem);
}
//---------------------------------------------------------------------------
void EnumMatingSystemConverter::cout(const EnumMatingSystem& myEnumMatingSystem) const
{
  std::cout << toString(myEnumMatingSystem) << std::endl;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

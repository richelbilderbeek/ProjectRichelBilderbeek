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
#include "UnitWeather.h"
//---------------------------------------------------------------------------
#include "Assert.h"
//---------------------------------------------------------------------------
#ifndef NDEBUG
  #include "UnitHelperFunctions.h"
#endif
//---------------------------------------------------------------------------
//std::auto_ptr<Weather> Weather::mpInstance(new Weather);
std::auto_ptr<Weather> Weather::mpInstance(0);
//---------------------------------------------------------------------------
#ifndef NDEBUG
  int Weather::mConstructorCalled = 0;
#endif
//---------------------------------------------------------------------------
Weather::Weather()
  : mTimeUnit(0)
{
  #ifndef NDEBUG
    ++mConstructorCalled;
    //Assert(mConstructorCalled==1);
  #endif
}
//---------------------------------------------------------------------------
Weather::~Weather()
{

}
//---------------------------------------------------------------------------
Weather* Weather::instance()
{
  if (mpInstance.get()==0) mpInstance.reset(new Weather);
  Assert(mpInstance.get()!=0);
  return mpInstance.get();
}
//---------------------------------------------------------------------------
void Weather::nextTimeUnit()
{
  ++mTimeUnit;
  #ifndef NDEBUG
    helper::dot("TimeUnit: ");
    helper::dot(mTimeUnit);
  #endif
}
//---------------------------------------------------------------------------
int Weather::getTimeUnit() const
{
  return mTimeUnit;
}
//---------------------------------------------------------------------------
void Weather::reset()
{
  mTimeUnit = 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)

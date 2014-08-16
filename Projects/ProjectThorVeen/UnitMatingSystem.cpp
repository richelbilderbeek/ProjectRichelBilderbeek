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

#include "UnitMatingSystem.h"
//---------------------------------------------------------------------------
#include <string>
#include "Assert.h"
#include "UnitSingleMalePool.h"
#include "UnitCouplePool.h"
//---------------------------------------------------------------------------
MatingSystemBase::MatingSystemBase()
{

}
//---------------------------------------------------------------------------
MatingSystemBase::~MatingSystemBase()
{
  
}
//---------------------------------------------------------------------------
MatingSystemMonogamy::MatingSystemMonogamy()
{
  
}
//---------------------------------------------------------------------------
MatingSystemMonogamy::~MatingSystemMonogamy()
{

}
//---------------------------------------------------------------------------
std::string MatingSystemMonogamy::getClassName() const
{
  return "MatingSystemMonogamy";
}
//---------------------------------------------------------------------------
MatingSystemPolygyny::MatingSystemPolygyny()
{

}
//---------------------------------------------------------------------------
MatingSystemPolygyny::~MatingSystemPolygyny()
{

}
//---------------------------------------------------------------------------
std::string MatingSystemPolygyny::getClassName() const
{
  return "MatingSystemPolygyny";
}
//---------------------------------------------------------------------------
void MatingSystemMonogamy::makeCouple(
  boost::shared_ptr<BirdBase>& female,
  boost::shared_ptr<BirdBase>& male,
  std::auto_ptr<SingleMalePool>& singleMalePool,
  std::auto_ptr<CouplePool>& couplePool) const
{
  Assert(female.get()!=0);
  Assert(male.get()!=0);
  Assert(singleMalePool.get()!=0);
  Assert(couplePool.get()!=0);

  couplePool->addCouple(female,male);
}
//---------------------------------------------------------------------------
void MatingSystemPolygyny::makeCouple(
  boost::shared_ptr<BirdBase>& female,
  boost::shared_ptr<BirdBase>& male,
  std::auto_ptr<SingleMalePool>& singleMalePool,
  std::auto_ptr<CouplePool>& couplePool) const
{
  Assert(female.get()!=0);
  Assert(male.get()!=0);
  Assert(singleMalePool.get()!=0);
  Assert(couplePool.get()!=0);

  boost::shared_ptr<BirdBase> maleCopy = male;
  couplePool->addCouple(female,male);
  Assert(maleCopy.get()!=0);
  singleMalePool->addMale(maleCopy);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)

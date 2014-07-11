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
#include "UnitCouplePool.h"
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include "Assert.h"
#include "UnitBird.h"
#include "UnitCouple.h"
#include "UnitDeadPool.h"
#include "UnitExceptions.h"
//---------------------------------------------------------------------------
void CouplePool::addCouple(
  boost::shared_ptr<BirdBase>& female,
  boost::shared_ptr<BirdBase>& male)
{
  Assert(female.get()!=0);
  Assert(male.get()!=0);
  Assert(female.use_count()==2); //One copy is stored in BirdWatcher
  Assert(male.use_count()==2); //One copy is stored in BirdWatcher

  boost::shared_ptr<Couple> couple(new Couple(female,male));

  Assert(female.get()==0);
  Assert(male.get()==0);

  Assert(couple->isFemaleNull() == false);
  Assert(couple->isMaleNull()   == false);

  mCouples.push_back(couple);

  Assert(mCouples.back()->isFemaleNull() == false );
  Assert(mCouples.back()->isMaleNull()   == false );

  couple.reset();

  Assert(couple.get()==0);
  //No couple anymore...  Assert(couple->isFemaleNull() == true);
  //No couple anymore...  Assert(couple->isMaleNull()   == true);
}
//---------------------------------------------------------------------------
boost::shared_ptr<Couple> CouplePool::getRandomCouple() const
{
  try
  {
    const int index = std::rand() % mCouples.size();
    return mCouples[ index ];
  }
  catch(...)
  {
    Assert(mCouples.size()==0);
    throw NoCouplesException();
  }
}
//---------------------------------------------------------------------------
void CouplePool::doEmpty(std::auto_ptr<DeadPool>& deadPool)
{
  Assert(deadPool.get()!=0);

  const int nCouples = mCouples.size();
  for (int i=0; i<nCouples; ++i)
  {
    boost::shared_ptr<BirdBase> female = mCouples[i]->getFemale();
    boost::shared_ptr<BirdBase> male = mCouples[i]->getMale();

    Assert(female.get()!=0);
    Assert(male.get()!=0);
    Assert(female.use_count()==2); //One copy is stored in BirdWatcher
    Assert(male.use_count()==2); //One copy is stored in BirdWatcher
    Assert(mCouples[i]->isFemaleNull() == true);
    Assert(mCouples[i]->isMaleNull() == true);

    deadPool->addFemale( female );
    deadPool->addMale( male );

    Assert(female.get()==0);
    Assert(male.get()==0);
  }
  mCouples.resize(0);
}
//---------------------------------------------------------------------------
bool CouplePool::isEmpty() const
{
  return mCouples.empty();
}
//---------------------------------------------------------------------------
int CouplePool::getSize() const
{
  return mCouples.size();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma package(smart_init)

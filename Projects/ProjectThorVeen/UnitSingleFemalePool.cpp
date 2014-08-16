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
#include <algorithm>
#include "UnitBird.h"
//---------------------------------------------------------------------------
#include "UnitSingleFemalePool.h"
#include "UnitDeadPool.h"
#include "Assert.h"
//---------------------------------------------------------------------------
SingleFemalePool::SingleFemalePool()
{

}
//---------------------------------------------------------------------------
void SingleFemalePool::addFemale(boost::shared_ptr<BirdBase>& female)
{
  Assert(female.get()!=0);
  #ifndef __HACK_RICHEL_879286486293
  if (female.use_count()!=2) ShowMessage(female.use_count());
  #endif
  Assert(female.use_count()==2); //One copy is stored in BirdWatcher

  mFemales.push_back( female );
  female.reset();

  Assert(female.get()==0);
  Assert(mFemales.back().get()!=0);
  Assert(mFemales.back().use_count()==2); //One copy is stored in BirdWatcher
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> SingleFemalePool::getFemale()
{
  Assert(mFemales.empty()==false);

  boost::shared_ptr<BirdBase> female(mFemales.back());
  mFemales.pop_back();

  Assert(female.get()!=0);
  Assert(female.use_count()==2); //One copy is stored in BirdWatcher

  return female;
}
//---------------------------------------------------------------------------
void SingleFemalePool::shuffle()
{
  std::random_shuffle(mFemales.begin(),mFemales.end());
}
//---------------------------------------------------------------------------
bool SingleFemalePool::isEmpty() const
{
  return mFemales.empty();
}
//---------------------------------------------------------------------------
int SingleFemalePool::getSize() const
{
  return mFemales.size();
}
//---------------------------------------------------------------------------
void SingleFemalePool::doEmpty(std::auto_ptr<DeadPool>& deadPool)
{
  while(mFemales.empty()==false)
  {
    boost::shared_ptr<BirdBase> female = mFemales.back();
    Assert(female.get()!=0);
    mFemales.pop_back();
    deadPool->addFemale(female);
    Assert(female.get()==0);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma package(smart_init)

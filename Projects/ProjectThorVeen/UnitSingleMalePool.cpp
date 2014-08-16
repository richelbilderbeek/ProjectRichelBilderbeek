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
#include "UnitSingleMalePool.h"
#include "UnitDeadPool.h"
#include "Assert.h"
//---------------------------------------------------------------------------
SingleMalePool::SingleMalePool()
{

}
//---------------------------------------------------------------------------
//void SingleMalePool::addMale(std::auto_ptr<BirdBase> male)
void SingleMalePool::addMale(boost::shared_ptr<BirdBase>& male)
{
  Assert(male.get()!=0);
  Assert(male.use_count()==2); //One copy is stored in BirdWatcher

  mMales.push_back( male );
  male.reset();

  Assert(mMales.back().get()!=0);
  Assert(mMales.back().use_count()==2); //One copy is stored in BirdWatcher
  Assert(male.get()==0);
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> SingleMalePool::getMale()
{
  Assert(this->isEmpty()==false);

  boost::shared_ptr<BirdBase> male(mMales.back());
  mMales.pop_back();

  Assert(male.get()!=0);
  Assert(male.use_count()==2); //One copy is stored in BirdWatcher
  return male;
}
//---------------------------------------------------------------------------
void SingleMalePool::shuffle()
{
  std::random_shuffle(mMales.begin(),mMales.end());
}
//---------------------------------------------------------------------------
bool SingleMalePool::isEmpty() const
{
  return mMales.empty();
}
//---------------------------------------------------------------------------
int SingleMalePool::getSize() const
{
  return mMales.size();
}
//---------------------------------------------------------------------------
void SingleMalePool::doEmpty(std::auto_ptr<DeadPool>& deadPool)
{
  while(mMales.empty()==false)
  {
    boost::shared_ptr<BirdBase> male = mMales.back();
    Assert(male.get()!=0);
    mMales.pop_back();
    deadPool->addMale(male);
    Assert(male.get()==0);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)

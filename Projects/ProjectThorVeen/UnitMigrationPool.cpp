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
#include "UnitMigrationPool.h"
//---------------------------------------------------------------------------
#include "UnitBird.h"
#include "Assert.h"
//---------------------------------------------------------------------------
void MigrationPool::addFemale(boost::shared_ptr<BirdBase>& female)
{
  mFemales.push_back( female );
  female.reset();
}
//---------------------------------------------------------------------------
void MigrationPool::addMale(boost::shared_ptr<BirdBase>& male)
{
  mMales.push_back( male );
  male.reset();
}
//---------------------------------------------------------------------------
bool MigrationPool::isEmpty() const
{
  return (mFemales.empty() == true && mMales.empty() == true);
}
//---------------------------------------------------------------------------
bool MigrationPool::hasFemales() const
{
  return (!mFemales.empty());
}
//---------------------------------------------------------------------------
bool MigrationPool::hasMales() const
{
  return (!mMales.empty());
}
//---------------------------------------------------------------------------
int MigrationPool::getNfemales() const
{
  return mFemales.size();
}
//---------------------------------------------------------------------------
int MigrationPool::getNmales() const
{
  return mMales.size();
}
//---------------------------------------------------------------------------
int MigrationPool::getSize() const
{
  return ( mMales.size() + mFemales.size() );
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> MigrationPool::getFemale()
{
  Assert(mFemales.empty()==false);

  boost::shared_ptr<BirdBase> female = mFemales.back();

  mFemales.pop_back();

  Assert(female.get()!=0);
  Assert(female.use_count()==2);

  return female;
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> MigrationPool::getMale()
{
  Assert(mMales.empty()==false);

  boost::shared_ptr<BirdBase> male = mMales.back();

  mMales.pop_back();

  Assert(male.get()!=0);
  Assert(male.use_count()==2); //One copy is stored in BirdWatcher

  return male;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#pragma package(smart_init)

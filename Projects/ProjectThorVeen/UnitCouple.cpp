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
#include "UnitBird.h"
#include "UnitCouple.h"
#include "UnitExceptions.h"
//---------------------------------------------------------------------------
#include "Assert.h"
#include "UnitBirdWatcher.h"
//---------------------------------------------------------------------------
BirdWatcher * Couple::mBirdWatcher = BirdWatcher::instance();
//---------------------------------------------------------------------------
Couple::Couple(boost::shared_ptr<BirdBase>& female, boost::shared_ptr<BirdBase>& male)
{
  Assert(female.get()!=0);
  Assert(male.get()!=0);

  mFemale = female;
  mMale   = male;

  female.reset();
  male.reset();

  Assert(mFemale.get()!=0);
  Assert(mMale.get()!=0);
  Assert(female.get()==0);
  Assert(male.get()==0);
}
//---------------------------------------------------------------------------
Couple::~Couple()
{
  Assert(mFemale.get()==0);
  Assert(mMale.get()==0);
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> Couple::createOneOffspring() const
{
  if (mMale->getClassType() == hawkDove )
  {
    boost::shared_ptr<BirdBase> kid(new BirdHawkDove(mFemale,mMale));
    mBirdWatcher->reportNewBird(kid);
    return kid;
  }
  Assert(!"Unknown bird type");
  throw UnknownBirdTypeException();
}
//---------------------------------------------------------------------------

boost::shared_ptr<BirdBase> Couple::getMale()
{
  boost::shared_ptr<BirdBase> male(mMale);
  mMale.reset();
  return male;
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> Couple::getFemale()
{
  boost::shared_ptr<BirdBase> female = mFemale;
  mFemale.reset();
  return female;
}

//---------------------------------------------------------------------------
bool Couple::isFemaleNull() const
{
  return ( mFemale.get() == 0 ? true : false );
}
//---------------------------------------------------------------------------
bool Couple::isMaleNull() const
{
  return ( mMale.get() == 0 ? true : false );
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

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
#include "UnitDeadPool.h"
//---------------------------------------------------------------------------
#include "assert.h"
#include "UnitBird.h"
//---------------------------------------------------------------------------
void DeadPool::addFemale(boost::shared_ptr<BirdBase>& female)
{
  assert(female.get()!=0);

  mFemales.push_back( female );
  female.reset();

  assert(female.get()==0);
}
//---------------------------------------------------------------------------
void DeadPool::addMale(boost::shared_ptr<BirdBase>& male)
{
  assert(male.get()!=0);

  mMales.push_back( male );
  male.reset();

  assert(male.get()==0);
}
//---------------------------------------------------------------------------
int DeadPool::getNfemales() const
{
  return mFemales.size();
}
//---------------------------------------------------------------------------
int DeadPool::getNmales() const
{
  return mMales.size();
}
//---------------------------------------------------------------------------
int DeadPool::getSize() const
{
  return ( mMales.size() + mFemales.size() );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)

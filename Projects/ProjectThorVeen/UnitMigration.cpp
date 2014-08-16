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

#include "UnitMigration.h"
//---------------------------------------------------------------------------
#include "UnitMigrationPool.h"
#include "UnitSingleFemalePool.h"
#include "UnitSingleMalePool.h"
#include "UnitDeadPool.h"
#include "Assert.h"
//---------------------------------------------------------------------------
void MigrationAllSurvive::migration(
  std::auto_ptr<MigrationPool>& migrationPool,
  std::auto_ptr<SingleFemalePool>& singleFemalePool,
  std::auto_ptr<SingleMalePool>& singleMalePool,
  std::auto_ptr<DeadPool>& deadPool) const
{

  const int nFemales = migrationPool->getNfemales();
  for (int i=0; i<nFemales; ++i)
  {
    boost::shared_ptr<BirdBase> female = migrationPool->getFemale();


    Assert(female.get()!=0);
    Assert(female.use_count()==2); //One copy is stored in BirdWatcher

    singleFemalePool->addFemale(female);

    Assert(female.get()==0);
  }

  const int nMales   = migrationPool->getNmales();
  for (int i=0; i<nMales; ++i)
  {
    boost::shared_ptr<BirdBase> male = migrationPool->getMale();

    Assert(male.get()!=0);
    Assert(male.use_count()==2); //One copy is stored in BirdWatcher

    singleMalePool->addMale(male);

    Assert(male.get()==0);
  }

  Assert(migrationPool->isEmpty()==true);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

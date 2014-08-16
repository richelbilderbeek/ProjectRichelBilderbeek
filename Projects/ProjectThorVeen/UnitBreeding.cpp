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
#include "UnitBreeding.h"
//---------------------------------------------------------------------------
#include <string>
#include "UnitCouplePool.h"
#include "UnitMigrationPool.h"
#include "UnitDeadPool.h"
#include "UnitCouple.h"
#include "UnitResults.h"
#include "UnitExceptions.h"
#include "UnitHelperFunctions.h"
//---------------------------------------------------------------------------
void BreedingSingleGeneration::breed(
  std::auto_ptr<CouplePool>& couplePool,
  std::auto_ptr<MigrationPool>& migrationPool,
  std::auto_ptr<DeadPool>& deadPool,
  const int& nFemalesWanted,
  const int& nMalesWanted) const
{
  //helper::dot("Start of void BreedingSingleGeneration::breed");
  //helper::dot("couplePool.size()= " + helper::itoa( couplePool->getSize() ) );

  //Create females
  try
  {
    for (int i=0; i<nFemalesWanted; ++i)
    {
      boost::shared_ptr<BirdBase> female = couplePool->getRandomCouple()->createOneOffspring();
      migrationPool->addFemale( female);
    }
  }
  catch (NoCouplesException& e)
  {
    Results * r = Results::instance();
    r->log("No couples left");
    throw NoCouplesException();
  }

  //Create males
  for (int i=0; i<nMalesWanted; ++i)
  {
    boost::shared_ptr<BirdBase> male = couplePool->getRandomCouple()->createOneOffspring();
    migrationPool->addMale( male );
  }

  //Kill parents
  couplePool->doEmpty(deadPool);

  //Offspring is in migrationPool

}
//---------------------------------------------------------------------------

#pragma package(smart_init)

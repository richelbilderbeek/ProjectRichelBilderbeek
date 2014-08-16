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
#include "UnitSimulationType.h"
//---------------------------------------------------------------------------
#include <string>
#include "Assert.h"
#include "UnitSimulationParameters.h"
#include "UnitInitialBirdNumbers.h"
#include "UnitBreedingParameters.h"
#include "UnitSingleMalePool.h"
#include "UnitSingleFemalePool.h"
#include "UnitCouplePool.h"
#include "UnitMigrationPool.h"
#include "UnitDeadPool.h"
#include "UnitFemaleChoice.h"
#include "UnitBreeding.h"
#include "UnitMigration.h"
#include "UnitResults.h"
#include "UnitBirdFactory.h"
#include "UnitExceptions.h"
#include "UnitHelperFunctions.h"
#include "UnitWeather.h"
#include "UnitBirdWatcher.h"
#include "UnitDisplayOptions.h"
//---------------------------------------------------------------------------
SimulationTypeBase::SimulationTypeBase()
  : mSingleMalePool(new SingleMalePool),
  mSingleFemalePool(new SingleFemalePool),
  mCouplePool(new CouplePool),
  mMigrationPool(new MigrationPool),
  mDeadPool(new DeadPool)
{
  //mSingleMalePool.reset(new SingleMalePool);
  //mSingleFemalePool.reset(new SingleFemalePool);
  //mCouplePool.reset(new CouplePool);
  //mMigrationPool.reset(new MigrationPool);
}
//---------------------------------------------------------------------------
void SimulationTypeBase::setFemaleChoice(
  const EnumFemaleChoice& femaleChoice,
  const EnumMatingSystem& matingSystem)
{
  switch(femaleChoice)
  {
    case winnerFight2males: mFemaleChoice.reset(new FemaleChoiceWinnerFight2males(matingSystem));
      break;
    default:
      Assert(!"Shouldn't get here: Unimplemented value of femaleChoice");
      std::exit(1);
  }
  Assert(mFemaleChoice.get()!=0);
}
//---------------------------------------------------------------------------
//Placeholder for multiple types of Breeding
void SimulationTypeBase::setBreeding()
{
  //switch(breeding)
  //{
  //  case singleGeneration:
      mBreeding.reset(new BreedingSingleGeneration);
  //    break;
  //  default: Assert(!"Shouldn't get here"); std::exit(1);
  //}
  Assert(mBreeding.get()!=0);
}
//---------------------------------------------------------------------------
void SimulationTypeBase::setMigration(const EnumMigration& migration)
{
  switch(migration)
  {
    case allSurvive: mMigration.reset(new MigrationAllSurvive);
      break;
    default: Assert(!"Shouldn't get here"); std::exit(1);
  }
  Assert(mMigration.get()!=0);
}
//---------------------------------------------------------------------------
void SimulationTypeBase::setBirdType(const EnumBirdType& birdType)
{

  switch(birdType)
  {
    case hawkDove: mBirdFactory.reset(new BirdFactoryHawkDove(mSimulationParameters->mBirdGeneralParameters,mSimulationParameters->mBirdHawkDoveParameters));
      break;
    default: Assert(!"Shouldn't get here"); std::exit(1);
  }
  Assert(mBirdFactory.get()!=0);
  Assert(mBirdFactory->getClassName()=="BirdFactoryHawkDove");
}
//---------------------------------------------------------------------------
void SimulationTypeBase::initializePools()
{
  Assert(mSimulationParameters.get()!=0);
  Assert(mSimulationParameters->mInitialBirdNumbers.get()!=0);
  const int nSingleFemales = mSimulationParameters->mInitialBirdNumbers->mNinitialSingleFemales;
  const int nSingleMales   = mSimulationParameters->mInitialBirdNumbers->mNinitialSingleMales;
  const int nCouples       = mSimulationParameters->mInitialBirdNumbers->mNinitialCouples;
  const int nMigrants      = mSimulationParameters->mInitialBirdNumbers->mNinitialMigrants;
  const int nDead          = mSimulationParameters->mInitialBirdNumbers->mNinitialDead;
  for (int i=0; i<nSingleFemales; ++i) { boost::shared_ptr<BirdBase> female = mBirdFactory->createBird(); mSingleFemalePool->addFemale(female); }
  for (int i=0; i<nSingleMales  ; ++i) { boost::shared_ptr<BirdBase> male   = mBirdFactory->createBird(); mSingleMalePool->addMale(male);       }
  Assert(nCouples==0);
  Assert(nMigrants==0);
  Assert(nDead==0);
}
//---------------------------------------------------------------------------
SimulationTypeCartoonModel::SimulationTypeCartoonModel(
  const boost::shared_ptr<SimulationParameters>& simulationParameters)
{
  Assert(simulationParameters.get()!=0);

  mSimulationParameters = simulationParameters;

  Assert(simulationParameters.get()!=0);
  Assert(mSimulationParameters.get()!=0);
  Assert(mSimulationParameters.get() == simulationParameters.get());

  const EnumBirdType birdType = mSimulationParameters->mEnumBirdType;
  setBirdType(birdType);

  const EnumFemaleChoice femaleChoice = mSimulationParameters->mEnumFemaleChoice;
  const EnumMatingSystem matingSystem = mSimulationParameters->mEnumMatingSystem;
  setFemaleChoice(femaleChoice,matingSystem);

  setBreeding();

  const EnumMigration migration = mSimulationParameters->mEnumMigration;
  setMigration(migration);

  Assert(mFemaleChoice.get()!=0);
  Assert(mBreeding.get()!=0);
  Assert(mBirdFactory.get()!=0);
  Assert(mMigration.get()!=0);
}
//---------------------------------------------------------------------------
void SimulationTypeCartoonModel::execute()
{
  Assert(mSimulationParameters.get()!=0);
  Assert(mSingleFemalePool.get()!=0);
  Assert(mSingleMalePool.get()!=0);
  Assert(mCouplePool.get()!=0);
  Assert(mMigrationPool.get()!=0);
  Assert(mDeadPool.get()!=0);

  //Reset birdwatcher
  //Must be reset BEFORE any bird constructor is called
  //i.e. before initializePools();
  BirdWatcher * birdWatcher = BirdWatcher::instance();
  Assert(birdWatcher!=0);
  birdWatcher->reset();
  birdWatcher->setPedigreeCharter(mSimulationParameters->mDisplayOptions->mPedigreeCharter);

  //Reset weather
  //Must be reset BEFORE any bird constructor is called,
  //otherwise birdWatcher will give an old (too high, i.e. non-zero) TimeUnit to
  //the first created birds
  Weather * weather = Weather::instance();
  Assert(weather!=0);
  weather->reset();

  //Initialize the pools with birds
  initializePools();


  Results * results = Results::instance();
  Assert(results!=0);
  results->reset();

  const int nGenerations = mSimulationParameters->mNgenerations;
  for ( ; weather->getTimeUnit() < nGenerations; weather->nextTimeUnit())
  {
    #ifndef NDEBUG
      helper::dot("Starting " + helper::itoa(weather->getTimeUnit()) + "th generation");
      helper::dot("Size of mean Condition heritable: " + helper::itoa(birdWatcher->getMeansConditionHeritable().size()));
    #endif
    {
      results->mNsingleFemales.push_back( mSingleFemalePool->getSize());
      results->mNsingleMales.push_back( mSingleFemalePool->getSize());
      results->mNcouples.push_back( mCouplePool->getSize());
      results->mNmigrants.push_back( mMigrationPool->getSize());
      results->mNdead.push_back( mDeadPool->getSize());
    }

    Assert(mFemaleChoice.get()!=0);
    //Single males and single females are in their pools
    //Female choice, creates individuals in CouplePool
    bool noError = true;
    try
    {
      while(noError == true)
      {
        mFemaleChoice->choose(mSingleFemalePool,mSingleMalePool,mCouplePool,mDeadPool);
      }
    }
    catch(NoFemaleException& e)
    {
      noError = false;
      //helper::dot("Female choice ended because no females were left");
    }
    catch(NoMaleException& e)
    {
      noError = false;
      //helper::dot("Female choice ended because no males were left");
    }

    Assert(mSingleFemalePool->isEmpty()==true);
    Assert(mSingleMalePool->isEmpty()==true);

    //Now we have a CouplePool filled with couples
    //When breeding, couples produce offspring.
    //Also, some parents die
    Assert(mBreeding.get()!=0);
    mBreeding->breed(mCouplePool,mMigrationPool,mDeadPool,
      mSimulationParameters->mBreedingParameters->mNfemaleOffspring,
      mSimulationParameters->mBreedingParameters->mNmaleOffspring);

    //Now we have a filled migrationpool
    Assert(mMigration.get()!=0);
    mMigration->migration(mMigrationPool,mSingleFemalePool,mSingleMalePool,mDeadPool);

    //And now we have single males and females again!
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)


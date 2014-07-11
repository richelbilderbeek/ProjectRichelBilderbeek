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

#include "UnitEnumBirdType.h"
//---------------------------------------------------------------------------
#include "UnitBird.h"
//---------------------------------------------------------------------------
#include <stdlib>
#include <string>
#include "UnitRandom.h"
#include "UnitSimulationFunctions.h"
#include "UnitBirdGeneralParameters.h"
#include "UnitBirdHawkDoveParameters.h"
#include "UnitBirdFactory.h"
#include "UnitBirdWatcher.h"
#include "Assert.h"
#include "UnitHelperFunctions.h"
//---------------------------------------------------------------------------
int BirdBase::mBirdIndexCounter = 1;
double BirdBase::mMutationConditionHeritable = 0.0;
BirdWatcher * BirdBase::mBirdWatcher = 0;
//BirdWatcher * BirdBase::mBirdWatcher = BirdWatcher::instance();
//---------------------------------------------------------------------------
double BirdHawkDove::mMutationPlayHawkAlpha = 0.0;
double BirdHawkDove::mMutationPlayHawkBeta  = 0.0;
double BirdHawkDove::mPdieHawkHawkLoser     = 0.0;
//---------------------------------------------------------------------------
//Before a first bird is created, the mBirdWatcher must be initialized
BirdBase::BirdBase()
{
  //The BirdWatcher watches this
  mBirdIndex = mBirdIndexCounter;
  ++mBirdIndexCounter;

  //helper::dot("New bird created: ");
  //helper::dot(mBirdIndexCounter);
  //mBirdWatcher->reportNewBird(mBirdIndex);
  Assert(mBirdWatcher);
  mBirdWatcher->reportNewBird(this);
}
//---------------------------------------------------------------------------
BirdBase::~BirdBase()
{
  //helper::dot("Bird died: ");
  //helper::dot(mBirdIndexCounter);

  //The BirdWatcher watches this
  Assert(mBirdWatcher);
  mBirdWatcher->reportDeadBird(mBirdIndex);

}
//---------------------------------------------------------------------------
void BirdBase::InitBirdWatcher()
{
  mBirdWatcher = BirdWatcher::instance();
}
//---------------------------------------------------------------------------
BirdBase::BirdBase(const BirdFactoryBase * birdFactory)
{
  Assert(!"This function should be overridden in the derived classes");
}
//---------------------------------------------------------------------------
BirdBase::BirdBase(const boost::shared_ptr<BirdBase>& mother, const boost::shared_ptr<BirdBase>& father)
{
  Assert(!"This function should be overridden in the derived classes");
}
//---------------------------------------------------------------------------
void BirdBase::initBase(const boost::shared_ptr<BirdGeneralParameters>& params)
{
  mConditionHeritable = rnd::normal(

    params->mInitialConditionHeritableMean,
    params->mInitialConditionHeritableStdDev);
}
//---------------------------------------------------------------------------
std::string BirdBase::getClassName() const
{
  return "BirdBase";
}
//---------------------------------------------------------------------------
int BirdBase::getIndexMother() const
{
  return mIndexMother;
}
//---------------------------------------------------------------------------
int BirdBase::getIndexFather() const
{
  return mIndexFather;
}
//---------------------------------------------------------------------------
int BirdBase::getBirdIndex() const
{
  return mBirdIndex;
}
//---------------------------------------------------------------------------
double BirdBase::getCondition() const
{
  return mConditionHeritable + mConditionEnvironment + mConditionParental;
}
//---------------------------------------------------------------------------
double BirdBase::getConditionHeritable() const
{
  return mConditionHeritable;
}
//---------------------------------------------------------------------------
double BirdBase::getConditionEnvironment() const
{
  return mConditionEnvironment;
}
//---------------------------------------------------------------------------
double BirdBase::getConditionParental() const
{
  return mConditionParental;
}
//---------------------------------------------------------------------------
void BirdBase::setMutationConditionHeritable(
  const BirdFactoryBase * birdFactory,
  const double& mutationConditionHeritable)
{
  Assert(birdFactory!=0);
  mMutationConditionHeritable = mutationConditionHeritable;
}
//---------------------------------------------------------------------------
std::string BirdHawkDove::getClassName() const
{
  return "BirdHawkDove";
}
//---------------------------------------------------------------------------
EnumBirdType BirdHawkDove::getClassType() const
{
  return hawkDove;
}
//---------------------------------------------------------------------------
void BirdHawkDove::setMutationPlayHawkAlpha(const BirdFactoryBase * birdFactory, const double& mutationPlayHawkAlpha)
{
  Assert(birdFactory!=0);
  Assert(birdFactory->getClassName()=="BirdFactoryHawkDove");
  mMutationPlayHawkAlpha = mutationPlayHawkAlpha;
}
//---------------------------------------------------------------------------
void BirdHawkDove::setMutationPlayHawkBeta(const BirdFactoryBase * birdFactory, const double& mutationPlayHawkBeta)
{
  Assert(birdFactory!=0);
  Assert(birdFactory->getClassName()=="BirdFactoryHawkDove");
  mMutationPlayHawkBeta = mutationPlayHawkBeta;
}
//---------------------------------------------------------------------------
void BirdHawkDove::setPdieHawkHawkLoser(const BirdFactoryBase * birdFactory,  const double& pDieHawkHawkLoser)
{
  Assert(birdFactory!=0);
  Assert(birdFactory->getClassName()=="BirdFactoryHawkDove");
  mPdieHawkHawkLoser = pDieHawkHawkLoser;
}
//---------------------------------------------------------------------------
BirdHawkDove::BirdHawkDove(const BirdFactoryBase * birdFactory,
  const boost::shared_ptr<BirdGeneralParameters>& birdGeneralParams,
  const boost::shared_ptr<BirdHawkDoveParameters>& hawkDoveParams)
{

  Assert(birdFactory!=0);
  Assert(birdFactory->getClassName()=="BirdFactoryHawkDove");
  #ifndef NDEBUG
  const double alphaMean   = hawkDoveParams->mPlayHawkAlphaMean;
  const double alphaStdDev = hawkDoveParams->mPlayHawkAlphaStdDev;
  const double betaMean    = hawkDoveParams->mPlayHawkBetaMean;
  const double betaStdDev  = hawkDoveParams->mPlayHawkBetaStdDev;

  Assert(alphaMean   > -1000.0 && alphaMean   < 1000.0);
  Assert(alphaStdDev > -1000.0 && alphaStdDev < 1000.0);
  Assert(betaMean    > -1000.0 && betaMean    < 1000.0);
  Assert(betaStdDev  > -1000.0 && betaStdDev  < 1000.0);

  mPlayHawkAlpha = rnd::normal(alphaMean,alphaStdDev);
  mPlayHawkBeta  = rnd::normal(betaMean,betaStdDev);
  #else
  mPlayHawkAlpha = rnd::normal(hawkDoveParams->mPlayHawkAlphaMean, hawkDoveParams->mPlayHawkAlphaStdDev);
  mPlayHawkBeta  = rnd::normal(hawkDoveParams->mPlayHawkBetaMean , hawkDoveParams->mPlayHawkBetaStdDev );
  #endif

  mIndexMother = 0;
  mIndexFather = 0;
  mConditionEnvironment = 0.0;
  mConditionParental = 0.0;

  Assert(mMutationPlayHawkAlpha > -1000.0 && mMutationPlayHawkAlpha < 1000.0);
  Assert(mMutationPlayHawkBeta  > -1000.0 && mMutationPlayHawkBeta  < 1000.0);
  Assert(mPlayHawkAlpha > -1000.0 && mPlayHawkAlpha < 1000.0);
  Assert(mPlayHawkBeta  > -1000.0 && mPlayHawkBeta  < 1000.0);

  //mBirdWatcher->reportNewBirdHawkDove(this);

}
//---------------------------------------------------------------------------
BirdHawkDove::BirdHawkDove(const boost::shared_ptr<BirdBase>& motherBase, const boost::shared_ptr<BirdBase>& fatherBase)
{
  Assert(motherBase.get()!=0);
  Assert(fatherBase.get()!=0);
  Assert(motherBase->getClassType() == hawkDove);
  Assert(fatherBase->getClassType() == hawkDove);

  const BirdHawkDove * mother = dynamic_cast<BirdHawkDove*>(motherBase.get());
  const BirdHawkDove * father = dynamic_cast<BirdHawkDove*>(fatherBase.get());

  char flags = std::rand() >> 4;
  { //Constitution
    if (flags%2==0)
    {
      mConditionHeritable = mother->mConditionHeritable + rnd::normal(0.0,mMutationConditionHeritable);
    }
    else
    {
      mConditionHeritable = father->mConditionHeritable + rnd::normal(0.0,mMutationConditionHeritable);
    }
  }
  flags>>=1;
  { //PlayHawkAlpha
    if (flags%2==0)
    {
      mPlayHawkAlpha = mother->mPlayHawkAlpha + rnd::normal(0.0,mMutationPlayHawkAlpha);
    }
    else
    {
      mPlayHawkAlpha = father->mPlayHawkAlpha + rnd::normal(0.0,mMutationPlayHawkAlpha);
    }
  }
  flags>>=1;
  { //PlayHawkBeta
    if (flags%2==0)
    {
      mPlayHawkBeta = mother->mPlayHawkBeta + rnd::normal(0.0,mMutationPlayHawkBeta);
    }
    else
    {
      mPlayHawkBeta = father->mPlayHawkBeta + rnd::normal(0.0,mMutationPlayHawkBeta);
    }
  }

  mConditionEnvironment = 0.0;
  mConditionParental = 0.0;

  mIndexMother = mother->getBirdIndex();
  mIndexFather = father->getBirdIndex();

  Assert(motherBase.get()!=0);
  Assert(fatherBase.get()!=0);

  Assert(mMutationPlayHawkAlpha > -1000.0 && mMutationPlayHawkAlpha < 1000.0);
  Assert(mMutationPlayHawkBeta  > -1000.0 && mMutationPlayHawkBeta  < 1000.0);
  Assert(mPlayHawkAlpha > -1000.0 && mPlayHawkAlpha < 1000.0);
  Assert(mPlayHawkBeta  > -1000.0 && mPlayHawkBeta  < 1000.0);

  //mBirdWatcher->reportNewBirdHawkDove(mPlayHawkAlpha,mPlayHawkBeta);
  //mBirdWatcher->reportNewBirdHawkDove(this);
}
//---------------------------------------------------------------------------
bool BirdHawkDove::willDieLoserFight() const
{
  return (rnd::uniform() < mPdieHawkHawkLoser ? true : false);

}
//---------------------------------------------------------------------------
bool BirdHawkDove::willFight(const boost::shared_ptr<BirdBase>& male)
{
  Assert(male.get()!=0);
  const double pPlayHawk = simFunc::logisticEquation(getCondition(),mPlayHawkAlpha,mPlayHawkBeta);
  //If pPlayHawk == 0.99 then rnd::uniform will be likely below this value
  return (rnd::uniform() < pPlayHawk ? true : false);
}
//---------------------------------------------------------------------------
double BirdHawkDove::getPlayHawkAlpha() const
{
  return mPlayHawkAlpha;
}
//---------------------------------------------------------------------------
double BirdHawkDove::getPlayHawkBeta() const
{
  return mPlayHawkBeta;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

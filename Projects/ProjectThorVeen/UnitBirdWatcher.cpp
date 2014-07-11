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
#include "UnitBirdWatcher.h"
//---------------------------------------------------------------------------
#include <string>
#include <algorithm>
#include "Assert.h"
#include "UnitBirdBase.h"
#include "UnitWeather.h"
#include "UnitHelperFunctions.h"
#include "UnitPedigreeCharter.h"
//---------------------------------------------------------------------------
//std::auto_ptr<BirdWatcher> BirdWatcher::mpInstance(new BirdWatcher);
boost::scoped_ptr<BirdWatcher> BirdWatcher::mpInstance(0);
//---------------------------------------------------------------------------
#ifndef NDEBUG
  int BirdWatcher::mConstructorCalled = 0;
#endif
//---------------------------------------------------------------------------
BirdWatcher::BirdWatcher()
{
  mWeather = Weather::instance();

  #ifndef NDEBUG
    ++mConstructorCalled;
    Assert(mConstructorCalled==1);
  #endif

}
//---------------------------------------------------------------------------
BirdWatcher::~BirdWatcher()
{

}
//---------------------------------------------------------------------------
BirdWatcher* BirdWatcher::instance()
{
  if (mpInstance.get()==0) mpInstance.reset(new BirdWatcher);
  Assert(mpInstance.get()!=0);
  return mpInstance.get();
}
//---------------------------------------------------------------------------
void BirdWatcher::reset()
{
  #ifndef NDEBUG
    mIndices.resize(0);
  #endif
    mBirds.resize(0);
  //mPlayHawkAlpha.resize(0);
  //mPlayHawkBeta.resize(0);
  Assert(mIndices.empty()==true);
  //Assert(mPlayHawkAlpha.empty()==true);
  //Assert(mPlayHawkBeta.empty()==true);
}
//---------------------------------------------------------------------------
void BirdWatcher::setPedigreeCharter(const EnumPedigreeCharter& pedigreeCharter)
{
  switch(pedigreeCharter)
  {
    case  pedigreeCharterNone:
      mPedigreeCharter.reset(new PedigreeCharterNone);
      break;
    case  pedigreeCharterAll:
      mPedigreeCharter.reset(new PedigreeCharterAll);
      break;
    default:
      Assert(!"Shouldn't get here");
      std::exit(1);
  }
}
//---------------------------------------------------------------------------
//Called from BirdBase's contructor
void BirdWatcher::reportNewBird(BirdBase* bird)
{
  #ifndef NDEBUG
  const int index = bird->getBirdIndex();
  mIndices.push_back(index);
  #endif
}
//---------------------------------------------------------------------------
//Called from Couple::CreateOffspring and BirdFactoryDerived::CreateBird
void BirdWatcher::reportNewBird(const boost::shared_ptr<BirdBase>& bird)
{
  const int timeUnit = mWeather->getTimeUnit();

  #ifndef __HACK_RICHEL_6565152765376524876988989898702347234623
    Weather * test = Weather::instance();
    Assert(test==mWeather);
    //if (timeUnit!=0) ShowMessage("YES!!!");
  #endif

  if(static_cast<int>(mBirds.size()) == timeUnit)
  {
    mBirds.push_back( std::vector<boost::shared_ptr<const BirdBase> >() );
  }

  Assert(timeUnit < static_cast<int>(mBirds.size()));

  mBirds[timeUnit].push_back(bird);
  Assert(bird.use_count()==2); //One copy is stored in BirdWatcher
}
//---------------------------------------------------------------------------
void BirdWatcher::reportDeadBird(const int& index)
{
  #ifndef NDEBUG
  Assert( std::find(mIndices.begin(),mIndices.end(),index) != mIndices.end() );
  *std::find(mIndices.begin(),mIndices.end(),index) = mIndices.back();
  mIndices.pop_back();
  #endif
}
//---------------------------------------------------------------------------
std::vector<double> BirdWatcher::getMeansPlayHawkAlpha() const
{
  std::vector<double> means;
  const int nMeans = mBirds.size();
  means.reserve(nMeans);
  for (int i=0; i<nMeans; ++i)
  {
    double sum = 0.0;
    const int nValues = mBirds[i].size();
    for (int j=0; j<nValues; ++j)
    {
      Assert(mBirds[i][j].get()!=0);
      Assert(mBirds[i][j]->getClassType()==hawkDove);
      const BirdHawkDove * tempCopy = dynamic_cast<const BirdHawkDove*>(mBirds[i][j].get());
      sum+= tempCopy->getPlayHawkAlpha();
    }
    const double mean = sum/static_cast<double>(nValues);
    means.push_back(mean);
  }
  Assert(means.size()==mBirds.size());
  return means;
}
//---------------------------------------------------------------------------
std::vector<double> BirdWatcher::getMeansPlayHawkBeta() const
{
  std::vector<double> means;
  const int nMeans = mBirds.size();
  means.reserve(nMeans);
  for (int i=0; i<nMeans; ++i)
  {
    double sum = 0.0;
    const int nValues = mBirds[i].size();
    for (int j=0; j<nValues; ++j)
    {
      Assert(mBirds[i][j].get()!=0);
      Assert(mBirds[i][j]->getClassType()==hawkDove);
      const BirdHawkDove * tempCopy = dynamic_cast<const BirdHawkDove*>(mBirds[i][j].get());
      sum+= tempCopy->getPlayHawkBeta();
    }
    const double mean = sum/static_cast<double>(nValues);
    means.push_back(mean);
  }
  Assert(means.size()==mBirds.size());
  return means;
}
//---------------------------------------------------------------------------
std::vector<double> BirdWatcher::getMeansConditionHeritable() const
{
  std::vector<double> means;
  const int size = mBirds.size();
  means.reserve(size);

  for (int t=0; t<size; ++t)
  {
    double sum = 0.0;
    const int nValues = mBirds[t].size();
    for (int j=0; j<nValues; ++j)
    {
      Assert(mBirds[t][j].get()!=0);
      sum+=mBirds[t][j]->getConditionHeritable();
    }
    const double mean = sum/static_cast<double>(nValues);
    means.push_back(mean);
  }
  Assert(means.size()==mBirds.size());
  return means;

}
//---------------------------------------------------------------------------
std::vector<double> BirdWatcher::getMeansConditionEnvironmental() const
{
  std::vector<double> means;
  const int size = mBirds.size();
  means.reserve(size);

  for (int t=0; t<size; ++t)
  {
    double sum = 0.0;
    const int nValues = mBirds[t].size();
    for (int j=0; j<nValues; ++j)
    {
      Assert(mBirds[t][j].get()!=0);
      sum+=mBirds[t][j]->getConditionEnvironment();
    }
    const double mean = sum/static_cast<double>(nValues);
    means.push_back(mean);
  }
  Assert(means.size()==mBirds.size());
  return means;

}
//---------------------------------------------------------------------------
std::vector<double> BirdWatcher::getMeansConditionParental() const
{
  std::vector<double> means;
  const int size = mBirds.size();
  means.reserve(size);

  for (int t=0; t<size; ++t)
  {
    double sum = 0.0;
    const int nValues = mBirds[t].size();
    for (int j=0; j<nValues; ++j)
    {
      Assert(mBirds[t][j].get()!=0);
      sum+=mBirds[t][j]->getConditionParental();
    }
    const double mean = sum/static_cast<double>(nValues);
    means.push_back(mean);
  }
  Assert(means.size()==mBirds.size());
  return means;

}
//---------------------------------------------------------------------------
std::vector<std::string> BirdWatcher::getPedigree() const
{
  return mPedigreeCharter->getPedigree();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)


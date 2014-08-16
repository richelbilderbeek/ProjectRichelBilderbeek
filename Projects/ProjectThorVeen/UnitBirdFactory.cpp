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
#include "UnitBirdFactory.h"
//---------------------------------------------------------------------------
#include <string>
#include "UnitBird.h"
#include "UnitBirdHawkDoveParameters.h"
#include "UnitBirdWatcher.h"
#include "Assert.h"
//---------------------------------------------------------------------------
BirdWatcher * BirdFactoryBase::mBirdWatcher = 0;
//BirdWatcher * BirdFactoryBase::mBirdWatcher = BirdWatcher::instance();
//---------------------------------------------------------------------------
std::string BirdFactoryBase::getClassName() const
{
  return "BirdFactoryBase";
}
//---------------------------------------------------------------------------
void BirdFactoryBase::initBase(const boost::shared_ptr<BirdGeneralParameters>& params)
{
  Assert(params.get()!=0);
  mBirdGeneralParams = params;
}
//---------------------------------------------------------------------------
void BirdFactoryBase::InitBirdWatcher()
{
  mBirdWatcher = BirdWatcher::instance();
}
//---------------------------------------------------------------------------
std::string BirdFactoryHawkDove::getClassName() const
{
  return "BirdFactoryHawkDove";
}
//---------------------------------------------------------------------------
EnumBirdType BirdFactoryHawkDove::getClassType() const
{
  return hawkDove;
}
//---------------------------------------------------------------------------
BirdFactoryHawkDove::BirdFactoryHawkDove(
    const boost::shared_ptr<BirdGeneralParameters>& birdGeneralParams,
    const boost::shared_ptr<BirdHawkDoveParameters>& birdHawkDoveParams)
  : mBirdHawkDoveParams(birdHawkDoveParams)
{
  initBase(birdGeneralParams);

  Assert(mBirdHawkDoveParams.get()!=0);
  const double playHawkAlphaMutation = mBirdHawkDoveParams->mPlayHawkAlphaMutation;
  const double playHawkBetaMutation  = mBirdHawkDoveParams->mPlayHawkBetaMutation;
  const double pDieHawkHawkLoser     = mBirdHawkDoveParams->mPdieHawkHawkLoser;
  Assert(playHawkAlphaMutation > -1000.0 && playHawkAlphaMutation < 1000.0);
  Assert(playHawkBetaMutation  > -1000.0 && playHawkBetaMutation < 1000.0);
  BirdHawkDove::setMutationPlayHawkAlpha(this,playHawkAlphaMutation);
  BirdHawkDove::setMutationPlayHawkBeta( this,playHawkBetaMutation);
  BirdHawkDove::setPdieHawkHawkLoser( this,pDieHawkHawkLoser);

}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdBase> BirdFactoryHawkDove::createBird() const
{
  boost::shared_ptr<BirdBase> kid(
    new BirdHawkDove(this,mBirdGeneralParams,mBirdHawkDoveParams));

  Assert(mBirdWatcher);
  mBirdWatcher->reportNewBird(kid);

  return kid;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

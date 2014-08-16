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
#include "UnitFemaleChoice.h"
//---------------------------------------------------------------------------
#include "UnitBird.h"
#include "UnitSingleFemalePool.h"
#include "UnitSingleMalePool.h"
#include "UnitCouplePool.h"
#include "UnitDeadPool.h"
#include "UnitMatingSystem.h"
#include "UnitExceptions.h"
#include "UnitRandom.h"
#include "Assert.h"
//---------------------------------------------------------------------------
void FemaleChoiceBase::setMatingSystem(const EnumMatingSystem& matingSystem)
{
  switch(matingSystem)
  {
    case monogamy:
      mMatingSystem.reset(new MatingSystemMonogamy);
      break;
    case polygyny:
      mMatingSystem.reset(new MatingSystemPolygyny);
      break;
    default:
      Assert(!"Shouldn't get here: Unimplemented mating system");
      std::exit(1);
  }
}
//---------------------------------------------------------------------------
FemaleChoiceWinnerFight2males::FemaleChoiceWinnerFight2males(const EnumMatingSystem& matingSystem)
{
  setMatingSystem(matingSystem);
}
//---------------------------------------------------------------------------
void FemaleChoiceWinnerFight2males::choose(
  std::auto_ptr<SingleFemalePool>& singleFemalePool,
  std::auto_ptr<SingleMalePool>& singleMalePool,
  std::auto_ptr<CouplePool>& couplePool,
  std::auto_ptr<DeadPool>& deadPool) const
{
  Assert(singleFemalePool.get()!=0);
  Assert(singleMalePool.get()!=0);
  Assert(couplePool.get()!=0);
  Assert(deadPool.get()!=0);
  //Try to get one female and two males
  if(singleFemalePool->isEmpty()==true)
  {
    //All males die in solitude
    singleMalePool->doEmpty(deadPool);
    throw NoFemaleException();
    //return;
  }
  boost::shared_ptr<BirdBase> female = singleFemalePool->getFemale();
  if(singleMalePool->isEmpty()==true)
  {
    //Single female dies in solitude
    singleFemalePool->doEmpty(deadPool);
    Assert(singleFemalePool->isEmpty()==true);
    throw NoMaleException();
    //return;
  }
  boost::shared_ptr<BirdBase> male1 = singleMalePool->getMale();
  if(singleMalePool->isEmpty()==true)
  {
    Assert(female.get()!=0);
    Assert(male1.get()!=0);
    //Put last male and last female in couplePool
    couplePool->addCouple(female,male1);
    //Kill all other solitary females
    singleFemalePool->doEmpty(deadPool);
    Assert(female.get()==0);
    Assert(male1.get()==0);
    Assert(singleFemalePool->isEmpty()==true);
    Assert(singleMalePool->isEmpty()==true);
    throw NoMaleException();
    //return;
  }
  boost::shared_ptr<BirdBase> male2 = singleMalePool->getMale();
  //Yes! We've one female and two males. Let them fight

  Assert(female->getClassType() == hawkDove);
  Assert(male1->getClassType()  == hawkDove);
  Assert(male2->getClassType()  == hawkDove);

  if( male1->willFight(male2)==true)
  {
    if (male2->willFight(male1)==true)
    {
      //male1 hawk - male2 hawk
      if (male1->getCondition() > male2->getCondition())
      {

        //male1 wins and gets female, male2 might die
        //The mating system determines whether male1 is copied back to the SingleMalePool again
        mMatingSystem->makeCouple(female,male1,singleMalePool,couplePool);
        //Does male2 die?
        if (male2->willDieLoserFight()==true)
        { //Yes, male2 dies
          deadPool->addMale(male2);
        }
        else
        { //No, male2 remains single
          singleMalePool->addMale(male2);
        }
      }
      else
      {
        //male2 wins and gets female, male1 dies
        //The mating system determines whether male2 is copied back to the SingleMalePool again
        mMatingSystem->makeCouple(female,male2,singleMalePool,couplePool);
        //Does male1 die?
        if (male1->willDieLoserFight()==true)
        { //Yes, male1 dies
          deadPool->addMale(male1);
        }
        else
        { //No, male1 remains single
          singleMalePool->addMale(male1);
        }
      }
    }
    else
    {
      //male1 hawk - male2 dove
      //male1 gets female, male2 remains single
      //The mating system determines whether male1 is copied back to the SingleMalePool again
      mMatingSystem->makeCouple(female,male1,singleMalePool,couplePool);
      singleMalePool->addMale(male2);
    }
  }
  else
  {
    if (male2->willFight(male1)==true)
    {
      //male1 dove - male2 hawk
      //male2 get female, male1 remains single
      //The mating system determines whether male2 is copied back to the SingleMalePool again
      mMatingSystem->makeCouple(female,male2,singleMalePool,couplePool);
      singleMalePool->addMale(male1);
    }
    else
    {
      //male1 dove - male2 dove
      if (rnd::uniform()<0.5)
      {
        //male1 gets female (by chance) and male2 remains single
        //The mating system determines whether male1 is copied back to the SingleMalePool again
        mMatingSystem->makeCouple(female,male1,singleMalePool,couplePool);
        singleMalePool->addMale(male2);
      }
      else
      {
        //male2 gets female (by chance) and male1 remains single
        //The mating system determines whether male1 is copied back to the SingleMalePool again
        mMatingSystem->makeCouple(female,male2,singleMalePool,couplePool);
        singleMalePool->addMale(male1);
      }
    }
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)


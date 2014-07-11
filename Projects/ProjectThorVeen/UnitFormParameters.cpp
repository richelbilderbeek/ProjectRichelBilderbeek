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
#include <vcl.h>
#pragma hdrstop

#include "UnitFormParameters.h"
//---------------------------------------------------------------------------
#include "UnitSimulationParameters.h"
#include "UnitBirdGeneralParameters.h"
#include "UnitBirdHawkDoveParameters.h"
#include "UnitBreedingParameters.h"
#include "UnitInitialBirdNumbers.h"
#include "UnitDisplayOptions.h"
#include "Assert.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParameters *FormParameters;
//---------------------------------------------------------------------------
__fastcall TFormParameters::TFormParameters(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
boost::shared_ptr<SimulationParameters> TFormParameters::getSimulationParameters() const
{
  boost::shared_ptr<SimulationParameters> params(new SimulationParameters);

  params->mBirdGeneralParameters = getBirdGeneralParameters();
  params->mInitialBirdNumbers    = getInitialBirdNumbers();
  params->mBreedingParameters    = getBreedingParameters();

  { //Get number of generations
    const int nGenerationsIndex = 1;
    Assert( ValueListGeneral->Cells[0][nGenerationsIndex] == "Number of generations");
    params->mNgenerations = ValueListGeneral->Cells[1][nGenerationsIndex].ToInt();
  }


  { //Get type of simulation
    switch(RadioGroupSimulationType->ItemIndex)
    {
      case 0:
        Assert(RadioGroupSimulationType->Items->operator [](0) == "Cartoon model");
        params->mEnumSimulationType = cartoonModel;
        break;
      default:
        Assert(!"Should not get here");
    }
  }
  { //Get Bird Type and their parameters
    switch(PageControlBirdType->ActivePageIndex)
    {
      case 0:
        Assert(PageControlBirdType->ActivePage->Caption=="Hawk-dove");
        params->mBirdHawkDoveParameters = getHawkDoveParameters();
        break;
      default:
        Assert(!"Unimplemented BirdType");
        std::exit(1);
    }
  }

  { //Get female choice
    switch(RadioGroupFemaleChoice->ItemIndex)
    {
      case 0:
        Assert(RadioGroupFemaleChoice->Items->operator [](0) == "Selects on trait only");
        params->mEnumFemaleChoice = traitOnly;
        break;
      case 1:
        Assert(RadioGroupFemaleChoice->Items->operator [](1) == "Selects on condition only");
        params->mEnumFemaleChoice = conditionOnly;
        break;
      case 2:
        Assert(RadioGroupFemaleChoice->Items->operator [](2) == "Selects on territory only");
        params->mEnumFemaleChoice = territoryOnly;
        break;
      case 3:
        Assert(RadioGroupFemaleChoice->Items->operator [](3) == "Selects winner of a fight of 2 males");
        params->mEnumFemaleChoice = winnerFight2males;
        break;
      default:
        Assert(!"Shouldn't get here: unimplemented female choice");
        std::exit(1);
    }
  }

  { //Mating system
    switch(RadioGroupMatingSystem->ItemIndex)
    {
      case 0:
        Assert(RadioGroupMatingSystem->Items->operator[](0)=="Monogamy");
        params->mEnumMatingSystem = monogamy;
        break;
      case 1:
        Assert(RadioGroupMatingSystem->Items->operator[](1)=="Polygyny");
        params->mEnumMatingSystem = polygyny;
        break;
      default:
        Assert(!"Shouldn't get here: unimplemented mating system");
        std::exit(1);
    }
  }

  //Display options
  switch(RadioGroupPedigree->ItemIndex)
  {
    case 0:
      Assert(RadioGroupPedigree->Items->operator [](0) =="None");
      params->mDisplayOptions->mPedigreeCharter = pedigreeCharterNone;
      break;
    case 1:
      Assert(RadioGroupPedigree->Items->operator [](1) =="All");
      params->mDisplayOptions->mPedigreeCharter = pedigreeCharterAll;
      break;
  }

  return params;
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdHawkDoveParameters> TFormParameters::getHawkDoveParameters() const
{
  boost::shared_ptr<BirdHawkDoveParameters> params(new BirdHawkDoveParameters);
  {
    const int index = 1;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "Initial 'play hawk alpha' mean");
    params->mPlayHawkAlphaMean = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }
  {
    const int index = 2;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "Initial 'play hawk alpha' stdDev");
    params->mPlayHawkAlphaStdDev = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }
  {
    const int index = 3;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "Initial 'play hawk beta' mean");
    params->mPlayHawkBetaMean = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }
  {
    const int index = 4;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "Initial 'play hawk beta' stdDev");
    params->mPlayHawkBetaStdDev = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }
  {
    const int index = 5;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "Mutation rate 'play hawk alpha'");
    params->mPlayHawkAlphaMutation = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }
  {
    const int index = 6;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "Mutation rate 'play hawk beta'");
    params->mPlayHawkBetaMutation = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }
  {
    const int index = 7;
    Assert(ValueListEditorBirdHawkDove->Cells[0][index] == "pDie loser in hawk-hawk fight");
    params->mPdieHawkHawkLoser = ValueListEditorBirdHawkDove->Cells[1][index].ToDouble();
  }


  return params;
}
//---------------------------------------------------------------------------
boost::shared_ptr<BirdGeneralParameters> TFormParameters::getBirdGeneralParameters() const
{
  boost::shared_ptr<BirdGeneralParameters> params(new BirdGeneralParameters);
  { //Initial constitution mean
    const int index = 1;
    Assert( ValueListBirdGeneral->Cells[0][index] == "Initial 'condition heritable' mean");
    params->mInitialConditionHeritableMean = ValueListBirdGeneral->Cells[1][index].ToDouble();
  }
  { //Initial conditionHeritable stdDev
    const int index = 2;
    Assert( ValueListBirdGeneral->Cells[0][index] == "Initial 'condition heritable' stdDev");
    params->mInitialConditionHeritableStdDev = ValueListBirdGeneral->Cells[1][index].ToDouble();
  }
  { //Constitution mutation
    const int index = 3;
    Assert( ValueListBirdGeneral->Cells[0][index] == "Mutation rate 'condition heritable'");
    params->mConditionHeritableMutation = ValueListBirdGeneral->Cells[1][index].ToDouble();
  }
  return params;
}
//---------------------------------------------------------------------------
boost::shared_ptr<InitialBirdNumbers> TFormParameters::getInitialBirdNumbers() const
{
  boost::shared_ptr<InitialBirdNumbers> params(new InitialBirdNumbers);

  { //Get initial single females
    const int index = 1;
    Assert( ValueListBirdNumbers->Cells[0][index] == "Initial single females");
    params->mNinitialSingleFemales = ValueListBirdNumbers->Cells[1][index].ToInt();
  }
  { //Get initial single males
    const int index = 2;
    Assert( ValueListBirdNumbers->Cells[0][index] == "Initial single males");
    params->mNinitialSingleMales = ValueListBirdNumbers->Cells[1][index].ToInt();
  }
  { //Get initial couples
    const int index = 3;
    Assert( ValueListBirdNumbers->Cells[0][index] == "Initial couples");
    params->mNinitialCouples = ValueListBirdNumbers->Cells[1][index].ToInt();
  }
  { //Get initial migrants
    const int index = 4;
    Assert( ValueListBirdNumbers->Cells[0][index] == "Initial migrants");
    params->mNinitialMigrants = ValueListBirdNumbers->Cells[1][index].ToInt();
  }
  { //Get initial death
    const int index = 5;
    Assert( ValueListBirdNumbers->Cells[0][index] == "Initial dead");
    params->mNinitialDead = ValueListBirdNumbers->Cells[1][index].ToInt();
  }
  return params;
}
//---------------------------------------------------------------------------
boost::shared_ptr<BreedingParameters> TFormParameters::getBreedingParameters() const
{
  boost::shared_ptr<BreedingParameters> params(new BreedingParameters);

  { //Get number of female offspring
    const int nFemalesIndex = 1;
    Assert( ValueListBreeding->Cells[0][nFemalesIndex] == "Female offspring");
    params->mNfemaleOffspring = ValueListBreeding->Cells[1][nFemalesIndex].ToInt();
  }
  { //Get number of male offspring
    const int nMalesIndex = 2;
    Assert( ValueListBreeding->Cells[0][nMalesIndex] == "Male offspring");
    params->mNmaleOffspring = ValueListBreeding->Cells[1][nMalesIndex].ToInt();
  }

  return params;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



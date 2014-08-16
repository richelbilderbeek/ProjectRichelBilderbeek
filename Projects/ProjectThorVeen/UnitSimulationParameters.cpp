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
#include "UnitSimulationParameters.h"
//---------------------------------------------------------------------------
#include <string>
#include "UnitBirdGeneralParameters.h"
#include "UnitBirdHawkDoveParameters.h"
#include "UnitInitialBirdNumbers.h"
#include "UnitBreedingParameters.h"
#include "UnitHelperFunctions.h"
#include "UnitDisplayOptions.h"
#include "Assert.h"
//---------------------------------------------------------------------------
SimulationParameters::SimulationParameters() :
  mNgenerations(1000),
  mEnumSimulationType(cartoonModel),
  mEnumFemaleChoice(winnerFight2males),
  //numBreeding(singleGeneration),
  mEnumMigration(allSurvive),
  mEnumBirdType(hawkDove),
  //mBirdHawkDoveParameters(new BirdHawkDoveParameters),
  mInitialBirdNumbers(new InitialBirdNumbers),
  mDisplayOptions(new DisplayOptions)
  //mBreedingParameters(new RearingParameters)
{
  Assert(mBirdHawkDoveParameters.get()==0);
}
//---------------------------------------------------------------------------
std::vector<std::string> SimulationParameters::getText() const
{
  std::vector<std::string> text;
  text.push_back("Ngenerations: " + helper::itoa(mNgenerations) );
  { //SimulationType
    EnumSimulationTypeConverter * conv = EnumSimulationTypeConverter::instance();
    text.push_back("SimulationType: " + conv->toString(mEnumSimulationType));
  }
  { //FemaleChoice
    EnumFemaleChoiceConverter * conv = EnumFemaleChoiceConverter::instance();
    text.push_back("FemaleChoice: " + conv->toString(mEnumFemaleChoice));
  }
  { //Migration
    EnumMigrationConverter * conv = EnumMigrationConverter::instance();
    text.push_back("Migration: " + conv->toString(mEnumMigration));
  }
  { //BirdType
    EnumBirdTypeConverter * conv = EnumBirdTypeConverter::instance();
    text.push_back("BirdType: " + conv->toString(mEnumBirdType));
  }

  { //BirdHawkDove parameters
    std::vector<std::string> temp = mBirdHawkDoveParameters->getText();
    helper::add(text,temp);
  }
  { //DisplayOptions parameters
    std::vector<std::string> temp = mDisplayOptions->getText();
    helper::add(text,temp);
  }


  return text;
}
//---------------------------------------------------------------------------


#pragma package(smart_init)

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
#ifndef UnitSimulationParametersH
#define UnitSimulationParametersH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "UnitEnumSimulationType.h"
#include "UnitEnumFemaleChoice.h"
#include "UnitEnumMigration.h"
#include "UnitEnumBirdType.h"
#include "UnitEnumMatingSystem.h"
//---------------------------------------------------------------------------
class BirdGeneralParameters;
class BirdHawkDoveParameters;
class BreedingParameters;
class InitialBirdNumbers;
class DisplayOptions;
//---------------------------------------------------------------------------
class SimulationParameters : public boost::noncopyable
{
  public:
  SimulationParameters();
  //General parameters
  int mNgenerations;
  //General enums
  EnumSimulationType mEnumSimulationType;
  EnumFemaleChoice mEnumFemaleChoice;
  EnumMigration mEnumMigration;
  EnumBirdType mEnumBirdType;
  EnumMatingSystem mEnumMatingSystem;
  //Specials
  boost::shared_ptr<BirdGeneralParameters> mBirdGeneralParameters;
  boost::shared_ptr<BirdHawkDoveParameters> mBirdHawkDoveParameters;
  boost::shared_ptr<InitialBirdNumbers> mInitialBirdNumbers;
  boost::shared_ptr<BreedingParameters> mBreedingParameters;
  boost::shared_ptr<DisplayOptions> mDisplayOptions;
  //Methods
  std::vector<std::string> getText() const;
  void saveToFile(const std::string& fileName) const;
  void loadFromFile(const std::string& fileName);
};

#endif

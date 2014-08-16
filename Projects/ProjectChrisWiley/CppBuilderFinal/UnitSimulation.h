//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
  Copyright (C) 2009  Richel Bilderbeek

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
#ifndef UnitSimulationH
#define UnitSimulationH
//---------------------------------------------------------------------------

#include <vector>
#include <memory>
#include <math>
#include <string>
#include <algorithm>

#include "UnitEnums.h"
#include "UnitParameters.h"
#include "UnitTallies.h"
#include "UnitHelperFunctions.h"
#include "UnitTimeSeries.h"
#include "UnitBird.h"

//Forward declarations of States
class StateMatingSystemBase;
class StateFemaleSamplingBase;
class StateDensityDependentSelectionBase;

class Simulation
{
  public:
  std::string mError;
  Simulation(const Parameters&);
  void execute();
  TimeSeries getTimeSeries() const { return mTimeSeries; }
  void setMatingSystem(const enumMatingSystem&, const enumDensityDependentSelection&);

  void setFemaleSampling(const enumFemaleSampling&);
  void setDensityDependentSelection(const enumDensityDependentSelection&);

  //void showPopulation(TStringGrid * stringGrid) const;
  static inline double chanceToSurviveSpecies(const double& descent, const double& alpha, const double& beta);
  static inline double chanceToSurviveTrait(const double& trait, const double& costTrait);
  static inline double chanceToSurvivePreference(const double& preference, const double& costPreference);

  //Debugging
  private:
  const Parameters mParameters;

  void speciesSelection();
  void viabilitySelection();
  bool willDieSpecies(const Bird& bird);
  bool willDiePreference(const Female& female);
  bool willDieTrait(const Male& male);

  void mating();
  std::auto_ptr<StateMatingSystemBase> mMatingSystem;
  std::auto_ptr<StateFemaleSamplingBase> mFemaleSampling;
  std::auto_ptr<StateDensityDependentSelectionBase> mDensityDependentSelection;
  std::auto_ptr<MateTally> mMateTally;
  std::vector<Bird> mMales;
  std::vector<Bird> mFemales;
  std::vector<Bird> mOffspring;
  TimeSeries mTimeSeries;
};


#include "UnitFemaleSampling.h"
#include "UnitMatingSystem.h"
#include "UnitDensityDependentSelection.h"

//void calculateTimePoint(const unsigned int& generation, TimeSeries& timeSeries, std::auto_ptr<MateTally>& mateTally);


#endif

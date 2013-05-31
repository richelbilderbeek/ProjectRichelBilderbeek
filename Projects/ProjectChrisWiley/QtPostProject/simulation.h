//---------------------------------------------------------------------------
/*
  The Chris Wiley Project, simulation on mixed-pair mating
  Copyright (C) 2009  Richl Bilderbeek

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
#ifndef PROJECTCHRISWILEY_SIMULATION_H
#define PROJECTCHRISWILEY_SIMULATION_H
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include <cmath>
#include <string>
#include <algorithm>
#include "enums.h"
#include "parameters.h"
#include "matetally.h"
#include "speciestally.h"
#include "helperfunctions.h"
#include "timeseries.h"
#include "bird.h"
//---------------------------------------------------------------------------
//Forward declarations of States
class StateMatingSystemBase;
class StateFemaleSamplingBase;
class StateDensityDependentSelectionBase;

class Simulation
{
  public:
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

  public:
  std::string mError;
};

#include "femalesampling.h"
#include "matingsystem.h"
#include "densitydependentselection.h"

#endif // PROJECTCHRISWILEY_SIMULATION_H

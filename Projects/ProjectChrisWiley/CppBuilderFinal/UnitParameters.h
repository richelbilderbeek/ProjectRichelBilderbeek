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
#ifndef UnitParametersH
#define UnitParametersH
//---------------------------------------------------------------------------
#include "UnitEnums.h"
#include "UnitHelperFunctions.h"

class Parameters
{
  public:
  unsigned int nGenerations;  //Number of generations
  unsigned int nFemales;      //Number of females
  unsigned int nMales;        //Number of males
  double fractionMaleA;       //Fraction of males being of species A
  double fractionFemaleA;     //Fraction of males being of species B
  unsigned int bestOfHowMuch; //Value of N in Best-of-N
  double assessingErrorA ;    //The probability a female A assess a male wrong
  double assessingErrorB;     //The probability a female B assess a male wrong
  double meanTraitA;
  double meanTraitB;
  double meanPreferenceA;
  double meanPreferenceB;
  double stdDevTraitA;
  double stdDevTraitB;
  double stdDevPreferenceA;
  double stdDevPreferenceB;
  double sigmaSquared;
  unsigned int nSimulations; //Number of simulations
  unsigned int nOffspring;   //Number of offspring produced per couple
  //unsigned int simIndex; //The simulation's index, or: the simIndex-th simulation that is being run
  double surviveSpeciesAlpha;
  double surviveSpeciesBeta;
  double costTrait;
  double costPreference;
  double mutationRate;
  enumMatingSystem matingSystem;     //Monogamy/polygyny
  enumFemaleSampling femaleSampling; //The way a female samples the male population
  enumDensityDependentSelection densityDependentSelection;
  void reset();
  unsigned int getNmalesAwanted() const;
  unsigned int getNmalesBwanted() const;
  unsigned int getNfemalesAwanted() const;
  unsigned int getNfemalesBwanted() const;
  void readFromFile(const std::string& fileName);
  void writeToFile(const std::string& fileName);
};


#endif

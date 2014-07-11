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
#pragma hdrstop

#include "UnitBird.h"

//---------------------------------------------------------------------------
Bird::Bird(const Bird& mother, const Bird& father, const double& mutation)
{
  descent = (mother.descent + father.descent) / 2.0;
  assert(descent>=-1.0 && descent<=1.0);
  const double chanceBeingPied = 1.0-((descent+1.0)/2.0);
  assert(chanceBeingPied>=0.0 && chanceBeingPied<=1.0);
  species = (rnd::uniform() > chanceBeingPied ? collaredFlycatcher : piedFlycatcher);
  //Make a bit
  unsigned int number = std::rand()%64;
  index = (number%2==0 ? mother.index : father.index);
  number>>=1;
  trait = (number%2==0 ? mother.trait : father.trait);
  trait+=rnd::normal(0.0,mutation);
  number>>=1;
  preference = (number%2==0 ? mother.preference : father.preference);
  preference+=rnd::normal(0.0,mutation);
  number>>=1;
  assessingError = (number%2==0 ? mother.assessingError : father.assessingError);

}
//---------------------------------------------------------------------------
std::vector<Male> Bird::createMales(const Parameters& parameters)
{
  //Create males
  assert(parameters.fractionMaleA>=0.0 && parameters.fractionMaleA<=1.0);
  //Create an empty vector of males
  std::vector<Male> males; //(parameters.nMales);
  //Calculate the number of males of speciesA
  const unsigned int nSpeciesA =
    0.5 + (static_cast<double>(parameters.nMales) * parameters.fractionMaleA)
    * (parameters.densityDependentSelection == beforeMating ? 2.0 : 1.0);
  const unsigned int nSpeciesB =
    0.5 + (static_cast<double>(parameters.nMales) * (1.0-parameters.fractionMaleA))
    * (parameters.densityDependentSelection == beforeMating ? 2.0 : 1.0);
  //Dot("Of " + IntToStr(nMales) + " males, there are " + IntToStr(nSpeciesA) + " of speciesA");
  //Fill the vector
  for (unsigned int i=0; i<nSpeciesA; ++i)
  {
    Male maleA;
    maleA.index = i;
    maleA.species = piedFlycatcher;
    maleA.descent = -1.0;
    maleA.trait = rnd::normal(parameters.meanTraitA, parameters.stdDevTraitA);
    maleA.preference = rnd::normal(parameters.meanPreferenceA, parameters.stdDevPreferenceA);
    maleA.assessingError = parameters.assessingErrorA;
    males.push_back(maleA);
  }
  for (unsigned int i=0 ; i<nSpeciesB; ++i)
  {
    Male maleB;
    maleB.index = i;
    maleB.species = collaredFlycatcher;
    maleB.descent = 1.0;
    maleB.trait = rnd::normal(parameters.meanTraitB, parameters.stdDevTraitB);
    maleB.preference = rnd::normal(parameters.meanPreferenceB, parameters.stdDevPreferenceB);
    maleB.assessingError = parameters.assessingErrorB;
    males.push_back(maleB);
  }
  return males;
}
//---------------------------------------------------------------------------
std::vector<Female> Bird::createFemales(const Parameters& parameters)
//Create females
{
  assert(parameters.fractionFemaleA>=0.0 && parameters.fractionFemaleA<=1.0);
  //Create an empty vector of females
  std::vector<Female> females;
  //Calculate the number of females of speciesA
  const unsigned int nSpeciesA
    = 0.5 + (static_cast<double>(parameters.nFemales) * parameters.fractionFemaleA)
    * (parameters.densityDependentSelection == beforeMating ? 2.0 : 1.0);

  const unsigned int nSpeciesB
    = 0.5 + (static_cast<double>(parameters.nFemales) * (1.0-parameters.fractionFemaleA))
    * (parameters.densityDependentSelection == beforeMating ? 2.0 : 1.0);

  //Fill the vector
  for (unsigned int i=0; i<nSpeciesA; ++i)
  {
    Female femaleA;
    femaleA.index = i;
    femaleA.species = piedFlycatcher;
    femaleA.descent = -1.0;
    femaleA.preference = rnd::normal(parameters.meanPreferenceA, parameters.stdDevPreferenceA);
    femaleA.assessingError = parameters.assessingErrorA;
    femaleA.trait = rnd::normal(parameters.meanTraitA, parameters.stdDevTraitA);
    females.push_back(femaleA);
  }
  for (unsigned int i=0 ; i<nSpeciesB; ++i)
  {
    Female femaleB;
    femaleB.index = i;
    femaleB.species = collaredFlycatcher;
    femaleB.descent = 1.0;
    femaleB.preference = rnd::normal(parameters.meanPreferenceB, parameters.stdDevPreferenceB);
    femaleB.assessingError = parameters.assessingErrorB;
    femaleB.trait = rnd::normal(parameters.meanTraitB, parameters.stdDevTraitB);
    females.push_back(femaleB);
  }
  return females;
}
//---------------------------------------------------------------------------
std::vector<Male> Bird::createTestMales(
  const Parameters& parameters,
  const double& species1, const double& trait1,
  const double& species2, const double& trait2,
  const double& species3, const double& trait3,
  const double& species4, const double& trait4
  )
{
  //Create an empty vector of males
  std::vector<Male> males;
  //Calculate the number of males of speciesA
  //Dot("Of " + IntToStr(nMales) + " males, there are " + IntToStr(nSpeciesA) + " of speciesA");
  //Fill the vector
  Male male1, male2, male3, male4;
  male1.descent = species1; male1.trait = trait1; male1.species = (rnd::uniform() > 1.0-((male1.descent+1.0)/2.0) ? collaredFlycatcher : piedFlycatcher);
  male2.descent = species2; male2.trait = trait2; male2.species = (rnd::uniform() > 1.0-((male2.descent+1.0)/2.0) ? collaredFlycatcher : piedFlycatcher);
  male3.descent = species3; male3.trait = trait3; male3.species = (rnd::uniform() > 1.0-((male3.descent+1.0)/2.0) ? collaredFlycatcher : piedFlycatcher);
  male4.descent = species4; male4.trait = trait4; male4.species = (rnd::uniform() > 1.0-((male4.descent+1.0)/2.0) ? collaredFlycatcher : piedFlycatcher);
  males.push_back(male1);
  males.push_back(male2);
  males.push_back(male3);
  males.push_back(male4);
  return males;
}
//---------------------------------------------------------------------------
std::vector<Female> Bird::createTestFemales(
    const Parameters& parameters,
    const double& species, const double& preference)
//Create females
{
  //Create an empty vector of females
  std::vector<Female> females;
  //Fill the vector with one female
  Female female;
  female.descent = species;
  female.species = (rnd::uniform() > 1.0-((female.descent+1.0)/2.0) ? collaredFlycatcher : piedFlycatcher);
  female.preference = preference;
  female.assessingError = parameters.assessingErrorA;
  females.push_back(female);
  return females;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

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
#include "densitydependentselection.h"
#include "speciestally.h"
//---------------------------------------------------------------------------
//bool StateDensityDependentSelectionAfterMating::canDoSelection(
//  std::vector<Female>& /*females*/,
//  std::vector<Male>& /*males*/,
//  const Parameters& /*parameters*/,
//  std::string& /*errorMessage*/
//  //const SpeciesTally& speciesTally
//  ) const
//{
//  return true;
//}
//---------------------------------------------------------------------------
//void StateDensityDependentSelectionAfterMating::doSelection(
//  std::vector<Female>& /*females*/,
//  std::vector<Male>& /*males*/,
//  const Parameters& /*parameters*/
//  //const SpeciesTally& speciesTally
//  ) const
//{
//  //Nothing, density dependent selection is found in MatingSystemFixedNumberOffspring
//}
//---------------------------------------------------------------------------
//This type of selection occurs before mating
//Idea is, that the population structure is constant before mating.
//This means that the number of malesA, malesB, femalesA and femalesB
//is constant. This is reached by removing superfluous individuals.
//If however, too few individuals are present, selection cannot take
//place and the population is called extinct.
bool StateDensityDependentSelectionBeforeMating::canDoSelection(
  std::vector<Female>& females,
  std::vector<Male>& males,
  const Parameters& parameters,
  std::string& errorMessage
  //const SpeciesTally& speciesTally
  ) const
{
  //assert(speciesTally.isNull()==false);
  SpeciesTally speciesTally;
  speciesTally.tallySpecies(females,males);

  if ( speciesTally.getNfemalesA() < parameters.getNfemalesAwanted())
  {
    errorMessage = "Too few femalesA for selection."
      " Needed: " + itoa(parameters.getNfemalesAwanted())
      + " ,got: " + itoa(speciesTally.getNfemalesA());
    Dot(errorMessage);
    return false;
  }
  if ( speciesTally.getNfemalesB() < parameters.getNfemalesBwanted())
  {
    errorMessage = "Too few femalesB for selection."
      " Needed: " + itoa(parameters.getNfemalesBwanted())
      + " ,got: " + itoa(speciesTally.getNfemalesB());
    Dot(errorMessage);
    return false;
  }
  if ( speciesTally.getNmalesA() < parameters.getNmalesAwanted())
  {
    errorMessage = "Too few malesA for selection."
      " Needed: " + itoa(parameters.getNmalesAwanted())
      + " ,got: " + itoa(speciesTally.getNmalesA());
    Dot(errorMessage);
    return false;
  }
  if ( speciesTally.getNmalesB() < parameters.getNmalesBwanted())
  {
    errorMessage =  "Too few malesB for selection."
      " Needed: " + itoa(parameters.getNmalesBwanted())
      + " ,got: " + itoa(speciesTally.getNmalesB());
    Dot(errorMessage);
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
void StateDensityDependentSelectionBeforeMating::doSelection(
  std::vector<Female>& females,
  std::vector<Male>& males,
  const Parameters& parameters
  //const SpeciesTally& speciesTally
  ) const
{
  unsigned int nMalesAwanted   = parameters.getNmalesAwanted();
  unsigned int nMalesBwanted   = parameters.getNmalesBwanted();
  assert(nMalesAwanted + nMalesBwanted == parameters.nMales);
  unsigned int nFemalesAwanted = parameters.getNfemalesAwanted();
  unsigned int nFemalesBwanted = parameters.getNfemalesBwanted();
  assert(nFemalesAwanted + nFemalesBwanted == parameters.nFemales);

  for (unsigned int i=0; i<males.size(); ) //No increment
  {
    if (males[i].species == piedFlycatcher) //Male is of type A
    {
      if (nMalesAwanted==0)
      {
        //Erase the male
         males.erase(males.begin() + i);
      }
      else
      {
        //Keep the male
        --nMalesAwanted;
        ++i;
      }
    }
    else //Male is of type B
    {
      if (nMalesBwanted==0)
      {
        //Erase the male
         males.erase(males.begin() + i);
      }
      else
      {
        //Keep the male
        --nMalesBwanted;
        ++i;
      }
    }
  }

  for (unsigned int i=0; i<females.size(); ) //No increment
  {
    if (females[i].species == piedFlycatcher) //Female is of type A
    {
      if (nFemalesAwanted==0)
      {
        //Erase the female
         females.erase(females.begin() + i);
      }
      else
      {
        //Keep the female
        --nFemalesAwanted;
        ++i;
      }
    }
    else //Female is of type B
    {
      if (nFemalesBwanted==0)
      {
        //Erase the female
         females.erase(females.begin() + i);
      }
      else
      {
        //Keep the female
        --nFemalesBwanted;
        ++i;
      }
    }
  }
  #ifdef __HACK_089236408766433745
    const unsigned int fs = females.size();
    const unsigned int ms = males.size();
    const unsigned int fw = parameters.nFemales;
    const unsigned int mw = parameters.nMales;
  #endif
  std::random_shuffle(females.begin(), females.end());
  std::random_shuffle(males.begin(), males.end());
  assert(females.size()==parameters.nFemales);
  assert(males.size()==parameters.nMales);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


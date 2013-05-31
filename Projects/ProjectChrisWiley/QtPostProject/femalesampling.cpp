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
#include <algorithm>
#include "femalesampling.h"
//---------------------------------------------------------------------------
#define EXTREME_TEST
//---------------------------------------------------------------------------
unsigned int StateFemaleSamplingBestOfNconspicific::getWinnerIndex(
  const std::vector<Male>& males,
  const Female& female,
  const Parameters& parameters) const
{
  const unsigned int bestOfHowMuch = parameters.bestOfHowMuch;
  //Create the male indices
  std::vector<unsigned int> maleIndices = createIndicesUnique(bestOfHowMuch, males.size());
  const std::vector<unsigned int> maleIndicesCopy = maleIndices;

  //Remove the males that are either heterospecific or assessed wrong
  for (unsigned int i=0; i<maleIndices.size(); ) //No ++i indeed
  {
    if (rnd::uniform() > female.assessingError) //The female does NOT make an error
    {
      if (female.species == piedFlycatcher) //Female is of species A (piedFlyCatcher)
      {
        if (males[ maleIndices[i] ].species == collaredFlycatcher) //Male is of species B
        {
          maleIndices.erase(maleIndices.begin() + i);
        }
        else //Male is of species A (piedFlycatcher)
          { ++i; } //The male is a conspicific and remains in the vecor
      }
      else //Female is of species B (collaredFlycatcher)
      {
        if (males[ maleIndices[i] ].species == collaredFlycatcher) //Male is of species B
          { ++i; }//The male is a conspicific and remains in the vecor
        else //Male is of species A
        {
          maleIndices.erase(maleIndices.begin() + i);
          //maleIndices.erase(&maleIndices.at(i));
        }
      }
    }
    else
    {
      ++i; //The wrongly assessed male remains
    }
  }

  //Dot("Remaining male Indices"); Dot(maleIndices);

  //With the remaining candidats, she mates at random
  if (maleIndices.size()>0) //She found a suitable candidat
  {
    const unsigned int candidatIndex = std::rand()%maleIndices.size();
    const unsigned int winnerIndex = maleIndices[candidatIndex];
    return winnerIndex;
  }
  else
  {
    return maleIndicesCopy[ std::rand()%maleIndicesCopy.size() ];
  }
}
//---------------------------------------------------------------------------
unsigned int StateFemaleSamplingBestOfNextremeTrait::getWinnerIndex(
  const std::vector<Male>& males,
  const Female& female,
  const Parameters& parameters) const
{
  const unsigned int bestOfHowMuch = ( parameters.bestOfHowMuch < males.size() ? parameters.bestOfHowMuch : males.size());
  //Create the male indices
  std::vector<unsigned int> maleIndices = createIndicesUnique(bestOfHowMuch, males.size());

  //Dot("Male Indices"); Dot(maleIndices);

  if (rnd::uniform() > female.assessingError) //The female does NOT make an error
  { //Get the best male
    if (female.preference < 0.0) //Find male with lowest trait
    {
      unsigned int candidatIndex = 0;
      double bestTrait = males[ maleIndices[0] ].trait;
      for (unsigned int i=1; i<bestOfHowMuch; ++i)
      {
        if (males[ maleIndices[i] ].trait < bestTrait)
        {
          bestTrait = males[ maleIndices[i] ].trait;
          candidatIndex = i;
        }
      }
      const unsigned int winnerIndex = maleIndices[candidatIndex];
      return winnerIndex;
    }
    else //Find male with highest trait
    {
      unsigned int candidatIndex = 0;
      double bestTrait = males[ maleIndices[0] ].trait;
      for (unsigned int i=1; i<bestOfHowMuch; ++i)
      {
        if (males[ maleIndices[i] ].trait > bestTrait)
        {
          bestTrait = males[ maleIndices[i] ].trait;
          candidatIndex = i;
        }
      }
      const unsigned int winnerIndex = maleIndices[candidatIndex];
      return winnerIndex;
    }
  }
  else
  {
    //Female mates at random
    const unsigned int candidatIndex = std::rand()%bestOfHowMuch;
    unsigned int winnerIndex = maleIndices[candidatIndex];
    return winnerIndex;
  }
}
//---------------------------------------------------------------------------
unsigned int StateFemaleSamplingBestOfNclosestTrait::getWinnerIndex(
  const std::vector<Male>& males,
  const Female& female,
  const Parameters& parameters) const
{
  const unsigned int bestOfHowMuch = ( parameters.bestOfHowMuch < males.size() ? parameters.bestOfHowMuch : males.size());
  //Create the male indices
  std::vector<unsigned int> maleIndices = createIndicesUnique(bestOfHowMuch, males.size());

  if (rnd::uniform() > female.assessingError) //The female does NOT make an error
  { //Get the best male
    unsigned int candidatIndex = 0;
    double closestTrait = std::fabs(males[ maleIndices[0] ].trait - female.preference);
    for (unsigned int i=1; i<bestOfHowMuch; ++i)
    {
      if (std::fabs(males[ maleIndices[i] ].trait - female.preference) < closestTrait)
      {
        closestTrait = std::fabs(males[ maleIndices[0] ].trait - female.preference);
        candidatIndex = i;
      }
    }
    const unsigned int winnerIndex = maleIndices[candidatIndex];
    return winnerIndex;
  }
  else
  {
    //Female mates at random
    const unsigned int candidatIndex = std::rand()%bestOfHowMuch;
    unsigned int winnerIndex = maleIndices[candidatIndex];
    return winnerIndex;
  }
}
//---------------------------------------------------------------------------
unsigned int StateFemaleSamplingFixedThresholdConspicific::getWinnerIndex(
  const std::vector<Male>& males,
  const Female& female,
  const Parameters& /*parameters*/) const
{
  const unsigned int nMales = males.size();
  const enumSpecies femaleSpecies = female.species;
  for(unsigned int i = 0; i < nMales*2; ++i) //The female searches all males 2x
  {
    const unsigned int maleIndex = std::rand()%nMales;
    const enumSpecies maleSpecies = males[maleIndex].species;
    if (rnd::uniform() >= female.assessingError) //The female does NOT make an error
    { //The female chooses him when either having a trait smaller of bigger then 0.5
      if (femaleSpecies == piedFlycatcher)
      { //She fancies a male of speciesA
        if ( maleSpecies == piedFlycatcher) return maleIndex;
      }
      else
      { //She fancies a male of species B
        if ( maleSpecies == collaredFlycatcher) return maleIndex;
      }
    }
    else //The female makes an error
    { //The female chooses him whatever species he is
      assert(female.assessingError>0.0);
      return maleIndex;
    }
  }
  //She has not found a mate
  //Dot("Female #" + IntToStr(female.index) + " has not found a mate");
  return nMales;

}
//---------------------------------------------------------------------------
unsigned int StateFemaleSamplingFixedThresholdTraitSign::getWinnerIndex(
  const std::vector<Male>& males,
  const Female& female,
  const Parameters& /*parameters*/) const
{
  const unsigned int nMales = males.size();
  const double femalePreference = female.preference;
  for(unsigned int i = 0; i < nMales*2; ++i) //The female searches all males 2x
  {
    const unsigned int maleIndex = std::rand()%nMales;
    const double maleTrait = males[maleIndex].trait;
    if (rnd::uniform() >= female.assessingError) //The female does NOT make an error
    { //The female chooses him when either having a trait smaller of bigger then 0.5
      if (femalePreference<=0.0)
      { //She fancies a male with low trait
        if ( maleTrait <= 0.0) return maleIndex;
      }
      else
      { //She fancies a male with high trait
        if ( maleTrait >= 0.0) return maleIndex;
      }
    }
    else //The female makes an error
    { //The female chooses him whatever species he is
      assert(female.assessingError>0.0);
      return maleIndex;
    }
  }
  //She has not found a mate
  return nMales;
}
//---------------------------------------------------------------------------
unsigned int StateFemaleSamplingFixedThresholdProbabilistic::getWinnerIndex(
  const std::vector<Male>& males,
  const Female& female,
  const Parameters& parameters) const
{
  const unsigned int nMales = males.size();
  const double sigmaSquared = parameters.sigmaSquared;
  const double femalePreference = female.preference;
  for(unsigned int i = 0; i < nMales*2; ++i) //The female searches all males 2x
  {
    const unsigned int maleIndex = std::rand()%nMales;
    const double maleTrait = males[maleIndex].trait;
    if (rnd::uniform() >= female.assessingError) //The female does NOT make an error
    { //The female chooses him when either having a trait smaller of bigger then 0.5
      //const double chanceToMate = std::exp(-(maleTrait-femalePreference)*(maleTrait-femalePreference)/sigmaSquared);
      const double chanceToMate = getChanceToMate(femalePreference,maleTrait,sigmaSquared);
      if (rnd::uniform() < chanceToMate) return maleIndex;
    }
    else //The female makes an error
    { //The female chooses him whatever species he is
      assert(female.assessingError>0.0);
      return maleIndex;
    }
  }
  //She has not found a mate
  return nMales;
}
//---------------------------------------------------------------------------
inline double StateFemaleSamplingFixedThresholdProbabilistic::getChanceToMate(
  const double& femalePreference,
  const double& maleTrait,
  const double& sigmaSquared)
{
   return std::exp(-(maleTrait-femalePreference)*(maleTrait-femalePreference)/sigmaSquared);
}
//---------------------------------------------------------------------------

//
// HELPER FUNCTIONS
//
//---------------------------------------------------------------------------
/*
unsigned int getBestMaleIndex(const std::vector<double>& maleTraits, const double& femalePreference, const double& assessingError)
//unsigned int getBestMaleIndex(
//  const std::vector<double>& maleTraits,
//  const double& femalePreference,
//  const double& assessingError)
{
    std::vector<unsigned int> bestMaleIndices;
    const unsigned int nCandidats = maleTraits.size();

    for (unsigned int i=0; i<nCandidats; ++i)
    {
      if (rnd::uniform() > assessingError) //The female does NOT make an error
      { //The female chooses her preference
        if ( maleTraits[i] == femalePreference) bestMaleIndices.push_back(i);
      }
      else //The female makes an error
      { //The female chooses him whatever species he is
        bestMaleIndices.push_back(i);
      }
    }
    //Select from the indices of best males the winner
    const unsigned int nCompetitors = bestMaleIndices.size();
    if (nCompetitors==0)
    {
      //Only losers, female chooses at random from all candidats
      const unsigned int bestMaleIndex = std::rand()%nCandidats;
      assert(bestMaleIndex<nCandidats);
      return bestMaleIndex;
    }
    //There are winner males, as nCompetitors > 0
    const unsigned int luckyCompetitorIndex = std::rand()%nCompetitors;
    const unsigned int bestMaleIndex = bestMaleIndices[luckyCompetitorIndex];
    assert(bestMaleIndex<nCandidats);
    return bestMaleIndex;
}
//---------------------------------------------------------------------------
//This function produces a vector of traits, in this case the select males' trait/ornaments
std::vector<double> createTraitsVector(const std::vector<Male>& males, const std::vector<unsigned int>& maleIndex)
//std::vector<double> createTraitsVector(
//  const std::vector<Male>& males,
//  const std::vector<unsigned int>& maleIndex)
{
  const unsigned int nMales = maleIndex.size();
  std::vector<double> maleTraits(nMales);
  for (unsigned int i=0; i<nMales; ++i)
  {
    const unsigned int indexMale = maleIndex[i];
    maleTraits[i] = males[indexMale].trait;
  }

  return maleTraits;
}
*/
//---------------------------------------------------------------------------
//Creates a vector of size 'bestOfHowMuch' with indices from 0 to 'nMales'
//An index might occur twice: if every index should be unique use 'createMaleIndices' instead.
std::vector<unsigned int> createIndices(
  const unsigned int& bestOfHowMuch,
  const unsigned int& nMales)
{
  std::vector<unsigned int> maleIndex(nMales);
  for(unsigned int mate = 0; mate < bestOfHowMuch; ++mate)
  {
    maleIndex[mate] = std::rand()%nMales;
    //No checking if a male is already chosen twice
    //if you want to do so, use 'createMaleIndicesUnique' instead of this function
  }
  return maleIndex;
}
//---------------------------------------------------------------------------
//Creates a vector of size 'bestOfHowMuch' from 0 to 'nMales'
//Every index is unique: if this is not important use 'createMaleIndices' instead
std::vector<unsigned int> createIndicesUnique(
  const unsigned int& bestOfHowMuch,
  const unsigned int& nMales)
{
  std::vector<unsigned int> maleIndex;

  if (bestOfHowMuch<nMales)
  {
    maleIndex.resize(bestOfHowMuch);
    assert(bestOfHowMuch<=nMales);

    maleIndex[0] = std::rand()%nMales; //0th element is always unique

    for(unsigned int mate = 1; mate < bestOfHowMuch; ++mate)
    {
      unsigned int index = 1000000; //1M
      do
      {
        index = std::rand()%nMales; //Do draw a random index
      }
      while(
        std::find(
          maleIndex.begin(),
          maleIndex.begin()+mate,
          index) != (maleIndex.begin()+mate)); //While not unqiue
      maleIndex[mate] = index;
    }
  }
  else
  { //To few males (nMales < bestOfHowMuch)
    maleIndex.resize(nMales);
    for (unsigned int male = 0; male< nMales; ++male) maleIndex[male] = male;
  }

  return maleIndex;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

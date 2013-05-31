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
#include "bird.h"
#include "simulation.h"
//---------------------------------------------------------------------------
Simulation::Simulation(const Parameters& parameters)
  : mParameters(parameters),
  mMateTally(new MateTally),
  mError("Finished simulation without errors.")
{
  //Copy parameters from mParameters
  setMatingSystem(mParameters.matingSystem, mParameters.densityDependentSelection);
  setFemaleSampling(mParameters.femaleSampling);
  //Reset results
  mMateTally->reset();
  mMales = Bird::createMales(mParameters);
  mFemales = Bird::createFemales(mParameters);

  //Shuffle the males and females
  std::random_shuffle(mMales.begin()  , mMales.end()  );
  std::random_shuffle(mFemales.begin(), mFemales.end());
}
//---------------------------------------------------------------------------
void Simulation::execute()
{
  const unsigned int nGenerations = mParameters.nGenerations;
  mTimeSeries.timePoints.resize(nGenerations);
  for (unsigned int generation=0; generation<nGenerations; ++generation)
  {
    //log("Start of species selection. Nmales: " + IntToStr(mMales.size()) + ",Nfemales: " + IntToStr(mFemales.size()));
    mTimeSeries.timePoints[generation].speciesTallyOffspring.tallySpecies(mFemales,mMales);
    mTimeSeries.timePoints[generation].getSample(mFemales,mMales);

    speciesSelection();   //Selection on species, hybrids have disadvantage

    //log("Start of viabilitySelection. Nmales: " + IntToStr(mMales.size()) + ",Nfemales: " + IntToStr(mFemales.size()));
    mTimeSeries.timePoints[generation].speciesTallyAfterSpeciesSelection.tallySpecies(mFemales,mMales);

    viabilitySelection(); //Selection on trait, individuals with high trait have disadvantage

    //log("Selection before mating. Nmales: " + IntToStr(mMales.size()) + ",Nfemales: " + IntToStr(mFemales.size()));
    mTimeSeries.timePoints[generation].speciesTallyAfterTraitSelection.tallySpecies(mFemales,mMales);

    bool canDoSelection = mDensityDependentSelection->canDoSelection(mFemales,mMales,mParameters,mError);
    if (canDoSelection==false) break;
    mDensityDependentSelection->doSelection(mFemales,mMales,mParameters);

    mTimeSeries.timePoints[generation].speciesTallyAfterDensityDependentSelection.tallySpecies(mFemales,mMales);

    Offspring offspring = mMatingSystem->mate(mMales,mFemales,mParameters,mFemaleSampling,mTimeSeries.timePoints[generation].mateTally);

    std::swap(mFemales, offspring.females);
    std::swap(mMales, offspring.males);

    if (mFemales.size()==0) break;
    if (mMales.size()==0) break;

  }
}
//---------------------------------------------------------------------------
//Selection on species, hybrids have disadvantage
void Simulation::speciesSelection()
{
  //Easy implementation: hybrids just die
  for (unsigned int male = 0; male < mMales.size(); ++male)
  {
    while(male < mMales.size() && willDieSpecies(mMales[male])==true)
    {
      #ifdef NDEBUG
        mMales.erase(&mMales[male]);
      #else
        mMales.erase(mMales.begin() + male);
      #endif
    }
  }

  for (unsigned int female = 0; female < mFemales.size(); ++female)
  {
    while(female < mFemales.size() && willDieSpecies(mFemales[female])==true)
    {
      #ifdef NDEBUG
        mFemales.erase(&mFemales[female]);
      #else
        mFemales.erase(mFemales.begin() + female);
      #endif
    }
  }
}
//---------------------------------------------------------------------------
//Selection on trait, individuals with high trait have disadvantage
void Simulation::viabilitySelection()
{
  //Easy implementation: hybrids just die
  for (unsigned int male = 0; male < mMales.size(); ++male)
  {
    while(male < mMales.size() && willDieTrait(mMales[male])==true)
    {
      #ifdef NDEBUG
        mMales.erase(&mMales[male]);
      #else
        mMales.erase(mMales.begin() + male);
      #endif
    }
  }

  for (unsigned int female = 0; female < mFemales.size(); ++female)
  {
    while(female < mFemales.size() && willDiePreference(mFemales[female])==true)
    {
      #ifdef NDEBUG
        mFemales.erase(&mFemales[female]);
      #else
        mFemales.erase(mFemales.begin() + female);
      #endif
    }
  }
}
//---------------------------------------------------------------------------
//Kills the hybrids
bool Simulation::willDieSpecies(const Bird& bird)
{
  assert(bird.descent>=-1.0 && bird.descent<=1.0);
  const double chanceToSurvive
    = chanceToSurviveSpecies(bird.descent, mParameters.surviveSpeciesAlpha, mParameters.surviveSpeciesBeta);
  //const double chanceToSurvive = 1.0 - (mParameters.surviveSpeciesAlpha *
  //  std::exp(-mParameters.surviveSpeciesBeta * bird.descent * bird.descent));
  assert(chanceToSurvive>=0.0 && chanceToSurvive<=1.0);
  //Dot("bird.descent: " + FloatToStr(bird.descent)
  //  + ", chance to survive: " + FloatToStr(chanceToSurvive));
  if (rnd::uniform() > chanceToSurvive) return true;
  else return false;
}
//---------------------------------------------------------------------------
bool Simulation::willDieTrait(const Male& male)
{
  const double chanceToSurvive = chanceToSurviveTrait(male.trait, mParameters.costTrait);
  //const double chanceToSurvive
  //  = std::exp(-mParameters.costTrait * male.trait * male.trait);
  assert(chanceToSurvive>=0.0 && chanceToSurvive<=1.0);
  if (rnd::uniform() > chanceToSurvive) return true;
  else return false;
}
//---------------------------------------------------------------------------
bool Simulation::willDiePreference(const Female& female)
{
  const double chanceToSurvive
  //  = std::exp(-mParameters.costPreference * female.preference * female.preference);
    = chanceToSurvivePreference(female.preference, mParameters.costPreference);
  assert(chanceToSurvive>=0.0 && chanceToSurvive<=1.0);
  if (rnd::uniform() > chanceToSurvive) return true;
  else return false;
}
//---------------------------------------------------------------------------
void Simulation::setMatingSystem(
  const enumMatingSystem& matingSystem,
  const enumDensityDependentSelection& selection)
{
  setDensityDependentSelection(selection);

  switch(selection)
  {
    //Selection after mating
    case afterMating:
        switch(matingSystem)
        {
          case monogamy:
            mMatingSystem.reset(new StateMatingSystemMonogamyFixedNumberOffspring);
            break;
          case polygyny:
            mMatingSystem.reset(new StateMatingSystemPolygynyFixedNumberOffspring);
            break;
          default: assert(!"Unknown mating system"); std::exit(1);
        }
        break;
    //Selection before mating
    case beforeMating:
        switch(matingSystem)
        {
          case monogamy:
            mMatingSystem.reset(new StateMatingSystemMonogamyFreeNumberOffspring);
            break;
          case polygyny:
            mMatingSystem.reset(new StateMatingSystemPolygynyFreeNumberOffspring);
            break;
          default: assert(!"Unknown mating system"); std::exit(1);
        }
        break;
    default:
      assert(!"Unknown enumDensityDependentSelection"); std::exit(1);
  }
  Dot("Mating system set to: " + mMatingSystem->getMatingSystem());
}
//---------------------------------------------------------------------------
void Simulation::setFemaleSampling(const enumFemaleSampling& femaleSampling)
{
  switch(femaleSampling)
  {
    case bestOfNconspicific:
      mFemaleSampling.reset(new StateFemaleSamplingBestOfNconspicific);
      break;
    case bestOfNextremeTrait:
      mFemaleSampling.reset(new StateFemaleSamplingBestOfNextremeTrait);
      break;
    case bestOfNclosestTrait:
      mFemaleSampling.reset(new StateFemaleSamplingBestOfNclosestTrait);
      break;
    case fixedThresholdConspicific:
      mFemaleSampling.reset(new StateFemaleSamplingFixedThresholdConspicific);
      break;
    case fixedThresholdTraitSign:
      mFemaleSampling.reset(new StateFemaleSamplingFixedThresholdTraitSign);
      break;
    case fixedThresholdProbabilistic:
      mFemaleSampling.reset(new StateFemaleSamplingFixedThresholdProbabilistic);
      break;
    default:
      assert(!"Unknown female sampling"); std::exit(1);
  }
  Dot("Female sampling set to: " + mFemaleSampling->getFemaleSampling());
}
//---------------------------------------------------------------------------
void Simulation::setDensityDependentSelection(const enumDensityDependentSelection& selection)
{
  switch(selection)
  {
    case beforeMating:
      mDensityDependentSelection.reset(new StateDensityDependentSelectionBeforeMating);
      break;
    //case afterMating:
    //  mDensityDependentSelection.reset(new StateDensityDependentSelectionAfterMating);
    //  break;
    default:
      assert(!"Unknown enumDensityDependentSelection"); std::exit(1);
  }
  Dot("Density dependent selection set to: " + mDensityDependentSelection->getString());
}
//---------------------------------------------------------------------------
inline double Simulation::chanceToSurviveSpecies(const double& descent, const double& alpha, const double& beta)
{
  return 1.0 - (alpha * std::exp(-beta * descent * descent));
}
//---------------------------------------------------------------------------
inline double Simulation::chanceToSurviveTrait(const double& trait, const double& costTrait)
{
  return  std::exp(-costTrait * trait * trait);
}
//---------------------------------------------------------------------------
inline double Simulation::chanceToSurvivePreference(const double& preference, const double& costPreference)
{
  return  std::exp(-costPreference * preference * preference);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

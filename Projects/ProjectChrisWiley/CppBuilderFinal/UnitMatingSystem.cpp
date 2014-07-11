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

#include "UnitMatingSystem.h"
//---------------------------------------------------------------------------
Offspring StateMatingSystemMonogamyFixedNumberOffspring::mate(
  std::vector<Female>& females,
  std::vector<Male>& males,
  const Parameters& parameters,
  const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
  MateTally& mateTally
  )
{
  std::auto_ptr<MateTally> debugMateTally(new MateTally);

  assert(mateTally.isNull()==true);
  //Get the fraction of species A and B
  const SpeciesTally speciesTally(males,females);
  /*
  const unsigned int nMalesAwanted   = static_cast<double>(parameters.nMales * speciesTally.getNallMalesA()) / static_cast<double>(speciesTally.getNallMales());
  const unsigned int nMalesBwanted   = static_cast<double>(parameters.nMales * speciesTally.getNallMalesB()) / static_cast<double>(speciesTally.getNallMales());
  const unsigned int nFemalesAwanted = static_cast<double>(parameters.nFemales * speciesTally.getNfemalesA()) / static_cast<double>(speciesTally.getNallFemales());
  const unsigned int nFemalesBwanted = static_cast<double>(parameters.nFemales * speciesTally.getNfemalesB()) / static_cast<double>(speciesTally.getNallFemales());
  */
  unsigned int nMalesAwanted   = parameters.getNmalesAwanted();
  unsigned int nMalesBwanted   = parameters.getNmalesBwanted();
  assert(nMalesAwanted + nMalesBwanted == parameters.nMales);
  unsigned int nFemalesAwanted = parameters.getNfemalesAwanted();
  unsigned int nFemalesBwanted = parameters.getNfemalesBwanted();
  assert(nFemalesAwanted + nFemalesBwanted == parameters.nFemales);

  const unsigned int nSpeciesAwanted = nMalesAwanted + nFemalesAwanted;
  const unsigned int nSpeciesBwanted = nMalesBwanted + nFemalesBwanted;
  const double mutation = parameters.mutationRate;

  assert(females.size()>0);

  //Create the couples
  std::vector< Couple > couples;
  for(unsigned int female = 0; female < females.size() && males.size() > 0; /*nothing*/)
  {
    //Let the female pick her favorite
    const unsigned int winnerIndex = femaleSampling->getWinnerIndex(males, females[female], parameters);
    assert(winnerIndex <= males.size());
    //Dot("The index of the mate in vector 'males' is: " + IntToStr(winnerIndex));
    if (winnerIndex == males.size())
    {
      //The female did not mate
      assert(parameters.femaleSampling!=bestOfNconspicific && parameters.femaleSampling!=bestOfNextremeTrait && parameters.femaleSampling!=bestOfNclosestTrait);
      ++female;
      continue;
    }
    //Form the std::pair from the lovers and store them in the std::vector couples
    Couple couple(females[female],males[winnerIndex]);
    couples.push_back(couple);
    //Remove the couple from the desperate others
    males.erase(&males[winnerIndex]);
    females.erase(&females[female]);
  }

  //Let the couples produce offspring
  std::vector<Bird> speciesA; //speciesA.reserve(nSpeciesAwanted);
  std::vector<Bird> speciesB; //speciesB.reserve(nSpeciesBwanted);
  const unsigned int nCouples = couples.size();
  const unsigned int maxTries = (nSpeciesAwanted + nSpeciesBwanted) * (nSpeciesAwanted + nSpeciesBwanted);
  unsigned int myTry = 0;
  while(speciesA.size()!=nSpeciesAwanted || speciesB.size()!=nSpeciesBwanted)
  {
    ++myTry;
    if (myTry==maxTries) break;
    for(unsigned int couple = 0; couple < nCouples; ++couple)
    {
      //Find out whether he is a conspicific and put it in the results
      Bird birdy(couples[couple].female,couples[couple].male,mutation);
      if (birdy.species == piedFlycatcher)
      { //Birdy is of speciesA
        debugMateTally->tally(couples[couple].female,couples[couple].male);
        if (speciesA.size() < nSpeciesAwanted)
        { //When we can use offspring of speciesA
          speciesA.push_back(birdy);
          mateTally.tally(couples[couple].female,couples[couple].male);
        }
      }
      else
      { //Birdy is of speciesB
        debugMateTally->tally(couples[couple].female,couples[couple].male); //DEBUG
        if (speciesB.size() < nSpeciesBwanted)
        { //When we can use offspring of speciesA
          speciesB.push_back(birdy);
          mateTally.tally(couples[couple].female,couples[couple].male);
        }
      }
    }
  }

  Dot("Broke while loop in reproduction");
  //Now the vectors of speciesA and speciesB are created,
  //they have to be changed to vectors of males and females
  Offspring offspring;
  if (myTry==maxTries)
  {
    //Create offspring of a failed simulation.
    //Easy! Just give the empty Offspring back
    return offspring;
  }

  assert(speciesA.size()==nSpeciesAwanted);
  assert(speciesB.size()==nSpeciesBwanted);
  //Females
  for (unsigned int i=0; i<nFemalesAwanted; ++i) offspring.females.push_back(speciesA[i]);
  for (unsigned int i=0; i<nFemalesBwanted; ++i) offspring.females.push_back(speciesB[i]);
  //Males
  for (unsigned int i=nFemalesAwanted; i<nSpeciesAwanted; ++i) offspring.males.push_back(speciesA[i]);
  for (unsigned int i=nFemalesBwanted; i<nSpeciesBwanted; ++i) offspring.males.push_back(speciesB[i]);

  assert(offspring.females.size()==nFemalesAwanted+nFemalesBwanted);
  assert(offspring.males.size()==nMalesAwanted+nMalesBwanted);

  //Dot("mateTally: "+mateTally.get());
  //Dot("DebugTally: "+debugMateTally->get());
  return offspring;

}
//---------------------------------------------------------------------------
Offspring StateMatingSystemPolygynyFixedNumberOffspring::mate(
  std::vector<Female>& females,
  std::vector<Male>& males,
  const Parameters& parameters,
  const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
  MateTally& mateTally
  )
{
  assert(mateTally.isNull()==true);
  //Get the fraction of species A and B
  const SpeciesTally speciesTally(males,females);
  /*
  const unsigned int nMalesAwanted   = static_cast<double>(parameters.nMales * speciesTally.getNallMalesA()) / static_cast<double>(speciesTally.getNallMales());
  const unsigned int nMalesBwanted   = static_cast<double>(parameters.nMales * speciesTally.getNallMalesB()) / static_cast<double>(speciesTally.getNallMales());
  const unsigned int nFemalesAwanted = static_cast<double>(parameters.nFemales * speciesTally.getNfemalesA()) / static_cast<double>(speciesTally.getNallFemales());
  const unsigned int nFemalesBwanted = static_cast<double>(parameters.nFemales * speciesTally.getNfemalesB()) / static_cast<double>(speciesTally.getNallFemales());
  */
  unsigned int nMalesAwanted   = parameters.getNmalesAwanted();
  unsigned int nMalesBwanted   = parameters.getNmalesBwanted();
  assert(nMalesAwanted + nMalesBwanted == parameters.nMales);
  unsigned int nFemalesAwanted = parameters.getNfemalesAwanted();
  unsigned int nFemalesBwanted = parameters.getNfemalesBwanted();
  assert(nFemalesAwanted + nFemalesBwanted == parameters.nFemales);

  const unsigned int nSpeciesAwanted = nMalesAwanted + nFemalesAwanted;
  const unsigned int nSpeciesBwanted = nMalesBwanted + nFemalesBwanted;
  const double mutation = parameters.mutationRate;
  const unsigned int nFemales = females.size();
  assert(nFemales>0);
  std::vector<Bird> speciesA;
  std::vector<Bird> speciesB;

  const unsigned int maxTries = (nSpeciesAwanted + nSpeciesBwanted) * (nSpeciesAwanted + nSpeciesBwanted);
  unsigned int myTry = 0;
  while(speciesA.size()!=nSpeciesAwanted || speciesB.size()!=nSpeciesBwanted)
  {
    ++myTry;
    if (myTry==maxTries) break;
    for(unsigned int female = 0; female < nFemales; ++female)
    {
      //Let the female pick her favorite
      const unsigned int winnerIndex = femaleSampling->getWinnerIndex(males, females[female], parameters);
      assert(winnerIndex <= males.size());

      //Dot("The index of the mate in vector 'males' is: " + IntToStr(winnerIndex));
      if (winnerIndex == males.size())
      {
        //The female did not mate
        assert(parameters.femaleSampling!=bestOfNconspicific && parameters.femaleSampling!=bestOfNextremeTrait && parameters.femaleSampling!=bestOfNclosestTrait);
        continue;
      }

      //Find out whether he is a conspicific and put it in the results
      Bird birdy(females[female],males[winnerIndex],mutation);
      if (birdy.species == piedFlycatcher)
      { //Birdy is of speciesA
        if (speciesA.size() < nSpeciesAwanted)
        { //When we can use offspring of speciesA
          speciesA.push_back(birdy);
          mateTally.tally(females[female],males[winnerIndex]);
        }
      }
      else
      { //Birdy is of speciesB
        if (speciesB.size() < nSpeciesBwanted)
        { //When we can use offspring of speciesA
          speciesB.push_back(birdy);
          mateTally.tally(females[female],males[winnerIndex]);
        }
      }
    }
  }

  Dot("Broke while loop in reproduction above line ");

  //Now the vectors of speciesA and speciesB are created,
  //they have to be changed to vectors of males and females

  Offspring offspring;
  if (myTry==maxTries)
  {
    //Create offspring of a failed simulation.
    //Easy! Just give the empty Offspring back
    return offspring;
  }

  assert(speciesA.size()==nSpeciesAwanted);
  assert(speciesB.size()==nSpeciesBwanted);
  //Females
  for (unsigned int i=0; i<nFemalesAwanted; ++i) offspring.females.push_back(speciesA[i]);
  for (unsigned int i=0; i<nFemalesBwanted; ++i) offspring.females.push_back(speciesB[i]);
  //Males
  for (unsigned int i=nFemalesAwanted; i<nSpeciesAwanted; ++i) offspring.males.push_back(speciesA[i]);
  for (unsigned int i=nFemalesBwanted; i<nSpeciesBwanted; ++i) offspring.males.push_back(speciesB[i]);

  assert(offspring.females.size()==nFemalesAwanted+nFemalesBwanted);
  assert(offspring.males.size()==nMalesAwanted+nMalesBwanted);
  return offspring;
}
//---------------------------------------------------------------------------
Offspring StateMatingSystemMonogamyFreeNumberOffspring::mate(
  std::vector<Female>& females,
  std::vector<Male>& males,
  const Parameters& parameters,
  const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
  MateTally& mateTally
  )
{
  std::auto_ptr<MateTally> debugMateTally(new MateTally);

  assert(mateTally.isNull()==true);
  const double mutation = parameters.mutationRate;
  assert(females.size()>0);

  //Create the couples
  std::vector< Couple > couples;
  for(unsigned int female = 0; female < females.size() && males.size() > 0; )
  {
    //Let the female pick her favorite
    const unsigned int winnerIndex = femaleSampling->getWinnerIndex(males, females[female], parameters);
    assert(winnerIndex <= males.size());
    //Dot("The index of the mate in vector 'males' is: " + IntToStr(winnerIndex));
    if (winnerIndex == males.size())
    {
      //The female did not mate
      assert(parameters.femaleSampling!=bestOfNconspicific && parameters.femaleSampling!=bestOfNextremeTrait && parameters.femaleSampling!=bestOfNclosestTrait);
      ++female;
      continue;
    }
    //Form the std::pair from the lovers and store them in the std::vector couples
    Couple couple(females[female],males[winnerIndex]);
    couples.push_back(couple);
    //Remove the couple from the desperate others
    males.erase(&males[winnerIndex]);
    females.erase(&females[female]);
  }

  //Let the couples produce offspring
  Offspring offspring;
  const unsigned int nCouples = couples.size();
  for(unsigned int couple = 0; couple < nCouples; ++couple)
  {
    const unsigned int nOffspring = parameters.nOffspring;
    for (unsigned i=0; i<nOffspring; ++i)
    {
      //Find out whether he is a conspicific and put it in the results
      Bird birdy(couples[couple].female,couples[couple].male,mutation);
      debugMateTally->tally(couples[couple].female,couples[couple].male); //DEBUG
      mateTally.tally(couples[couple].female,couples[couple].male);
      if (std::rand()%2==0)
        offspring.males.push_back(birdy);
      else
        offspring.females.push_back(birdy);
    }
  }

  //Now the vectors of speciesA and speciesB are created,
  //they have to be changed to vectors of males and females
  //Dot("mateTally: "+mateTally.get());
  //Dot("DebugTally: "+debugMateTally->get());
  return offspring;
}
//---------------------------------------------------------------------------
Offspring StateMatingSystemPolygynyFreeNumberOffspring::mate(
  std::vector<Female>& females,
  std::vector<Male>& males,
  const Parameters& parameters,
  const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
  MateTally& mateTally
  )
{
  std::auto_ptr<MateTally> debugMateTally(new MateTally);
  assert(mateTally.isNull()==true);
  //Get the fraction of species A and B
  const double mutation = parameters.mutationRate;
  const unsigned int nFemales = females.size();
  assert(nFemales>0);
  Offspring offspring;
  for(unsigned int female = 0; female < nFemales; ++female)
  {
    //Let the female pick her favorite
    const unsigned int winnerIndex = femaleSampling->getWinnerIndex(males, females[female], parameters);
    assert(winnerIndex <= males.size());

    //Dot("The index of the mate in vector 'males' is: " + IntToStr(winnerIndex));
    if (winnerIndex == males.size())
    {
      //The female did not mate
      assert(parameters.femaleSampling!=bestOfNconspicific && parameters.femaleSampling!=bestOfNextremeTrait && parameters.femaleSampling!=bestOfNclosestTrait);
      continue;
    }

    const unsigned int nOffspring = parameters.nOffspring;
    //Let them produce many offspring
    for (unsigned i=0; i<nOffspring; ++i)
    {
      //Find out whether he is a conspicific and put it in the results
      Bird birdy(females[female],males[winnerIndex],mutation);
      debugMateTally->tally(females[female],males[winnerIndex]); //DEBUG
      mateTally.tally(females[female],males[winnerIndex]);
      if (std::rand()%2==0)
        offspring.males.push_back(birdy);
      else
        offspring.females.push_back(birdy);
    }
  }

  return offspring;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

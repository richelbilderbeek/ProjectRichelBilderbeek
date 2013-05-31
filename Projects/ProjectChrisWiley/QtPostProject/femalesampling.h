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
#ifndef FEMALESAMPLING_H
#define FEMALESAMPLING_H
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include "bird.h"
#include "parameters.h"
#include "random.h"

//---------------------------------------------------------------------------
class StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingBase() {}
  virtual unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const = 0;
  virtual std::string getFemaleSampling() const = 0;
};
//---------------------------------------------------------------------------
class StateFemaleSamplingBestOfNconspicific : public StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingBestOfNconspicific() {}
  unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const;
  std::string getFemaleSampling() const { return "Best of N conspicific"; }
};
//---------------------------------------------------------------------------
class StateFemaleSamplingBestOfNextremeTrait : public StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingBestOfNextremeTrait() {}
  unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const;
  std::string getFemaleSampling() const { return "Best of N extreme trait"; }
};
//---------------------------------------------------------------------------
class StateFemaleSamplingBestOfNclosestTrait : public StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingBestOfNclosestTrait() {}
  unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const;
  std::string getFemaleSampling() const { return "Best of N closest trait"; }
};
//---------------------------------------------------------------------------
class StateFemaleSamplingFixedThresholdConspicific : public StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingFixedThresholdConspicific() {}
  unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const;
  std::string getFemaleSampling() const { return "Fixed threshold conspicific"; }
};
//---------------------------------------------------------------------------
class StateFemaleSamplingFixedThresholdTraitSign : public StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingFixedThresholdTraitSign() {}
  unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const;
  std::string getFemaleSampling() const { return "Fixed threshold trait sign"; }
};
//---------------------------------------------------------------------------
class StateFemaleSamplingFixedThresholdProbabilistic : public StateFemaleSamplingBase
{
  public:
  StateFemaleSamplingFixedThresholdProbabilistic() {}
  unsigned int getWinnerIndex(const std::vector<Male>& males, const Female& female, const Parameters& parameters) const;
  std::string getFemaleSampling() const { return "Fixed threshold probabilistic"; }
  static inline double getChanceToMate(const double& femalePreference, const double& maleTrait, const double& sigmaSquared);


};
//---------------------------------------------------------------------------
std::vector<unsigned int> createIndices(const unsigned int& bestOfHowMuch, const unsigned int& nMales);
std::vector<unsigned int> createIndicesUnique(const unsigned int& bestOfHowMuch, const unsigned int& nMales);
//std::vector<double> createSpeciesVector(const std::vector<Male>& males, const std::vector<unsigned int>& maleIndex);
//std::vector<double> createTraitsVector(const std::vector<Male>& males, const std::vector<unsigned int>& maleIndex);
//unsigned int getBestMaleIndex(const std::vector<double>& maleTraits, const double& femalePreference, const double& assessingError);
//---------------------------------------------------------------------------
#endif // FEMALESAMPLING_H

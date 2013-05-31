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
#ifndef TIMEPOINT_H
#define TIMEPOINT_H
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <algorithm>
#include "matetally.h"
#include "speciestally.h"
//---------------------------------------------------------------------------
class TimePoint
{
  public:
  TimePoint() { reset(); }
  std::vector<double> traits;
  std::vector<double> preferences;
  std::vector<double> descents;
  MateTally mateTally;
  SpeciesTally speciesTallyOffspring;
  SpeciesTally speciesTallyAfterSpeciesSelection;
  SpeciesTally speciesTallyAfterTraitSelection;
  SpeciesTally speciesTallyAfterDensityDependentSelection;

  void reset();
  bool isNull() const;
  void getSample(const std::vector<Female>& females, const std::vector<Male>& males);

  void operator/=(const unsigned int& valueInt) //For taking the average of multiple timepoints
  {
    //const double value = static_cast<double>(valueInt);
    speciesTallyOffspring/=valueInt;
    speciesTallyAfterSpeciesSelection/=valueInt;
    speciesTallyAfterTraitSelection/=valueInt;
    speciesTallyAfterDensityDependentSelection/=valueInt;
    std::random_shuffle(traits.begin(),traits.end());
    std::random_shuffle(preferences.begin(),preferences.end());
    std::random_shuffle(descents.begin(),descents.end());
    traits.resize(traits.size()/valueInt);
    preferences.resize(preferences.size()/valueInt);
    descents.resize(descents.size()/valueInt);

  }
  void operator+=(const TimePoint& timePoint) //For taking the average of multiple timepoints
  {
    mateTally+=timePoint.mateTally;
    speciesTallyOffspring+=timePoint.speciesTallyOffspring;
    speciesTallyAfterSpeciesSelection+=timePoint.speciesTallyAfterSpeciesSelection;
    speciesTallyAfterTraitSelection+=timePoint.speciesTallyAfterTraitSelection;
    speciesTallyAfterDensityDependentSelection+=timePoint.speciesTallyAfterDensityDependentSelection;

    const unsigned int traitSize = timePoint.traits.size();
    for (unsigned int i=0; i<traitSize; ++i) traits.push_back(timePoint.traits[i]);
    const unsigned int preferenceSize = timePoint.preferences.size();
    for (unsigned int i=0; i<preferenceSize; ++i) preferences.push_back(timePoint.preferences[i]);
    const unsigned int descentSize = timePoint.descents.size();
    for (unsigned int i=0; i<descentSize; ++i) descents.push_back(timePoint.descents[i]);
  }
};
//---------------------------------------------------------------------------
#endif // TIMEPOINT_H

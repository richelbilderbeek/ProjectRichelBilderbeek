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
#ifndef UnitDensityDependentSelectionH
#define UnitDensityDependentSelectionH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <algorithm>
#include "UnitTallies.h"
#include "UnitParameters.h"
#include "UnitBird.h"

class StateDensityDependentSelectionBase
{
  public:
  StateDensityDependentSelectionBase() {}
  virtual std::string getString() const = 0;
  virtual bool canDoSelection(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    std::string& errorMessage
    //const SpeciesTally& speciesTally
    ) const = 0;
  virtual void doSelection(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters
    //const SpeciesTally& speciesTally
    ) const = 0;
};
//---------------------------------------------------------------------------
class StateDensityDependentSelectionAfterMating : public StateDensityDependentSelectionBase
{
  public:
  StateDensityDependentSelectionAfterMating() {}
  std::string getString() const { return "DensityDependentSelectionAfterMating"; }
  bool canDoSelection(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    std::string& errorMessage
    //const SpeciesTally& speciesTally
    ) const;
  void doSelection(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters
    //const SpeciesTally& speciesTally
    ) const;
};
//---------------------------------------------------------------------------
class StateDensityDependentSelectionBeforeMating : public StateDensityDependentSelectionBase
{
  public:
  StateDensityDependentSelectionBeforeMating() {}
  std::string getString() const { return "DensityDependentSelectionBeforeMating"; }
  bool canDoSelection(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    std::string& errorMessage
    //const SpeciesTally& speciesTally
    ) const;
  void doSelection(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters
    //const SpeciesTally& speciesTally
    ) const;
};
//---------------------------------------------------------------------------
#endif

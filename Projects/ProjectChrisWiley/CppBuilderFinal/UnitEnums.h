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
#ifndef UnitEnumsH
#define UnitEnumsH
//---------------------------------------------------------------------------
enum enumSpecies
{
  piedFlycatcher, //descent/speciesValue = -1
  collaredFlycatcher  //descent/speciesValue = 1.0
};

enum enumDensityDependentSelection
{
  beforeMating,
  afterMating
};

enum enumMatingSystem
{
  monogamy,
  polygyny //Male can mate multiple times
};

enum enumFemaleSampling
{
  bestOfNconspicific,
  bestOfNextremeTrait,
  bestOfNclosestTrait,
  fixedThresholdConspicific,
  fixedThresholdTraitSign,
  fixedThresholdProbabilistic
};

#endif

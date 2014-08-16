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
#ifndef UnitMatingSystemH
#define UnitMatingSystemH
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>


#include "UnitBird.h"
#include "UnitParameters.h"
#include "UnitFemaleSampling.h"
#include "UnitTallies.h"
#include "UnitHelperFunctions.h"
#include "UnitRandom.h"

class StateMatingSystemBase
{
  public:
  StateMatingSystemBase() {}
  virtual std::string getMatingSystem() const = 0;
  virtual Offspring mate(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
    MateTally& tally
    ) = 0;
};
//---------------------------------------------------------------------------
class StateMatingSystemMonogamyFixedNumberOffspring : public StateMatingSystemBase
{
  public:
  StateMatingSystemMonogamyFixedNumberOffspring() {}
  std::string getMatingSystem() const { return "MonogamyFixedNumberOffspring"; }
  Offspring mate(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
    MateTally& tally
    );

};
//---------------------------------------------------------------------------
class StateMatingSystemPolygynyFixedNumberOffspring : public StateMatingSystemBase
{
  public:
  StateMatingSystemPolygynyFixedNumberOffspring() {}
  std::string getMatingSystem() const { return "PolygynyFixedNumberOffspring"; }
  Offspring mate(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
    MateTally& tally
    );
};
//---------------------------------------------------------------------------
class StateMatingSystemMonogamyFreeNumberOffspring : public StateMatingSystemBase
{
  public:
  StateMatingSystemMonogamyFreeNumberOffspring() {}
  std::string getMatingSystem() const { return "MonogamyFreeNumberOffspring"; }
  Offspring mate(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
    MateTally& tally
    );

};
//---------------------------------------------------------------------------
class StateMatingSystemPolygynyFreeNumberOffspring : public StateMatingSystemBase
{
  public:
  StateMatingSystemPolygynyFreeNumberOffspring() {}
  std::string getMatingSystem() const { return "PolygynyFreeNumberOffspring"; }
  Offspring mate(
    std::vector<Female>& females,
    std::vector<Male>& males,
    const Parameters& parameters,
    const std::auto_ptr<StateFemaleSamplingBase>& femaleSampling,
    MateTally& tally
    );
};
//---------------------------------------------------------------------------


#endif

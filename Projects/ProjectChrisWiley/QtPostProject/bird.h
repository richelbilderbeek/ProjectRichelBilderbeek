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
#ifndef BIRD_H
#define BIRD_H
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <cassert>
#include "helperfunctions.h"
#include "parameters.h"
#include "enums.h"
#include "random.h"

class Couple; //Forward declaration

class Bird
{
  public:

  Bird(const Bird& mother, const Bird& father, const double& mutation);

  static std::vector<Bird> createMales(const Parameters& parameters);
  static std::vector<Bird> createFemales(const Parameters& parameters);

  static std::vector<Bird> createTestMales(
    const Parameters& parameters,
    const double& species1, const double& trait1,
    const double& species2, const double& trait2,
    const double& species3, const double& trait3,
    const double& species4, const double& trait4);

  static std::vector<Bird> createTestFemales(
    const Parameters& parameters,
    const double& species, const double& preference);

  unsigned int index;
  double descent;
  enumSpecies species;
  double trait;
  double preference;
  double assessingError;


  private:
  //No empty constructor, Birds are either created from parents or
  //from the static createMales/createFemales functions
  Bird() {}
};

typedef Bird Male;
typedef Bird Female;

struct Offspring
{
  std::vector<Female> females;
  std::vector<Male>   males;
};

typedef Offspring Population;

class Couple
{
  public:
  Couple(const Female& anyFemale, const Male& anyMale)
    : female(anyFemale),
    male(anyMale)
  {
    //Nothing
  }
  Female female;
  Male   male;
};
//---------------------------------------------------------------------------
#endif // BIRD_H

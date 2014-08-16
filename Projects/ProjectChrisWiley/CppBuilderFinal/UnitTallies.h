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
#ifndef UnitTalliesH
#define UnitTalliesH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "UnitBird.h"

//---------------------------------------------------------------------------
class MateTally
{
  public:
  MateTally() { reset(); }
  void tally(const Bird& mother, const Bird& father);
  void reset();
  std::string get() const;
  bool isNull() const;
  double calculateBiasA() const;
  double calculateBiasB() const;
  double calculateFractionMixedPairs() const;

  unsigned int getNmateAA() const { return nMateAA; } //Female A - male A
  unsigned int getNmateAB() const { return nMateAB; } //Female A - male B
  unsigned int getNmateBA() const { return nMateBA; } //Female B - male A
  unsigned int getNmateBB() const { return nMateBB; } //Female B - male B
  unsigned int getNmateAll() const { return nMateAA + nMateAB + nMateBA + nMateBB; }

  void operator/=(const unsigned int& intValue);
  void operator+=(const MateTally&  mateTally);

  private:
  unsigned int nMateAA; //Female A - male A
  unsigned int nMateAB; //Female A - male B
  unsigned int nMateBA; //Female B - male A
  unsigned int nMateBB; //Female B - male B
};
//---------------------------------------------------------------------------
class SpeciesTally
{
  public:
  SpeciesTally() { reset(); }
  SpeciesTally(const std::vector<Female>& females, const std::vector<Male>& males)
  {
    reset();
    tallySpecies(females,males);
  }
  void reset();
  bool isNull() const;
  void tallySpecies(const std::vector<Female>& females, const std::vector<Male>& males);
  void operator+=(const SpeciesTally& speciesTally);
  void operator/=(const unsigned int& intValue);

  //Plain retrieval
  unsigned int getNmalesA()         const { return nMalesA;         }
  unsigned int getNmalesB()         const { return nMalesB;         }
  unsigned int getNfemalesA()       const { return nFemalesA;       }
  unsigned int getNfemalesB()       const { return nFemalesB;       }
  //Some group retrieval
  unsigned int getNallMalesA()   const { return nMalesA; }
  unsigned int getNallMalesB()   const { return nMalesB; }
  unsigned int getNallMales()    const { return nMalesA + nMalesB; }
  unsigned int getNallFemalesA() const { return nFemalesA; }
  unsigned int getNallFemalesB() const { return nFemalesB; }
  unsigned int getNallFemales()  const { return nFemalesA + nFemalesB; }
  unsigned int getNall()         const { return getNallFemales() + getNallMales(); }

  /*
  unsigned int getNallMalesA()   const { return nMalesA + nMaleHybridsA; }
  unsigned int getNallMalesB()   const { return nMalesB + nMaleHybridsB; }
  unsigned int getNallMales()    const { return nMalesA + nMaleHybridsA + nMalesB + nMaleHybridsB; }
  unsigned int getNallFemalesA() const { return nFemalesA + nFemaleHybridsA; }
  unsigned int getNallFemalesB() const { return nFemalesB + nFemaleHybridsB; }
  unsigned int getNallFemales()  const { return nFemalesA + nFemaleHybridsA + nFemalesB + nFemaleHybridsB; }
  unsigned int getNall()         const { return getNallFemales() + getNallMales(); }
  */
  private:
  //The private variables it is all about
  unsigned int nMalesA;         //SpeciesValue < -0.5
  unsigned int nMalesB;         //SpeciesValue > 0.5
  unsigned int nFemalesA;       //SpeciesValue < -0.5
  unsigned int nFemalesB;       //SpeciesValue > 0.5
};
//---------------------------------------------------------------------------


#endif

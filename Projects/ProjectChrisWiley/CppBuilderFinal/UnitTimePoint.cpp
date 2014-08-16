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

#include "UnitTimePoint.h"

//---------------------------------------------------------------------------
void TimePoint::reset()
{
  traits.resize(0);
  preferences.resize(0);
  descents.resize(0);
  mateTally.reset();
  speciesTallyOffspring.reset();
  speciesTallyAfterSpeciesSelection.reset();
  speciesTallyAfterTraitSelection.reset();
  speciesTallyAfterDensityDependentSelection.reset();
}
//---------------------------------------------------------------------------
bool TimePoint::isNull() const
{
  if (traits.size()>0) return false;
  if (preferences.size()>0) return false;
  if (descents.size()>0) return false;
  if (mateTally.isNull()==false) return false;
  if (speciesTallyOffspring.isNull()==false) return false;
  if (speciesTallyAfterSpeciesSelection.isNull()==false) return false;
  if (speciesTallyAfterTraitSelection.isNull()==false) return false;
  if (speciesTallyAfterDensityDependentSelection.isNull()==false) return false;
  return true;
}
//---------------------------------------------------------------------------
void TimePoint::getSample(const std::vector<Female>& females, const std::vector<Male>& males)
{
  const unsigned int sampleSize = 2;
  //Get sample of female preferences
  unsigned int nFemalesA = 0, nFemalesB = 0;
  const unsigned int nFemales = females.size();
  for (unsigned int i=0; i<nFemales ; ++i)
  {
    if (females[i].species==piedFlycatcher)
    {
      if (nFemalesA<sampleSize)
      {
        preferences.push_back(females[i].preference);
        descents.push_back(females[i].descent);
        ++nFemalesA;
      }
    }
    else
    {
      if (nFemalesB<sampleSize)
      {
        preferences.push_back(females[i].preference);
        descents.push_back(females[i].descent);
        ++nFemalesB;
      }
    }
    if (nFemalesA==sampleSize && nFemalesB==sampleSize) break;
    assert(nFemalesA<=sampleSize);
    assert(nFemalesB<=sampleSize);
  }

  //Get sample of male traits
  unsigned int nMalesA = 0, nMalesB = 0;
  const unsigned int nMales = males.size();
  for (unsigned int i=0; i<nMales ; ++i)
  {
    if (males[i].species==piedFlycatcher)
    {
      if (nMalesA<sampleSize)
      {
        traits.push_back(males[i].trait);
        descents.push_back(males[i].descent);
        ++nMalesA;
      }
    }
    else
    {
      if (nMalesB<sampleSize)
      {
        traits.push_back(males[i].trait);
        descents.push_back(males[i].descent);
        ++nMalesB;
      }
    }
    if (nMalesA==sampleSize && nMalesB==sampleSize) break;
    assert(nMalesA<=sampleSize);
    assert(nMalesB<=sampleSize);
  }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
#pragma package(smart_init)

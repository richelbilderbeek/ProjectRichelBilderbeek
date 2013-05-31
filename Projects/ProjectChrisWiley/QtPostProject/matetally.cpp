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
#include "matetally.h"
//---------------------------------------------------------------------------
void MateTally::reset()
{
  nMateAA = 0;
  nMateAB = 0;
  nMateBA = 0;
  nMateBB = 0;
}
//---------------------------------------------------------------------------
void MateTally::operator/=(const unsigned int& intValue)
{
  nMateAA/=intValue;
  nMateAB/=intValue;
  nMateBA/=intValue;
  nMateBB/=intValue;
}
//---------------------------------------------------------------------------
void MateTally::operator+=(const MateTally& mateTally)
{
  nMateAA+=mateTally.nMateAA;
  nMateAB+=mateTally.nMateAB;
  nMateBA+=mateTally.nMateBA;
  nMateBB+=mateTally.nMateBB;
}
//---------------------------------------------------------------------------
std::string MateTally::get() const
{
  std::string result;
  result+= "nMateAA: " + itoa(nMateAA);
  result+= " ,nMateAB: " + itoa(nMateAB);
  result+= " ,nMateBA: " + itoa(nMateBA);
  result+= " ,nMateBB: " + itoa(nMateBB);
  return result;
}
//---------------------------------------------------------------------------
bool MateTally::isNull() const
{
  if ( nMateAA!=0
    || nMateAB!=0
    || nMateBA!=0
    || nMateBB!=0) return false;
  return true;
}
//---------------------------------------------------------------------------
void MateTally::tally(const Bird& mother, const Bird& father)
{
  if (mother.species == piedFlycatcher)
  {
    if (father.species == piedFlycatcher)
      { ++nMateAA; }
    else
      { ++nMateAB; }
  }
  else
  {
    if (father.species == piedFlycatcher)
    { ++nMateBA; }
    else
    { ++nMateBB; }
  }
}
//---------------------------------------------------------------------------
double MateTally::calculateBiasA() const
{
  return (nMateAB + nMateBA == 0 ? 0.0
    : static_cast<double>(nMateAB) / static_cast<double>(nMateAB + nMateBA));

}
//---------------------------------------------------------------------------
double MateTally::calculateBiasB() const
{
  return (nMateAB + nMateBA == 0 ? 0.0
    : static_cast<double>(nMateBA) / static_cast<double>(nMateAB + nMateBA));
}
//---------------------------------------------------------------------------
double MateTally::calculateFractionMixedPairs() const
{
  return (this->isNull()==true ? 0.0
    : static_cast<double>(nMateAB + nMateBA) / static_cast<double>(nMateAA + nMateAB + nMateBA + nMateBB));
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



#ifndef MATETALLY_H
#define MATETALLY_H

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
#include <string>
#include <vector>
#include "bird.h"
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
#endif // MATETALLY_H

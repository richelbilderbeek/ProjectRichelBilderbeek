//---------------------------------------------------------------------------
/*
  The Thor Veen Project, simulation to investigate honest signalling
  Copyright (C) 2006  Rich�l Bilderbeek

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
#ifndef UnitBreedingParametersH
#define UnitBreedingParametersH
//---------------------------------------------------------------------------
#include <iosfwd>
#include <vector>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
class BreedingParameters : public boost::noncopyable
{
  public:
  //Number of birds
  int mNfemaleOffspring;
  int mNmaleOffspring;
  //Type of breeding
  //EnumBreeding mEnumBreeding;
  //Random independent rearing
  double mRandomMeanNotUsed;
  double mRandomStdDevNotUsed;
  //Other rearings
  //E.g. rearing dependent on... (e.g condition mother/father/etc.)
  std::vector<std::string> getText() const;
};

#endif
 
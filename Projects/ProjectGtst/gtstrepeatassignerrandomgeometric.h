
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTREPEATASSIGNERRANDOMGEOMETRIC_H
#define PROJECTGTSTREPEATASSIGNERRANDOMGEOMETRIC_H

#include "gtstrepeatassigner.h"


namespace ribi {
namespace gtst {

///\brief
///A RepeatAssignerRandomGeometric that assigns the IPGG to be
///repeated a random number of times following a geometric distribution
///
///The random number of times the IPGG is player is calculated
///by a Monte Carlo run in Assign
struct RepeatAssignerRandomGeometric : public RepeatAssigner
{
  ///Create the RepeatAssigner with the chance it will choose to do another IPGG round
  RepeatAssignerRandomGeometric(const double w);

  ///Assign determines the number of IPGG repeats
  int Assign() const;

  ///Converts RepeatAssignerRandomUniform to std::string
  const std::string ToStr() const;

  private:
  ~RepeatAssignerRandomGeometric() {}
  friend void boost::checked_delete<>(RepeatAssignerRandomGeometric*);

  ///Parameter w is the chance that after a round, another one will follow
  const double m_w;

  ///Get a random number from 0.0 to 1.0 in a uniform distribution
  static double GetRandomUniform();
};

} //~namespace gtst
} //~namespace ribi

#endif // REPEATASSIGNERRANDOMGEOMETRIC_H

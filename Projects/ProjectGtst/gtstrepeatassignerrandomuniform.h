
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

#ifndef PROJECTGTSTREPEATASSIGNERRANDOMUNIFORM_H
#define PROJECTGTSTREPEATASSIGNERRANDOMUNIFORM_H

#include "gtstrepeatassigner.h"


namespace ribi {
namespace gtst {

///\brief
///A RepeatAssigner that assigns the IPGG to repeated a random number of times.
///
///This random number of times is a random number from a certain range
///in a uniform distribution
struct RepeatAssignerRandomUniform : public RepeatAssigner
{
  ///Create the RepeatAssigner with the range of values it chooses from
  ///to determine the number of IPGG rounds
  RepeatAssignerRandomUniform(const int from, const int to);

  ///Assign determines the number of IPGG repeats
  int Assign() const;

  ///Converts RepeatAssignerRandomUniform to std::string
  const std::string ToStr() const;

  private:
  ~RepeatAssignerRandomUniform() {}
  friend void boost::checked_delete<>(RepeatAssignerRandomUniform*);

  ///The lowest value RepeatAssignerRandomUniform chooses from to
  ///determine the number of IPGG rounds
  const int m_from;

  ///The range its to(-but-not-included)-value RepeatAssignerRandomUniform
  ///chooses from to determine the number of IPGG rounds
  const int m_to;
};

} //~namespace gtst
} //~namespace ribi

#endif // REPEATASSIGNERRANDOMUNIFORM_H

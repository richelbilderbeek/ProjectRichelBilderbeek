
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

#ifndef PROJECTGTSTREPEATASSIGNERFIXED_H
#define PROJECTGTSTREPEATASSIGNERFIXED_H

#include "gtstrepeatassigner.h"


namespace ribi {
namespace gtst {

///\brief
///A RepeatAssigner that always assigns the IPGG to be repeated a fixed
///amount of times
struct RepeatAssignerFixed : public RepeatAssigner
{
  ///Create the RepeatAssigner with the value it will always produce
  RepeatAssignerFixed(const int value);

  ///Assign determines the number of IPGG repeats
  int Assign() const;

  ///Converts RepeatAssignerFixed to std::string
  const std::string ToStr() const;

  private:
  ~RepeatAssignerFixed() {}
  friend void boost::checked_delete<>(RepeatAssignerFixed*);

  ///The number of IPGG repeats
  const int m_value;

};

} //~namespace gtst
} //~namespace ribi

#endif // REPEATASSIGNERFIXED_H


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

#ifndef PROJECTGTSTREPEATASSIGNER_H
#define PROJECTGTSTREPEATASSIGNER_H

#include <string>
#include <vector>

#include <boost/checked_delete.hpp>



namespace ribi {
namespace gtst {

///\brief
///RepeatAssigner is a Strategy to determined
///how often a certain state is repeated
struct RepeatAssigner
{
  RepeatAssigner();
  RepeatAssigner(const RepeatAssigner&) = delete;
  RepeatAssigner& operator=(const RepeatAssigner&) = delete;

  ///Assign determines the number of IPGG repeats
  virtual int Assign() const = 0;

  ///Returns the last assigned number of repeats
  bool CanGetLastAssigned() const;

  ///Returns if there already is a value assigned
  int GetLastAssigned() const;

  ///Converts a RepeatAssigner to std::string
  virtual const std::string ToStr() const = 0;

  protected:
  virtual ~RepeatAssigner() {}
  friend void boost::checked_delete<>(RepeatAssigner*);

  ///The log of all assigned values
  mutable std::vector<int> m_assigned_values;
};


} //~namespace gtst
} //~namespace ribi

#endif // REPEATASSIGNER_H

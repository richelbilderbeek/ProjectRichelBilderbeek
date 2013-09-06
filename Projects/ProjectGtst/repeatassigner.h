//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011 Richel Bilderbeek

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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#ifndef PROJECTGTSTREPEATASSIGNER_H
#define PROJECTGTSTREPEATASSIGNER_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///RepeatAssigner is a Strategy to determined
///how often a certain state is repeated
struct RepeatAssigner : public boost::noncopyable
{

  ///Assign determines the number of IPGG repeats
  virtual int Assign() const = 0;

  ///Returns the last assigned number of repeats
  bool CanGetLastAssigned() const;

  ///Returns if there already is a value assigned
  int GetLastAssigned() const;

  ///Converts a RepeatAssigner to std::string
  virtual const std::string ToStr() const = 0;

  protected:
  ///Let RepeatAssigner only be instanciated by its derived classes
  //Herb Sutter, Andrei Alexandrescu. C++ coding standards: 101 rules,
  //guidelines, and best practices. ISBN: 0-32-111358-6. Item 50: 'Make base
  //class destructors public and virtual, or protected and nonvirtual'.
  virtual ~RepeatAssigner() {}
  ///Only let smart pointers delete RepeatAssigner
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(RepeatAssigner*);

  ///The log of all assigned values
  mutable std::vector<int> m_assigned_values;
};


} //~namespace gtst
} //~namespace ribi

#endif // REPEATASSIGNER_H

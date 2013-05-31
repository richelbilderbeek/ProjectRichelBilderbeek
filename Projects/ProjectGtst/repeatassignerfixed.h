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
#ifndef PROJECTGTSTREPEATASSIGNERFIXED_H
#define PROJECTGTSTREPEATASSIGNERFIXED_H
//---------------------------------------------------------------------------
#include "repeatassigner.h"
//---------------------------------------------------------------------------
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
  ///Only allow a Boost smart pointer to delete RepeatAssignerFixed
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~RepeatAssignerFixed() {}
  ///Only allow a Boost smart pointer to delete RepeatAssignerFixed
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(RepeatAssignerFixed*);

  ///The number of IPGG repeats
  const int m_value;

};
//---------------------------------------------------------------------------


#endif // REPEATASSIGNERFIXED_H

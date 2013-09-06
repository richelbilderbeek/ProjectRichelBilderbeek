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
#ifndef PARAMETERSVIEWRESULTSALL_H
#define PARAMETERSVIEWRESULTSALL_H
//---------------------------------------------------------------------------
#include <iosfwd>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///Parameters for the view-results-all state
struct ParametersViewResultsAll
{
  ParametersViewResultsAll();

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///Get the number of times the larger-cycle/experiment repeats itself
  int GetNumberOfPeriods() const;

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);

  ///Set the number of times the larger-cycle/experiment repeats itself
  void SetNumberOfPeriods(const int n_periods);

  private:
  ///Only allow a Boost smart pointer to delete ParametersViewResultsAll
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParametersViewResultsAll() {}
  ///Only let smart pointers delete ParametersViewResultsAll
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParametersViewResultsAll*);

  ///Time that is allowed in this phase
  int m_duration;

  ///\brief
  ///The number of times the larger-cycle/experiment repeats itself
  ///
  ///An m_n_periods of 1 denotes that the larger-cycle/experiment does
  ///not repeat itself
  int m_n_periods;
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersViewResultsAll& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSVIEWRESULTSALL_H

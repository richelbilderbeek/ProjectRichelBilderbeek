
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

#ifndef PARAMETERSVIEWRESULTSALL_H
#define PARAMETERSVIEWRESULTSALL_H

#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

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
  ~ParametersViewResultsAll() {}
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

std::ostream& operator<<(std::ostream& os,const ParametersViewResultsAll& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSVIEWRESULTSALL_H

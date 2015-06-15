
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

#ifndef PROJECTGTSTPARAMETERSVIEWRESULTSVOTING_H
#define PROJECTGTSTPARAMETERSVIEWRESULTSVOTING_H

#include <iosfwd>

#include <boost/checked_delete.hpp>


#include "gtstforward_declarations.h"


namespace ribi {
namespace gtst {

///\brief
///Parameters for the view-results-voting state
struct ParametersViewResultsVoting
{
  ParametersViewResultsVoting();

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);

  private:
  ~ParametersViewResultsVoting() {}
  friend void boost::checked_delete<>(ParametersViewResultsVoting*);

  ///Time that is allowed in this phase
  int m_duration;
};

std::ostream& operator<<(std::ostream& os,const ParametersViewResultsVoting& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSVIEWRESULTSVOTING_H

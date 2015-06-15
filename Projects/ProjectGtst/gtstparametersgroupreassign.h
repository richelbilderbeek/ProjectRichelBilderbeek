
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

#ifndef PARAMETERSGROUPREASSIGN_H
#define PARAMETERSGROUPREASSIGN_H

#include <iosfwd>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>

#include "gtstforward_declarations.h"
#include "gtststate.h"
#pragma GCC diagnostic pop


namespace ribi {
namespace gtst {

///\brief
///Parameters for the group dynamics state
struct ParametersGroupReAssign : public StateGroupReAssign
{
  ParametersGroupReAssign();

  ///Calculate how much payoff the active participant is rewarded
  ///for reaching the next round
  double CalculateNextPeriodPayoff(const double payoff) const;

  ///Get the duration of the ServerState (in seconds)
  int GetDuration() const;

  ///Get the function that determines how much payoff the active participant is rewarded
  ///for reaching the next round
  const std::string& GetNextPeriodPayoffFunction() const { return m_next_period_payoff_function; }

  ///Get the number of times the larger-cycle/experiment repeats itself
  int GetNumberOfPeriods() const;

  ///Set the duration of the ServerState (in seconds)
  void SetDuration(const int time);

  ///Set the function that determines how much payoff the active participant is rewarded
  ///for reaching the next round
  void SetNextPeriodPayoffFunction(const std::string& function);

  ///Set the number of times the larger-cycle/experiment repeats itself
  void SetNumberOfPeriods(const int n_periods);

  ///Parse a line
  void Parse(const std::string& s);

  private:
  ~ParametersGroupReAssign() {}
  friend void boost::checked_delete<>(ParametersGroupReAssign*);

  ///Time that is allowed in this phase
  int m_duration;

  ///\brief
  ///The number of times the larger-cycle/experiment repeats itself
  ///
  ///An m_n_periods of 1 denotes that the larger-cycle/experiment does
  ///not repeat itself
  int m_n_periods;

  ///\brief
  ///The function that determines how much payoff the active participant is rewarded
  ///for reaching the next round waiting
  ///
  ///This payoff is assigned when the active participants are reassigned to another
  ///period.
  ///This payoff function is dependent on variable 'p', which denotes the average payoff
  ///of the active participants, which can be negative
  ///For example '1 + (0.1 * p)' denotes that an active participant gets
  ///one plus a tenth of the average payoff gained by the other active participants.
  ///If statements are also possible: '(p>0)*p' denotes 'if (p>0) return p, else zero',
  ///because '(p>0)' evaluates to one if p is bigger than zero, and evaluates to
  ///zero if p is smaller or equal to zero.
  std::string m_next_period_payoff_function;
};

std::ostream& operator<<(std::ostream& os,const ParametersGroupReAssign& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSGROUPREASSIGN_H

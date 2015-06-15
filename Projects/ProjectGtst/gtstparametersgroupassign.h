
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

#ifndef PARAMETERSGROUPASSIGN_H
#define PARAMETERSGROUPASSIGN_H

#include <iosfwd>
#include <string>

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
///Parameters for the group dynamics state
struct ParametersGroupAssign
{
  ParametersGroupAssign();

  ///Calculate how much payoff the waiting participant is rewarded
  ///for simply waiting
  double CalculateWaitingPayoff(const double average_payoff) const;

  ///Get the message shown to an assigned participant
  const std::string& GetMessageAssigned() const { return m_message_assigned; }

  ///Get the message shown to an unassigned participant
  const std::string& GetMessageUnassigned() const { return m_message_unassigned; }

  ///Set the function that determines how much payoff the waiting
  ///participant is rewarded for simply waiting
  const std::string& GetWaitingPayoffFunction() const { return m_waiting_payoff_function; }

  ///Parse a line
  void Parse(const std::string& s);

  ///Set the message shown to an assigned participant
  void SetMessageAssigned(const std::string& message);

  ///Set the message shown to an unassigned participant
  void SetMessageUnassigned(const std::string& message);

  ///Set the function that determines how much payoff the waiting
  ///participant is rewarded for simply waiting
  void SetWaitingPayoffFunction(const std::string& function);

  private:
  ~ParametersGroupAssign() {}
  friend void boost::checked_delete<>(ParametersGroupAssign*);

  ///The message at the group dynamics screen when assigned to a group
  std::string m_message_assigned;

  ///The message at the group dynamics screen when not yet assigned to a group
  std::string m_message_unassigned;

  ///\brief
  ///The function that determines how much payoff the waiting participant is rewarded
  ///for simply waiting
  ///
  ///This payoff is assigned when the active participants are reassigned to another
  ///period.
  ///This payoff function is dependent on variable 'p', which denotes the average payoff
  ///of the active participants, which can be negative
  ///For example '1.0 + (0.1 * p)' denotes that a waiting participant gets
  ///one plus a tenth of the average payoff gained by the other participants.
  ///If statements are also possible: '(p>0)*p' denotes 'if (p>0) return p, else zero',
  ///because '(p>0)' evaluates to one if p is bigger than zero, and evaluates to
  ///zero if p is smaller or equal to zero.
  std::string m_waiting_payoff_function;
};

std::ostream& operator<<(std::ostream& os,const ParametersGroupAssign& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSGROUPASSIGN_H

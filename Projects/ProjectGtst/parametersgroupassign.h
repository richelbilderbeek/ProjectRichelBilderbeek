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
#ifndef PARAMETERSGROUPASSIGN_H
#define PARAMETERSGROUPASSIGN_H
//---------------------------------------------------------------------------
#include <iosfwd>
#include <string>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------

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
  ///Only allow a Boost smart pointer to delete ParametersGroupAssign
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParametersGroupAssign() {}
  ///Only let smart pointers delete ParametersGroupAssign
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
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
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ParametersGroupAssign& parameters);

} //~namespace gtst
} //~namespace ribi

#endif // PARAMETERSGROUPASSIGN_H

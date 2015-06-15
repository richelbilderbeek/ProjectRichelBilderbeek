
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

#ifndef PROJECTGTSTSERVERSTATEASSIGNPAYOFF_H
#define PROJECTGTSTSERVERSTATEASSIGNPAYOFF_H

#include <iosfwd>
#include <map>
#include <boost/shared_ptr.hpp>

#include "gtststate.h"
#include "gtstserverstate.h"

namespace ribi {
namespace gtst {

///\brief
///The Server is in the assign-payoff state
struct ServerStateAssignPayoff : public ServerState, StateAssignPayoff
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateAssignPayoff(
    Server * const server,
    const int period,
    const int cycle,
    const boost::shared_ptr<const ParametersAssignPayoff> parameters,
    const boost::shared_ptr<const ServerStateViewResultsVoting> state_view_results_voting);

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///Create this ServerState its specific Parameters
  void SetParameters(const boost::shared_ptr<const ParametersAssignPayoff>& parameters);

  ///Start or restart the state, for example by resetting the timer
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateAssignPayoff::ToStr(); }

  private:
  ~ServerStateAssignPayoff() {}
  friend void boost::checked_delete<>(ServerStateAssignPayoff*);

  friend std::ostream& operator<<(std::ostream& os,const ServerStateAssignPayoff& s);

  ///Keeps track of Participants having assigned their payoff
  std::map<const Participant *,bool> m_has_assigned_payoff;

  ///Read-only parameters
  const boost::shared_ptr<const ParametersAssignPayoff> m_parameters;


  ///ServerStateViewResultsVoting this ServerState reads its information from
  const boost::shared_ptr<const ServerStateViewResultsVoting> m_state_view_results_voting;
};

std::ostream& operator<<(std::ostream& os,const ServerStateAssignPayoff& s);

} //~namespace gtst
} //~namespace ribi

#endif // ServerSTATEASSIGNPAYOFF_H

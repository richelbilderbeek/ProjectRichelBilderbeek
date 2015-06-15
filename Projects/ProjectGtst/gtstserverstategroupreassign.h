
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

#ifndef SERVERSTATEGROUPREASSIGN_H
#define SERVERSTATEGROUPREASSIGN_H

#include <map>

#include <boost/shared_ptr.hpp>

#include "gtstserverstate.h"


namespace ribi {
namespace gtst {

///\brief
///The Server in the state when each Participant is assigned his/her group
struct ServerStateGroupReAssign : public ServerState, StateGroupReAssign
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateGroupReAssign(
    Server * const server,
    const int period,
    const int cycle,
    const boost::shared_ptr<const ParametersGroupReAssign>& parameters);

  ///Request the server to assign the Participant to a Group
  void AssignGroup(const boost::shared_ptr<const Participant>& participant) const;

  ///Ask the server if the Participant can be asssigned to a Group
  bool CanAssignGroup(const boost::shared_ptr<const Participant>& participant) const;

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///Let this one Group split from 3 Participants
  ///to 5 Participants
  void NotifyGroupGrowth(const Group * const group) const;

  ///Let this one Group split from 5 Participants
  ///to two Groups of 3 Participants
  void NotifyGroupSplit(const Group * const group) const;

  ///Kill the Group
  void NotifyKillGroup(const Group * const group) const;

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///Get the worst and best group
  std::pair<const Group *,const Group *> GetWorstAndBestGroup() const { return m_worst_and_best_group; }

  ///Create this ServerState its specific Parameters
  //void SetParameters(const boost::shared_ptr<const ParametersGroupReAssign>& parameters);

  ///Set the ID's (=key) of the Participants that are
  ///allowed to join a group (=value)
  //void SetJoiners(const std::map<int,int>& joiners);

  ///Start or restart the state, calculate the joiners
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateGroupReAssign::ToStr(); }

  private:
  ~ServerStateGroupReAssign() {}
  friend void boost::checked_delete<>(ServerStateGroupReAssign*);
  friend std::ostream& operator<<(std::ostream& os,const ServerStateGroupReAssign& s);

  ///Calculate the average payoff of the active particpants
  double CalculateAveragePayoff() const;

  ///Determine which groups are worst and best
  const std::pair<const Group *,const Group *> CalculateWorstAndBestGroup() const;


  ///\brief
  ///The group its average payoff in the entire last IPGG cycle
  ///
  ///int = key = group_index
  ///std::pair = value:
  ///- double: average payoff
  ///
  ///Example: Group of 3, for 2 IPGG cycles
  ///#1: 1 4
  ///#2: 2 5
  ///#3: 3 6
  ///Average = (1 + 2 + 3 + 4 + 5 + 6) / 6 = 3.5
  std::map<const Group *,double> m_group_payoffs;

  ///The ServerStateViewResultsAll its read-only ParametersViewResultsAll
  const boost::shared_ptr<const ParametersGroupReAssign> m_parameters;

  ///The worst and best group
  std::pair<const Group *,const Group *> m_worst_and_best_group;
};

std::ostream& operator<<(std::ostream& os,const ServerStateGroupReAssign& s);

} //~namespace gtst
} //~namespace ribi

#endif // SERVERSTATEGROUPREASSIGN_H

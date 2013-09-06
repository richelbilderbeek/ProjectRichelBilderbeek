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
#ifndef PROJECTGTSTSERVERSTATEVIEWRESULTSVOTING_H
#define PROJECTGTSTSERVERSTATEVIEWRESULTSVOTING_H

#include <map>

#include "serverstate.h"

namespace ribi {
namespace gtst {

///\brief
///The Server in the state when each Participant can view the
///voting results of his/her group.
struct ServerStateViewResultsVoting : public ServerState, StateViewResultsVoting
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateViewResultsVoting(Server * const server, const int period, const int cycle,
  const boost::shared_ptr<const ParametersViewResultsVoting>& parameters);

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///\brief
  ///Get the VotingOptions voted for by each Group
  ///
  ///If no consensus is reached, VotingOptions is null
  const std::map<const Group *,const VotingOption *>& GetVotedOptions() const { return m_voted_concensus; }

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Create this ServerState its specific Parameters
  //void SetParameters(const boost::shared_ptr<const ParametersViewResultsVoting>& parameters);

  ///Get the Participant-dependent results of the votes of his/her group
  const std::vector<boost::shared_ptr<Vote> > GetGroupResults(
    const boost::shared_ptr<const Participant>& participant) const;

  ///Start or restart the state, for example by resetting the timer
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateViewResultsVoting::ToStr(); }

  private:
  ///Only allow a Boost smart pointer to delete ServerStateViewResultsVoting
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ServerStateViewResultsVoting() {}
  ///Only let smart pointers delete ServerStateViewResultsVoting
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ServerStateViewResultsVoting*);

  friend std::ostream& operator<<(std::ostream& os,const ServerStateViewResultsVoting& s);

  ///The parameters
  const boost::shared_ptr<const ParametersViewResultsVoting> m_parameters;

  ///\brief
  ///The consensus of the VotingOptions voted for by each Group
  ///
  ///If no consensus is reached, VotingOptions is null
  std::map<const Group *,const VotingOption *> m_voted_concensus;
};

std::ostream& operator<<(std::ostream& os,const ServerStateViewResultsVoting& s);

} //~namespace gtst
} //~namespace ribi

#endif // ServerSTATEVIEWRESULTSVOTING_H

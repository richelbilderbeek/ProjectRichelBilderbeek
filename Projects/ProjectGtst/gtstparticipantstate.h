
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

#ifndef PROJECTGTSTPARTICIPANTSTATE_H
#define PROJECTGTSTPARTICIPANTSTATE_H



#include "gtstforward_declarations.h"
#include "gtststate.h"


namespace ribi {
namespace gtst {

///\brief
///The State the Participant is in.
///
///Every ParticipantState has certain assumptions:
///- ParticipantStateNotLoggedIn: no ID, no IP address
///- ParticipantStateLoggedIn: assigns ID, assigns IP address, not in a Group
///- ParticipantStateGroupDynamics: assigns Group
///- ParticipantStateChat: adds chat messages
///- ParticipantStateVoting: adds vote
///- ParticipantStateViewResultsVoting: views group votes
///- ParticipantStateChooseAction: adds action
///- ParticipantStateAssignPayoff: assign payoff
///- ParticipantStateViewResultsGroup: views group payoff
///- ParticipantStateViewResultsAll: views all group payoff
struct ParticipantState : public State
{
  ///Contruct every ParticipantState from a pointer to its Participant
  ParticipantState(
    Participant * const participant,
    Server * const server);
  ParticipantState(const ParticipantState&) = delete;
  ParticipantState& operator=(const ParticipantState&) = delete;

  ///Obtain a read-only Participant
  const Participant * GetParticipant() const { return m_participant; }

  ///Represent the State as a std::string
  //const std::string StateToStr() const;

  ///Represent the ParticipantState as a std::string for an Administrator
  virtual const std::string ToAdminStr() const = 0;

  protected:
  ///Only let a smart pointer delete this ParticipantState
  virtual ~ParticipantState() {}
  ///Only let a smart pointer delete this ParticipantState
  friend void boost::checked_delete<>(ParticipantState*);

  private:
  ///The Participant this ParticipantState works on
  ///
  ///\note
  ///Do not change this to boost::shared_ptr<const Participant>, because
  ///each State is constructed at the constructor of a Participant,
  ///which requires a pointer to 'this'
  Participant * const m_participant;

  protected:
  Server * const m_server;

};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTSTATE_H

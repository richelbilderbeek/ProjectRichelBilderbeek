
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

#ifndef PROJECTGTSTPARTICIPANTSTATELOGGEDIN_H
#define PROJECTGTSTPARTICIPANTSTATELOGGEDIN_H

#include <boost/checked_delete.hpp>

#include "gtststate.h"
#include "gtstparticipantstate.h"


namespace ribi {
namespace gtst {

///The Participant is in the StateLoggedIn ParticipantState
struct ParticipantStateLoggedIn
  : public ParticipantState, StateLoggedIn
{
  ///Contruct every ParticipantState from a pointer to its Participant
  ParticipantStateLoggedIn(Participant * const participant,Server * const server);

  ///Get the message from the server if others finish a period, where
  ///this participant is waiting to participate
  const std::string& GetMessage() const { return m_message; }

  ///Set the message (done by the Server) if others finish a period, where
  ///this participant is waiting to participate
  void SetMessage(const std::string& message) { m_message = message; }

  ///Represent the ParticipantState as a std::string for an Administrator
  const std::string ToAdminStr() const;

  ///Represent the State at a std::string
  const std::string ToStr() const { return this->StateLoggedIn::ToStr(); }

  private:
  ///Only let a smart pointer delete this ParticipantState
  ~ParticipantStateLoggedIn() {}

  ///Only let a smart pointer delete this ParticipantState
  friend void boost::checked_delete<>(ParticipantStateLoggedIn*);

  ///The message from the server if others finish a period, where
  ///this participant is waiting to participate. This message
  ///shows how much payoff the Participant is given for waiting a period
  std::string m_message;
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTSTATELOGGEDIN_H

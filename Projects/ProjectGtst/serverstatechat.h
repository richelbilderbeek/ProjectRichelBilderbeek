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
#ifndef PROJECTGTSTSERVERSTATECHAT_H
#define PROJECTGTSTSERVERSTATECHAT_H
//---------------------------------------------------------------------------
#include <string>
#include <map>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
#include "state.h"
#include "serverstate.h"
//---------------------------------------------------------------------------
///\brief
///The Server is in the chat state
struct ServerStateChat: public ServerState, StateChat
{
  ///Create this ServerState by passing the Server it is a State of
  ServerStateChat(
    Server * const server,
    const int period,
    const int cycle,
    const boost::shared_ptr<const ParametersChat> parameters);

  ///See if the Participant has pending chat messages,
  ///sent by him/herself or the others
  bool CanGetChatMessages(
    const boost::shared_ptr<const Participant>& participant) const;

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  bool CanGoToNextState() const;

  ///Obtain the Participant his/her pending chat messages,
  ///sent by him/herself or the others
  const std::vector<boost::shared_ptr<ChatMessage> > GetChatMessages(
    const boost::shared_ptr<const Participant>& participant);

  ///ServerState dependent response to a timer
  void OnTimer();

  ///Obtain the duration of the state in seconds
  int GetStateDuration() const;

  ///Create this ServerState its specific Parameters
  //void SetParameters(const boost::shared_ptr<const ParametersChat>& parameters);

  ///In the 'Chat' phase, any Participant can send a chat message that
  ///will be broadcasted to all group members
  void NotifyChatMessage(
    const boost::shared_ptr<const Participant>& participant,
    const boost::shared_ptr<ChatMessage>& message);

  ///Start or restart the state
  void Start();

  ///Represent this ServerState as a std::string
  const std::string ToStr() const { return this->StateChat::ToStr(); }

  private:
  ///Only allow a Boost smart pointer to delete ServerStateChat
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ServerStateChat() {}
  ///Only allow a Boost smart pointer to delete ServerStateChat
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ServerStateChat*);

  friend std::ostream& operator<<(std::ostream& os,const ServerStateChat& s);

  ///Chat parameters
  const boost::shared_ptr<const ParametersChat> m_parameters;

  ///Checks if each Participant has chatted already this/last round
  //bool GetAllParticipantsHaveChatted() const;

  ///For Participant, m_chat_messages contains
  ///his/her pending chat messages
  std::map<boost::shared_ptr<const Participant>,std::vector<boost::shared_ptr<ChatMessage> > > m_chat_messages;
};
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ServerStateChat& s);
//---------------------------------------------------------------------------
#endif // ServerSTATECHAT_H

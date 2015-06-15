//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <fstream>

#include "gtstadministrator.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstchatmessage.h"
#include "gtstgroup.h"
#include "gtstgroupfinished.h"
#include "gtstgrouploggedin.h"
#include "gtstgroupnotloggedin.h"
#include "gtstgroupparticipating.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtststate.h"
#include "trace.h"
#include "wtserverpusher.h"

ribi::gtst::ServerStateChat::ServerStateChat(
  Server * const server,
  const int period,
  const int cycle,
  const boost::shared_ptr<const ParametersChat> parameters)
  : ServerState(server,period,cycle),
    m_chat_messages{},
    m_parameters(parameters)
{
  assert(m_parameters);
}

///See if the Participant has pending chat messages,
///sent by him/herself or the others
bool ribi::gtst::ServerStateChat::CanGetChatMessages(
  const boost::shared_ptr<const Participant>& participant) const
{
  assert(participant);
  return m_chat_messages.find(participant) != m_chat_messages.end();
}

///Check if this state can go to the next state.
bool ribi::gtst::ServerStateChat::CanGoToNextState() const
{
  return GetTimeLeft() < 0;
}

///Obtain the Participant his/her pending chat messages,
///sent by him/herself or the others
const std::vector<boost::shared_ptr<ribi::gtst::ChatMessage> > ribi::gtst::ServerStateChat::GetChatMessages(
  const boost::shared_ptr<const Participant>& participant)
{
  assert(CanGetChatMessages(participant));

  //Get new messages
  const std::vector<boost::shared_ptr<ChatMessage> > messages
    = m_chat_messages[participant];
  //Remove pending messages
  m_chat_messages[participant].resize(0);
  //Return new messages
  return messages;
}

///Obtain the duration of the state in seconds
int ribi::gtst::ServerStateChat::GetStateDuration() const
{
  return m_parameters->GetDuration();
}

void ribi::gtst::ServerStateChat::OnTimer()
{
  if (CanGoToNextState()) GoToNextState();
}

///In the 'Chat' phase, any Participant can send a chat message that
///will be broadcasted to all group members
void ribi::gtst::ServerStateChat::NotifyChatMessage(
  const boost::shared_ptr<const Participant>& participant,
  const boost::shared_ptr<ChatMessage>& message)
{
  assert(GetServer());

  LogFile * const logfile = GetServer()->GetLog();
  assert(logfile);

  //Append the chat message to the Participant his/her own log
  FindParticipant(participant)->AppendChat(message);

  //Logging this event
  logfile->LogChatMessage(participant,message);

  //Broadcasting chat texts for participants of the same group
  //including the sender itself
  {
    const Group * const group = GetServer()->GetGroups()->FindMyGroup(participant);
    const auto ps = group->CollectParticipants();

    std::for_each(ps.begin(),ps.end(),
      [this,message](const boost::shared_ptr<const Participant>& p)
      {
        this->m_chat_messages[p].push_back(message);
      }
    );
  }

  WtServerPusher::GetInstance()->Post();
}

/*
void ribi::gtst::ServerStateChat::SetParameters(const boost::shared_ptr<const ParametersChat>& parameters)
{
  assert(parameters);
  m_parameters = parameters;

  ResetTimeLeft();
  assert(this->GetTimeLeft() >= 0);
}
*/

///Start or restart the state. Just go to the next chat phase, because
///every Participant can have or have not chatted the last round
void ribi::gtst::ServerStateChat::Start()
{
  ResetTimeLeft();
  m_chat_messages.clear();

  const auto ps = GetServer()->GetGroups()->CollectParticipants(false,false,true,false);
  std::for_each(ps.begin(),ps.end(),
    [this](const boost::shared_ptr<const Participant>& p)
    {
      const StateChat * const state = dynamic_cast<const StateChat*>(this);
      assert(state);
      this->FindParticipant(p)->SetState(state);
      this->FindParticipant(p)->StartChat();
    }
  );
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateChat& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    << "<has_assigned_payoff>";
  std::for_each(s.m_chat_messages.begin(),s.m_chat_messages.end(),
    [&os](const std::pair<boost::shared_ptr<const Participant>,std::vector<boost::shared_ptr<ChatMessage> > >& p)
    {
      os
        << p.first;
      std::for_each(p.second.begin(),p.second.end(),
        [&os](const boost::shared_ptr<ChatMessage>& m)
      {
        os << m;
      } );

    } );

  os
    << "</has_assigned_payoff>"
    << s.m_parameters
    //<< s.m_server
    //<< s.m_stopwatch
    //<< s.m_wait_time
    << "</state_" << s.ToStr() << ">";
  return os;
}


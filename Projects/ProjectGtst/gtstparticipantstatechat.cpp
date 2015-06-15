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
#include "gtstchatmessage.h"
#include "gtstparticipant.h"
#include "gtstparticipantstatechat.h"

ribi::gtst::ParticipantStateChat::ParticipantStateChat(
  Participant * const participant,Server * const server)
  : ParticipantState(participant,server)
{

}

const std::string ribi::gtst::ParticipantStateChat::ToAdminStr() const
{
  const Participant * const participant = GetParticipant();
  std::string s = std::to_string(participant->GetId())
    + std::string(": ");
  const std::vector<std::vector<boost::shared_ptr<ChatMessage> > >& chat
    = participant->GetChatLog();
  if (chat.back().empty())
  {
    s+="[no chat this round]";
  }
  else
  {
    std::for_each(chat.back().begin(), chat.back().end(),
      [&s](const boost::shared_ptr<ChatMessage>& t)
    {
      s+=t->GetText() +" | ";
    } );
  }
  return s;
}


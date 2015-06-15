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
#include <iostream>

#include "gtstchatmessage.h"
#include "gtstparticipant.h"

ribi::gtst::ChatMessage::ChatMessage(
  const boost::shared_ptr<const Participant>& sender,
  std::string message)
  : m_sender(sender), m_text(message)
{
  assert(m_sender);
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ChatMessage& p)
{
  os
    << "<chat_message>"
    << "<text>"
    << p.GetText()
    << "</text>"
    << (*(p.GetSender()))
    << "</chat_message>";
  return os;
}


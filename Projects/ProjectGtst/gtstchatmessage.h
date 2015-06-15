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
#ifndef PROJECTGTSTCHATMESSAGE_H
#define PROJECTGTSTCHATMESSAGE_H

#include <iosfwd>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

struct ChatMessage
{
  ChatMessage(
    //const boost::shared_ptr<Participant>& sender,
    const boost::shared_ptr<const Participant>& sender,
    std::string text);

  ///Obtain a read-only pointer to the sender
  const boost::shared_ptr<const Participant>& GetSender() const { return m_sender; }

  ///Obtain the chat message its text
  const std::string& GetText() const { return m_text; }

  private:
  ~ChatMessage() {}
  friend void boost::checked_delete<>(ChatMessage*);

  ///The ShapeWidget of the sender
  //const boost::shared_ptr<Participant> m_sender;
  const boost::shared_ptr<const Participant> m_sender;

  ///The chat message its text
  const std::string m_text;
};

//Forward declarations.
//Herb Sutter. Exceptional C++. ISBN: 0-201-61562-2. Item 26: 'Never #include a header when a forward declaration will suffice'
std::ostream& operator<<(std::ostream& os,const ChatMessage& p);

} //~namespace gtst
} //~namespace ribi

#endif // CHATMESSAGE_H

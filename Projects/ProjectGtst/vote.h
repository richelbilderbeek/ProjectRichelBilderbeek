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
#ifndef PROJECTGTSTVOTE_H
#define PROJECTGTSTVOTE_H
//---------------------------------------------------------------------------
#include <iosfwd>
#include <string>
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------
///A Vote is a Participant its voted VotingOption
struct Vote
{
  Vote(
    const boost::shared_ptr<const Participant>& sender,
    const VotingOption * const vote);

  ///Obtain a read-only pointer to the sender
  const boost::shared_ptr<const Participant>& GetSender() const { return m_sender; }

  ///Obtain the chat message its text
  const VotingOption * GetVote() const { return m_vote; }

  private:
  ///\brief Only allow a Boost smart pointer to delete Vote
  ///
  ///This prevents the following trouble,
  ///cited from http://www.boost.org/libs/utility/checked_delete.html:
  ///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  ///class types to be deleted with a delete-expression.
  ///When the class has a non-trivial destructor, or a class-specific operator
  ///delete, the behavior is undefined. Some compilers issue a warning when an
  ///incomplete type is deleted, but unfortunately, not all do, and programmers
  ///sometimes ignore or disable warnings.
  ~Vote() {}
  ///Only allow a Boost smart pointer to delete Vote
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(Vote*);

  ///The ShapeWidget of the sender
  //const boost::shared_ptr<Participant> m_sender;
  const boost::shared_ptr<const Participant> m_sender;

  ///The chat message its text
  const VotingOption * const m_vote;
};
//---------------------------------------------------------------------------
//Forward declarations.
//Herb Sutter. Exceptional C++. ISBN: 0-201-61562-2. Item 26: 'Never #include a header when a forward declaration will suffice'
std::ostream& operator<<(std::ostream& os,const Vote& p);
//---------------------------------------------------------------------------
#endif // VOTE_H

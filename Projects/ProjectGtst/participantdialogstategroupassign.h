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
#ifndef PARTICIPANTDIALOGSTATEGROUPASSIGN_H
#define PARTICIPANTDIALOGSTATEGROUPASSIGN_H
//---------------------------------------------------------------------------
#include "participantdialogstate.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///The state that a Participant is or has to be assigned to a group.
///
///ParticipantDialogStateGroupAssign is the state the ParticipantDialog
///has just logged in and must be assigned a group (and thus has to
///wait), or when a period (the larger cycle) is repeated (where the
///Participant has his/her group re-assigned)
struct ParticipantDialogStateGroupAssign
  : public ParticipantDialogState, StateGroupAssign
{
  ///Create every ParticipantDialogState with a pointer to
  ///its ParticipantDialog
  ParticipantDialogStateGroupAssign(
    ParticipantDialog * const dialog,
    Server * const server);

  ///Do something random with the UI, used by DebugDialog
  void DoSomethingRandom() {}

  ///Respond to WtServerPusher
  void RespondToServerPush() {}

  ///Respond to WtTimedServerPusher
  void RespondToTimedServerPush();

  ///Change the Participant's State to this ParticipantDialogState's State
  void SetParticipantState();

  ///Show this web page
  void ShowPage(ParticipantDialog * const dialog);

  ///Represent this ParticipantDialogState as a std::string
  const std::string ToStr() const { return this->StateGroupAssign::ToStr(); }

  private:
  ///Only allow a Boost smart pointer to delete ParticipantDialogStateGroupAssign
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParticipantDialogStateGroupAssign() {}
  ///Only allow a Boost smart pointer to delete ParticipantDialogStateGroupAssign
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParticipantDialogStateGroupAssign*);

  ///The user interface
  struct Ui
  {
    Ui() : m_label_group(0), m_label_status(0) {}
    Wt::WLabel * m_label_group;
    Wt::WLabel * m_label_status;
  } ui;
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTDIALOGSTATEGROUPASSIGN_H

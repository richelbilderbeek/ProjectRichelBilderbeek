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
#ifndef PROJECTGTSTPARTICIPANTDIALOGSTATEQUIZ_H
#define PROJECTGTSTPARTICIPANTDIALOGSTATEQUIZ_H
//---------------------------------------------------------------------------
#include "participantdialogstate.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///The ParticipantDialog is in its view results group state.
struct ParticipantDialogStateQuiz
 : public ParticipantDialogState, StateQuiz
{
  ///Create every ParticipantDialogState with a pointer to
  ///its ParticipantDialog
  ParticipantDialogStateQuiz(
    ParticipantDialog * const dialog,
    Server * const server);

  ///Do something random with the UI, used by DebugDialog
  void DoSomethingRandom();

  ///Respond to WtServerPusher
  void RespondToServerPush() {}

  ///Respond to WtTimedServerPusher
  void RespondToTimedServerPush();

  ///Change the Participant's State to this ParticipantDialogState's State
  void SetParticipantState();

  ///Show this web page
  void ShowPage(ParticipantDialog * const dialog);

  ///Represent this ParticipantDialogState as a std::string
  const std::string ToStr() const { return this->StateQuiz::ToStr(); }

  private:
  ///Only allow a Boost smart pointer to delete ParticipantDialogStateQuiz
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~ParticipantDialogStateQuiz() {}
  ///Only let smart pointers delete ParticipantDialogStateQuiz
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParticipantDialogStateQuiz*);

  ///User interface of this class
  struct Ui
  {
    ///Constructor of the user interface of this class
    Ui() : m_mc_dialog(0), m_label_status(0), m_label_time_left(0) {}
    ///The multiple choice question dialog
    WtMultipleChoiceQuestionDialog * m_mc_dialog;
    ///Label showing the status
    Wt::WLabel * m_label_status;
    ///Label showing the time left
    Wt::WLabel * m_label_time_left;
  } ui;

  ///Checks if each Participant has voted already this/last round
  //Could have use lambda functions instead as well :-(
  bool GetAllParticipantsHaveVoted() const;

  ///The user clicks submit
  void OnSubmitClick();
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTDIALOGSTATEQUIZ_H


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

#ifndef PROJECTGTSTPARTICIPANTDIALOGSTATE_H
#define PROJECTGTSTPARTICIPANTDIALOGSTATE_H

#include <string>
#include <vector>

#include <boost/checked_delete.hpp>

#include <Wt/WObject>

#include "gtstforward_declarations.h"
#include "gtststate.h"


namespace ribi {
namespace gtst {

///\brief
///The state of ParticipantDialog.
///
///The State Design Pattern of the ParticipantDialog.
///ParticipantDialog is an Observer of Participant
struct ParticipantDialogState : public State, Wt::WObject
{
  ///Create every ParticipantDialogState with a pointer to
  ///its ParticipantDialog
  ParticipantDialogState(
    ParticipantDialog * const dialog,
    Server * const server);
  ParticipantDialogState(const ParticipantDialogState&) = delete;
  ParticipantDialogState& operator=(const ParticipantDialogState&) = delete;

  ///Do something random with the UI, used by DebugDialog
  virtual void DoSomethingRandom() = 0;

  ///RespondToServerPush responds to the WtServerPusher
  virtual void RespondToServerPush() = 0;

  ///RespondToServerPush responds to the WtTimedServerPusher
  virtual void RespondToTimedServerPush() = 0;

  ///ShowPage shows the webpage
  virtual void ShowPage(ParticipantDialog * const dialog) = 0;

  ///Get the ParticipantDialog
  ParticipantDialog * GetDialog();

  ///Get the ParticipantDialog, read-only
  const ParticipantDialog * GetDialog() const;

  ///Responds to the Participant his/her ParticipantState, which
  ///can be changed by the Server
  void RespondToParticipant();

  protected:
  ///Only let a smart pointer delete this ParticipantDialogState
  virtual ~ParticipantDialogState() {}
  ///Only let a smart pointer delete this ParticipantDialogState
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(ParticipantDialogState*);

  private:
  ///The dialog this state works on
  ///
  ///\note
  ///Do not change this to boost::shared_ptr<const ParticipantDialog>, because
  ///each State is constructed at the constructor of a ParticipantDialog,
  ///which requires a pointer to 'this'
  ParticipantDialog * const m_dialog;

  //Nobody logs out: he/she refreshes or has a browser crash
  void Logout();

  protected:
  Server * const m_server;

  public:
  ///\brief
  ///Converts a currency to std::string
  ///
  ///For example: 123.456789 to 123.46
  static const std::string CurrencyToStr(const double value);
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTDIALOGSTATE_H

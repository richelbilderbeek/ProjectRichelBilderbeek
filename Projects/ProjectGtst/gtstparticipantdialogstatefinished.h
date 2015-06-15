
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

#ifndef PROJECTGTSTPARTICIPANTDIALOGSTATEFINISHED_H
#define PROJECTGTSTPARTICIPANTDIALOGSTATEFINISHED_H

#include "gtstparticipantdialogstate.h"


namespace ribi {
namespace gtst {

///\brief
///ParticipantDialogStateFinished is the state the ParticipantDialog is
///in when the experiment has finished.
///
///In this state, nothing
///exciting is expected to happen.
struct ParticipantDialogStateFinished
 : public ParticipantDialogState, StateFinished
{
  ///Create every ParticipantDialogState with a pointer to
  ///its ParticipantDialog
  ParticipantDialogStateFinished(
    ParticipantDialog * const dialog,
    Server * const server);

  ///Do something random with the UI, used by DebugDialog
  void DoSomethingRandom() {}

  ///Respond to WtServerPusher
  void RespondToServerPush() {}

  ///Respond to WtTimedServerPusher
  void RespondToTimedServerPush() {}

  ///Show this web page
  void ShowPage(ParticipantDialog * const dialog);

  ///Represent this ParticipantDialogState as a std::string
  const std::string ToStr() const { return this->StateFinished::ToStr(); }

  private:
  ~ParticipantDialogStateFinished() {}
  friend void boost::checked_delete<>(ParticipantDialogStateFinished*);
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTDIALOGSTATEFINISHED_H

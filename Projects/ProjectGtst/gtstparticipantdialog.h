
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

#ifndef PROJECTGTSTPARTICIPANTDIALOG_H
#define PROJECTGTSTPARTICIPANTDIALOG_H

#include <string>


#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>

#include "gtstforward_declarations.h"
#include "wtserverpusherclient.h"
#include "wttimedserverpusherclient.h"


namespace ribi {
namespace gtst {

///\brief
///ParticipantDialog handles the user interface for a Participant.
///
///ParticipantDialog is an Observer of Participant and does
///not alter Participant itself. It does so by connecting to
///the Server.
struct ParticipantDialog
  : public Wt::WContainerWidget, WtServerPusherClient, WtTimedServerPusherClient
{
  ///Construct a ParticipantDialog and use its IP address
  ParticipantDialog(
    Server * const server,
    const SafeIpAddress * const ip_address);

  ///Check if a valid read-only pointer to the Participant can be get
  bool CanGetParticipant() const;

  ///Do something random with the UI, used by DebugDialog
  void DoSomethingRandom();

  ///Get this ParticipantDialog its IP address
  const boost::shared_ptr<const SafeIpAddress> GetIpAddress() const;

  ///Obtain a read-only pointer to the Participant
  const boost::shared_ptr<const Participant>& GetParticipant() const;

  ///Obtain the ParticipantDialogStates
  const boost::shared_ptr<const ParticipantDialogStates> GetStates() const;

  ///Assign a Participant to this ParticipantDialog
  void SetParticipant(const boost::shared_ptr<const Participant>& participant);

  ///Set the ParticipantDialogState of a ParticipantDialog
  void SetState(ParticipantDialogState * const state);

  private:
  ParticipantDialog( const ParticipantDialog& );
  const ParticipantDialog& operator=( const ParticipantDialog& );

  ~ParticipantDialog();
  friend void boost::checked_delete<>(ParticipantDialog*);

  ///The IP address this ParticipantDialog is recognized with
  boost::shared_ptr<SafeIpAddress> m_ip_address;

  ///Read-only Participant pointer, obtained from server
  boost::shared_ptr<const Participant> m_participant;

  Server * const m_server;

  ///ParticipantDialogStates manages the ParticipantDialogState instances
  boost::shared_ptr<ParticipantDialogStates> m_states;

  ///Create the start/heading/beginning of all ParticipantDialog instances
  ParticipantDialog * CreateDialogHeading();

  ///Respond to WtServerPusher
  void OnServerPush();

  ///Respond to WtTimedServerPusher
  void OnTimedServerPush();

  #ifndef NDEBUG
  struct Ui
  {
    Ui() : m_led(0) {}
    //Wt::WLabel * m_label_time_left;
    WtLedWidget * m_led;
  } m_ui;
  #endif
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTDIALOG_H

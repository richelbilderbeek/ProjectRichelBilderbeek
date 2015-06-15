
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

#ifndef PROJECTGTSTDEBUGDIALOG_H
#define PROJECTGTSTDEBUGDIALOG_H

#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>

#include "gtstforward_declarations.h"
#include "wttimedserverpusherclient.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///DebugDialog simulates an experiment visually from loading
///a parameter file
struct DebugDialog : public Wt::WContainerWidget, WtTimedServerPusherClient
{
  ///Construct a DebugDialog and use its IP address
  DebugDialog(Server * const server);
  DebugDialog(const DebugDialog&) = delete;
  DebugDialog& operator=(const DebugDialog&) = delete;

  private:
  ~DebugDialog();
  friend void boost::checked_delete<>(DebugDialog*);

  ///The collection of ParticipantDialogs
  std::vector<ParticipantDialog*> m_dialogs;

  ///The file-upload widget
  Wt::WFileUpload * m_fileupload;

  ///A status label
  Wt::WLabel * m_label_state_upload;

  Server * const m_server;

  ///Respond to WtTimedServerPusher
  void OnTimedServerPush();

  ///Respond to upload of parameter file
  void OnUploadDone();

  ///Show the DebugDialog
  void Show();

};

} //~namespace gtst
} //~namespace ribi

#endif // DEBUGDIALOG_H

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
#ifndef PROJECTGTSTDEBUGDIALOG_H
#define PROJECTGTSTDEBUGDIALOG_H
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <Wt/WContainerWidget>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
#include "wttimedserverpusherclient.h"
//---------------------------------------------------------------------------

namespace ribi {
namespace gtst {

///\brief
///DebugDialog simulates an experiment visually from loading
///a parameter file
struct DebugDialog : public Wt::WContainerWidget, WtTimedServerPusherClient
{
  ///Construct a DebugDialog and use its IP address
  DebugDialog(Server * const server);

  private:
  ///\brief Only allow a Boost smart pointer to delete DebugDialog
  ///
  ///This prevents the following trouble,
  ///cited from http://www.boost.org/libs/utility/checked_delete.html:
  ///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  ///class types to be deleted with a delete-expression.
  ///When the class has a non-trivial destructor, or a class-specific operator
  ///delete, the behavior is undefined. Some compilers issue a warning when an
  ///incomplete type is deleted, but unfortunately, not all do, and programmers
  ///sometimes ignore or disable warnings.
  ~DebugDialog();
  ///Only allow a Boost smart pointer to delete DebugDialog
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(DebugDialog*);

  ///The file-upload widget
  Wt::WFileUpload * m_fileupload;

  ///A status label
  Wt::WLabel * m_label_state_upload;

  ///The collection of ParticipantDialogs
  std::vector<ParticipantDialog*> m_dialogs;

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

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
#ifndef PROJECTGTSTADMINISTRATORDIALOGSTATELOGGEDIN_H
#define PROJECTGTSTADMINISTRATORDIALOGSTATELOGGEDIN_H

#include "gtstadministratordialogstate.h"
#include "gtstforward_declarations.h"


namespace ribi {
namespace gtst {

///\brief
///The WtAdministratorDialog its state for a logged in Administrator
struct AdministratorDialogStateLoggedIn : public AdministratorDialogState
{
  ///This AdministratorDialogState its AdministratorDialog
  AdministratorDialogStateLoggedIn(
    Server * const server,
    AdministratorDialog * const dialog);

  ///Respond to timer
  void OnTimer();

  ///Show this AdministratorDialogState its page
  void ShowPage(AdministratorDialog * const dialog);

  private:
  ~AdministratorDialogStateLoggedIn() {}
  friend void boost::checked_delete<>(AdministratorDialogStateLoggedIn* x);

  struct SafeCompile
  {
    SafeCompile(WtSelectFileDialog * const p) : m_select_file_dialog(p) {}
    boost::scoped_ptr<WtSelectFileDialog> m_select_file_dialog;
  } m_safe_compile;

  struct Ui
  {
    Ui()
      :
        m_button_group_set_phase(0),
        m_group_widget(0),
        m_fileupload(0),
        m_label_state_server(0),
        m_label_state_upload(0),
        m_server_anchor(0),
        m_server_select_file_dialog{},
        m_text_groups(0),
        m_text_parameter_file(0),
        m_text_participants(0)
    {

    }
    Wt::WButtonGroup * m_button_group_set_phase;
    WtShapeGroupWidget * m_group_widget;
    Wt::WFileUpload * m_fileupload;
    Wt::WLabel * m_label_state_server;
    Wt::WLabel * m_label_state_upload;
    Wt::WAnchor * m_server_anchor;
    WtSelectFileDialog * m_server_select_file_dialog;
    Wt::WTextArea * m_text_groups;
    Wt::WTextArea * m_text_parameter_file;
    Wt::WTextArea * m_text_participants;
  } m_ui;

  Wt::WContainerWidget * CreateStartExperimentDialog();
  Wt::WContainerWidget * CreateViewGroupsDialog();
  Wt::WContainerWidget * CreateViewParametersDialog();
  Wt::WContainerWidget * CreateViewParticipantsDialog();
  Wt::WContainerWidget * CreateViewServerDialog();

  const std::vector<std::vector<const Shape*> > ExtractShapes() const;

  ///void OnDeleteParticipants();

  ///Respond to a change in Groups
  void OnGroupsChanged();

  ///Stops the server
  void OnStopServer();

  ///Respond to the parameter file upload
  void OnUploadDone();

  ///View a log file
  void OnViewLogFile();

  ///Returns the extension of a filename
  ///Assumes that the filename has an extension
  ///From http://www.richelbilderbeek.nl/CppGetExtension.htm
  static std::string GetExtension(const std::string& filename);
};

} //~namespace gtst
} //~namespace ribi

#endif // ADMINISTRATORDIALOGSTATELOGGEDIN_H

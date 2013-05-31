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
#ifndef PROJECTGTSTADMINISTRATORDIALOGSTATELOGGEDIN_H
#define PROJECTGTSTADMINISTRATORDIALOGSTATELOGGEDIN_H
//---------------------------------------------------------------------------
#include "administratordialogstate.h"
#include "forward_declarations.h"
//---------------------------------------------------------------------------
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
  ///Only allow a Boost smart pointer to delete AdministratorDialogStateLoggedIn
  //to prevent the following trouble,
  //cited from http://www.boost.org/libs/utility/checked_delete.html:
  //The C++ StandardParticipantDialogState allows, in 5.3.5/5, pointers to incomplete
  //class types to be deleted with a delete-expression.
  //When the class has a non-trivial destructor, or a class-specific operator
  //delete, the behavior is undefined. Some compilers issue a warning when an
  //incomplete type is deleted, but unfortunately, not all do, and programmers
  //sometimes ignore or disable warnings.
  ~AdministratorDialogStateLoggedIn() {}
  ///Only allow a Boost smart pointer to delete AdministratorDialogStateLoggedIn
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(AdministratorDialogStateLoggedIn* x);

  struct Ui
  {
    Ui()
      : m_server_anchor(0),
        m_button_group_set_phase(0),
        m_group_widget(0),
        m_fileupload(0),
        m_label_state_server(0),
        m_label_state_upload(0),
        m_text_groups(0),
        m_text_parameter_file(0),
        m_text_participants(0)
    {

    }
    Wt::WAnchor * m_server_anchor;
    Wt::WButtonGroup * m_button_group_set_phase;
    WtShapeGroupWidget * m_group_widget;
    Wt::WFileUpload * m_fileupload;
    Wt::WLabel * m_label_state_server;
    Wt::WLabel * m_label_state_upload;
    Wt::WTextArea * m_text_groups;
    Wt::WTextArea * m_text_parameter_file;
    Wt::WTextArea * m_text_participants;
    WtSelectFileDialog * m_server_select_file_dialog;
  } ui;

  struct SafeCompile
  {
    boost::scoped_ptr<WtSelectFileDialog> m_select_file_dialog;
  } m_safe_compile;

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
  static const std::string GetExtension(const std::string& filename);

  ///Split an XML std::string into its parts
  //From http://www.richelbilderbeek.nl/CppSplitXml.htm
  static const std::vector<std::string> SplitXml(const std::string& s);

  ///Pretty-print an XML std::string
  //From http://www.richelbilderbeek.nl/CppXmlToPretty.htm
  static const std::vector<std::string> XmlToPretty(const std::string& s);


};
//---------------------------------------------------------------------------
#endif // ADMINISTRATORDIALOGSTATELOGGEDIN_H

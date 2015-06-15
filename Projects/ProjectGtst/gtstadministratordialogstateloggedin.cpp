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
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wcomment"
//#include <boost/filesystem.hpp>

#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WCheckBox>
#include <Wt/WFileResource>
#include <Wt/WFileUpload>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>
#include <Wt/WStackedWidget>
#include <Wt/WTextArea>

#include "fileio.h"
#include "gtstadministrator.h"
#include "gtstadministratordialog.h"
#include "gtstadministratordialogstateloggedin.h"
#include "gtstadministratordialogstateloggedin.h"
#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroup.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstresources.h"
#include "gtstserver.h"
#include "shape.h"
#include "shapewidget.h"
#include "stopwatch.h"
#include "trace.h"
#include "wtserverpusher.h"
#include "wtselectfiledialog.h"
#include "wtshapegroupwidget.h"
#include "wtshapewidget.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::gtst::AdministratorDialogStateLoggedIn::AdministratorDialogStateLoggedIn(
  Server * const server,
  AdministratorDialog * const dialog)
  : AdministratorDialogState(server,dialog),
    m_safe_compile{nullptr},
    m_ui{}

{
  m_safe_compile.m_select_file_dialog.reset(new WtSelectFileDialog);
}

Wt::WContainerWidget * ribi::gtst::AdministratorDialogStateLoggedIn::CreateStartExperimentDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  assert(dialog);

  m_ui.m_fileupload = new Wt::WFileUpload;
  m_ui.m_label_state_upload = new Wt::WLabel;

  assert(m_ui.m_fileupload);
  assert(m_ui.m_label_state_upload);

  dialog->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_label_state_upload);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_fileupload);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);

  m_ui.m_label_state_upload->setText("Please select a file to upload or press the button");

  //Upload automatically when the user entered a file
  m_ui.m_fileupload->changed().connect(
    m_ui.m_fileupload,
    &Wt::WFileUpload::upload);

  //Call WtTextUploadDialog::on_upload_done when file is uploaded
  m_ui.m_fileupload->uploaded().connect(
    this,
    &ribi::gtst::AdministratorDialogStateLoggedIn::OnUploadDone);
  return dialog;
}

Wt::WContainerWidget * ribi::gtst::AdministratorDialogStateLoggedIn::CreateViewGroupsDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  assert(dialog);

  m_ui.m_text_groups = new Wt::WTextArea;
  m_ui.m_group_widget = new WtShapeGroupWidget;

  assert(m_ui.m_text_groups);
  assert(m_ui.m_group_widget);

  dialog->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_group_widget);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_text_groups);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WImage("Groups.png",dialog);
  m_ui.m_text_groups->setReadOnly(true);
  m_ui.m_text_groups->setMinimumSize(600,200);
  m_ui.m_group_widget->resize(400,400);

  m_server->GetGroups()->m_signal_groups_changed.connect(
    boost::bind(&ribi::gtst::AdministratorDialogStateLoggedIn::OnGroupsChanged,this));
  m_ui.m_group_widget->SetShapes(ExtractShapes());

  return dialog;
}

Wt::WContainerWidget * ribi::gtst::AdministratorDialogStateLoggedIn::CreateViewParametersDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  assert(dialog);

  m_ui.m_text_parameter_file = new Wt::WTextArea;

  assert(m_ui.m_text_parameter_file);

  dialog->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(dialog);
  m_ui.m_text_parameter_file->setReadOnly(true);
  m_ui.m_text_parameter_file->setMinimumSize(600,300);
  dialog->addWidget(m_ui.m_text_parameter_file);

  return dialog;
}

Wt::WContainerWidget * ribi::gtst::AdministratorDialogStateLoggedIn::CreateViewParticipantsDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  assert(dialog);

  m_ui.m_text_participants = new Wt::WTextArea;

  assert(m_ui.m_text_participants);

  dialog->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_text_participants);
  m_ui.m_text_participants->setReadOnly(true);
  m_ui.m_text_participants->setMinimumSize(600,300);
  return dialog;
}

Wt::WContainerWidget * ribi::gtst::AdministratorDialogStateLoggedIn::CreateViewServerDialog()
{
  Wt::WContainerWidget * const dialog = new Wt::WContainerWidget;
  assert(dialog);

  m_ui.m_server_anchor = new Wt::WAnchor;
  m_ui.m_label_state_server = new Wt::WLabel;
  m_ui.m_server_select_file_dialog = new WtSelectFileDialog;

  assert(m_ui.m_label_state_server);
  assert(m_ui.m_server_select_file_dialog);

  dialog->setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_label_state_server);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_server_select_file_dialog);
  dialog->addWidget(m_ui.m_server_anchor);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  {
    Wt::WPushButton * const button = new Wt::WPushButton("Stop and update server");
    dialog->addWidget(button);
    button->clicked().connect(this,&ribi::gtst::AdministratorDialogStateLoggedIn::OnStopServer);
  }

  m_ui.m_label_state_server->setText("Server state: ... (updated automatically)");
  m_ui.m_server_select_file_dialog->setMinimumSize(600,300);
  m_ui.m_server_select_file_dialog->SetFilter(".*(\\.xml|\\.txt|\\.sh)");
  m_ui.m_server_select_file_dialog->SetFilterReadOnly(true);

  m_ui.m_server_select_file_dialog->m_signal_selected.connect(
    boost::bind(&ribi::gtst::AdministratorDialogStateLoggedIn::OnViewLogFile,this));

  return dialog;
}

const std::vector<std::vector<const ribi::Shape*> > ribi::gtst::AdministratorDialogStateLoggedIn::ExtractShapes() const
{

  std::vector<std::vector<const Shape*> > v;
  //Instead of collecting the GroupUnassigned, just add an empty group to v
  v.push_back(std::vector<const Shape*>());

  const auto groups = m_server->GetGroups()->CollectGroups(false,true,true,true);
  std::for_each(groups.begin(),groups.end(),
    [&v](const Group * const group)
    {
      std::vector<const Shape*> w;
      const std::vector<boost::shared_ptr<const Participant> > p
        = group->CollectParticipants();
      std::transform(
        p.begin(), p.end(),
        std::back_inserter(w),
        [](const boost::shared_ptr<const Participant>& i)
        {

          return i->GetChatShape()->GetWidget()->GetShape();
        }
      );
      assert(w.size() == p.size());
      v.push_back(w);
    }
  );
  return v;
}

std::string ribi::gtst::AdministratorDialogStateLoggedIn::GetExtension(const std::string& filename)
{
  const size_t i = filename.rfind('.');
  assert(i != std::string::npos && "Filename must contain a dot");
  assert(i != filename.size() - 1 && "Filename must not end with a dot");
  assert(filename[i+1] != '\\' && "Filename must have an extension");
  assert(filename[i+1] != '/' && "Filename must have an extension");
  return filename.substr(i+1,filename.size());
}

void ribi::gtst::AdministratorDialogStateLoggedIn::OnGroupsChanged()
{
  TRACE_FUNC();
  m_ui.m_group_widget->SetShapes(ExtractShapes());

  //Display textual info
  {
    std::string text;
    //First display the Group its Participants
    const auto groups = m_server->GetGroups()->CollectGroups();
    std::for_each(groups.begin(),groups.end(),
      [&text](const Group * const group)
      {
        text+=std::string("Group #")
          + std::to_string(group->GetId())
          + std::string(" (")
          + group->ToStr()
          + std::string("):\n- Participants: ");
        const auto participants = group->CollectParticipants();
        std::for_each(participants.begin(),participants.end(),
          [&text](const boost::shared_ptr<const Participant>& participant)
          {
            text
              += (participant->CanGetId()
                ? std::to_string(participant->GetId())
                : std::string("no ID"))
              + std::string(", ");
          }
        );
        if (group->CollectParticipants().empty())
        {
          text+= "no participants";
        }
        else
        {
          assert(text.size() >= 2);
          //Pop trailing ', '
          text.resize(text.size() -2);
        }
        text+="\n- Payoffs: ";
        if (!group->GetAveragePayoffs().empty())
        {
          text
            +=std::string(" (")
            + std::to_string(
              group->GetAveragePayoffs().size())
            + std::string("): ");
          const auto payoffs = group->GetAveragePayoffs();
          std::for_each(payoffs.begin(),payoffs.end(),
            [&text](const double& payoff)
            {
              text
                += std::to_string(payoff)
                + std::string(", ");
            }
          );
          text.resize(text.size() - 2);
        }
        else
        {
          text+= "no payoffs assigned";
        }
        text+="\n";
      } );

    assert(!text.empty());
    m_ui.m_text_groups->setText(text.c_str());
    TRACE_FUNC();
  }
}

///Stops the server
void ribi::gtst::AdministratorDialogStateLoggedIn::OnStopServer()
{
  Wt::WApplication::instance()->quit();
  std::exit(0);
}

///Show all automatically
void ribi::gtst::AdministratorDialogStateLoggedIn::OnTimer()
{
   
  //server->Save("server.xml");

  //Update server state
  {
    const std::string text
      = std::string("Current server state: \'")
      + m_server->GetStates()->GetCurrentState()->ToStr()
      + std::string("\' (updated automatically)");
    assert(m_ui.m_label_state_server);
    m_ui.m_label_state_server->setText(text.c_str());
  }
  //Display Parameters
  {
    std::stringstream s;
    s << (*m_server->GetParameters());
    const std::vector<std::string> v = xml::XmlToPretty(s.str());
    std::string text;
    std::for_each(v.begin(),v.end(),
      [&text](const std::string& t)
      {
        text += t + '\n';
      }
    );
    assert(!text.empty());
    text.resize(text.size() - 1);
    m_ui.m_text_parameter_file->setText(text.c_str());
  }
  //Display Participants
  {
    std::string text
      = "Number of participants: "
      + std::to_string(
        m_server->GetGroups()->CollectParticipants().size())
      + '\n';
    const auto participants = m_server->GetGroups()->CollectParticipants();
    std::for_each(participants.begin(),participants.end(),
      [&text](const boost::shared_ptr<const Participant>& participant)
      {
        text+=participant->ToAdminStr()+'\n';
      }
    );
    if (text.empty())
    {
      text = "[No participants]";
    }
    else
    {
      //Pop trailing newline
      text.resize(text.size() - 1);
    }
     m_ui.m_text_participants->setText(text.c_str());
  }
}

void ribi::gtst::AdministratorDialogStateLoggedIn::ShowPage(AdministratorDialog * const dialog)
{
  assert(dialog);
  assert(IsLoggedIn() && "Assume a logged in administrator");

  new Wt::WLabel("Welcome administrator",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);

  //Menu
  {
    Wt::WStackedWidget * const contents = new Wt::WStackedWidget;
    Wt::WMenu * const menu = new Wt::WMenu(contents,Wt::Horizontal,dialog);
    //Using CSS styleclass is the best (only?) way to display the menu well
    menu->setStyleClass("menu");
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Start",
        CreateStartExperimentDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Groups",
        CreateViewGroupsDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Parameters",
        CreateViewParametersDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Participants",
        CreateViewParticipantsDialog());
      menu->addItem(item);
    }
    {
      Wt::WMenuItem * const item = new Wt::WMenuItem(
        "Server",
        CreateViewServerDialog());
      menu->addItem(item);
    }
    dialog->addWidget(contents);
  }
}

void ribi::gtst::AdministratorDialogStateLoggedIn::OnUploadDone()
{

  assert(fileio::FileIo().IsRegularFile(m_ui.m_fileupload->spoolFileName()));
  //Display parameter file
  {
    const std::vector<std::string> v = fileio::FileIo().FileToVector(m_ui.m_fileupload->spoolFileName());
    std::string text;
    std::for_each(v.begin(),v.end(),[&text](const std::string& s) { text+=(s+'\n'); } );
    //Pop trailing newline
    text.resize(text.size() - 1);
    assert(m_ui.m_text_parameter_file);
    m_ui.m_text_parameter_file->setText(text.c_str());
  }

  boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
  assert(parameters);
  try
  {
    assert(fileio::FileIo().IsRegularFile(m_ui.m_fileupload->spoolFileName()));
    parameters->ReadFromFile(m_ui.m_fileupload->spoolFileName());
  }
  catch (std::runtime_error& e)
  {
    m_ui.m_label_state_upload->setText(e.what());
    return;
  }

  m_ui.m_label_state_upload->setText("OK: parameter file loaded");
  m_server->SetParameters(parameters);

  WtServerPusher::GetInstance()->Post();
}

void ribi::gtst::AdministratorDialogStateLoggedIn::OnViewLogFile()
{
  const std::string filename = m_ui.m_server_select_file_dialog->GetSelectedFile();

  m_ui.m_server_anchor->setText((std::string("Download ") + m_ui.m_server_select_file_dialog->GetSelectedFile()).c_str() );
  m_ui.m_server_anchor->setResource(new Wt::WFileResource(m_ui.m_server_select_file_dialog->GetSelectedFile(),m_ui.m_server_select_file_dialog->GetSelectedFile()));
}

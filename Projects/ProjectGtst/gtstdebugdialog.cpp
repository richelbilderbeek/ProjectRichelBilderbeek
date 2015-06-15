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
#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wcomment"
#include <Wt/WBreak>
#include <Wt/WFileUpload>
#include <Wt/WGroupBox>
#include <Wt/WLabel>

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstdebugdialog.h"
#include "gtstgroups.h"
#include "ipaddress.h"
#include "gtstlogfile.h"
#include "gtstparticipantdialog.h"
#include "ipaddress.h"
#include "gtstserver.h"
#include "stopwatch.h"
#include "wttimedserverpusher.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

ribi::gtst::DebugDialog::DebugDialog(Server * const server)
  : m_dialogs{},
    m_fileupload{},
    m_label_state_upload{},
    m_server(server)
{
  assert(m_server);
  Show();
}

ribi::gtst::DebugDialog::~DebugDialog()
{

}

///Do something random to the dialog
void ribi::gtst::DebugDialog::OnTimedServerPush()
{
  std::for_each(m_dialogs.begin(),m_dialogs.end(),
    [](ParticipantDialog* dialog) { dialog->DoSomethingRandom(); }
  );
}

void ribi::gtst::DebugDialog::OnUploadDone()
{
  boost::shared_ptr<Parameters> parameters(new Parameters(m_server));
  assert(parameters);
  try
  {
    parameters->ReadFromFile(m_fileupload->spoolFileName());
  }
  catch (std::runtime_error& e)
  {
    m_label_state_upload->setText(e.what());
    return;
  }

  m_label_state_upload->setText("OK: parameter file loaded");
  m_server->Reset();
  m_server->SetParameters(parameters);

  //Create the Participant dialogs

  ///Remove all ParticipantDialogs from Wt::WContainerWidget and std::vector
  this->clear();
  m_dialogs.resize(0);

  const int n_participants = m_server->GetGroups()->CollectParticipants().size();

  //Display the dialogs in a random order
  std::vector<int> indices(n_participants);
  std::iota(indices.begin(),indices.end(),0);
  std::random_shuffle(indices.begin(),indices.end());

  for (int dialog_index=0; dialog_index!=n_participants; ++dialog_index)
  {
    const int i = indices[dialog_index];
    std::string ip_address_str
      = "000.000.000."
      + std::to_string(i);
    boost::scoped_ptr<SafeIpAddress> ip_address(
      new SafeIpAddress(ip_address_str));
    ParticipantDialog* const dialog = new ParticipantDialog(m_server,ip_address.get());
    m_dialogs.push_back(dialog);

    Wt::WGroupBox * const box = new Wt::WGroupBox;
    box->addWidget(dialog);
    addWidget(new Wt::WBreak);
    addWidget(new Wt::WBreak);
    addWidget(box);
  }
}

void ribi::gtst::DebugDialog::Show()
{
  this->clear();

  m_fileupload = new Wt::WFileUpload;
  m_label_state_upload = new Wt::WLabel;

  assert(m_fileupload);
  assert(m_label_state_upload);

  setContentAlignment(Wt::AlignCenter);
  new Wt::WBreak(this);
  addWidget(m_label_state_upload);
  new Wt::WBreak(this);
  new Wt::WBreak(this);
  addWidget(m_fileupload);

  m_label_state_upload->setText("Please select a file to upload or press the button");

  //Upload automatically when the user entered a file
  m_fileupload->changed().connect(
    m_fileupload,
    &Wt::WFileUpload::upload);

  //Call OnUploadDone when file is uploaded
  m_fileupload->uploaded().connect(
    this,
    &ribi::gtst::DebugDialog::OnUploadDone);
}


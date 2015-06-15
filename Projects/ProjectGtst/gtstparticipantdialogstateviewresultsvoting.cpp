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
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WTextArea>

#include "gtstall_groups.h"
#include "gtstall_serverstates.h"
#include "gtstgroups.h"
#include "gtststate.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstateviewresultsvoting.h"
#include "gtstserverstates.h"
#include "shape.h"
#include "shapewidget.h"
//#include "trace.h"
#include "gtstvote.h"
#include "gtstvotingoption.h"
#include "wtserverpusher.h"
#include "wtshapewidget.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateViewResultsVoting::ParticipantDialogStateViewResultsVoting(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}

void ribi::gtst::ParticipantDialogStateViewResultsVoting::RespondToTimedServerPush()
{
  assert(GetDialog()->CanGetParticipant()
    && "Assume that only existing participants can have finished an experiment");

  const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();

  //Update label_time_left
  {
    const std::string text
    =  std::string("Time left: ")
    + std::to_string(time_left)
    + std::string(" seconds ");
    assert(ui.m_label_time_left);
    ui.m_label_time_left->setText(text.c_str());
  }

  ///Follow the server its tempo
  RespondToParticipant();
}

void ribi::gtst::ParticipantDialogStateViewResultsVoting::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->GetParticipant());
  const auto participant = GetDialog()->GetParticipant();
  assert(participant);
  const auto group = m_server->GetGroups()->FindMyGroup(participant);
  assert(group);

  ui.m_label_time_left = new Wt::WLabel;

  dialog->addWidget(new Wt::WLabel("Voting results"));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(ui.m_label_time_left);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel(
    (
        std::string("You are in group #")
      + std::to_string(group->GetId())
    ).c_str()));


  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  Wt::WTable * const table = new Wt::WTable(dialog);

  ServerStateViewResultsVoting * const server_state
    = dynamic_cast<ServerStateViewResultsVoting*>(m_server->GetStates()->GetCurrentState());
  if (!server_state)
  {
    std::clog << __func__ << ": warning: no ServerStateViewResultsVoting\n";
    return;
  }

  const auto votes = server_state->GetGroupResults(participant);
  std::for_each(votes.begin(),votes.end(),
    [&table,participant](const boost::shared_ptr<Vote>& vote)
    {
      assert(vote);
      assert(vote->GetSender());
      assert(vote->GetSender()->GetChatShape());
      table->insertRow(0);
      table->elementAt(0,0)->addWidget(new Wt::WText("Participant "));
      table->elementAt(0,1)->addWidget(vote->GetSender()->GetChatShape()->Clone());
      table->elementAt(0,2)->addWidget(
        new Wt::WText( (std::string("voted for "
          + vote->GetVote()->GetDescription())).c_str()));

       if (vote->GetSender() == participant)
       {
         table->elementAt(0,3)->addWidget(new Wt::WText("your vote"));
       }
     }
  );

  const auto i = server_state->GetVotedOptions().find(group);
  assert(i!=server_state->GetVotedOptions().end());
  assert((*i).first == group);

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  {
    const std::string s
      = std::string("As a result of the voting, your group will hire ")
      + ((*i).second ? (*i).second->GetDescription() : "no supervisor");
    dialog->addWidget(new Wt::WLabel(s.c_str()));
  }
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  {
    const std::string s
      = std::string("In each round of this period, all members of your group will automatically pay ")
      + CurrencyToStr((*i).second ? (*i).second->GetCost() : 0.0)
      + std::string(" points for this");
    dialog->addWidget(new Wt::WLabel(s.c_str()));
  }
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  {
    const double p = ((*i).second ? (*i).second->GetChance() : 0.0);
    assert(p >= 0.0);
    assert(p <= 1.0);
    if (p == 0.0)
    {

      dialog->addWidget(new Wt::WLabel("In each round of this period,"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WLabel("all members of your group that do not contribute to the group project"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WLabel("will receive a share of the group revenue"));
    }
    else if (p == 1.0)
    {
      dialog->addWidget(new Wt::WLabel("In each round of this period,"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WLabel("all members of your group that do not contribute to the group project"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("will <b>not</b> receive a share of the group revenue"));
    }
    else
    {
      dialog->addWidget(new Wt::WLabel("In each round of this period,"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WLabel("all members of your group that do not contribute to the group project"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WLabel("will receive a share of the group revenue"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("<b>with a chance of {1}%</b>").arg(
        CurrencyToStr(p))));
    }
  }
}


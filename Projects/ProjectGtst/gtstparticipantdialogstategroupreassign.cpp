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
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WTable>
#include <Wt/WText>

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroup.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstate.h"
#include "gtstparticipantdialogstatechat.h"
#include "gtstparticipantdialogstategroupassign.h"
#include "gtstparticipantdialogstategroupreassign.h"
#include "gtstpayoff.h"
#include "gtstpayoffs.h"
#include "gtstserver.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "trace.h"
#include "wtserverpusher.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateGroupReAssign::ParticipantDialogStateGroupReAssign(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}

void ribi::gtst::ParticipantDialogStateGroupReAssign::RespondToTimedServerPush()
{
  assert(GetDialog()->CanGetParticipant()
    && "Assume that only existing participants can have their payoffs assigned");

  //Update label_time_left
  {
    const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();
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

void ribi::gtst::ParticipantDialogStateGroupReAssign::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->CanGetParticipant()
    && "A Participant must be logged in in this state");

  const boost::shared_ptr<const Participant>& participant = dialog->GetParticipant();
  assert(GetDialog()->GetParticipant()->CanGetId()
    && "A Participant must be assigned an ID before entering this state");

  const auto payoffs = participant->GetPayoffs();

  const Group * const group = m_server->GetGroups()->FindMyGroup(participant);
  assert(group);

  //Create the widget(s)
  ui.m_label_status = new Wt::WLabel;
  ui.m_label_time_left = new Wt::WLabel;

  //Check the widget(s)
  assert(ui.m_label_status);
  assert(ui.m_label_time_left);

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel("Group re-assign"));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(ui.m_label_time_left);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel("This is the end of this period"));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel(
    (std::string("You are in group #")
    + std::to_string(group->GetId())).c_str()));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel(
    (std::string("Your earnings in this period are ")
      + CurrencyToStr(payoffs->GetLast()->m_payoff)
      + std::string(" points")).c_str()));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel(
    (std::string("Your total earnings are ")
      + CurrencyToStr(payoffs->GetTotal())
      + std::string(" points")).c_str()));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WLabel("Group average earnings:"));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  Wt::WTable * table = new Wt::WTable(dialog);
  const auto groups = m_server->GetGroups()->CollectGroups(false,false,true,false);
  std::for_each(groups.begin(),groups.end(),
    [&dialog,&table,this,group](const Group* const any_group)
    {
      assert(!any_group->GetAveragePayoffs().empty());
      table->insertRow(0);

      table->elementAt(0,0)->addWidget(new Wt::WText(
        Wt::WString("Group {1}").arg(any_group->GetId())));

      table->elementAt(0,1)->addWidget(new Wt::WText(
        Wt::WString("{1} points").arg(
          this->CurrencyToStr(any_group->GetAveragePayoffs().back()))));

      if (any_group == group)
      {
        table->elementAt(0,2)->addWidget(new Wt::WText("your group"));
      }
    }
  );


  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  ServerStateGroupReAssign * const server_state
    = dynamic_cast<ServerStateGroupReAssign*>(m_server->GetStates()->GetCurrentState());
  if (!server_state)
  {
    std::clog << __func__ << ": warning: no ServerStateGroupReAssign\n";
    return;
  }

  const auto p = server_state->GetWorstAndBestGroup();
  if (group == p.first)
  {
    //Worst
    if (p.second->GetSize() == 5)
    {
      dialog->addWidget(new Wt::WText("Your group has the lowest average earnings in this period"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("and has been selected to <b>be eliminated from the experiment</b>"));
    }
    else
    {
      dialog->addWidget(new Wt::WText(Wt::WString("Group {1} has the highest average earnings in this period and has been selected to grow").arg(p.first->GetId())));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("This group grows from 3 to 5 members.")));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("Your group <b>remains the same</b>")));
    }
  }
  else if (group == p.second)
  {
    if (group->GetSize() == 5)
    {
      dialog->addWidget(new Wt::WText("Your group has the highest average earnings in this period"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("and has been selected to <b>grow and split</b> into two groups."));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("Your group first grows from 5 to 6 members, and then splits into two groups of three members."));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("Your group in the next period will be one of those two groups"));
    }
    else
    {
      dialog->addWidget(new Wt::WText("Your group has the highest average earnings in this period and has been selected to <b>grow</b>"));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("Your group grows from 3 to 5 members"));
    }
  }
  else
  {
    if (p.second->GetSize() == 3)
    {
      //Best group grows
      dialog->addWidget(new Wt::WText(Wt::WString("Group {1} has the highest average earnings in this period and has been selected to grow").arg(p.first->GetId())));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("This group grows from 3 to 5 members.")));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("Your group <b>remains the same</b>")));
    }
    else
    {
      //Best group splits, worst dies
      dialog->addWidget(new Wt::WText(Wt::WString("Group {1} has the highest average earnings in this period").arg(p.second->GetId())));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("and has been selected to grow and split into two groups."));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("Group {1} has the lowest average earnings in this period").arg(p.first->GetId())));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText("and has been selected to be eliminated from the experiment."));
      dialog->addWidget(new Wt::WBreak);
      dialog->addWidget(new Wt::WText(Wt::WString("Your group <b>remains the same</b>")));
    }
  }

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  if (group == p.first && p.second->GetSize() == 5)
  {
    //A dead Participant :3
    dialog->addWidget(new Wt::WLabel("For you, this experiment ends now"));
  }
  else
  {
    //A survivor
    #define TEMP_DEBUG_215487632492487527652376428
    #ifdef TEMP_DEBUG_215487632492487527652376428
    if(!dynamic_cast<const PayoffReAssign*>(payoffs->GetLast().get()))
    {
      TRACE(group->GetId());
      TRACE(participant->GetId());
    }
    #endif
    assert(dynamic_cast<const PayoffReAssign*>(payoffs->GetLast().get()));
    dialog->addWidget(new Wt::WLabel(
      Wt::WString("You earn {1} points for reaching the next period").arg(
        CurrencyToStr(payoffs->GetLast()->m_payoff))));
  }

}


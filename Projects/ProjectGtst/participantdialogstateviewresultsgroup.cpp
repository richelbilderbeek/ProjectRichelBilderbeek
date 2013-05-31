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
#include <cassert>
#include <fstream>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WTextArea>
//---------------------------------------------------------------------------
#include "all_groups.h"
#include "all_serverstates.h"
#include "chooseactionoption.h"
#include "groups.h"
#include "payoff.h"
#include "payoffs.h"
#include "state.h"
#include "serverstates.h"
#include "logfile.h"
#include "participant.h"
#include "repeatassigner.h"
#include "stopwatch.h"
#include "server.h"
#include "participantdialog.h"
#include "participantdialogstateviewresultsgroup.h"
#include "shape.h"
#include "shapewidget.h"
#include "wtserverpusher.h"
#include "wtshapewidget.h"
//---------------------------------------------------------------------------
ParticipantDialogStateViewResultsGroup::ParticipantDialogStateViewResultsGroup(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server)
{

}
//---------------------------------------------------------------------------
void ParticipantDialogStateViewResultsGroup::RespondToTimedServerPush()
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
//---------------------------------------------------------------------------
void ParticipantDialogStateViewResultsGroup::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);

  const boost::shared_ptr<const Participant>& participant = dialog->GetParticipant();
  assert(participant);

  ui.m_label_time_left = new Wt::WLabel;

  dialog->addWidget(
    new Wt::WLabel(
      Wt::WString("Results of round {1} of this period").arg(
        this->m_server->GetStates()->GetCurrentState()->GetPeriod())
    )
  );
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(ui.m_label_time_left);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  //assert(!participant->GetPayoffs().empty()
  const Group * const group = m_server->GetGroups()->FindMyGroup(participant);


  dialog->addWidget(new Wt::WLabel(
    (std::string("You are in group #")
    + std::to_string(
      m_server->GetGroups()->FindMyGroup(participant)->GetId())).c_str()));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  if (!participant->GetPayoffs()->IsEmpty())
  {
    dialog->addWidget(new Wt::WLabel(
      (std::string("Your earnings from the previous round are ")
      + CurrencyToStr(participant->GetPayoffs()->GetLast()->m_payoff)
      + std::string(" points")).c_str()));
    dialog->addWidget(new Wt::WBreak);
    dialog->addWidget(new Wt::WLabel(
      (std::string("Your total earnings are ")
      + CurrencyToStr(participant->GetPayoffs()->GetTotal())
      + std::string(" points")).c_str()));
  }
  else
  {
    dialog->addWidget(new Wt::WLabel(
      "Your earnings in the last cycle are none"));
  }

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);

  Wt::WTable * const table = new Wt::WTable(dialog);

  const auto ps = group->CollectParticipants();
  std::for_each(ps.begin(),ps.end(),
    [&table,participant](const boost::shared_ptr<const Participant>& other)
    {
      if (!other->GetPayoffs()->IsEmpty())
      {
        table->insertRow(0);
        table->elementAt(0,0)->addWidget(new Wt::WText("Player"));
        table->elementAt(0,1)->addWidget(other->GetChatShape()->Clone());
        const boost::shared_ptr<const Payoff> last_payoff_base = other->GetPayoffs()->GetLast();
        const PayoffIpgg * payoff = dynamic_cast<const PayoffIpgg*>(last_payoff_base.get());
        assert(payoff);


        table->elementAt(0,2)->addWidget(new Wt::WText(
           (payoff->m_did_contribute
           ? std::string("did contribute")
           : std::string("did not contribute")).c_str()));
        if (participant == other)
        {
          std::string s;
          if (!payoff->m_did_contribute)
          {
            if (payoff->m_did_get_caught)
            {
              s = "the supervisor did take your share of the revenue";
            }
            else
            {
              s = "the supervisor did not take your share of the revenue";
            }
          }
          table->elementAt(0,3)->addWidget(new Wt::WText(s.c_str()));
        }
        else
        {
          std::string s;
          if (!payoff->m_did_contribute)
          {
            if (payoff->m_did_get_caught)
            {
              s = "the supervisor did take the share of the revenue of this player";
            }
            else
            {
              s = "the supervisor did not take the share of the revenue of this player";
            }
          }
          table->elementAt(0,3)->addWidget(new Wt::WText(s.c_str()));
        }
        if (participant == other)
        {
          table->elementAt(0,4)->addWidget(new Wt::WText("this is you"));
        }
      }
    }
  );
}
//---------------------------------------------------------------------------

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

#include <Wt/WBreak>
#include <Wt/WLabel>

#include "all_groups.h"
#include "all_parameters.h"
#include "all_serverstates.h"
#include "groups.h"
#include "logfile.h"
#include "participant.h"
#include "payoff.h"
#include "payoffs.h"
#include "state.h"
#include "stopwatch.h"
#include "participantdialog.h"
#include "participantdialogstate.h"
#include "participantdialogstatefinished.h"
#include "server.h"
#include "wtserverpusher.h"

ribi::gtst::ParticipantDialogStateFinished::ParticipantDialogStateFinished(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server)
{

}

void ribi::gtst::ParticipantDialogStateFinished::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog());
  assert(GetDialog()->GetParticipant());
  assert(m_server->GetParameters());
  assert(m_server->GetParameters()->GetFinished());

  const double total_payoff = dialog->GetParticipant()->GetPayoffs()->GetTotal();
  const double earnings
    = m_server->GetParameters()->GetFinished()->CalculateEarnings(total_payoff);

  dialog->addWidget(new Wt::WBreak);
  //Display the status message
  dialog->addWidget(
    new Wt::WLabel(
      m_server->GetParameters()->GetFinished()->GetMessage().c_str()));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(
    new Wt::WLabel(
      std::string("You have obtained a total payoff of ")
      + CurrencyToStr(total_payoff)));
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(
    new Wt::WLabel(
      std::string("You have earned ")
      + CurrencyToStr(
        earnings)
      + " euros"));

}


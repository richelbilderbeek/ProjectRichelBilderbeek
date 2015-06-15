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
#include "gtstparticipant.h"
#include "gtstparticipantstateassignpayoff.h"
#include "gtstpayoff.h"
#include "gtstpayoffs.h"

ribi::gtst::ParticipantStateAssignPayoff::ParticipantStateAssignPayoff(
  Participant * const participant,
  Server * const server)
  : ParticipantState(participant,server)
{

}

const std::string ribi::gtst::ParticipantStateAssignPayoff::ToAdminStr() const
{
  const Participant * const participant = GetParticipant();
  std::string s
    = std::to_string(participant->GetId())
    + std::string(": ");
  const auto payoffs = participant->GetPayoffs();
  if (payoffs->IsEmpty())
  {
    s+="no payoffs assigned";
    return s;
  }
  else
  {
    s +=std::to_string(payoffs->GetSize())
      + std::string(" payoffs, last: ")
      + std::to_string(payoffs->GetLast()->m_payoff);
  }
  return s;
}


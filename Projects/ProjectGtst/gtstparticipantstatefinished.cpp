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
#include "gtstall_groups.h"
//#include "gtstall_serverstates.h"
#include "gtstall_parameters.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstserver.h"
#include "gtstparticipant.h"
#include "gtstparticipantstatefinished.h"
#include "gtstpayoffs.h"
#include "stopwatch.h"
#include "wtserverpusher.h"

ribi::gtst::ParticipantStateFinished::ParticipantStateFinished(
  Participant * const participant,Server * const server)
  : ParticipantState(participant,server)
{

}

const std::string ribi::gtst::ParticipantStateFinished::ToAdminStr() const
{
  assert(GetParticipant());

  const Participant * const participant = GetParticipant();
  std::string s
    = std::to_string(participant->GetId())
    + std::string(": ")
    + this->ToStr()
    + std::string(": earnings: ")
    + std::to_string(
        m_server->GetParameters()->GetFinished()->CalculateEarnings(
        participant->GetPayoffs()->GetTotal()))
    + std::string(" euros");
  return s;
}


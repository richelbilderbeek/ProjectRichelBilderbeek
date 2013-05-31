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
 
//---------------------------------------------------------------------------
#include "all_groups.h"
//#include "all_serverstates.h"
#include "all_parameters.h"
#include "groups.h"
#include "logfile.h"
#include "server.h"
#include "participant.h"
#include "participantstatefinished.h"
#include "payoffs.h"
#include "stopwatch.h"
#include "wtserverpusher.h"
//---------------------------------------------------------------------------
ParticipantStateFinished::ParticipantStateFinished(
  Participant * const participant,Server * const server)
  : ParticipantState(participant,server)
{

}
//---------------------------------------------------------------------------
const std::string ParticipantStateFinished::ToAdminStr() const
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
//---------------------------------------------------------------------------

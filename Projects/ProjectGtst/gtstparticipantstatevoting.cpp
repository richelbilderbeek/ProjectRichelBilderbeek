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
#include "gtstparticipantstatevoting.h"
#include "gtstvotingoption.h"

ribi::gtst::ParticipantStateVoting::ParticipantStateVoting(
  Participant * const participant,Server * const server)
  : ParticipantState(participant,server)
{

}

const std::string ribi::gtst::ParticipantStateVoting::ToAdminStr() const
{
 const Participant * const participant = GetParticipant();

  std::string s
    = std::to_string(participant->GetId())
    + std::string(": ")
    + this->ToStr()
    + std::string(": ");
  if (!participant->GetVotes().empty())
  {
    for(const boost::shared_ptr<VotingOption>& i: participant->GetVotes())
    {
      s+=i->GetDescription()+",";
    }
    s.resize(s.size() - 1);
    s += std::string("(")
      + std::to_string(participant->GetVotes().size())
      + std::string(")");
  }
  else
  {
    s+="no votes";
  }
  return s;
}



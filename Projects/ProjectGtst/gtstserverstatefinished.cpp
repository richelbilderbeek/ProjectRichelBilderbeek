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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/bounds.hpp>

#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroup.h"
#include "gtstgroupfinished.h"
#include "gtstgrouploggedin.h"
#include "gtstgroupnotloggedin.h"
#include "gtstgroupparticipating.h"
#include "gtstgroups.h"
#include "gtststate.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstparticipant.h"
#include "stopwatch.h"
#include "gtstserver.h"
#pragma GCC diagnostic pop

ribi::gtst::ServerStateFinished::ServerStateFinished(
  Server * const server, const int period, const int cycle)
  : ServerState(server,period,cycle)
{

}

///Check if this state can go to the next state.
bool ribi::gtst::ServerStateFinished::CanGoToNextState() const
{
  return false;
}

///Obtain the duration of the state in seconds
int ribi::gtst::ServerStateFinished::GetStateDuration() const
{
  return boost::numeric::bounds<int>::highest();
}

void ribi::gtst::ServerStateFinished::OnTimer()
{
  //Do exactly nothing
}

void ribi::gtst::ServerStateFinished::Start()
{
  for(
    const boost::shared_ptr<const Participant>& p:
    this->GetServer()->GetGroups()->CollectParticipants())
  {
    FindParticipant(p)->SetState(new StateFinished);
  }

  GetServer()->GetGroups()->MoveAllToFinished();
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateFinished& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    //<< s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}


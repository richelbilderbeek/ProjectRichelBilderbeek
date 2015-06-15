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
#include <iostream>

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
#include "gtstgroupassigner.h"
#include "gtstgroups.h"
#include "gtststate.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "stopwatch.h"
#include "gtstserver.h"
//#include "trace.h"
#pragma GCC diagnostic pop

ribi::gtst::ServerStateGroupAssign::ServerStateGroupAssign(
  Server * const server, const int period, const int cycle)
  : ServerState(server,period,cycle)
{

}

///Check if this state can go to the next state.
void ribi::gtst::ServerStateGroupAssign::AssignGroup(const boost::shared_ptr<const Participant>& participant) const
{
  const GroupAssigner * const assigner = participant->GetGroupAssigner();
  assert(assigner);
  if (const GroupAssignerPredetermined * const p
    = dynamic_cast<const GroupAssignerPredetermined*>(assigner))
  {
    const Group * const group_from
      = this->GetServer()->GetGroups()->FindMyGroup(participant);

    const std::vector<const Group*> groups
      = this->GetServer()->GetGroups()->CollectGroups();

    const int group_to_index = p->GetGroup();

    //const Group * const group_to
    //  = *std::find_if(groups.begin(),groups.end(),
    //    boost::bind(&Group::GetId,boost::lambda::_1) == group_to_index);
    const Group * const group_to
      = *std::find_if(groups.begin(),groups.end(),
        [group_to_index](const Group * const i) { return  i->GetId() == group_to_index; } );

    //Transfer the Particippayoffsant
    FindGroup(group_to)->AddParticipant(
      FindGroup(group_from)->RemoveParticipant(participant));


    //Log group assignment
    m_server->GetLog()->LogAssignGroup(group_to,participant);
  }
  else
  {
    assert(!"?Should not get here?");
  }
}

///Check if the Participant can be assigned to a group.
bool ribi::gtst::ServerStateGroupAssign::CanAssignGroup(
  const boost::shared_ptr<const Participant>& participant) const
{
  //Sure, any logged-in Participant can be assigned to a group
  return GetServer()->GetGroups()->GetGroupLoggedIn()->IsMember(participant);
}

///Check if this state can go to the next state.
///ServerStateGroupAssign can only go to the next state if
///- all Participants have had their IP addresses assigned
bool ribi::gtst::ServerStateGroupAssign::CanGoToNextState() const
{
  assert(GetServer());
  assert(GetServer()->GetParameters());

  return
    //Nobody must be not logged in
    GetServer()->GetGroups()->CollectParticipants(true,false,false,false).empty()
    //Somebody must be logged in or participating
    && !GetServer()->GetGroups()->CollectParticipants(false,true,true,false).empty();
}

///Obtain the duration of the state in seconds
int ribi::gtst::ServerStateGroupAssign::GetStateDuration() const
{
  return boost::numeric::bounds<int>::highest();
}

void ribi::gtst::ServerStateGroupAssign::OnTimer()
{
  if (CanGoToNextState())
  {
    GetServer()->GetGroups()->MoveLoggedInToParticipating();
    GoToNextState();
  }
}

void ribi::gtst::ServerStateGroupAssign::Start()
{
  assert(GetServer());
  assert(GetServer()->GetGroups());

  //Set the state of the participants
  const auto ps = GetServer()->GetGroups()->CollectParticipants(false,false,true,false);
  std::for_each(ps.begin(),ps.end(),
    [this](const boost::shared_ptr<const Participant>& p)
    {
      const StateGroupAssign * const state
        = dynamic_cast<const StateGroupAssign*>(this);
      assert(state);
      this->FindParticipant(p)->SetState(state);
    }
  );
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateGroupAssign& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    //<< s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}


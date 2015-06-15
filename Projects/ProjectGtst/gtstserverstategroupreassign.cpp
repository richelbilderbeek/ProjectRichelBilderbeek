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
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

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
#include "gtstparticipantstate.h"
#include "gtstparticipantstateloggedin.h"
#include "gtstparticipantstategroupreassign.h"
#include "gtstpayoff.h"
#include "gtstpayoffs.h"
#include "gtstrepeatassigner.h"
#include "stopwatch.h"
#include "gtstserver.h"
#pragma GCC diagnostic pop

ribi::gtst::ServerStateGroupReAssign::ServerStateGroupReAssign(
  Server * const server, const int period, const int cycle,
  const boost::shared_ptr<const ParametersGroupReAssign>& parameters)
  : ServerState(server,period,cycle),
    m_group_payoffs{},
    m_parameters(parameters),
    m_worst_and_best_group{}
{

}

///Check if this state can go to the next state.
void ribi::gtst::ServerStateGroupReAssign::AssignGroup(const boost::shared_ptr<const Participant>& participant) const
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

    const Group * const group_to = *std::find_if(groups.begin(),groups.end(),
      [group_to_index](const Group* group) { return group->GetId() == group_to_index; } );

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

bool ribi::gtst::ServerStateGroupReAssign::CanAssignGroup(
  const boost::shared_ptr<const Participant>& participant) const
{
  //Sure, any logged-in Participant can be assigned to a group
  return GetServer()->GetGroups()->GetGroupLoggedIn()->IsMember(participant);
}

bool ribi::gtst::ServerStateGroupReAssign::CanGoToNextState() const
{
  return GetTimeLeft() < 0;
}

double ribi::gtst::ServerStateGroupReAssign::CalculateAveragePayoff() const
{
  const int n_ipgg_cycles = GetServer()->GetStates()->GetCycles(GetServer()->GetStates()->GetCurrentState()->GetPeriod());


  double average_payoff = 0.0;
  int n_active_participants = 0;
  const std::vector<const Group *> groups_active = GetServer()->GetGroups()->CollectGroups(false,false,true,false);
  std::for_each(groups_active.begin(),groups_active.end(),
    [this,&average_payoff,&n_active_participants,n_ipgg_cycles](const Group * const group)
    {
      ///Sum the payoff
      const std::vector<boost::shared_ptr<const Participant> > w = group->CollectParticipants();
      std::for_each(w.begin(),w.end(),
        [&average_payoff,&n_active_participants,n_ipgg_cycles](const boost::shared_ptr<const Participant>& p)
        {
          average_payoff += p->GetPayoffs()->GetLast(n_ipgg_cycles);
          ++n_active_participants;
        }
      );
    }
  );

  ///Average the payoff
  if (n_active_participants != 0) average_payoff /= boost::numeric_cast<double>(n_active_participants);

  return average_payoff;
}

int ribi::gtst::ServerStateGroupReAssign::GetStateDuration() const
{
  return m_parameters->GetDuration();
}

const std::pair<const ribi::gtst::Group *,const ribi::gtst::Group *>
  ribi::gtst::ServerStateGroupReAssign::CalculateWorstAndBestGroup() const
{
  assert(m_group_payoffs.size() >= 2);

  const auto ps = std::minmax_element(m_group_payoffs.begin(),m_group_payoffs.end(),
    [](const std::pair<const Group *,double>& lhs,const std::pair<const Group *,double>& rhs)
    {
      return rhs.second > lhs.second;
    }
  );
  const std::pair<const Group *,const Group *> p
    = std::make_pair((*ps.first).first,(*ps.second).first);

  assert(p.first != p.second);
  return p;
}

///Let this one Group split from 3 Participants
///to 5 Participants
void ribi::gtst::ServerStateGroupReAssign::NotifyGroupGrowth(const Group * const group) const
{
  GetServer()->GetGroups()->GrowGroup(group);
}

///Let this one Group split from 5 Participants
///to two Groups of 3 Participants
void ribi::gtst::ServerStateGroupReAssign::NotifyGroupSplit(const Group * const group) const
{
  GetServer()->GetGroups()->SplitGroup(group);
}

///Kill the Group
void ribi::gtst::ServerStateGroupReAssign::NotifyKillGroup(const Group * const group) const
{
  GetServer()->GetGroups()->KillGroup(group);
}

void ribi::gtst::ServerStateGroupReAssign::OnTimer()
{
  if (CanGoToNextState())
  {
    //Actually move the Participants
    const Group * const most_successful_group = m_worst_and_best_group.second;
    //Get the group size of the group with the highest payoffs
    const int group_size = most_successful_group->GetSize();

    if (group_size == 3)
    {
      std::clog << "A group of size 3 grows to 5!\n";
      NotifyGroupGrowth(most_successful_group);
    }
    else if (group_size == 5)
    {
      std::clog << "A group of size 5 splits!\n";
      const Group * const least_successful_group = m_worst_and_best_group.first;
      assert(least_successful_group);
      assert(least_successful_group != most_successful_group);

      ///\note
      ///The operation below invalidates const Group * const least_successful_group
      NotifyKillGroup(least_successful_group);
      //Again find the most successful group and let it split
      //Find the group with the highest payoff
      assert(most_successful_group->GetSize() == 5);

      NotifyGroupSplit(most_successful_group);
    }

    GoToNextState();

  }


}

void ribi::gtst::ServerStateGroupReAssign::Start()
{
  const double average_payoff = CalculateAveragePayoff();

  ///Give all waiting Participants their payoff for waiting
  {
    ///Give the average payoff to the waiting participants
    const std::vector<const Group *> group_waiting = GetServer()->GetGroups()->CollectGroups(false,true,false,false);
    std::for_each(group_waiting.begin(),group_waiting.end(),
      [this,average_payoff](const Group * const group)
      {
        const std::vector<boost::shared_ptr<const Participant> > w = group->CollectParticipants();
        std::for_each(w.begin(),w.end(),
          [this,average_payoff](const boost::shared_ptr<const Participant>& p)
          {
            const double my_payoff = this->GetServer()->GetParameters()->GetGroupAssign()->CalculateWaitingPayoff(average_payoff);
            const int period = this->GetServer()->GetStates()->GetCurrentState()->GetPeriod();
            boost::shared_ptr<Payoff> payoff(new PayoffAssign(period,my_payoff));
            this->FindParticipant(p)->GetPayoffs()->Add(payoff);
            assert(dynamic_cast<ParticipantStateLoggedIn*>(this->FindParticipant(p)->GetState()));
            ParticipantStateLoggedIn * const state = dynamic_cast<ParticipantStateLoggedIn*>(this->FindParticipant(p)->GetState());
            state->SetMessage(
              (std::string("Your total earnings are: ")
              + std::to_string(p->GetPayoffs()->GetTotal())).c_str());
            this->GetServer()->GetLog()->LogAssignPayoff(p);
          }
        );
      }
    );

  }

  ///Update the group_payoffs for determining the best and worst group
  {
    m_group_payoffs.clear();
    assert(m_group_payoffs.empty());

    const int n_ipgg_cycles = GetServer()->GetStates()->GetCycles(GetServer()->GetStates()->GetCurrentState()->GetPeriod());

    const std::vector<const Group *> groups
      = GetServer()->GetGroups()->CollectGroups(false,false,true,false);

    std::for_each(groups.begin(),groups.end(),
      [n_ipgg_cycles,this](const Group * const group)
    {
      double payoff = 0.0;
      //Sum the payoff
      const std::vector<boost::shared_ptr<const Participant> > w = group->CollectParticipants();
      std::for_each(w.begin(),w.end(),
        [n_ipgg_cycles,&payoff](const boost::shared_ptr<const Participant>& p)
      {
        payoff += p->GetPayoffs()->GetLast(n_ipgg_cycles);
      } );
      //Average the payoff
      payoff /= boost::numeric_cast<double>(w.size());
      m_group_payoffs.insert(std::make_pair(group,payoff));
      this->FindGroup(group)->AppendAveragePayoff(payoff);
    } );
  }
  assert(m_group_payoffs.size() == GetServer()->GetGroups()->CollectGroups(false,false,true,false).size());

  //Calculate joiners
  if (m_group_payoffs.empty() || m_group_payoffs.size() == 1)
  {
    return;
  }

  m_worst_and_best_group = CalculateWorstAndBestGroup();
  assert(m_worst_and_best_group.first != m_worst_and_best_group.second);

  //Assign payoff for surviving
  {
    const int group_size_most_successful = m_worst_and_best_group.second->GetSize();
    const std::vector<const Group *> all_active_groups = GetServer()->GetGroups()->CollectGroups(false,false,true,false);
    std::vector<const Group *> survived_groups;
    if (group_size_most_successful == 5)
    {
      std::copy_if(all_active_groups.begin(),all_active_groups.end(),
        std::back_inserter(survived_groups),
        [this](const Group * group)
        {
          return group != this->m_worst_and_best_group.first;
        }
      );
    }
    else
    {
      survived_groups = all_active_groups;
    }
    //Reward survived_groups for reaching the next round
    std::for_each(survived_groups.begin(),survived_groups.end(),
      [this,average_payoff](const Group * group)
      {
        const std::vector<boost::shared_ptr<const Participant> > w = group->CollectParticipants();
        std::for_each(w.begin(),w.end(),
          [this,average_payoff](const boost::shared_ptr<const Participant>& p)
          {
            const double my_payoff = this->GetServer()->GetParameters()->GetGroupReAssign()->CalculateNextPeriodPayoff(average_payoff);
            const int period = this->GetServer()->GetStates()->GetCurrentState()->GetPeriod();
            boost::shared_ptr<Payoff> payoff(new PayoffReAssign(period,my_payoff));
            this->FindParticipant(p)->GetPayoffs()->Add(payoff);
            this->GetServer()->GetLog()->LogReAssignPayoff(p);
          }
        );
      }
    );
  }

  //Set the state of the participants
  {
    const auto ps = GetServer()->GetGroups()->CollectParticipants(false,false,true,false);
    std::for_each(ps.begin(),ps.end(),
    [this](const boost::shared_ptr<const Participant>& p)
    {
      const StateGroupReAssign * const state
        = dynamic_cast<const StateGroupReAssign*>(this);
      assert(state);
      this->FindParticipant(p)->SetState(state);
    } );
  }
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateGroupReAssign& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    << s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}


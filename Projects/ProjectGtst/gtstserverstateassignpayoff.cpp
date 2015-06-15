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
#include <fstream>
#include <map>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>

#include "gtstadministrator.h"
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
#include "gtstrepeatassigner.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "trace.h"
#include "gtstvotingoption.h"
#pragma GCC diagnostic pop

ribi::gtst::ServerStateAssignPayoff::ServerStateAssignPayoff(
  Server * const server,
  const int period,
  const int cycle,
  const boost::shared_ptr<const ParametersAssignPayoff> parameters,
  const boost::shared_ptr<const ServerStateViewResultsVoting> state_view_results_voting)
  : ServerState(server,period,cycle),
    m_has_assigned_payoff{},
    m_parameters(parameters),
    m_state_view_results_voting(state_view_results_voting)
{
  assert(m_parameters);
  assert(m_state_view_results_voting);
}

///Check if this state can go to the next state.
bool ribi::gtst::ServerStateAssignPayoff::CanGoToNextState() const
{
  return true;
}

///Obtain the duration of the state in seconds
int ribi::gtst::ServerStateAssignPayoff::GetStateDuration() const
{
  return boost::numeric::bounds<int>::highest();
}

void ribi::gtst::ServerStateAssignPayoff::OnTimer()
{
  if (CanGoToNextState()) GoToNextState();
}

void ribi::gtst::ServerStateAssignPayoff::Start()
{
  const int period = this->GetPeriod();
  const int cycle  = this->GetCycle();

  ///assigns all Participant payoffs
  const auto groups = GetServer()->GetGroups()->CollectGroups(false,false,true,false);
  std::for_each(groups.begin(),groups.end(),
    [this,period,cycle](const Group * const group)
    {
      assert(group);

      assert(this->m_state_view_results_voting->GetVotedOptions().find(
        group) != this->m_state_view_results_voting->GetVotedOptions().end());
      const VotingOption * const option
        = this->m_state_view_results_voting->GetVotedOptions().find(group)->second;
      ///\note
      ///If option is null, no consensus is reached within this group
      this->FindGroup(group)->AssignPayoff(period,cycle,option);
    }
  );

  const auto ps = GetServer()->GetGroups()->CollectParticipants(false,false,true,false);
  std::for_each(ps.begin(),ps.end(),
    [this](const boost::shared_ptr<const Participant>& p)
    {
      const StateAssignPayoff * const state
        = dynamic_cast<const StateAssignPayoff*>(this);
      assert(state);
      this->FindParticipant(p)->SetState(state);
    }
  );
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateAssignPayoff& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    << "<has_assigned_payoff>";
  std::for_each(s.m_has_assigned_payoff.begin(),s.m_has_assigned_payoff.end(),
    [&os](const std::pair<const Participant *,bool>& p)
    {
      os
        << p.first
        << "<yesno>"
        << p.second
        << "</yesno>";
    } );

  //  << s.m_has_assigned_payoff
  os
    << "</has_assigned_payoff>"
    << s.m_parameters
    //<< s.m_server
    //<< s.m_stopwatch
    //<< s.m_wait_time
    << "</state_" << s.ToStr() << ">";
  return os;
}


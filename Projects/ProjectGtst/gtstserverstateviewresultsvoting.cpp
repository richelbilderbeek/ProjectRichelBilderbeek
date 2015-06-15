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
#include <algorithm>
#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/shared_ptr.hpp>

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
#include "stopwatch.h"
#include "gtstserver.h"
#include "trace.h"
#include "gtstvote.h"
#include "gtstvotingoption.h"
#pragma GCC diagnostic pop

ribi::gtst::ServerStateViewResultsVoting::ServerStateViewResultsVoting(
  Server * const server, const int period, const int cycle,
  const boost::shared_ptr<const ParametersViewResultsVoting>& parameters)
  : ServerState(server,period,cycle),
    m_parameters(parameters),
    m_voted_concensus{}
{
  assert(m_parameters);
}

///Check if this state can go to the next state.1
bool ribi::gtst::ServerStateViewResultsVoting::CanGoToNextState() const
{
  return GetTimeLeft() < 0;
}

const std::vector<boost::shared_ptr<ribi::gtst::Vote> > ribi::gtst::ServerStateViewResultsVoting::GetGroupResults(
  const boost::shared_ptr<const Participant>& participant) const
{
  assert(participant);
  assert(GetServer());
  assert(GetServer()->GetParameters());
  assert(GetServer()->GetParameters()->GetVoting());

  std::vector<boost::shared_ptr<Vote> > v;

  const Group * const group
    = GetServer()->GetGroups()->FindMyGroup(participant);
  assert(group);

  for(const boost::shared_ptr<const Participant>& participant:
    group->CollectParticipants())
  {
    assert(!participant->GetVotes().empty());

    v.push_back(
      boost::shared_ptr<Vote>(
        new Vote(
          participant,
          participant->GetVotes().back().get())));
  }
  return v;
}

///Obtain the duration of the state in seconds
int ribi::gtst::ServerStateViewResultsVoting::GetStateDuration() const
{
  assert(m_parameters);
  return m_parameters->GetDuration();
}

void ribi::gtst::ServerStateViewResultsVoting::OnTimer()
{
  if (CanGoToNextState()) GoToNextState();
}

/*
void ribi::gtst::ServerStateViewResultsVoting::SetParameters(
  const boost::shared_ptr<const ParametersViewResultsVoting>& parameters)
{
  assert(parameters);
  m_parameters = parameters;
  ResetTimeLeft();
  assert(this->GetTimeLeft() >= 0);
}
*/

///Start or restart the state
void ribi::gtst::ServerStateViewResultsVoting::Start()
{
  ///Setting the group its vote
  m_voted_concensus.clear();

  for(const Group * const group:
    GetServer()->GetGroups()->CollectGroups(false,false,true,false))
  {
    //Only participating groups will have voted
    assert(dynamic_cast<const GroupParticipating*>(group));

    if(group->CollectParticipants().empty())
    {
      TRACE(group->GetId());
    }
    assert(!group->CollectParticipants().empty()
      && "Assume a group is never empty");

    //Tally all votes
    std::map<std::string,int> vote_tally;
    for(const boost::shared_ptr<const Participant>& participant:
      group->CollectParticipants())
    {
      assert(!participant->GetVotes().empty());
      const std::string s = participant->GetVotes().back()->GetDescription();
      if (vote_tally.find(s) == vote_tally.end())
      {
        vote_tally[s] = 0;
      }
      else
      {
        ++vote_tally[s];
      }
    }

    //Get the highest tally value (that is: the second int)
    const std::map<std::string,int>::const_iterator max
      = std::max_element(
        vote_tally.begin(),
        vote_tally.end(),
        boost::lambda::bind(&std::pair<const std::string,int>::second, boost::lambda::_2)
         > boost::lambda::bind(&std::pair<const std::string,int>::second, boost::lambda::_1));
    const int max_count
      = std::count_if(
       vote_tally.begin(),
       vote_tally.end(),
       boost::lambda::bind(&std::pair<const std::string,int>::second, boost::lambda::_1)
         == max->second);

    if (max_count == 0)
    {
      for(const boost::shared_ptr<const Participant>& participant:
        group->CollectParticipants())
      {
        const int id = participant->GetId();
        const std::string s = participant->GetVotes().back()->GetDescription();
        std::cerr << "ID: " << id << " vote: " << s << '\n';
      }
      std::cerr << "max->first: " << max->first << '\n';
      std::cerr << "max->second: " << max->second << '\n';
      std::cerr << "max_count: " << max_count << '\n';
    }
    assert(max_count >= 1);

    if (max_count == 1)
    {
      //Unique!
      //assert(max->first < boost::numeric_cast<int>(
      //  GetServer()->GetParameters()->GetVoting()->GetOptions().size()));
      const std::vector<boost::shared_ptr<VotingOption> > v
        = GetServer()->GetParameters()->GetVoting()->GetOptions();
      assert(
        std::find_if(v.begin(),v.end(),
          boost::bind(&VotingOption::GetDescription,boost::lambda::_1) == max->first)
          != v.end());
      m_voted_concensus[group]
        = (*std::find_if(v.begin(),v.end(),
          boost::bind(&VotingOption::GetDescription,boost::lambda::_1) == max->first)).get();

    }
    else
    {
      //No consensus in voting
      m_voted_concensus[group] = 0;
    }

  }
  for(const boost::shared_ptr<const Participant>& p:
    GetServer()->GetGroups()->CollectParticipants(false,false,true,false))
  {
    const StateViewResultsVoting * const state
      = dynamic_cast<const StateViewResultsVoting*>(this);
    assert(state);
    FindParticipant(p)->SetState(state);
  }
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ServerStateViewResultsVoting& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    << s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}


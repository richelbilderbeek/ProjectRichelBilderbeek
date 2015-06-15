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
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/weak_ptr.hpp>

#include "gtstchooseactionoption.h"
#include "gtstlogfile.h"
#include "gtstgroup.h"
#include "gtstparticipant.h"
#include "gtstpayoff.h"
#include "gtstpayoffs.h"
//#include "trace.h"
#include "gtstserver.h"
#include "gtstvotingoption.h"
#pragma GCC diagnostic pop

ribi::gtst::Group::Group(Server * const server)
  : m_average_payoffs{},
    m_participants{},
    m_server{server}
{
  assert(m_server);
}

///Add a Participant to the Group
void ribi::gtst::Group::AddParticipant(boost::shared_ptr<Participant> participant)
{
  assert(participant);
  this->m_participants.push_back(participant);

  m_server->GetLog()->LogAssignGroup(this,participant);
}

///Append the last IPGG's cycle(s) average payoff to m_payoffs
void ribi::gtst::Group::AppendAveragePayoff(const double payoff)
{
  m_average_payoffs.push_back(payoff);
}

///Assign the payoffs to this group
///
///\note
///If option is null, no concensus is reached in voting
void ribi::gtst::Group::AssignPayoff(
  const int period,
  const int round,
  const VotingOption * const option)
{
  assert((option || !option)
    && "If option is null, no concensus is reached in voting within this group");

  //Obtain the payoff contributed to the group
  const double total_group_payoff
    = std::accumulate(
      m_participants.begin(),m_participants.end(),0.0,
      [](double& sum,const boost::shared_ptr<Participant>& participant)
      {
        assert(!participant->GetActions().empty());
        return sum + participant->GetActions().back()->GetContribution();
      }
    );

  #ifndef NDEBUG
  const int size = this->GetSize();
  assert(size!=0);
  #endif

  std::map<boost::shared_ptr<Participant>,std::tuple<bool,boost::logic::tribool> > s;

  //Collect the benefactors
  std::for_each(m_participants.begin(),m_participants.end(),
    [&s,this,option](const boost::shared_ptr<Participant>& participant)
    {
      assert(!participant->GetActions().empty());
      const double contribution = participant->GetActions().back()->GetContribution();
      const bool did_contribute = (contribution != 0.0);
      if (did_contribute)
      {
        s[participant] = std::make_tuple(did_contribute, boost::logic::tribool::indeterminate_value);
      }
      else
      {
        const bool did_get_caught = (option == 0
          //Without a concensus there is no police force
          ? false
          //With a concensus, non-contributor only benefits when not detected by the supervisor
          : this->GetRandomUniform() < option->GetChance());
        s[participant] = std::make_tuple(did_contribute, did_get_caught);
      }
    }
  );


  const int n_benefactors = std::count_if(s.begin(),s.end(),
    [](std::pair<const boost::shared_ptr<Participant>,std::tuple<bool,boost::logic::tribool> >& p)
    {

      return std::get<0>(p.second) || std::get<1>(p.second) == false;
    }
  );

  const double benefactors_share
    = total_group_payoff
    / (n_benefactors ? boost::numeric_cast<double>(n_benefactors) : 1.0);

  ///Assign each participants' payoff
  std::for_each(s.begin(),s.end(),
    [this,period,round,benefactors_share](std::pair<const boost::shared_ptr<Participant>,std::tuple<bool,boost::logic::tribool> >& p)
    {

      const bool did_contribute = std::get<0>(p.second);
      const boost::logic::tribool did_get_caught = std::get<1>(p.second);
      const double individual_payoff
        = -p.first->GetActions().back()->GetCost()
        + (did_contribute || !did_get_caught
          ? benefactors_share
          : 0.0);
      boost::shared_ptr<Payoff> payoff(new PayoffIpgg(period,round,individual_payoff,did_contribute,did_get_caught));
      p.first->GetPayoffs()->Add(payoff);
      this->m_server->GetLog()->LogAssignPayoff(p.first);
    }
  );
}

///Clear all Participants
void ribi::gtst::Group::Clear()
{
  m_participants.resize(0);
}

///Collects all Participants in this Group as read-only pointers
const std::vector<boost::shared_ptr<const ribi::gtst::Participant> > ribi::gtst::Group::CollectParticipants() const
{
  //TRACE_FUNC();
  //TRACE(*this);
  std::vector<boost::shared_ptr<const Participant> > v;
  std::transform(m_participants.begin(),m_participants.end(),
    std::back_inserter(v),
    [](const boost::shared_ptr<Participant>& p) { return p;} );
  assert(v.size() == m_participants.size());
  assert(v.empty() || v[0] == m_participants[0]);
  return v;
}

///Obtain a random double in the range [0.0,1.0>
//From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double ribi::gtst::Group::GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}

///Get the Group its size
int ribi::gtst::Group::GetSize() const
{
  return boost::numeric_cast<int>(m_participants.size());
}

///Checks if a Participant is present in this Group
bool ribi::gtst::Group::IsMember(const boost::shared_ptr<const Participant>& participant) const
{
  return std::find_if(
    m_participants.begin(),
    m_participants.end(),
    [participant](const boost::shared_ptr<const Participant>& i) { return i == participant; }
  )
  != m_participants.end();
}

///Remove a Participant from a Group
boost::shared_ptr<ribi::gtst::Participant> ribi::gtst::Group::RemoveParticipant(const boost::shared_ptr<const Participant>& participant)
{
  assert(IsMember(participant));
  assert(std::any_of(
    m_participants.begin(),m_participants.end(),
    [this,participant](boost::shared_ptr<Participant>& p)
    {
      return participant == p;
    }
  ));

  boost::shared_ptr<Participant> q =
    *std::find_if(m_participants.begin(),m_participants.end(),
    [this,participant](boost::shared_ptr<Participant>& p)
    {
      return participant == p;
    }
  );

  m_participants.erase(
    std::remove_if(
      m_participants.begin(),m_participants.end(),
      [this,participant](boost::shared_ptr<Participant>& p)
      {
        return participant == p;
      }
    )
  );

  /*
  std::for_each(m_participants.begin(),m_participants.end(),
    [this,participant](boost::shared_ptr<Participant>& p)
    {
      if (participant == p)
      {
        boost::shared_ptr<Participant> q = p;
        std::swap(p,m_participants.back());
        m_participants.pop_back();
        return q;
      }
    }
  );
  */
  m_server->GetLog()->LogRemoveParticipant(this,q);

  return q;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os, const Group& group)
{
  os << "<" << group.ToStr() << ">\n";
  std::for_each(group.m_participants.begin(),group.m_participants.end(),
    [&os](const boost::shared_ptr<const Participant>& p)
    {
      os << *p << '\n';
    }
  );
  os << "<payoffs>\n";
  std::for_each(group.m_average_payoffs.begin(),group.m_average_payoffs.end(),
    [&os](const double& d)
    {
      os << d << '\n';
    }
  );
  os << "</payoffs>\n";
  os << "</" << group.ToStr() << ">";
  return os;
}



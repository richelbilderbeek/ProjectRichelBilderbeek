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
#include <mutex>
#include <numeric>
#include <stdexcept>
#include <thread>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/weak_ptr.hpp>

#include "gtstgroupassigner.h"
#include "gtstgroups.h"
#include "gtstgroupfinished.h"
#include "gtstgrouploggedin.h"
#include "gtstgroupnotloggedin.h"
#include "gtstgroupparticipating.h"
#include "ipaddress.h"
#include "gtstserver.h"
#include "gtststate.h"
#include "trace.h"
#pragma GCC diagnostic pop

std::recursive_mutex ribi::gtst::Groups::m_mutex;

boost::signals2::signal<void ()> ribi::gtst::Groups::m_signal_groups_changed;

ribi::gtst::Groups::Groups(Server * const server)
  : m_finished{new GroupFinished(server)},
    m_last_id_participant{},
    m_logged_in{new GroupLoggedIn(server)},
    m_not_logged_in{new GroupNotLoggedIn(server)},
    m_participating{},
    m_server{server}
{
  assert(m_server);
  m_signal_groups_changed();
}

///Check if a Participant can be from his/her non-wildcard IP address
bool ribi::gtst::Groups::CanFind(const boost::shared_ptr<const SafeIpAddress>& ip_address) const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(ip_address);

  const std::vector<boost::shared_ptr<const Participant> > v = CollectParticipants();

  if (v.empty()) return false;


  assert(std::none_of(v.begin(),v.end(),
      [](const boost::shared_ptr<const Participant>& p) { return !p; } ));


  const auto i
    = std::find_if(
      v.begin(),v.end(),
      [ip_address](const boost::shared_ptr<const Participant>& participant)
      {
        return participant->CanGetIpAddress() && participant->GetIpAddress().get() == ip_address.get();
      } );

  return i!=v.end();
}

///Search the Group for a Participant with a certain IP address
bool ribi::gtst::Groups::CanGetParticipantWithIpAddress(const boost::shared_ptr<const SafeIpAddress>& ip_address) const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(ip_address);
  //Obtain all Participants
  const auto ps = this->CollectParticipants();


  return std::find_if(
    ps.begin(),
    ps.end(),
      [ip_address](const boost::shared_ptr<const Participant>& p)
      {
        return p->CanGetIpAddress() && p->GetIpAddress() == ip_address;
      }
    ) != ps.end();
}

///A Participant can log in, if
///- he/she reloaded the page by pressing F5, recovery of all actions
///- he/she started viewing the page, start of new actions
bool ribi::gtst::Groups::CanLetLogin(const boost::shared_ptr<const SafeIpAddress>& ip_address) const
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(ip_address);
  //Obtain all Participants
  const auto ps = this->CollectParticipants();

  return std::find_if(
    ps.begin(),
    ps.end(),
      [ip_address](const boost::shared_ptr<const Participant>& p)
      {
        return !p->CanGetIpAddress() || p->GetIpAddress() == ip_address;
      }
    ) != ps.end();
}

///Collect all Groups as a read-only std::vector
const std::vector<const ribi::gtst::Group *> ribi::gtst::Groups::CollectGroups(
  const bool not_logged_in,
  const bool logged_in,
  const bool participating,
  const bool finished) const
{
  std::vector<const Group *> v;
  if (not_logged_in)
  {
    v.push_back(m_not_logged_in.get());
  }
  if (logged_in)
  {
    v.push_back(m_logged_in.get());
  }
  if (participating)
  {
    std::transform(m_participating.begin(),m_participating.end(),
      std::back_inserter(v),
      [](const boost::shared_ptr<GroupParticipating>& g) { return g.get(); } );
  }
  if (finished)
  {
    v.push_back(m_finished.get());
  }
  return v;
}

///Collect all Participants as a read-only std::vector
const std::vector<boost::shared_ptr<const ribi::gtst::Participant> > ribi::gtst::Groups::CollectParticipants(
  const bool not_logged_in,
  const bool logged_in,
  const bool participating,
  const bool finished) const
{
  ///Let this thread sleep, to give the other thread a chance
  //std::this_thread::sleep_for(std::chrono::milliseconds(1));
  //std::lock_guard<std::mutex> lock(Server::m_mutex);


  std::vector<boost::shared_ptr<const Participant> > v;

  const auto groups = CollectGroups(not_logged_in,logged_in,participating,finished);
  std::for_each(groups.begin(),groups.end(),
    [&v](const Group * group)
  {
    const std::vector<boost::shared_ptr<const Participant> > w = group->CollectParticipants();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  } );
  return v;
}

///Find a Participant from his/her non-wildcard IP address
const boost::shared_ptr<const ribi::gtst::Participant> ribi::gtst::Groups::Find(const boost::shared_ptr<const SafeIpAddress>& ip_address) const
{
  assert(ip_address);
  assert(CanFind(ip_address));

  const std::vector<boost::shared_ptr<const Participant> > v = CollectParticipants();

  assert(std::none_of(v.begin(),v.end(),
    [](const boost::shared_ptr<const Participant>& p) { return !p; } ));



  //Search for a Participant with this IP address
  {
    const std::vector<boost::shared_ptr<const Participant> >::const_iterator i
      = std::find_if(
        v.begin(),
        v.end(),
        [ip_address](const boost::shared_ptr<const Participant>& participant)
        {
          return participant->CanGetIpAddress() && participant->GetIpAddress().get() == ip_address.get();
        }
      );
    //A Participant with a known IP address is found
    if (i!=v.end())
    {
      assert((*i));
      assert((*i)->CanGetIpAddress());
      assert((*i)->GetIpAddress()->Get() == ip_address->Get());
      return *i;
    }
  }
  assert(!"Should not get here");
  throw std::logic_error("Should not get here");
}

///Find a read/write Group from a read-only Group
///Just checks if the Group really exists
///
///\note const_cast!
ribi::gtst::Group * ribi::gtst::Groups::FindGroup(const Group * const group) const
{
  assert(group);

  #ifndef NDEBUG
  const std::vector<const Group *> groups = CollectGroups();
  assert(std::any_of(groups.begin(),groups.end(),
    [group](const Group * const other_group)
    {
      return other_group == group;
    } ));
  #endif

  return const_cast<Group*>(group);
}

///Finds the Group the Participant is in
const ribi::gtst::Group * ribi::gtst::Groups::FindMyGroup(const boost::shared_ptr<const Participant>& participant) const
{

  const auto groups = CollectGroups();
  const auto my_group
    = std::find_if(groups.begin(),groups.end(),
        [participant](const Group * const group)
        {
          return group->IsMember(participant);
        } );
  if (my_group != groups.end()) return *my_group;

  assert(!"All Participants must be in a Group");
  return 0;
}

///Find a read/write Participant from a read-only Participant
///Just checks if the Participant really exists
///
///\note const_cast!
boost::shared_ptr<ribi::gtst::Participant> ribi::gtst::Groups::FindParticipant(const boost::shared_ptr<const Participant>& participant) const
{
  assert(participant);
  assert(FindMyGroup(participant)!=0
    && "Every Participant must be in a Group");

  return boost::const_pointer_cast<Participant>(participant);
}

const ribi::gtst::GroupFinished * ribi::gtst::Groups::GetGroupFinished() const
{
  assert(m_finished);
  return m_finished.get();
}

const ribi::gtst::GroupLoggedIn * ribi::gtst::Groups::GetGroupLoggedIn() const
{
  assert(m_logged_in);
  return m_logged_in.get();
}

const ribi::gtst::GroupNotLoggedIn * ribi::gtst::Groups::GetGroupNotLoggedIn() const
{
  assert(m_not_logged_in);
  return m_not_logged_in.get();
}

///Find the Group for the Participant with a certain IP address
const boost::shared_ptr<const ribi::gtst::Participant> ribi::gtst::Groups::GetParticipantWithIpAddress(
  const boost::shared_ptr<const SafeIpAddress>& ip_address) const
{
  assert(CanGetParticipantWithIpAddress(ip_address));
  const std::vector<boost::shared_ptr<const Participant> > p = this->CollectParticipants();

  return *std::find_if(
    p.begin(),p.end(),
    [ip_address](const boost::shared_ptr<const Participant>& participant)
    {
      return participant->CanGetIpAddress()
        && participant->GetIpAddress().get() == ip_address.get();
    }
  );
}

///Let a Group grow from 3 to 5 Participants
void ribi::gtst::Groups::GrowGroup(const Group * const group)
{
  GroupLoggedIn * const from_group = this->m_logged_in.get();
  Group * const to_group = FindGroup(group);
  assert(to_group->GetSize() == 3);
  if (from_group->GetSize() != 0)
  {
    to_group->AddParticipant(
      from_group->RemoveParticipant(
        from_group->CollectParticipants().back()));
  }
  if (from_group->GetSize() != 0)
  {
    to_group->AddParticipant(
      from_group->RemoveParticipant(
        from_group->CollectParticipants().back()));
  }
  m_signal_groups_changed();
}

///Relocate a GroupParticipating to GroupFinished
void ribi::gtst::Groups::KillGroup(const Group * const group_to_move)
{
  std::for_each(m_participating.begin(),m_participating.end(),
    [this,group_to_move](boost::shared_ptr<GroupParticipating> group)
    {
      if (group.get() == group_to_move)
      {
        const auto ps = group->CollectParticipants();
        std::for_each(ps.begin(),ps.end(),
          [this,group](const boost::shared_ptr<const Participant>& p)
          {

            //Move the Participant from its current group
            //to the GroupFinished
            this->m_finished->AddParticipant(
              group->RemoveParticipant(p));
            //Set the Participant his/her new State

            const State * state
              = dynamic_cast<const State *>(
                m_finished.get());
            assert(state);
            this->FindParticipant(p)->SetState(state);

          }
        );

        //Remove the (empty) group
        m_participating.erase(group);

        return;
      }
    }
  );

  ///\note
  ///Should get here!
  ///Calling return in a lambda expression
  ///just quits the lambda expression
  m_signal_groups_changed();
}

///Move a Participant from the any Group to the GroupLoggedIn
const boost::shared_ptr<const ribi::gtst::Participant> ribi::gtst::Groups::LetLogin(const boost::shared_ptr<const SafeIpAddress>& ip_address)
{
  std::lock_guard<std::recursive_mutex> lock(m_mutex);

  assert(CanLetLogin(ip_address));

  ///Assign this IP address to a Participant
  if (CanFind(ip_address))
  {
    assert(Find(ip_address)->CanGetId());
    assert(Find(ip_address)->CanGetIpAddress());
    return Find(ip_address);
  }

  const std::vector<boost::shared_ptr<const Participant> > v = CollectParticipants();

  //Let a random unassigned participant be assigned
  std::vector<boost::shared_ptr<const Participant> > w;
  std::copy_if(
    v.begin(),v.end(),
    std::back_inserter(w),
    [](const boost::shared_ptr<const Participant>& participant)
    {
      return !participant->CanGetIpAddress();
    }
  );

  const boost::shared_ptr<const Participant> participant
    = w[ std::rand() % boost::numeric_cast<int>(w.size()) ];

  //Let a non-random unassigned participant be assigned
  /*
  const boost::shared_ptr<const Participant> participant
    = *std::find_if(
      v.begin(),v.end(),
      [](const boost::shared_ptr<const Participant>& participant)
      {
        return !participant->CanGetIpAddress();
      }
    );
  */

  assert(!participant->CanGetIpAddress());

  //Assign the ID
  ///\note const_cast
  boost::const_pointer_cast<Participant>(participant)->AssignId(++m_last_id_participant);

  assert(participant->CanGetId()
    && "Assume that the new Participant now has his/her ID assigned");

  //Assign the IP address
  ///\note const_cast
  boost::const_pointer_cast<Participant>(participant)->SetIpAddress(ip_address);

  assert(participant->CanGetIpAddress()
    && "Every participant must have a valid IP address after logging in");

  //Move the Participant
  assert(FindMyGroup(participant) == m_not_logged_in.get());
  assert(GetGroupNotLoggedIn()->IsMember(participant));
  assert(!GetGroupLoggedIn()->IsMember(participant));

  m_logged_in->AddParticipant(m_not_logged_in->RemoveParticipant(participant));

  assert(!GetGroupNotLoggedIn()->IsMember(participant));
  assert(GetGroupLoggedIn()->IsMember(participant));

  //Set the new state
  ///\note const_cast
  boost::const_pointer_cast<Participant>(participant)->SetState(new StateLoggedIn);

  m_signal_groups_changed();

  return participant;
}

///Split a Group of 5 Participants to 2 groups of 3
void ribi::gtst::Groups::SplitGroup(const Group * const group)
{
  assert(group->GetSize() == 5);
  assert(m_logged_in->GetSize());
  Group * group1 = FindGroup(group);
  group1->AddParticipant(
    m_logged_in->RemoveParticipant(
      m_logged_in->CollectParticipants().back()));
  assert(group1->GetSize() == 6);
  std::vector<boost::shared_ptr<const Participant> > p = group1->CollectParticipants();
  std::random_shuffle(p.begin(),p.end());

  boost::shared_ptr<GroupParticipating> group2(new GroupParticipating(m_server));

  for (int i=0; i!=3; ++i)
  {
    group2->AddParticipant(
      group1->RemoveParticipant(
        p[i]));
  }
  assert(group1->GetSize() == 3);
  assert(group2->GetSize() == 3);
  m_participating.insert(group2);
  m_signal_groups_changed();
}

///MoveAllToFinished moves all Participants to the Finished Group
void ribi::gtst::Groups::MoveAllToFinished()
{
  {
    const std::vector<boost::shared_ptr<const Participant> > v
      = m_not_logged_in->CollectParticipants();
    std::for_each(v.begin(),v.end(),
      [this](const boost::shared_ptr<const Participant>& p)
      {
        this->m_finished->AddFinishedParticipant(this->m_not_logged_in->RemoveParticipant(p));
      }
    );
  }
  {
    const std::vector<boost::shared_ptr<const Participant> > v
      = m_logged_in->CollectParticipants();
    std::for_each(v.begin(),v.end(),
      [this](const boost::shared_ptr<const Participant>& p)
      {
        m_finished->AddFinishedParticipant(m_logged_in->RemoveParticipant(p));
      }
    );
  }
  std::for_each(m_participating.begin(),m_participating.end(),
    [this](boost::shared_ptr<GroupParticipating> group)
    {
      const std::vector<boost::shared_ptr<const Participant> > v
        = group->CollectParticipants();
      std::for_each(v.begin(),v.end(),
        [this,group](const boost::shared_ptr<const Participant>& p)
        {
          m_finished->AddFinishedParticipant(group->RemoveParticipant(p));
        }
      );
    }
  );

  m_signal_groups_changed();
}

///Moves all logged in Participants to the GroupPartipating
void ribi::gtst::Groups::MoveLoggedInToParticipating()
{
  const std::vector<boost::shared_ptr<const Participant> > v
    = m_logged_in->CollectParticipants();
  std::for_each(v.begin(),v.end(),
    [this](const boost::shared_ptr<const Participant>& p)
    {
      if (const GroupAssignerPredetermined * const a
        = dynamic_cast<const GroupAssignerPredetermined*>(p->GetGroupAssigner()))
      {
        const int group_index = a->GetGroup();
        //If there ain't a group with this index, create it
        while (std::find_if(m_participating.begin(),
          m_participating.end(),
          [group_index](const boost::shared_ptr<const GroupParticipating>& group)
            {
              return group->GetId() == group_index;
            }
          ) == m_participating.end())
        {
          boost::shared_ptr<GroupParticipating> new_group(new GroupParticipating(m_server));
          m_participating.insert(new_group);
        }

        //Assume the group with this index can be found
        assert(std::any_of(m_participating.begin(),m_participating.end(),
          [group_index](const boost::shared_ptr<const GroupParticipating>& group)
          {
              return group->GetId() == group_index;
          }
        ));

        //Retrieve the group with this index
        auto new_group_iter
          = std::find_if(m_participating.begin(),m_participating.end(),
          [group_index](const boost::shared_ptr<const GroupParticipating>& group)
          {
            return group->GetId() == group_index;
          }
        );
        (*new_group_iter)->AddParticipant(m_logged_in->RemoveParticipant(p));
      }
    }
  );

  m_signal_groups_changed();
}

///Remove all Participants
void ribi::gtst::Groups::Reset()
{
  m_finished->Clear();
  m_last_id_participant = 0;
  m_logged_in->Clear();
  m_not_logged_in->Clear();
  //m_participating.resize(0);
  m_participating.clear();
  GroupParticipating::Reset();

  m_signal_groups_changed();
}

///Set the Participants for the coming experiment
void ribi::gtst::Groups::SetParticipants(std::vector<boost::shared_ptr<Participant> > participants)
{
  Reset();
  assert(m_not_logged_in->GetSize() == 0);
  std::for_each(participants.begin(),participants.end(),
    [this](const boost::shared_ptr<Participant>& p)
    {
      m_not_logged_in->AddParticipant(p);
    }
  );

  m_signal_groups_changed();
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const Groups& groups)
{
  os
    << "<groups>"
    << (*groups.m_finished)
    << groups.m_last_id_participant
    << (*groups.m_logged_in)
    << (*groups.m_not_logged_in);
  std::for_each(groups.m_participating.begin(),groups.m_participating.end(),
    [&os](const boost::shared_ptr<GroupParticipating>& group)
    {
      os << (*group);
    }
  );
  os
    << "</groups>";
  return os;
}



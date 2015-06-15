
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

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTGROUPS_H
#define PROJECTGTSTGROUPS_H

#include <mutex>
#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///Groups is a Facade for managing all Group instances
///
///Groups is befriended to ServerStateGroupDynamics for modifying
///the Participant Group distribution
struct Groups
{
  ///Groups constructor
  Groups(Server * const server);
  Groups(const Groups&) = delete;
  Groups& operator=(const Groups&) = delete;

  ///Check if a Participant can be from his/her non-wildcard IP address
  bool CanFind(const boost::shared_ptr<const SafeIpAddress>& ip_address) const;

  ///Search the Group for a Participant with a certain IP address
  bool CanGetParticipantWithIpAddress(const boost::shared_ptr<const SafeIpAddress>& ip_address) const;

  ///A Participant can log in, if
  ///- he/she reloaded the page by pressing F5, recovery of all actions
  ///- he/she started viewing the page, start of new actions
  bool CanLetLogin(const boost::shared_ptr<const SafeIpAddress>& ip_address) const;

  ///Collect all desired Groups as a read-only std::vector
  const std::vector<const Group *> CollectGroups(
    const bool not_logged_in = true,
    const bool logged_in = true,
    const bool participating = true,
    const bool finished = true) const;

  ///Collect all Participants as a read-only std::vector
  const std::vector<boost::shared_ptr<const Participant> > CollectParticipants(
    const bool not_logged_in = true,
    const bool logged_in = true,
    const bool participating = true,
    const bool finished = true) const;

  ///Find a Participant from his/her non-wildcard IP address
  const boost::shared_ptr<const Participant> Find(const boost::shared_ptr<const SafeIpAddress>& ip_address) const;

  ///Finds the Group the Participant is in
  const Group * FindMyGroup(const boost::shared_ptr<const Participant>& participant) const;

  ///Obtain the GroupLoggedIn as a read-only pointer
  const GroupFinished * GetGroupFinished() const;

  ///Obtain the GroupLoggedIn as a read-only pointer
  const GroupLoggedIn * GetGroupLoggedIn() const;

  ///Obtain the GroupNotLoggedIn as a read-only pointer
  const GroupNotLoggedIn * GetGroupNotLoggedIn() const;

  ///Find the Group for the Participant with a certain IP address
  const boost::shared_ptr<const Participant> GetParticipantWithIpAddress(
    const boost::shared_ptr<const SafeIpAddress>& ip_address) const;

  ///Move a Participant from the passive to the active Group
  const boost::shared_ptr<const Participant> LetLogin(const boost::shared_ptr<const SafeIpAddress>& ip_address);

  ///Moves all Participants to the GroupFinished
  void MoveAllToFinished();

  ///Moves all logged in Participants to the GroupPartipating
  void MoveLoggedInToParticipating();

  ///Set the Participants for the coming experiment
  void SetParticipants(std::vector<boost::shared_ptr<Participant> > participants);

  ///Signal that is emitted when Groups changes.
  ///
  ///\note
  ///This signal is static, because the Groups pointer is reset sometimes,
  ///and the signal should not be lost
  static boost::signals2::signal<void ()> m_signal_groups_changed;

  private:
  ~Groups() {}
  friend void boost::checked_delete<>(Groups*);

  ///ServerState can modify
  ///the Group distribution
  friend class ServerState;

  ///ServerStateGroupNotParticipatingGroupDynamics can modify
  ///the Participant Group distribution
  friend class ServerStateGroupReAssign;

  friend std::ostream& operator<<(std::ostream& os,const Groups& groups);

  ///ServerStateFinished can modify
  ///the Participant Group distribution
  ///friend class ServerStateFinished;

  ///The group with Participants that are finished
  boost::scoped_ptr<GroupFinished> m_finished;

  ///The ID given to the last Participant
  int m_last_id_participant;

  ///The group with Participants that are logged in,
  ///but not assigned to a group
  boost::scoped_ptr<GroupLoggedIn> m_logged_in;

  ///The mutex
  static std::recursive_mutex m_mutex;

  ///The group with Participants that are not logged in
  boost::scoped_ptr<GroupNotLoggedIn> m_not_logged_in;

  ///The Participants assigned to a group
  std::set<boost::shared_ptr<GroupParticipating> > m_participating;

  Server * const m_server;

  ///Find a read/write Group from a read-only Group
  ///Just checks if the Group really exists
  Group * FindGroup(const Group * const group) const;

  ///Find a read/write Participant from a read-only Participant
  ///Just checks if the Participant really exists
  boost::shared_ptr<Participant> FindParticipant(const boost::shared_ptr<const Participant>& participant) const;

  ///Let a Group grow from 3 to 5 Participants
  void GrowGroup(const Group * const group);

  ///Remove a Group
  void KillGroup(const Group * const group);

  ///Split a Group of 6 Participants to 2 groups of 3
  void SplitGroup(const Group * const group);

  ///Remove all Participants
  void Reset();
};

std::ostream& operator<<(std::ostream& os,const Groups& groups);

} //~namespace gtst
} //~namespace ribi

#endif // GROUPS_H

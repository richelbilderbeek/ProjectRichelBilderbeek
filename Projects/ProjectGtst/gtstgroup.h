
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

#ifndef PROJECTGTSTGROUP_H
#define PROJECTGTSTGROUP_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "gtstparticipant.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///Group is a Participant group
struct Group
{
  Group(Server * const server);
  Group(const Group&) = delete;
  Group& operator=(const Group&) = delete;

  ///Add a Participant to the Group
  void AddParticipant(boost::shared_ptr<Participant> participant);

  ///Append the last IPGG's cycle(s) average payoff to m_payoffs
  void AppendAveragePayoff(const double payoff);

  ///Assign the payoffs to this group
  ///
  ///\note
  ///This is a non-const method, because it changes every Participant
  void AssignPayoff(
    const int period,
    const int round,
    const VotingOption * const option);

  ///Checks if there is a last average payoff
  //bool CanGetLastAveragePayoff() const;

  ///Clear all Participants
  void Clear();

  ///Collects all Participants in this Group as read-only pointers
  const std::vector<boost::shared_ptr<const Participant> > CollectParticipants() const;

  ///Get the average payoffs assigned after completing the IPGG periods
  const std::vector<double>& GetAveragePayoffs() const { return  m_average_payoffs; }

  ///Get the Group its ID
  virtual int GetId() const = 0;

  ///Get the last average payoff assigned
  //double GetLastAveragePayoff() const;

  ///Get the Group its size
  int GetSize() const;

  ///Get all Participants
  ///const std::vector<boost::shared_ptr<Participant> >& GetParticipants() const { return m_participants; }
  //const std::vector<boost::shared_ptr<const Participant> > GetParticipants() const { return m_participants; }

  ///Checks if a Participant is present in this Group
  bool IsMember(const boost::shared_ptr<const Participant>& participant) const;

  ///Remove a Participant from a Group
  boost::shared_ptr<Participant> RemoveParticipant(const boost::shared_ptr<const Participant>& participant);

  ///Reset the m_group_last_id to zero
  //static void Reset();

  ///Represent the Group type as a std::string
  virtual const std::string ToStr() const = 0;

  protected:
  virtual ~Group() {}
  friend void boost::checked_delete<>(Group*);

  ///Allow operator<< access to prevent recursion
  friend std::ostream& operator<<(std::ostream& os, const Group& group);

  ///The average payoffs assigned after completing the IPGG periods
  std::vector<double> m_average_payoffs;

  ///The Participant collection in this Group
  std::vector<boost::shared_ptr<Participant> > m_participants;

  Server * const m_server;

  private:

  ///Obtain a random double in the range [0.0,1.0>
  static double GetRandomUniform();
};

std::ostream& operator<<(std::ostream& os, const Group& group);

} //~namespace gtst
} //~namespace ribi

#endif // GROUP_H

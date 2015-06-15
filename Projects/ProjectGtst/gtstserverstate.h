
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

#ifndef PROJECTGTSTSERVERSTATE_H
#define PROJECTGTSTSERVERSTATE_H

#include <string>
#include <vector>

#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>


#include "gtstforward_declarations.h"
#include "gtststate.h"

namespace ribi {
namespace gtst {

///\brief
///ServerState embodies the state of the server.
///
///ServerState is a State.
struct ServerState : public State
{
  ///Create a ServerState with a pointer to its Server
  ServerState(Server * const server, const int period, const int cycle);
  ServerState(const ServerState&) = delete;
  ServerState& operator=(const ServerState&) = delete;

  ///Check if this state can go to the next state.
  ///This method is implemented like this for possible future
  ///more complex state transitions
  virtual bool CanGoToNextState() const = 0;

  ///Find a read/write Group from a read-only Group
  ///
  ///\note
  ///This is the only method that const_casts a Group
  Group * FindGroup(const Group * const group) const;

  ///Find a read/write Participant from a read-only Participant
  ///
  ///\note
  ///This is the only method that const_casts a Participant
  boost::shared_ptr<Participant> FindParticipant(const boost::shared_ptr<const Participant>& participant) const;

  ///Go to the next state
  void GoToNextState();

  ///Obtain the IPGG cycle this ServerState is in
  int GetCycle() const { return m_period; }

  ///Obtain all Participant's their states relevant for the current ServerState
  std::vector<std::string> GetParticipantStates() const;

  ///Obtain the period this ServerState is in
  int GetPeriod() const { return m_period; }

  ///Obtain the time left (in seconds) in this State
  int GetTimeLeft() const;

  ///Obtain the State its parent
  Server * GetServer() const;

  ///Obtain the duration of the state in seconds
  virtual int GetStateDuration() const = 0;

  ///ServerState dependent response to a timer
  virtual void OnTimer() = 0;

  ///Reset the timer, when the State is started
  void ResetTimeLeft();

  ///Start or restart the state, for example by resetting the timer
  virtual void Start() = 0;

  protected:
  virtual ~ServerState() {}
  friend void boost::checked_delete<>(ServerState*);

  ///The IPGG cycle this ServerState is in
  const int m_cycle;

  ///The period this ServerState is in
  const int m_period;

  ///(re)set the time left in this state
  void SetTimeLeft(const int time);

  protected:
  Server * const m_server;

  private:
  ///The server this state works on
  ///\note
  ///Do not change this to boost::shared_ptr<const Server>, because
  ///each State is constructed at the constructor of a Server,
  ///which requires a pointer to 'this'

  ///A Stopwatch used in the timed States
  const boost::scoped_ptr<Stopwatch> m_stopwatch;

  ///The time that must yet be waited before the state is ended
  int m_wait_time;

  public:
  ///\brief
  ///Converts a currency to std::string
  ///
  ///For example: 123.456789 to 123.46
  static const std::string CurrencyToStr(const double value);
};

} //~namespace gtst
} //~namespace ribi

#endif // ServerSTATE_H

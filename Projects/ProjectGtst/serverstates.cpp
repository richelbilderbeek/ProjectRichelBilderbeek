//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011 Richel Bilderbeek

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
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "all_serverstates.h"
#include "logfile.h"
#include "parameters.h"
#include "parametersgroupreassign.h"
#include "parametersviewresultsgroup.h"
#include "repeatassigner.h"
#include "server.h"
#include "stopwatch.h"
//---------------------------------------------------------------------------
ribi::gtst::ServerStates::ServerStates(
  Server * const server,
  boost::shared_ptr<const Parameters> parameters,
  LogFile * const log)
  : m_i(0), m_log(log)
{
  assert(parameters);
  assert(m_log);

  m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateGroupAssign(server,0,0)));
  const int n_periods = parameters->GetGroupReAssign()->GetNumberOfPeriods();
  for (int period = 0; period!=n_periods; ++period)
  {
    m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateChat(server,period,0,parameters->GetChat())));

    const boost::shared_ptr<ServerState> voting(
      new ServerStateVoting(server,period,0,parameters->GetVoting()));
    m_v.push_back(voting);

    const boost::shared_ptr<ServerStateViewResultsVoting> view_results_voting(
      new ServerStateViewResultsVoting(server,period,0,parameters->GetViewResultsVoting()));
    m_v.push_back(view_results_voting);

    const int n_cycles = parameters->GetViewResultsGroup()->GetRepeatAssigner()->Assign();
    ///Store the number of IPGG cycles
    m_n_cycles[period] = n_cycles;

    for (int cycle = 0; cycle!=n_cycles; ++cycle)
    {
      m_v.push_back(boost::shared_ptr<ServerState>(
        new ServerStateChooseAction(server,period,cycle,parameters->GetChooseAction())));
      m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateAssignPayoff(server,period,cycle,
        parameters->GetAssignPayoff(),view_results_voting)));
      m_v.push_back(boost::shared_ptr<ServerState>(
        new ServerStateViewResultsGroup(server,period,cycle,parameters->GetViewResultsGroup())));
    }
    m_v.push_back(boost::shared_ptr<ServerState>(
      new ServerStateGroupReAssign(server,period,0,parameters->GetGroupReAssign())));
  }
  m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateFinished(server,n_periods,0)));
}
//---------------------------------------------------------------------------
ribi::gtst::ServerState * ribi::gtst::ServerStates::GetCurrentState()
{
  assert(m_i >= 0);
  assert(m_i < boost::numeric_cast<int>(m_v.size()));
  return m_v[m_i].get();
}
//---------------------------------------------------------------------------
const ribi::gtst::ServerState * ribi::gtst::ServerStates::GetCurrentState() const
{
  assert(m_i >= 0);
  assert(m_i < boost::numeric_cast<int>(m_v.size()));
  return m_v[m_i].get();
}
//---------------------------------------------------------------------------
int ribi::gtst::ServerStates::GetCycles(const int period) const
{
  assert(m_n_cycles.find(period) != m_n_cycles.end());
  return (*m_n_cycles.find(period)).second;
}
//---------------------------------------------------------------------------
void ribi::gtst::ServerStates::GoToNextState()
{
  ++m_i;
  assert(m_i >= 0);
  assert(m_i < boost::numeric_cast<int>(m_v.size()));

  m_v[m_i]->Start();
  m_v[m_i]->ResetTimeLeft();

  m_log->LogExperimentStateChanged(GetCurrentState());
}
//---------------------------------------------------------------------------
/*
void ribi::gtst::ServerStates::SetParameters(boost::shared_ptr<const Parameters> parameters)
{
  Server * server = m_server;

  m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateGroupAssign(server,0,0)));
  const int n_periods = parameters->GetGroupReAssign()->GetNumberOfPeriods();
  for (int period = 0; period!=n_periods; ++period)
  {
    m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateChat(server,period,0,parameters->GetChat())));

    const boost::shared_ptr<ServerState> voting(
      new ServerStateVoting(server,period,0,parameters->GetVoting()));
    m_v.push_back(voting);

    const boost::shared_ptr<ServerStateViewResultsVoting> view_results_voting(
      new ServerStateViewResultsVoting(server,period,0,parameters->GetViewResultsVoting()));
    m_v.push_back(view_results_voting);

    const int n_cycles = parameters->GetViewResultsGroup()->GetRepeatAssigner()->Assign();
    for (int cycle = 0; cycle!=n_cycles; ++cycle)
    {
      m_v.push_back(boost::shared_ptr<ServerState>(
        new ServerStateChooseAction(server,period,cycle,parameters->GetChooseAction())));
      m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateAssignPayoff(server,period,cycle,
        parameters->GetAssignPayoff(),view_results_voting)));
      m_v.push_back(boost::shared_ptr<ServerState>(
        new ServerStateViewResultsGroup(server,period,cycle,parameters->GetViewResultsGroup())));
    }
    m_v.push_back(boost::shared_ptr<ServerState>(
      new ServerStateGroupReAssign(server,period,0,parameters->GetGroupReAssign())));
  }
  m_v.push_back(boost::shared_ptr<ServerState>(new ServerStateFinished(server,n_periods,0)));
  m_i = 0;
}
*/
//---------------------------------------------------------------------------

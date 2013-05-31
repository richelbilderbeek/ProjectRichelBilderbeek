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
#include <iostream>
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/bounds.hpp>
//---------------------------------------------------------------------------
#include "all_groups.h"
#include "all_parameters.h"
#include "all_serverstates.h"
#include "groups.h"
#include "state.h"
#include "logfile.h"
#include "participant.h"
#include "stopwatch.h"
#include "server.h"
//---------------------------------------------------------------------------
ServerStateWaiting::ServerStateWaiting(
  Server * const server, const int period, const int cycle)
  : ServerState(server,period,cycle)
{

}
//---------------------------------------------------------------------------
///Check if this state can go to the next state.
bool ServerStateWaiting::CanGoToNextState() const
{
  return true;
}
//---------------------------------------------------------------------------
///Obtain the duration of the state in seconds
int ServerStateWaiting::GetStateDuration() const
{
  return boost::numeric::bounds<int>::highest();
}
//---------------------------------------------------------------------------
void ServerStateWaiting::OnTimer()
{
  //if (CanGoToNextState()) GoToNextState();
  //Do NOT go to the next state by a timer, but by uploading Parameters
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const ServerStateWaiting& s)
{
  os
    << "<state_" << s.ToStr() << ">"
    //<< s.m_parameters
    << "</state_" << s.ToStr() << ">";
  return os;
}
//---------------------------------------------------------------------------

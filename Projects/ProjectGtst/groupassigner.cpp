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
#include <cassert>
#include <iostream>
#include <stdexcept>
//---------------------------------------------------------------------------
#include <boost/weak_ptr.hpp>
//---------------------------------------------------------------------------
#include "all_serverstates.h"
#include "groupassigner.h"
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groups.h"
#include "logfile.h"
#include "server.h"
#include "stopwatch.h"
//---------------------------------------------------------------------------
boost::shared_ptr<GroupAssigner> GroupAssigner::CreateAssigner(
  const std::string& s)
{
  if (s == "?")
  {
    boost::shared_ptr<GroupAssigner> a(
      new GroupAssignerDeterminedByServer(/*m_server*/));
    return a;
  }
  try
  {
    std::stoi(s);
  }
  catch(std::exception&)
  {
    throw std::runtime_error("Invalid group assigner: must be either a number or a question mark");
  }
  boost::shared_ptr<GroupAssigner> a(
    new GroupAssignerPredetermined(
      std::stoi(s)));
  return a;
}
//---------------------------------------------------------------------------
GroupAssignerDeterminedByServer::GroupAssignerDeterminedByServer()
  //const Server * const server)
  //: m_server(server)
{

}
//---------------------------------------------------------------------------
/*
int GroupAssignerDeterminedByServer::Assign(
  const int ) const
{
  if (m_server->GetStateGroupDynamics()->HasFreePlaces())
  {
    return m_server->GetStateGroupDynamics()->OccupyFreePlace();
  }
  return -1; //Do not assign or unassign
}
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

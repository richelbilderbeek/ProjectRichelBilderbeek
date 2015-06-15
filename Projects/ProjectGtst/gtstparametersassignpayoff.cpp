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
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "gtstparametersassignpayoff.h"

ribi::gtst::ParametersAssignPayoff::ParametersAssignPayoff()
  : m_message("Assigning payoffs...")
{

}

///Parse a line
void ribi::gtst::ParametersAssignPayoff::Parse(const std::string& s)
{
  if (s.size() > 27 && s.substr(0,27) == "individual_cost_contribute=")
  {
    const std::string t = s.substr(27,s.size()-27);
    throw std::runtime_error("Obsolete parameter: assign_payoff_individual_cost_contribute");
  }
  else if (s.size() > 25 && s.substr(0,25) == "group_benefit_contribute=")
  {
    throw std::runtime_error("Obsolete parameter: assign_payoff_group_benefit_contribute");
    return;
  }
  else if (s.size() > 8 && s.substr(0,8) == "message=")
  {
    const std::string t = s.substr(8,s.size()-8);
    SetMessage(t);
    return;
  }
}

///Set the message displayed in the ParticipantDialogStateAssignPayoff
void ribi::gtst::ParametersAssignPayoff::SetMessage(const std::string& message)
{
  assert(!message.empty());
  m_message = message;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersAssignPayoff& parameters)
{
  os
    << "<parametersassignpayoff>"
    //<< "<group_benefit_contribute>"
    //<< parameters.GetGroupBenefitContribute()
    //<< "</group_benefit_contribute>"
    //<< "<individual_cost_contribute>"
    //<< parameters.GetIndividualCostContribute()
    //<< "</individual_cost_contribute>"
    << "<message>"
    << parameters.GetMessage()
    << "</message>"
    << "</parametersassignpayoff>";

  return os;
}



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
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "fparser.hh"
#include "gtstparametersgroupassign.h"
//#include "trace.h"
#pragma GCC diagnostic pop

ribi::gtst::ParametersGroupAssign::ParametersGroupAssign()
  : m_message_assigned("Waiting for others. You have been assigned to group "),
    m_message_unassigned("Waiting for server to assign you to a group"),
    m_waiting_payoff_function{}
{
  SetWaitingPayoffFunction("0.0");
}

double ribi::gtst::ParametersGroupAssign::CalculateWaitingPayoff(const double average_payoff) const
{
  FunctionParser f;
  //Parse the formula
  f.Parse(m_waiting_payoff_function,"p");
  assert(f.GetParseErrorType()== FunctionParser::FP_NO_ERROR);

  //Evaluate the parsed formula
  const double payoffs[1] = { average_payoff };
  const double payoff_waiting = f.Eval(payoffs);

  if (f.EvalError()!=0)
  {
    std::clog
      << "Function \'"
      << m_waiting_payoff_function
      << "\'could not be evaluated"
      << " for an average payoff of "
      << average_payoff
      << '\n';
    return 0.0;
  }

  return payoff_waiting;
}

///Parse a line
void ribi::gtst::ParametersGroupAssign::Parse(const std::string& s)
{
  if (s.size() > 19 && s.substr(0,19) == "message_unassigned=")
  {
    const std::string t = s.substr(19,s.size()-19);
    SetMessageUnassigned(t);
    return;
  }
  else if (s.size() > 17 && s.substr(0,17) == "message_assigned=")
  {
    const std::string t = s.substr(17,s.size()-17);
    SetMessageAssigned(t);
    return;
  }
  else if (s.size() > 24 && s.substr(0,24) == "waiting_payoff_function=")
  {
    static_assert(sizeof("waiting_payoff_function=") == 24 + 1,"Assume size 24");
    const std::string t = s.substr(24,s.size()-24);
    FunctionParser f;
    //Parse the formula
    f.Parse(t,"p");
    if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
    {
      throw std::runtime_error("group_assign_waiting_payoff_function could not be parsed, use for example \'sqrt(p)+10\'");
    }
    SetWaitingPayoffFunction(t);
    return;
  }

  throw std::runtime_error(
    (std::string("Unparsable parameter file line: group_assign_") + s).c_str());

}

///Set the message shown to an assigned participant
void ribi::gtst::ParametersGroupAssign::SetMessageAssigned(const std::string& message)
{
  assert(!message.empty());
  m_message_assigned = message;
}

///Set the message shown to an unassigned participant
void ribi::gtst::ParametersGroupAssign::SetMessageUnassigned(const std::string& message)
{
  assert(!message.empty());
  m_message_unassigned = message;
}

void ribi::gtst::ParametersGroupAssign::SetWaitingPayoffFunction(const std::string& function)
{
  FunctionParser f;
  //Parse the formula
  f.Parse(function,"p");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    throw std::runtime_error("finished_earnings_function could not be parsed, use for example \'sqrt(p)+10\'");
  }
  m_waiting_payoff_function = function;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersGroupAssign& parameters)
{
  os
    << "<parameterschat>"
    << "<messageassigned>"
    << parameters.GetMessageAssigned()
    << "</messageassigned>"
    << "<messageunassigned>"
    << parameters.GetMessageUnassigned()
    << "</messageunassigned>"
    << "</parameterschat>";

  return os;
}



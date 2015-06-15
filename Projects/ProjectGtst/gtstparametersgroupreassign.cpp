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
#include "gtstparametersgroupreassign.h"
#pragma GCC diagnostic pop

ribi::gtst::ParametersGroupReAssign::ParametersGroupReAssign()
  : m_duration(30),
    m_n_periods(1),
    m_next_period_payoff_function{}
{
  SetNextPeriodPayoffFunction("0.0");
}

double ribi::gtst::ParametersGroupReAssign::CalculateNextPeriodPayoff(const double average_payoff) const
{
  FunctionParser f;
  //Parse the formula
  f.Parse(m_next_period_payoff_function,"p");
  assert(f.GetParseErrorType()== FunctionParser::FP_NO_ERROR);

  //Evaluate the parsed formula
  const double payoffs[1] = { average_payoff };
  const double payoff_for_reaching_next_period = f.Eval(payoffs);

  if (f.EvalError()!=0)
  {
    std::clog
      << "Function \'"
      << m_next_period_payoff_function
      << "\'could not be evaluated"
      << " for a payoff of "
      << average_payoff
      << '\n';
    return 0.0;
  }

  return payoff_for_reaching_next_period;
}

int ribi::gtst::ParametersGroupReAssign::GetDuration() const
{
  assert(m_duration >= 0);
  return m_duration;
}

///Get the number of times the larger-cycle/experiment repeats itself
int ribi::gtst::ParametersGroupReAssign::GetNumberOfPeriods() const
{
  assert(m_n_periods >= 0);
  return m_n_periods;
}

///Parse a line
void ribi::gtst::ParametersGroupReAssign::Parse(const std::string& s)
{
  if (s.size() > 9 && s.substr(0,9) == "duration=")
  {
    const std::string t = s.substr(9,s.size()-9);
    try
    {
      std::stoi(t);
    }
    catch (std::exception&)
    {
      throw std::runtime_error("group_reassign_duration must be an integer");
    }
    const int time = std::stoi(t);
    if (time < 0) throw std::runtime_error("group_reassign_duration must be zero or posive");
    SetDuration(time);
    return;
  }
  else if (s.size() > 18 && s.substr(0,18) == "number_of_periods=")
  {
    const std::string t = s.substr(18,s.size()-18);
    try
    {
      std::stoi(t);
    }
    catch (std::exception&)
    {
      throw std::runtime_error("group_reassign_number_of_periods must be an integer");
    }
    const int n_periods = std::stoi(t);
    if (n_periods < 0) throw std::runtime_error("group_reassign_number_of_periods must be zero or posive");
    SetNumberOfPeriods(n_periods);
    return;
  }
  else if (s.size() > 28 && s.substr(0,28) == "next_period_payoff_function=")
  {
    static_assert(sizeof("next_period_payoff_function=") == 28 + 1,"Assume size 28");
    const std::string t = s.substr(28,s.size()-28);
    FunctionParser f;
    //Parse the formula
    f.Parse(t,"p");
    if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
    {
      throw std::runtime_error("group_reassign_next_period_payoff_function could not be parsed, use for example \'sqrt(p)+10\'");
    }
    SetNextPeriodPayoffFunction(t);
    return;
  }

  throw std::runtime_error(
    (std::string("Unparsable parameter file line: group_reassign_") + s).c_str());

}

void ribi::gtst::ParametersGroupReAssign::SetNextPeriodPayoffFunction(const std::string& function)
{
  FunctionParser f;
  //Parse the formula
  f.Parse(function,"p");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    throw std::runtime_error("finished_earnings_function could not be parsed, use for example \'sqrt(p)+10\'");
  }
  m_next_period_payoff_function = function;
}

void ribi::gtst::ParametersGroupReAssign::SetDuration(const int time)
{
  m_duration = time;
  assert(m_duration >= 0);
}

///Set the number of times the larger-cycle/experiment repeats itself
void ribi::gtst::ParametersGroupReAssign::SetNumberOfPeriods(const int n_periods)
{
  m_n_periods = n_periods;
  assert(m_n_periods >= 1);
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersGroupReAssign& parameters)
{
  os
    << "<parameters_" << parameters.ToStr() << ">"
    //<< "<messageassigned>"
    //<< parameters.GetMessageAssigned()
    //<< "</messageassigned>"
    //<< "<messageunassigned>"
    //<< parameters.GetMessageUnassigned()
    //<< "</messageunassigned>"
    << "</parameters_" << parameters.ToStr() << ">";

  return os;
}


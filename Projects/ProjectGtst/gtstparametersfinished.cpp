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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "fparser.hh"
#include "gtstparametersfinished.h"
#pragma GCC diagnostic pop

ribi::gtst::ParametersFinished::ParametersFinished()
  : m_earnings_function{},
    m_message{}
{
  SetEarningsFunction("1.0 + (0.01 * p)");
  SetMessage("Thanks for participating in this experiment");
}

double ribi::gtst::ParametersFinished::CalculateEarnings(const double payoff) const
{
  FunctionParser f;
  //Parse the formula
  f.Parse(m_earnings_function,"p");
  assert(f.GetParseErrorType()== FunctionParser::FP_NO_ERROR);

  //Evaluate the parsed formula
  const double payoffs[1] = { payoff };
  const double earnings = f.Eval(payoffs);

  if (f.EvalError()!=0)
  {
    std::clog
      << "Function \'"
      << m_earnings_function
      << "\'could not be evaluated"
      << " for a payoff of "
      << payoff
      << '\n';
    return 0.0;
  }

  return earnings;
}

///Parse a line
void ribi::gtst::ParametersFinished::Parse(const std::string& s)
{
  if (s.size() > 8 && s.substr(0,8) == "message=")
  {
    const std::string t = s.substr(8,s.size()-8);
    SetMessage(t);
    return;
  }
  else if (s.size() > 18 && s.substr(0,18) == "earnings_function=")
  {
    const std::string t = s.substr(18,s.size()-18);
    FunctionParser f;
    //Parse the formula
    f.Parse(t,"p");
    if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
    {
      throw std::runtime_error("finished_earnings_function could not be parsed, use for example \'sqrt(p)+10\'");
    }
    SetEarningsFunction(t);
  }
}

///Set the function that is used to calculate the earnings of
///a Participant for participating, from the amount of payoff
///he/she has gathered
void ribi::gtst::ParametersFinished::SetEarningsFunction(const std::string& earnings_function)
{
  FunctionParser f;
  //Parse the formula
  f.Parse(earnings_function,"p");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    throw std::runtime_error("finished_earnings_function could not be parsed, use for example \'sqrt(p)+10\'");
  }
  m_earnings_function = earnings_function;
}

///Set the message shown to the Participant when the experiment has finished
void ribi::gtst::ParametersFinished::SetMessage(const std::string& message)
{
  assert(!message.empty());
  m_message = message;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersFinished& parameters)
{
  os
    << "<parameterschat>"
    << "<earnings_function>"
    << parameters.GetEarningsFunction()
    << "</earnings_function>"
    << "<message>"
    << parameters.GetMessage()
    << "</message>"
    << "</parameterschat>";

  return os;
}



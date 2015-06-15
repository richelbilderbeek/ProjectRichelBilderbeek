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
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>

#include "gtstchooseactionoption.h"
#include "gtstparameterschooseaction.h"
#pragma GCC diagnostic pop

ribi::gtst::ParametersChooseAction::ParametersChooseAction()
  : m_duration{5},
    m_options{},
    m_wait(true)
{
}

int ribi::gtst::ParametersChooseAction::GetDuration() const
{
  assert(m_duration >= 0);
  return m_duration;
}

///Parse a line
void ribi::gtst::ParametersChooseAction::Parse(const std::string& s)
{
  if (s.size() > 5 && s.substr(0,5) == "wait=")
  {
    const std::string t = s.substr(5,s.size()-5);
    if (t=="y" || t=="Y" || t=="1" || t == "n" || t == "N" || t =="0")
    {
      if (t=="y" || t=="Y" || t=="1")
      {
        SetWait(true);
      }
      else
      {
        SetWait(false);
      }
    }
    else
    {
      throw std::runtime_error("choose_action_wait me be either \'y\' or \'n\'");
    }
    return;
  }
  if (s.size() > 9 && s.substr(0,9) == "duration=")
  {
    const std::string t = s.substr(9,s.size()-9);
    try
    {
      std::stoi(t);
    }
    catch (std::exception&)
    {
      throw std::runtime_error("choose_action_duration must be an integer");
    }
    const int time = std::stoi(t);
    if (time < 0) throw std::runtime_error("choose_action_duration must be zero or posive");
    SetDuration(time);
    return;
  }

  if (s.size() > 7 && s.substr(0,7) == "option=")
  {
    const std::string t = s.substr(7,s.size() - 7);
    const std::vector<std::string> v = SeperateString(t,',');
    if (v.size() != 4)
    {
      throw std::runtime_error(
        "choose_action_option line must have four elements");
    }
    assert(v.size() == 4 && "choose_action_options must have four elements");

    const std::string description = v[0];
    const std::string contribution_str = v[1];
    const std::string cost_str = v[2];
    const std::string message = v[3];

    try
    {
      std::stod(contribution_str);
    }
    catch (std::exception&)
    {
      throw std::runtime_error(
        std::string("Incorrectly formed contribution: ")
        + contribution_str);
    }
    try
    {
      std::stod(cost_str);
      //std::stod(cost_str);
    }
    catch (std::exception&)
    {
      throw std::runtime_error(
        std::string("Incorrectly formed cost: ")
        + cost_str);
    }

    const double contribution = std::stod(contribution_str);
    const double cost = std::stod(cost_str);

    boost::shared_ptr<ChooseActionOption> p(
      new ChooseActionOption(contribution,cost,description,message));
    m_options.push_back(p);
    return;
  }
}

///SeperateString splits a std::string
//From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> ribi::gtst::ParametersChooseAction::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::istringstream is(input);
  std::vector<std::string> v;
  for (
    std::string sub;
    std::getline(is, sub, seperator);
    v.push_back(sub))
  {
    //Empty for loop
  }
  return v;
}

void ribi::gtst::ParametersChooseAction::SetDuration(const int time)
{
  m_duration = time;
  assert(m_duration >= 0);
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersChooseAction& parameters)
{
  os
    << "<parameterschooseaction>"
    << "<duration>"
    << parameters.GetDuration()
    << "</duration>"
    << "<wait>"
    << parameters.GetWait()
    << "</wait>";
  const int n_actions = boost::numeric_cast<int>(
    parameters.GetOptions().size());
  for (int i=0; i!=n_actions;++i)
  {
    os
      << "<option" << i << ">"
      << (*(parameters.GetOptions()[i]))
      << "</option" << i << ">";
  }
  os
    << "</parameterschooseaction>";
  return os;
}

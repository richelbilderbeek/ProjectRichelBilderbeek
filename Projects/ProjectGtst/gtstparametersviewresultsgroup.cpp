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
#include <sstream>
#include <stdexcept>

// 

#include "gtstparametersviewresultsgroup.h"
#include "gtstrepeatassigner.h"
#include "gtstrepeatassignerfixed.h"
#include "gtstrepeatassignerrandomgeometric.h"
#include "gtstrepeatassignerrandomuniform.h"

ribi::gtst::ParametersViewResultsGroup::ParametersViewResultsGroup()
  : m_repeat_assigner(new RepeatAssignerFixed(3)),
    m_duration(5)
{
}

int ribi::gtst::ParametersViewResultsGroup::GetDuration() const
{
  assert(m_duration >= 0);
  return m_duration;
}

///Parse a line
void ribi::gtst::ParametersViewResultsGroup::Parse(const std::string& s)
{
  //View results time in the same group, in the IPGG phase
  if (s.size() > 9 && s.substr(0,9) == "duration=")
  {
    const std::string t = s.substr(9,s.size()-9);
    try
    {
      std::stoi(t);
      //std::stoi(t);
    }
    catch (std::exception&)
    //catch (std::exception&)
    {
      throw std::runtime_error("view_results_group_duration must be an integer");
    }
    const int time = std::stoi(t);
    //const int time = std::stoi(t);
    if (time < 0) throw std::runtime_error("view_results_group_duration must be zero or posive");
    SetDuration(time);
    return;
  }
  //View results time in the same group, in the IPGG phase
  if (s.size() > 7 && s.substr(0,7) == "cycles=")
  {
    const std::string t = s.substr(7,s.size()-7);
    ParseCycles(t);
  }
}

///Parse a line starting with cycles=
void ribi::gtst::ParametersViewResultsGroup::ParseCycles(const std::string& s)
{
  if (s.empty()) throw std::runtime_error("Empty value. view_results_group_cycles must non-empty, for example \'2\' or \'[3,5>\'");
  if (s[0] == '[')
  {
    if (s[s.size()-1]!='>') throw std::runtime_error("Invalid range notation. view_results_group_cycles ranges must be defined in the notation \'[from,to>\', for example '[3,5>\'");
    const std::string range_str = s.substr(1,s.size()-2);
    const std::vector<std::string> range = SeperateString(range_str,',');
    if (range.size() != 2) throw std::runtime_error("Invalid range. view_results_group_cycles ranges must be defined in the notation \'[from,to>\', for example '[3,5>\'");
    try
    {
      std::stoi(range[0]);
      //std::stoi(range[0]);
    }
    catch (std::exception&)
    //catch (std::exception&)
    {
      throw std::runtime_error("Non-number at first position in range. view_results_group_cycles must be an integer");
    }
    try
    {
      std::stoi(range[1]);
      //std::stoi(range[1]);
    }
    catch (std::exception&)
    //catch (std::exception&)
    {
      throw std::runtime_error("Non-number at second position in range. view_results_group_cycles must be an integer");
    }
    const int from = std::stoi(range[0]);
    //const int from = std::stoi(range[0]);
    const int to = std::stoi(range[1]);
    //const int to = std::stoi(range[1]);
    if (from >= to)
    {
      throw std::runtime_error("Invalid range: \'from\' must be less than \'to\' value. view_results_group_cycles must be an integer");
    }
    boost::shared_ptr<RepeatAssigner> assigner(
      new RepeatAssignerRandomUniform(from,to));
    this->SetRepeatAssigner(assigner);
    return;
  }
  else if (s[0] == '?')
  {
    const std::string t = s.substr(1,s.size()-1);
    try
    {
      std::stod(t);
      //std::stod(t);
    }
    catch (std::exception&)
    //catch (std::exception&)
    {
      throw std::runtime_error("w must be a double (view_results_group_cycles)");
    }
    const double w = std::stod(t);
    //const double w = std::stod(t);
    if (w < 0.0) throw std::runtime_error("w must be positive (view_results_group_cycles)");
    if (w >= 1.0) throw std::runtime_error("w must be smaller than one (view_results_group_cycles)");
    boost::shared_ptr<RepeatAssigner> assigner(
      new RepeatAssignerRandomGeometric(w));
    this->SetRepeatAssigner(assigner);
    return;
  }
  else
  {
    try
    {
      std::stoi(s);
      //std::stoi(s);
    }
    catch (std::exception&)
    //catch (std::exception&)
    {
      throw std::runtime_error("view_results_group_cycles must be an integer");
    }
    const int n_cycles = std::stoi(s);
    //const int n_cycles = std::stoi(s);
    if (n_cycles <= 0) throw std::runtime_error("view_results_group_cycles must be posive");
    boost::shared_ptr<RepeatAssigner> assigner(
      new RepeatAssignerFixed(n_cycles));
    this->SetRepeatAssigner(assigner);
    return;
  }
}

///SeperateString splits a std::string
//From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> ribi::gtst::ParametersViewResultsGroup::SeperateString(
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

void ribi::gtst::ParametersViewResultsGroup::SetDuration(const int time)
{
  m_duration = time;
  assert(m_duration >= 0);
}

void ribi::gtst::ParametersViewResultsGroup::SetRepeatAssigner(boost::shared_ptr<RepeatAssigner> assigner)
{
  assert(assigner);
  m_repeat_assigner = assigner;
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersViewResultsGroup& parameters)
{
  os
    << "<parametersviewresultsgroup>"
    << "<duration>"
    << parameters.GetDuration()
    << "</duration>"
    << "<repeat_assigner>"
    << (parameters.GetRepeatAssigner()->ToStr())
    << "</repeat_assigner>"
    << "</parametersviewresultsgroup>";

  return os;
}



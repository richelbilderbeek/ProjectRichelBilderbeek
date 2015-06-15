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

// 

#include "gtstparametersviewresultsvoting.h"

ribi::gtst::ParametersViewResultsVoting::ParametersViewResultsVoting()
  : m_duration(5)
{
}

int ribi::gtst::ParametersViewResultsVoting::GetDuration() const
{
  assert(m_duration >= 0);
  return m_duration;
}

///Parse a line
void ribi::gtst::ParametersViewResultsVoting::Parse(const std::string& s)
{
  //View results time in the same group, in the IPGG phase
  if (s.size() > 9 && s.substr(0,9) == "duration=")
  {
    const std::string t = s.substr(9,s.size()-9);
    try { std::stoi(t); }
    catch (std::exception&)
    {
      throw std::runtime_error("view_results_voting_duration must be an integer");
    }
    const int time = std::stoi(t);
    if (time < 0) throw std::runtime_error("view_results_voting_duration must be zero or posive");
    SetDuration(time);
    return;
  }
}

void ribi::gtst::ParametersViewResultsVoting::SetDuration(const int time)
{
  m_duration = time;
  assert(m_duration >= 0);
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersViewResultsVoting& parameters)
{
  os
    << "<parametersviewresultsvoting>"
    << "<time>"
    << parameters.GetDuration()
    << "</time>"
    << "</parametersviewresultsvoting>";

  return os;
}



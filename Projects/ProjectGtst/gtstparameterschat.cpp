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

#include "gtstparameterschat.h"

ribi::gtst::ParametersChat::ParametersChat()
  : m_duration(5)
{

}

int ribi::gtst::ParametersChat::GetDuration() const
{
  assert(m_duration >= 0);
  return m_duration;
}

void ribi::gtst::ParametersChat::SetDuration(const int time)
{
  m_duration = time;
  assert(m_duration >= 0);
}

///Parse a line
void ribi::gtst::ParametersChat::Parse(const std::string& s)
{
  //Chat time
  if (s.size() > 9 && s.substr(0,9) == "duration=")
  {
    const std::string t = s.substr(9,s.size()-9);
    try
    {
      std::stoi(t);
      //std::stoi(t);
    }
    catch (std::exception&)
    {
      throw std::runtime_error("chat_duration must be an integer");
    }
    const int time = std::stoi(t);
    //const int time = std::stoi(t);
    if (time < 0) throw std::runtime_error("chat_duration must be zero or posive");
    SetDuration(time);
    return;
  }
}

std::ostream& ribi::gtst::operator<<(std::ostream& os,const ParametersChat& parameters)
{
  os
    << "<parameterschat>"
    << "<duration>"
    << parameters.GetDuration()
    << "</duration>"
    << "</parameterschat>";

  return os;
}



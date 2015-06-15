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

#include "gtstrepeatassignerrandomuniform.h"

ribi::gtst::RepeatAssignerRandomUniform::RepeatAssignerRandomUniform(const int from, const int to)
  : m_from(from),
    m_to(to)
{
  assert(m_from > 0 && "An experimental state must be visited at least once");
  assert(m_to > 0 && "An experimental state must be visited at least once");
  assert(m_from != m_to && "A range consists of two different number");
  assert(m_from < m_to && "A range must start with the lower number");
}

int ribi::gtst::RepeatAssignerRandomUniform::Assign() const
{
  const int value
    = m_from + (std::rand() % (m_from - m_to));
  assert(value >= m_from && "A range starts at m_from");
  assert(value  < m_to && "A range from m_from to _and not including_ m_to");

  m_assigned_values.push_back(value);

  assert(CanGetLastAssigned());
  assert(GetLastAssigned() == value);
  return value;
}

///Converts RepeatAssignerRandomUniform to std::string
const std::string ribi::gtst::RepeatAssignerRandomUniform::ToStr() const
{
  return
      std::string("<repeatassigner_random_uniform>")
    + std::string("<from>")
    + std::to_string(m_from)
    + std::string("</from>")
    + std::string("<to>")
    + std::to_string(m_to)
    + std::string("</to>")
    + std::string("</repeatassigner_random_uniform>");
}


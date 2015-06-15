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
//#include <cstdlib>
#include "gtstrepeatassignerfixed.h"

ribi::gtst::RepeatAssignerFixed::RepeatAssignerFixed(const int value)
  : RepeatAssigner{},
    m_value(value)
{
  assert(m_value > 0 && "An experimental state must be visited at least once");
}

int ribi::gtst::RepeatAssignerFixed::Assign() const
{
  m_assigned_values.push_back(m_value);

  assert(CanGetLastAssigned());
  assert(GetLastAssigned() == m_value);
  return m_value;
}

///Converts RepeatAssignerFixed to std::string
const std::string ribi::gtst::RepeatAssignerFixed::ToStr() const
{
  return
      std::string("<repeatassigner_fixed>")
    + std::to_string(m_value)
    + std::string("</repeatassigner_fixed>");
}


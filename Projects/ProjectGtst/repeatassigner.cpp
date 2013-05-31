//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
Copyright (C) 2011 Richel Bilderbeek

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
#include <cstdlib>
#include <iostream>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "repeatassigner.h"
//---------------------------------------------------------------------------
///Returns the last assigned number of repeats
bool RepeatAssigner::CanGetLastAssigned() const
{
  return !m_assigned_values.empty();
}
//---------------------------------------------------------------------------
///Returns if there already is a value assigned
int RepeatAssigner::GetLastAssigned() const
{
  if (!CanGetLastAssigned())
  {
    std::clog << "BREAK\n";
  }
  assert(CanGetLastAssigned());
  return m_assigned_values.back();
}
//---------------------------------------------------------------------------

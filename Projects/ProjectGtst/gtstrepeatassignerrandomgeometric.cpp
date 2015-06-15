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

 

#include "gtstrepeatassignerrandomgeometric.h"

ribi::gtst::RepeatAssignerRandomGeometric::RepeatAssignerRandomGeometric(const double w)
  : m_w(w)
{
  assert(m_w >= 0.0 && "w must be at least zero");
  assert(m_w  < 1.0 && "w must be at highest (but excluding) one");
}

///Assign the number of round that there will be played beforehand by Monte Carlo
int ribi::gtst::RepeatAssignerRandomGeometric::Assign() const
{
  int value = 1;
  //Monte Carlo
  while (GetRandomUniform() < m_w)
  {
    ++value;
  }
  m_assigned_values.push_back(value);

  assert(CanGetLastAssigned());
  assert(GetLastAssigned() == value);
  return value;
}

///Get a random number from 0.0 to 1.0 in a uniform distribution
//From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double ribi::gtst::RepeatAssignerRandomGeometric::GetRandomUniform()
{
  return static_cast<double>(std::rand())
    / static_cast<double>(RAND_MAX);
}

///Converts RepeatAssignerRandomGeometric to std::string
const std::string ribi::gtst::RepeatAssignerRandomGeometric::ToStr() const
{
  return
      std::string("<repeatassigner_random_geometric>")
    + std::string("<w>")
    + std::to_string(m_w)
    + std::string("</w>")
    + std::string("</repeatassigner_random_geometric>");
}


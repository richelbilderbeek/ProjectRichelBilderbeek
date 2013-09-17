//---------------------------------------------------------------------------
/*
RichelBilderbeek::ProgramStatus, status of a program by Richel Bilderbeek
Copyright (C) 2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeekProgramStatus.htm
//---------------------------------------------------------------------------
#include "richelbilderbeekprogramstatus.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

const std::string ribi::RichelBilderbeek::ProgramStatusToStr(const ProgramStatus c)
{
  switch (c)
  {
    case ProgramStatus::yes: return "yes";
    case ProgramStatus::no : return "no";
    case ProgramStatus::nvr: return "never";
    case ProgramStatus::n_a: return "n/a";
    case ProgramStatus::wip: return "wip";
    case ProgramStatus::tbd: return "todo";
    case ProgramStatus::unk: return "unknown";
    default: assert(!"Should not get here");
  }
  throw std::logic_error("RichelBilderbeek::ProgramStatusToStr");
}

const std::string ribi::RichelBilderbeek::ProgramStatusVersion::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::RichelBilderbeek::ProgramStatusVersion::GetVersionHistory() noexcept
{
  return {
    "2012-02-19: Version 1.0: initial version"
  };
}

std::ostream& ribi::RichelBilderbeek::operator<<(std::ostream& os, const ProgramStatus c)
{
  os << ProgramStatusToStr(c);
  return os;
}

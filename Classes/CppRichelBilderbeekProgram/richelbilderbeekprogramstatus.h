//---------------------------------------------------------------------------
/*
RichelBilderbeek::ProgramStatus, status of a program by Richel Bilderbeek
Copyright (C) 2012-2014 Richel Bilderbeek

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
#ifndef RIBI_RICHELBILDERBEEKPROGRAMSTATUS_H
#define RIBI_RICHELBILDERBEEKPROGRAMSTATUS_H

#include <string>
#include <vector>

namespace ribi {

///Status: yes, no, never, not applicable, work in progress, to be done and unknown
enum class ProgramStatus { yes, no, nvr, n_a, wip, tbd, unk };

struct ProgramStatusVersion
{
  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;
};

std::string ProgramStatusToStr(const ProgramStatus c);
std::ostream& operator<<(std::ostream& os, const ProgramStatus c);

} //~namespace ribi

#endif // RIBI_RICHELBILDERBEEKPROGRAMSTATUS_H

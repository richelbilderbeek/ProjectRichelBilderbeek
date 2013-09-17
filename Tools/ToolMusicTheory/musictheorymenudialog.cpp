//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C)  2012  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------


#include "musictheorymenudialog.h"

#include "musicchord.h"
#include "musicnote.h"
#include "musicscale.h"
//#include "qtcreatorprofile.h"

const ribi::About ribi::MusicTheoryMenuDialog::GetAbout() noexcept
{
  About a(
    "Richel Bilderbeek",
    "MusicTheory",
    "tool for visualizing my music theory",
    "the 11th of August 2012",
    "2012",
    "http://www.richelbilderbeek.nl/ToolMusicTheory.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Music::Chord version: " + Music::Chord::GetVersion());
  a.AddLibrary("Music::Note version: " + Music::Note::GetVersion());
  a.AddLibrary("Music::Scale version: " + Music::Scale::GetVersion());
  return a;
}

const std::string ribi::MusicTheoryMenuDialog::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::MusicTheoryMenuDialog::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-08-10: version 1.0: initial version");
  v.push_back("2012-08-11: version 1.1: changes in the background, support crosscompiling to Windows");
  v.push_back("2012-08-17: version 1.2: added multi-scale chord relations");
  return v;
}


//---------------------------------------------------------------------------
/*
Visual ABC, visual ABC editor
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolVisualAbc.htm
//---------------------------------------------------------------------------
#ifndef TOOLVISUALABCMAINDIALOG_H
#define TOOLVISUALABCMAINDIALOG_H

#include <string>
#include <vector>

namespace ribi {

struct VisualAbcMainDialog
{
  static void ConvertToPng(const std::string& s);
  static void ConvertToMid(const std::string& s);
  static void PlayMid();
  static std::vector<std::string> GetAbcFriday();
  static std::string m_abc_filename;
  static std::string m_log_filename;
  static std::string m_mid_filename;
  static std::string m_png_filename;
  static std::string m_pngs_filename;
};

} //~namespace ribi

#endif // TOOLVISUALABCMAINDIALOG_H

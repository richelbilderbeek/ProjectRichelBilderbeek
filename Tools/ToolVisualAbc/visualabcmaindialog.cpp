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
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "visualabcmaindialog.h"
#pragma GCC diagnostic pop

std::string ribi::VisualAbcMainDialog::m_abc_filename = "temp.abc";
std::string ribi::VisualAbcMainDialog::m_log_filename = "temp.log";
std::string ribi::VisualAbcMainDialog::m_mid_filename = "temp.mid";
std::string ribi::VisualAbcMainDialog::m_png_filename = "temp.png";
std::string ribi::VisualAbcMainDialog::m_pngs_filename = "temp-0.png";

std::vector<std::string> ribi::VisualAbcMainDialog::GetAbcFriday()
{
  std::vector<std::string> v;
  v.push_back("X:1");
  v.push_back("T:Friday");
  v.push_back("C:Richel Bilderbeek");
  v.push_back("L:1/4");
  v.push_back("Q:1/4=240");
  v.push_back("M:4/4");
  v.push_back("K:B");
  v.push_back("V:V1 clef=treble");
  v.push_back("V:V2 clef=bass");
  v.push_back("%");
  v.push_back("% B  : F# B D#");
  v.push_back("% G#m: G# B D#");
  v.push_back("% E  : G# B E ");
  v.push_back("% F# : F# A# C#");
  v.push_back("% B Scale = C# D# E F# G# A# B ");
  v.push_back("% Intro 1-8");
  v.push_back("%");
  v.push_back("% Verse 1, 9-12");
  v.push_back("%");
  v.push_back("[V:V1] [FBd]2 d  B   | [FBd]2 d B   | [GBd]2 B d   | [GBd]2 B d    | ");
  v.push_back("w:     dot    se-ven | zip    ~ ex- | tract in the | mor-     ning |");
  v.push_back("[V:V2] B,,4          | B,4          | G,,4         | G,4           |");
  v.push_back("%      B             |              | G#m          |               | ");
  v.push_back("%");
  v.push_back("% Verse 1, 13-16");
  v.push_back("%");
  v.push_back("[V:V1] [GBe]2  e B   | [GBe]2  e B  | [FAc]2 c A  | [FAc]2 c   A  |");
  v.push_back("w:     gotta have my | tools, gotta | have ~ mer- | cu-    ri- al |");
  v.push_back("[V:V2] E,4           | E4           | F,,4        | F,4           |");
  v.push_back("%      E             |              | F#          |               |");
  return v;
}

void ribi::VisualAbcMainDialog::ConvertToPng(const std::string& s)
{
  //Save to file
  {
    std::ofstream f(m_abc_filename.c_str());
    f << s;
  }
  //Convert ABC file to PS
  {
    const std::string cmd = "abcm2ps " + m_abc_filename;
    const int error = std::system(cmd.c_str());
    assert(!error);
    if (error) throw std::runtime_error(cmd.c_str());
  }
  //Convert PS file to PNG or PNGs

  {
    const std::string cmd
      = "convert -density 250 -trim Out.ps "
      + m_png_filename;
    const int error = std::system(cmd.c_str());
    assert(!error);
    if (error) throw std::runtime_error(cmd.c_str());
  }
}

void ribi::VisualAbcMainDialog::ConvertToMid(const std::string& s)
{
  //Save to file
  {
    std::ofstream f(m_abc_filename.c_str());
    f << s;
  }
  //Convert ABC file to midi
  {
    const std::string cmd = "abc2midi "
      + m_abc_filename
      + " -o " + m_mid_filename;
    const int error = std::system(cmd.c_str());
    assert(!error);
    if (error) throw std::runtime_error(cmd.c_str());
  }
}

void ribi::VisualAbcMainDialog::PlayMid()
{
  //Convert ABC file to midi
  {
    const std::string cmd = "playsound "
      + m_mid_filename;
    const int error = std::system(cmd.c_str());
    assert(!error && "playsound not found, type 'sudo apt-get install playmidi'");
    if (error) throw std::runtime_error(cmd.c_str());
  }
}


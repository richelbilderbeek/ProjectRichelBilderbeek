//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "connectthreeresources.h"

#include <cassert>
#include <stdexcept>
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>
//---------------------------------------------------------------------------
#include "trace.h"
//---------------------------------------------------------------------------
#include <QFile>
//---------------------------------------------------------------------------
ConnectThreeResources::ConnectThreeResources()
  : // m_background_filename(
    //  "RichelbilderbeekNlBackground.png"),
    m_computers_filenames(
    {
      "ConnectThreeComputer1.png",
      "ConnectThreeComputer2.png",
      "ConnectThreeComputer3.png"
    } ),
    m_computer_grey_filename(
      "ConnectThreeComputerGrey.png"),
    m_css("wt.css"),
    m_empty_filename(
      "ConnectThreeEmpty.png"),
    m_instructions_good_filenames(
    {
      "ConnectThreeGood1.png",
      "ConnectThreeGood2.png"
    } ),
    m_instructions_wrong_filename(
      "ConnectThreeWrong.png"),
    m_players_filenames(
    {
      "ConnectThreePlayer1.png",
      "ConnectThreePlayer2.png",
      "ConnectThreePlayer3.png"
    } ),
    m_players_grey_filenames(
    {
      "ConnectThreePlayer1Grey.png",
      "ConnectThreePlayer2Grey.png",
      "ConnectThreePlayer3Grey.png"
    } )
{
  Check();
}
//---------------------------------------------------------------------------
void ConnectThreeResources::Check()
{
  //CheckFile(m_background_filename);
  CheckFile(m_computers_filenames[0]);
  CheckFile(m_computers_filenames[1]);
  CheckFile(m_computers_filenames[2]);
  CheckFile(m_computer_grey_filename);
  CheckFile(m_css);
  CheckFile(m_empty_filename);
  CheckFile(m_instructions_good_filenames[0]);
  CheckFile(m_instructions_good_filenames[1]);
  CheckFile(m_instructions_wrong_filename);
  CheckFile(m_players_filenames[0]);
  CheckFile(m_players_filenames[1]);
  CheckFile(m_players_filenames[2]);
  CheckFile(m_players_grey_filenames[0]);
  CheckFile(m_players_grey_filenames[1]);
  CheckFile(m_players_grey_filenames[2]);
}
//---------------------------------------------------------------------------
void ConnectThreeResources::CheckFile(const std::string& s)
{
  if (!boost::filesystem::exists(s))
  {
    const std::string filename = ":/images/" + s;
    QFile f(filename.c_str());
    f.copy(s.c_str());
    if (!boost::filesystem::exists(s)) { TRACE(s); }
    assert(boost::filesystem::exists(s));
  }
  if (!boost::filesystem::exists(s)) { TRACE(s); }
  assert(boost::filesystem::exists(s));
}
//---------------------------------------------------------------------------

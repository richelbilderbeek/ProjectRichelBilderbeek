//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2013 Richel Bilderbeek

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
#ifndef CONNECTTHREERESOURCES_H
#define CONNECTTHREERESOURCES_H

#include <string>
#include <vector>

///ConnectThreeResources contains all resources' filenames
///and checks that these are present
struct ConnectThreeResources
{
  virtual ~ConnectThreeResources();
  //const std::string& GetBackgroundFilename() const { return m_background_filename; }
  const std::string& GetCss() const { return m_css; }
  const std::vector<std::string>& GetComputersFilenames() const { return  m_computers_filenames; }
  const std::string& GetComputerGreyFilename() const { return m_computer_grey_filename; }
  const std::string& GetEmptyFilename() const { return m_empty_filename; }
  const std::vector<std::string>& GetInstructionsGoodFilenames() const { return  m_instructions_good_filenames; }
  const std::string& GetInstructionsWrongFilename() const { return m_instructions_wrong_filename; }
  const std::vector<std::string>& GetPlayersFilenames() const { return  m_players_filenames; }
  const std::vector<std::string>& GetPlayersGreyFilenames() const { return  m_players_grey_filenames; }

  protected:
  ConnectThreeResources(
    const std::vector<std::string>& computers_filenames,
    const std::string& computer_grey_filename,
    const std::string& css,
    const std::string& empty_filename,
    const std::vector<std::string>& instructions_good_filenames,
    const std::string& instructions_wrong_filename,
    const std::vector<std::string>& players_filenames,
    const std::vector<std::string>& players_grey_filenames
    );

  //const std::string m_background_filename;
  const std::vector<std::string> m_computers_filenames;
  const std::string m_computer_grey_filename;
  const std::string m_css;
  const std::string m_empty_filename;
  const std::vector<std::string> m_instructions_good_filenames;
  const std::string m_instructions_wrong_filename;
  const std::vector<std::string> m_players_filenames;
  const std::vector<std::string> m_players_grey_filenames;
  void Check();
  private:
  void CheckFile(const std::string& s);
};

#endif // CONNECTTHREERESOURCES_H

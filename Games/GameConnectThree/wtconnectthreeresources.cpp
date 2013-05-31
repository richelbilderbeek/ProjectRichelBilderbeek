//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2011 Richel Bilderbeek

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
#include <Wt/WFileResource>
#include <Wt/WResource>
//---------------------------------------------------------------------------
#include "wtconnectthreeresources.h"
//---------------------------------------------------------------------------
//Enable debugging
#undef NDEBUG
#include <cassert>
//---------------------------------------------------------------------------
WtConnectThreeResources * WtConnectThreeResources::m_instance = 0;
//---------------------------------------------------------------------------
WtConnectThreeResources::WtConnectThreeResources()
#ifdef DO_REALLY_REALLY_USE_WT_RESOURCES
  :
#ifdef BILDERBIKKEL_USE_IMAGE_PNG_AS_FIRST_ARGUMENT
    m_computers(
      {
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetComputersFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetComputersFilenames()[1])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetComputersFilenames()[2]))
      } ),
    m_computer_grey(
      new Wt::WFileResource("image/png",GetComputerGreyFilename())),
    m_empty(
      new Wt::WFileResource("image/png",GetEmptyFilename())),
    m_instructions_good(
      {
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetInstructionsGoodFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetInstructionsGoodFilenames()[1])),
      } ),
    m_instructions_wrong(
      new Wt::WFileResource("image/png",GetInstructionsWrongFilename())),
    m_players(
      {
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetPlayersFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetPlayersFilenames()[1])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetPlayersFilenames()[2]))
      } ),
    m_players_grey(
      {
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetPlayersGreyFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetPlayersGreyFilenames()[1])),
        boost::shared_ptr<Wt::WResource>(new Wt::WFileResource("image/png",GetPlayersGreyFilenames()[2]))
      } )
#else
//This feels so stupid...
    m_computers(
      {
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetComputersFilenames()[0],
            GetComputersFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetComputersFilenames()[1],
            GetComputersFilenames()[1])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetComputersFilenames()[2],
            GetComputersFilenames()[2]))
      } ),
    m_computer_grey(
      new Wt::WFileResource(
        GetComputerGreyFilename(),
        GetComputerGreyFilename())),
    m_empty(
      new Wt::WFileResource(
        GetEmptyFilename(),
        GetEmptyFilename())),
    m_instructions_good(
      {
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetInstructionsGoodFilenames()[0],
            GetInstructionsGoodFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetInstructionsGoodFilenames()[1],
            GetInstructionsGoodFilenames()[1])),
      } ),
    m_instructions_wrong(
      new Wt::WFileResource(
        GetInstructionsWrongFilename(),
        GetInstructionsWrongFilename())),
    m_players(
      {
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetPlayersFilenames()[0],
            GetPlayersFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetPlayersFilenames()[1],
            GetPlayersFilenames()[1])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetPlayersFilenames()[2],
            GetPlayersFilenames()[2]))
      } ),
    m_players_grey(
      {
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetPlayersGreyFilenames()[0],
            GetPlayersGreyFilenames()[0])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetPlayersGreyFilenames()[1],
            GetPlayersGreyFilenames()[1])),
        boost::shared_ptr<Wt::WResource>(
          new Wt::WFileResource(
            GetPlayersGreyFilenames()[2],
            GetPlayersGreyFilenames()[2]))
      } )
#endif
#endif
{
  #ifdef DO_REALLY_REALLY_USE_WT_RESOURCES
  assert(m_computers.size() == 3);
  assert(m_players.size() == 3);
  assert(m_players_grey.size() == 3);
  for (int i=0; i!=3; ++i)
  {
    assert(m_computers[i]);
    assert(m_players[i]);
    assert(m_players_grey[i]);
  }
  assert(m_computer_grey);
  assert(m_empty);
  #endif
}
//---------------------------------------------------------------------------
WtConnectThreeResources * WtConnectThreeResources::GetInstance()
{
  if (!m_instance) m_instance = new WtConnectThreeResources;
  assert(m_instance);
  return m_instance;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

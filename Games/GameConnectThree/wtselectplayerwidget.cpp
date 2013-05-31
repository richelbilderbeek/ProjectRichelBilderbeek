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
#include <Wt/WImage>
#include <Wt/WPainter>
//---------------------------------------------------------------------------
#include "trace.h"
#include "wtconnectthreeresources.h"
#include "wtselectplayerwidget.h"
//---------------------------------------------------------------------------
//Enable debugging
#undef NDEBUG
#include <cassert>
//---------------------------------------------------------------------------
///Yes, naming the filename twice feels dumb, but
///I could not find enough documentation about
///how I should use the Wt::WPainter::Image constructor
WtSelectPlayerWidget::WtSelectPlayerWidget()
  : m_computer_grey(new Wt::WPainter::Image(
      WtConnectThreeResources::GetInstance()
        ->GetComputerGreyFilename(),
      WtConnectThreeResources::GetInstance()
        ->GetComputerGreyFilename())
      ),
    m_computers(
    {
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetComputersFilenames()[0],
        WtConnectThreeResources::GetInstance()
          ->GetComputersFilenames()[0]
        ),
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetComputersFilenames()[1],
        WtConnectThreeResources::GetInstance()
          ->GetComputersFilenames()[1]
        ),
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetComputersFilenames()[2],
        WtConnectThreeResources::GetInstance()
          ->GetComputersFilenames()[2]
        )
    } ),
    m_players(
    {
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetPlayersFilenames()[0],
        WtConnectThreeResources::GetInstance()
          ->GetPlayersFilenames()[0]),
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetPlayersFilenames()[1],
        WtConnectThreeResources::GetInstance()
          ->GetPlayersFilenames()[1]),
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetPlayersFilenames()[2],
        WtConnectThreeResources::GetInstance()
          ->GetPlayersFilenames()[2])
    } ),
    m_players_grey(
    {
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetPlayersGreyFilenames()[0],
        WtConnectThreeResources::GetInstance()
          ->GetPlayersGreyFilenames()[0]),
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetPlayersGreyFilenames()[1],
        WtConnectThreeResources::GetInstance()
          ->GetPlayersGreyFilenames()[1]),
      new Wt::WPainter::Image(
        WtConnectThreeResources::GetInstance()
          ->GetPlayersGreyFilenames()[2],
        WtConnectThreeResources::GetInstance()
          ->GetPlayersGreyFilenames()[2])
    } )
{
  m_is_player_human[0] = true;
  m_is_player_human[1] = true;
  m_is_player_human[2] = true;

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

  const int sprite_width  = m_computer_grey->width();
  const int sprite_height = m_computer_grey->height();

  this->resize(2 * sprite_width,3 * sprite_height);
  this->mouseWentDown().connect(this, &WtSelectPlayerWidget::OnClick);
  this->update();
}
//---------------------------------------------------------------------------
void WtSelectPlayerWidget::OnClick(const Wt::WMouseEvent& e)
{
  const int sprite_width  = m_computer_grey->width();
  const int sprite_height = m_computer_grey->height();

  const int mouse_x = e.widget().x;
  const int mouse_y = e.widget().y;
  const int index = mouse_y / sprite_height;
  const bool is_human = ( mouse_x / sprite_width == 0);
  m_is_player_human[index] = is_human;
  m_signal_on_clicked();
  this->update();
}
//---------------------------------------------------------------------------
void WtSelectPlayerWidget::paintEvent(Wt::WPaintDevice *paintDevice)
{
  Wt::WPainter painter(paintDevice);
  const int sprite_width  = m_computer_grey->width();
  const int sprite_height = m_computer_grey->height();

  painter.drawImage(0 * sprite_width,0 * sprite_height,m_is_player_human[0] ? *m_players[0]    : *m_players_grey[0]);
  painter.drawImage(0 * sprite_width,1 * sprite_height,m_is_player_human[1] ? *m_players[1]    : *m_players_grey[1]);
  painter.drawImage(0 * sprite_width,2 * sprite_height,m_is_player_human[2] ? *m_players[2]    : *m_players_grey[2]);
  painter.drawImage(1 * sprite_width,0 * sprite_height,m_is_player_human[0] ? *m_computer_grey : *m_computers[0]);
  painter.drawImage(1 * sprite_width,1 * sprite_height,m_is_player_human[1] ? *m_computer_grey : *m_computers[1]);
  painter.drawImage(1 * sprite_width,2 * sprite_height,m_is_player_human[2] ? *m_computer_grey : *m_computers[2]);
}
//---------------------------------------------------------------------------


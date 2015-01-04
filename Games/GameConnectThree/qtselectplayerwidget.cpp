//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtselectplayerwidget.h"
#include <QMouseEvent>
#include <QPainter>
#pragma GCC diagnostic pop

const int ribi::con3::QtSelectPlayerWidget::m_sprite_height = 50;
const int ribi::con3::QtSelectPlayerWidget::m_sprite_width  = 50;

ribi::con3::QtSelectPlayerWidget::QtSelectPlayerWidget(QWidget *parent)
  : QWidget(parent),
    m_is_player_human{},
    m_player1(":/images/ConnectThreePlayer1.png"),
    m_player1_grey(":/images/ConnectThreePlayer1Grey.png"),
    m_player2(":/images/ConnectThreePlayer2.png"),
    m_player2_grey(":/images/ConnectThreePlayer2Grey.png"),
    m_player3(":/images/ConnectThreePlayer3.png"),
    m_player3_grey(":/images/ConnectThreePlayer3Grey.png"),
    m_computer1(":/images/ConnectThreeComputer1.png"),
    m_computer2(":/images/ConnectThreeComputer2.png"),
    m_computer3(":/images/ConnectThreeComputer3.png"),
    m_computer_grey(":/images/ConnectThreeComputerGrey.png")
{
  m_is_player_human[0] = true;
  m_is_player_human[1] = true;
  m_is_player_human[2] = true;
  this->setMinimumWidth( 2 * m_sprite_width );
  this->setMinimumHeight(3 * m_sprite_height);
  this->setMaximumWidth( 2 * m_sprite_width );
  this->setMaximumHeight(3 * m_sprite_height);
}

void ribi::con3::QtSelectPlayerWidget::mousePressEvent(QMouseEvent * e)
{
  const int mouse_x = e->x();
  const int mouse_y = e->y();
  const int index = mouse_y / m_sprite_height;
  const bool is_human = ( mouse_x / m_sprite_width == 0);
  m_is_player_human[index] = is_human;
  this->repaint();
}

void ribi::con3::QtSelectPlayerWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0 * m_sprite_width,0 * m_sprite_height,m_is_player_human[0] ? m_player1 : m_player1_grey);
  painter.drawImage(0 * m_sprite_width,1 * m_sprite_height,m_is_player_human[1] ? m_player2 : m_player2_grey);
  painter.drawImage(0 * m_sprite_width,2 * m_sprite_height,m_is_player_human[2] ? m_player3 : m_player3_grey);
  painter.drawImage(1 * m_sprite_width,0 * m_sprite_height,m_is_player_human[0] ? m_computer_grey : m_computer1);
  painter.drawImage(1 * m_sprite_width,1 * m_sprite_height,m_is_player_human[1] ? m_computer_grey : m_computer2);
  painter.drawImage(1 * m_sprite_width,2 * m_sprite_height,m_is_player_human[2] ? m_computer_grey : m_computer3);
}


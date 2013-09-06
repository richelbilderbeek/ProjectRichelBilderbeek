//---------------------------------------------------------------------------
/*
BeerWanter. A simple game.
Copyright (C) 2005-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBeerWanter.htm
//---------------------------------------------------------------------------
#include "beerwantermaindialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

ribi::BeerWanterMainDialog::BeerWanterMainDialog(
  int screen_width,
  int screen_height,
  int sprite_width,
  int sprite_height,
  int window_width,
  int window_height)
  : m_level(1),
   m_screen_height(screen_height),
   m_screen_width(screen_width),
   m_sprite_height(sprite_height),
   m_sprite_width(sprite_width),
   m_window_height(window_height),
   m_window_width(window_width)
{
  m_cursor_x = m_window_width  / 2;
  m_cursor_y = m_window_height / 2;
  m_sprite_x = (m_window_width  / 2) - (m_sprite_width  / 2);
  m_sprite_y = (m_window_height / 2) - (m_sprite_height / 2);
  m_window_x = (m_screen_width  / 2) - (m_window_width  / 2);
  m_window_y = (m_screen_height / 2) - (m_window_height / 2);
}

bool ribi::BeerWanterMainDialog::ClickWilBeSuccess() const
{
  return (
       (m_cursor_x >= m_sprite_x)
    && (m_cursor_x <= m_sprite_x + m_sprite_width)
    && (m_cursor_y >= m_sprite_y)
    && (m_cursor_y <= m_sprite_y + m_sprite_height));
}

bool ribi::BeerWanterMainDialog::Click()
{
  if (ClickWilBeSuccess())
  {
    //Clicked the sprite
    //Move the sprite to a new random position
    m_sprite_x = std::rand() % (m_window_width  - m_sprite_width );
    m_sprite_y = std::rand() % (m_window_height - m_sprite_height);

    ++m_level;

    return true;
  }
  return false;
}

int ribi::BeerWanterMainDialog::GetRandomCursorShake() const
{
  return (std::rand() % (2*((m_level-1)/2)+1))
    - ((m_level-1)/2);
}

int ribi::BeerWanterMainDialog::GetRandomWindowShake() const
{
  return (std::rand() % (2*((m_level-1)/4)+1))
    - ((m_level-1)/4);
}

const std::string ribi::BeerWanterMainDialog::GetWindowTitle() const
{
  return std::string("BeerWanter (C) 2005-2013 Richel Bilderbeek. Beer already got: ")
    + boost::lexical_cast<std::string>(m_level - 1);
}

void ribi::BeerWanterMainDialog::SetCursorPos(const int x, const int y)
{
  m_cursor_x = x;
  m_cursor_y = y;
}

void ribi::BeerWanterMainDialog::ShakeCursor()
{
  //std::clog
  //  << "ShakeCursor: ("
  //  << m_cursor_x
  //  << ","
  //  << m_cursor_y
  //  << ") -> (";

  //Note that cursor is allowed to leave the window :-)
  m_cursor_x += GetRandomCursorShake();
  m_cursor_y += GetRandomCursorShake();

  //std::clog
  //  << m_cursor_x
  //  << ","
  //  << m_cursor_y
  //  << ")\n";
}

void ribi::BeerWanterMainDialog::ShakeWindow()
{
  m_window_x += GetRandomWindowShake();
  m_window_y += GetRandomWindowShake();
}

//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#ifndef DASWAHRESCHLAGERFESTWIDGET_H
#define DASWAHRESCHLAGERFESTWIDGET_H

#include <iosfwd>
#include <vector>

//Cannot use Boost, due to libnds

namespace ribi {

struct DasWahreSchlagerfestDisplay;

///DasWahreSchlagerfestWidget contains the game logic of Das Wahre Schlagerfest
struct DasWahreSchlagerfestWidget
{
  enum class Key { up, right, down, left };
  enum class Tile { empty, beer, bratwurst, richel };
  struct Cursor
  {
    Cursor(const int any_x, const int any_y, const Tile any_tile)
      : x(any_x), y(any_y), tile(any_tile) {}
    int x; int y; Tile tile;
  };

  DasWahreSchlagerfestWidget(
    DasWahreSchlagerfestDisplay& display,
    const int width = 9,
    const int height = 5
  );
  DasWahreSchlagerfestWidget(const DasWahreSchlagerfestWidget&) = delete;
  DasWahreSchlagerfestWidget& operator=(const DasWahreSchlagerfestWidget&) = delete;

  void Display() const;

  ///Obtain the cursor
  const Cursor& GetCursor() const { return m_cursor; }

  ///Obtain the Y-X ordered tiles, without the cursor
  const std::vector<std::vector<Tile> >& GetTiles() const { return m_v; }

  ///Respond to the user pressing a key
  void PressKey(const Key key);

  private:
  ///The cursor
  Cursor m_cursor;

  ///The display of the game, can be console, GUI or NDS
  DasWahreSchlagerfestDisplay& m_display;

  ///The Y-X ordered tiles
  std::vector<std::vector<Tile>> m_v;

  //Check for three in a rows
  void CheckThree();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os,const DasWahreSchlagerfestWidget& w);

} //~namespace ribi

#endif // DASWAHRESCHLAGERFESTWIDGET_H

//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2014 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "daswahreschlagerfestwidget.h"

#include <numeric>

#include "testtimer.h"
#include "textcanvas.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::DasWahreSchlagerfestWidget::DasWahreSchlagerfestWidget(const int width, const int height)
  : m_signal_changed{},
    m_cursor{Cursor(width / 2,0,Tile::beer)},
    m_v(height,std::vector<Tile>(width,Tile::empty))
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(height == static_cast<int>(m_v.size()));
  assert(width == static_cast<int>(m_v[0].size()));
}

void ribi::DasWahreSchlagerfestWidget::CheckThree()
{
  assert(!m_v.empty());
  assert(!m_v[0].empty());
  const int height = m_v.size();
  const int width = m_v[0].size();
  std::vector<std::vector<bool> > w(height,std::vector<bool>(width,false));
  assert(w.size() == m_v.size());
  assert(w[0].size() == m_v[0].size());
  bool found = false;
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      if (m_v[y][x] == Tile::empty) continue;

      if (x < width-2 && m_v[y][x] == m_v[y][x+1] && m_v[y][x+1] == m_v[y][x+2])
      {
        w[y][x] = true; w[y][x+1] = true; w[y][x+2] = true; found = true;
      }
      if (y < height - 2 && m_v[y][x] == m_v[y+1][x] && m_v[y+1][x] == m_v[y+2][x])
      {
        w[y][x] = true; w[y+1][x] = true; w[y+2][x] = true; found = true;
      }
      if (x < width -2 && y < height -2 && m_v[y][x] == m_v[y+1][x+1] && m_v[y+1][x+1] == m_v[y+2][x+2])
      {
        w[y][x] = true; w[y+1][x+1] = true; w[y+2][x+2] = true; found = true;
      }
      if (x < width -2 && y > 2 && m_v[y][x] == m_v[y-1][x+1] && m_v[y-1][x+1] == m_v[y-2][x+2])
      {
        w[y][x] = true; w[y-1][x+1] = true; w[y-2][x+2] = true; found = true;
      }
    }
  }
  if (!found) return;
  //Remove the tiles
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      if (w[y][x]) m_v[y][x] = Tile::empty;
    }
  }

  //Make the tiles fall down
  {
    bool found = true;
    while (found)
    {
      found = false;
      for (int y=0; y!=height-1; ++y)
      {
        for (int x=0; x!=width; ++x)
        {
          if (m_v[y][x] != Tile::empty && m_v[y+1][x] == Tile::empty)
          {
            std::swap(m_v[y][x],m_v[y+1][x]);
            found = true;
          }
        }
      }
    }
  }
  //Check if all tile have fallen down
  #ifndef NDEBUG
  {
    for (int y=0; y!=height-1; ++y)
    {
      for (int x=0; x!=width; ++x)
      {
        if (m_v[y][x] != Tile::empty) assert(m_v[y+1][x] != Tile::empty && "Assume no empty space beneath tile");
      }
    }
  }
  #endif
  CheckThree();
}

void ribi::DasWahreSchlagerfestWidget::PressKey(const ribi::DasWahreSchlagerfestWidget::Key key)
{
  switch (key)
  {
    case Key::up:
    {
      //No use
    }
    break;
    case Key::right:
    {
      if (m_cursor.x + 1 < static_cast<int>(m_v[m_cursor.y].size()))
      {
        if (m_cursor.tile == Tile::richel)
        {
          //Richel eats blocks
          ++m_cursor.x;
          m_v[m_cursor.y][m_cursor.x] = Tile::empty;
          m_signal_changed();
        }
        else if (m_v[m_cursor.y][m_cursor.x + 1] == Tile::empty)
        {
          ++m_cursor.x;
          m_signal_changed();
        }
      }
    }
    break;
    case Key::down:
    {
      if (m_cursor.y + 1 != static_cast<int>(m_v.size()))
      {
        if (m_cursor.tile == Tile::richel)
        {
          //Richel eats blocks
          ++m_cursor.y;
          m_v[m_cursor.y][m_cursor.x] = Tile::empty;
          m_signal_changed();
          return;
        }
        else if (m_v[m_cursor.y+1][m_cursor.x] == Tile::empty)
        {
          ++m_cursor.y;
          m_signal_changed();
          return;
        }
      }
      if (m_cursor.y + 1 == static_cast<int>(m_v.size()) || m_v[m_cursor.y+1][m_cursor.x] != Tile::empty)
      {
        //Place non-Richel block
        if (m_cursor.tile != Tile::richel)
        {
          m_v[m_cursor.y][m_cursor.x] = m_cursor.tile;
          //Check for three in a row
          CheckThree();
        }
        //Place cursor
        m_cursor.x = static_cast<int>(m_v[0].size()) / 2;
        m_cursor.y = 0;
        while (m_v[m_cursor.y+1][m_cursor.x] != Tile::empty)
        {
          //Look for another spot
          m_cursor.x = std::rand() % static_cast<int>(m_v[0].size());
        }

        if (m_v[m_cursor.y+1][m_cursor.x] != Tile::empty)
        {
          assert(!"Impossible since version 2.2");
          m_cursor.tile = Tile::richel;
        }
        else
        {
          //New
          if (std::accumulate(m_v.begin(),m_v.end(),0,
              [](int& sum, const std::vector<Tile>& w)
              { return sum + std::count(w.begin(),w.end(),Tile::beer); }
            ) > 5) { m_cursor.tile = Tile::beer; }
          else if (std::accumulate(m_v.begin(),m_v.end(),0,
              [](int& sum, const std::vector<Tile>& w)
              { return sum + std::count(w.begin(),w.end(),Tile::bratwurst); }
            ) > 5) { m_cursor.tile = Tile::bratwurst; }
          else m_cursor.tile = (std::rand() >> 4) % 2 ? Tile::beer : Tile::bratwurst;
        }
        m_signal_changed();
      }

    }
    break;
    case Key::left:
    {
      if (m_cursor.x > 0)
      {
        if (m_cursor.tile == Tile::richel)
        {
          //Richel eats blocks
          --m_cursor.x;
          m_v[m_cursor.y][m_cursor.x] = Tile::empty;
          m_signal_changed();
        }
        else if (m_v[m_cursor.y][m_cursor.x - 1] == Tile::empty)
        {
          --m_cursor.x;
          m_signal_changed();
        }
      }
    }
    break;
  }
}

#ifndef NDEBUG
void ribi::DasWahreSchlagerfestWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

const boost::shared_ptr<ribi::TextCanvas> ribi::DasWahreSchlagerfestWidget::ToTextCanvas() const noexcept
{
  const int n_rows = static_cast<int>(GetTiles().size());
  assert(n_rows > 0);
  const int n_cols = static_cast<int>(GetTiles()[0].size());
  assert(n_cols > 0);

  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(n_cols,n_rows)
  };

  for (int row=0; row!=n_rows; ++row)
  {
    for (int col=0; col!=n_cols; ++col)
    {
      DasWahreSchlagerfestWidget::Tile tile = GetTiles()[row][col];
      const auto cursor = GetCursor();
      if (col == cursor.x && row == cursor.y) { tile = cursor.tile; }
      char c = ' ';
      switch (tile)
      {
        case DasWahreSchlagerfestWidget::Tile::beer     : c = 'V'; break;
        case DasWahreSchlagerfestWidget::Tile::bratwurst: c = 'U'; break;
        case DasWahreSchlagerfestWidget::Tile::empty    : c = '.'; break;
        case DasWahreSchlagerfestWidget::Tile::richel   : c = 'R'; break;
      }
      canvas->PutChar(col,row,c);
    }
  }
  return canvas;
}

std::ostream& ribi::operator<<(std::ostream& os, const ribi::DasWahreSchlagerfestWidget& w)
{
  os << (*w.ToTextCanvas());
  return os;
}

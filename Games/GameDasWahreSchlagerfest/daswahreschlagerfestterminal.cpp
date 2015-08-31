#include "daswahreschlagerfestterminal.h"

#include <cassert>
#include <iostream>
#include "textcanvas.h"
#include "daswahreschlagerfestwidget.h"

ribi::dws::Terminal::Terminal()
  : m_auto_play{false}
{

}

void ribi::dws::Terminal::DoDisplay(const Widget& widget)
{

  const int n_rows = static_cast<int>(widget.GetTiles().size());
  assert(n_rows > 0);
  const int n_cols = static_cast<int>(widget.GetTiles()[0].size());
  assert(n_cols > 0);

  TextCanvas canvas(n_cols,n_rows);

  for (int row=0; row!=n_rows; ++row)
  {
    for (int col=0; col!=n_cols; ++col)
    {
      Tile tile = widget.GetTiles()[row][col];
      const auto cursor = widget.GetCursor();
      if (col == cursor.x && row == cursor.y) { tile = cursor.tile; }
      const char c = ToChar(tile);
      canvas.PutChar(col,row,c);
    }
  }
  std::cout << canvas << std::endl;
}

void ribi::dws::Terminal::OnChanged(const Widget& /* widget */)
{
  //Display(widget);
}

ribi::dws::Key ribi::dws::Terminal::RequestKey()
{
  if (m_auto_play)
  {
    switch((std::rand() >> 4) % 4)
    {
      default:
      case 0: //Prefer downwards
      case 1: return ribi::dws::Key::down;
      case 2: return ribi::dws::Key::left;
      case 3: return ribi::dws::Key::right;
    }
  }
  else
  {
    while (1)
    {
      char c = '\0';
      std::cin >> c;

      if (!std::cin)
      {
        std::cout << "Please type 'a', 's', 'd' or 'q'" << std::endl;
        continue;
      }

      switch(c)
      {
        case 's': return ribi::dws::Key::down;
        case 'a': return ribi::dws::Key::left;
        case 'd': return ribi::dws::Key::right;
        case 'q': return ribi::dws::Key::quit;
        default: break;
      }
    }
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "tictactoewidget.h"

#include <cassert>
#include "textcanvas.h"
#include "tictactoegame.h"

#pragma GCC diagnostic pop

ribi::tictactoe::Widget::Widget()
  : m_signal_changed{},
    m_game{new Game},
    m_x{1},
    m_y{1}
{

}

bool ribi::tictactoe::Widget::CanSelect(const int x, const int y) const noexcept
{
  return GetGame()->CanDoMove(x,y);
}

void ribi::tictactoe::Widget::DoMove() noexcept
{
  assert(GetGame()->CanDoMove(m_x,m_y));
  m_game->DoMove(m_x,m_y);
}

std::string ribi::tictactoe::Widget::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::tictactoe::Widget::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2014-xx-xx: version 1.0: initial version, in GameTicTacToe folder",
    "2014-03-17: version 1.1: moved from the game TicTacToe to CppTicTacToeFolder, improved interface"
  };
  return v;
}

ribi::tictactoe::Winner ribi::tictactoe::Widget::GetWinner() const noexcept
{
  return GetGame()->GetWinner();
}

void ribi::tictactoe::Widget::PressKey(const ribi::tictactoe::Key key) noexcept
{
  switch (key)
  {
    case Key::up    : if (m_y > 0) --m_y; m_signal_changed(); break;
    case Key::right : if (m_x < 2) ++m_x; m_signal_changed(); break;
    case Key::down  : if (m_y < 2) ++m_y; m_signal_changed(); break;
    case Key::left  : if (m_x > 0) --m_x; m_signal_changed(); break;
    case Key::select:
    {
      if (m_game->CanDoMove(m_x,m_y))
      {
        m_game->DoMove(m_x,m_y);
        m_signal_changed();
      }
    }
    break;
  }
}

void ribi::tictactoe::Widget::Restart() noexcept
{
  m_game->Restart();
}

void ribi::tictactoe::Widget::Select(const int x, const int y) noexcept
{
  assert(CanSelect(x,y));
  if (m_x != x || m_y != y)
  {
    m_x = x;
    m_y = y;
    m_signal_changed();
  }
}

boost::shared_ptr<ribi::TextCanvas> ribi::tictactoe::Widget::ToTextCanvas() const noexcept
{
  const boost::shared_ptr<TextCanvas> canvas {
    m_game->ToTextCanvas()
  };
  assert(canvas);

  if (m_game->GetWinner() == Winner::player1
   || m_game->GetWinner() == Winner::player2)
  {
    for (int i=0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        canvas->PutChar(i,j, m_game->GetWinner() == Winner::player1 ? 'X': 'O');
      }
    }
  }
  const char c = canvas->GetChar(m_x,m_y);
  char d = ' ';
  switch (c)
  {
    case ' ': d = '.'; break;
    case '.': d = ' '; break;
    case 'O': d = 'o'; break;
    case 'X': d = 'x'; break;
    case 'o': d = 'O'; break;
    case 'x': d = 'X'; break;
  }
  canvas->PutChar(m_x,m_y,d);
  return canvas;
}



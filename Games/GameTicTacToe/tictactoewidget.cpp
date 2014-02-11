#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "tictactoewidget.h"

#include <cassert>
#include "textcanvas.h"
#include "tictactoe.h"

#pragma GCC diagnostic pop

ribi::TicTacToeWidget::TicTacToeWidget()
  : m_signal_changed{},
    m_tictactoe{new TicTacToe},
    m_x{1},
    m_y{1}
{

}

void ribi::TicTacToeWidget::PressKey(const TicTacToeWidget::Key key)
{
  switch (key)
  {
    case Key::up    : if (m_y > 0) --m_y; m_signal_changed(); break;
    case Key::right : if (m_x < 2) ++m_x; m_signal_changed(); break;
    case Key::down  : if (m_y < 2) ++m_y; m_signal_changed(); break;
    case Key::left  : if (m_x > 0) --m_x; m_signal_changed(); break;
    case Key::select:
    {
      if (m_tictactoe->CanDoMove(m_x,m_y))
      {
        m_tictactoe->DoMove(m_x,m_y);
        m_signal_changed();
      }
    }
    break;
  }
}

const boost::shared_ptr<ribi::TextCanvas> ribi::TicTacToeWidget::ToTextCanvas() const noexcept
{
  const boost::shared_ptr<TextCanvas> canvas {
    m_tictactoe->ToTextCanvas()
  };
  assert(canvas);

  if (m_tictactoe->GetWinner() == TicTacToe::player1 || m_tictactoe->GetWinner() == TicTacToe::player2)
  {
    for (int i=0; i!=3; ++i)
    {
      for (int j=0; j!=3; ++j)
      {
        canvas->PutChar(i,j, m_tictactoe->GetWinner() == TicTacToe::player1 ? 'X': 'O');
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

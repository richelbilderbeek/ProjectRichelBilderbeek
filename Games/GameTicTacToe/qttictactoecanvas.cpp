#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttictactoecanvas.h"

#ifdef SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918

#include <QKeyEvent>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "tictactoewidget.h"
#include "qttictactoewidget.h"
#pragma GCC diagnostic pop

ribi::tictactoe::QtTicTacToeCanvas::QtTicTacToeCanvas()
  : QtCanvas(CreateCanvas()),
    m_widget(CreateWidget())
{
  m_widget->m_signal_changed.connect(
    boost::bind(&ribi::tictactoe::QtTicTacToeCanvas::OnChanged,this));

  OnChanged();
}

const boost::shared_ptr<ribi::Canvas> ribi::tictactoe::QtTicTacToeCanvas::CreateCanvas() noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(3,3)
  };
  return canvas;
}

const boost::shared_ptr<ribi::tictactoe::Widget> ribi::tictactoe::QtTicTacToeCanvas::CreateWidget() noexcept
{
  const boost::shared_ptr<Widget> w {
    new Widget
  };
  return w;
}

void ribi::tictactoe::QtTicTacToeCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_widget->PressKey(Key::up);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_widget->PressKey(Key::right);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_widget->PressKey(Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_widget->PressKey(Key::left);
      break;
    case Qt::Key_Space: case Qt::Key_Return:
      m_widget->PressKey(Key::select);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::tictactoe::QtTicTacToeCanvas::OnChanged()
{
  SetCanvas(m_widget->ToTextCanvas());
}

#endif //SUPPORT_RETRO_VERSION_OF_TICTACTOE_AGAIN_20150918

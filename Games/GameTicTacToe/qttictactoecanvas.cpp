#include "qttictactoecanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "tictactoewidget.h"
#include "qttictactoewidget.h"
#pragma GCC diagnostic pop

ribi::QtTicTacToeCanvas::QtTicTacToeCanvas()
  : QtCanvas(CreateCanvas()),
    m_widget(CreateWidget())
{
  m_widget->m_signal_changed.connect(
    boost::bind(&ribi::QtTicTacToeCanvas::OnChanged,this));

  OnChanged();
}

const boost::shared_ptr<ribi::Canvas> ribi::QtTicTacToeCanvas::CreateCanvas() noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(3,3)
  };
  return canvas;
}

const boost::shared_ptr<ribi::TicTacToeWidget> ribi::QtTicTacToeCanvas::CreateWidget() noexcept
{
  const boost::shared_ptr<TicTacToeWidget> w {
    new TicTacToeWidget
  };
  return w;
}

void ribi::QtTicTacToeCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_widget->PressKey(ribi::TicTacToeWidget::Key::up);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_widget->PressKey(ribi::TicTacToeWidget::Key::right);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_widget->PressKey(ribi::TicTacToeWidget::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_widget->PressKey(ribi::TicTacToeWidget::Key::left);
      break;
    case Qt::Key_Space: case Qt::Key_Return:
      m_widget->PressKey(ribi::TicTacToeWidget::Key::select);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::QtTicTacToeCanvas::OnChanged()
{
  SetCanvas(m_widget->ToTextCanvas());
}

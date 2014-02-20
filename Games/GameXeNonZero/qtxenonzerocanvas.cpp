#include "qtxenonzerocanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>
#include <QTimer>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "xenonzeromaindialog.h"
#pragma GCC diagnostic pop

ribi::xnz::QtXeNonZeroCanvas::QtXeNonZeroCanvas(const int width, const int height
)
  : QtCanvas(CreateCanvas(width,height)),
    m_dialog(CreateWidget())
{
  //m_dialog->m_signal_game_over.connect(
  //  boost::bind(&ribi::xnz::QtXeNonZeroCanvas::OnGameOver,this)
  //);
  //m_dialog->m_signal_game_won.connect(
  //  boost::bind(&ribi::xnz::QtXeNonZeroCanvas::OnGameWon,this)
  //);
}

ribi::xnz::QtXeNonZeroCanvas::~QtXeNonZeroCanvas() noexcept
{

}

const boost::shared_ptr<ribi::Canvas> ribi::xnz::QtXeNonZeroCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  assert(canvas);
  return canvas;
}

const boost::shared_ptr<ribi::xnz::Dialog> ribi::xnz::QtXeNonZeroCanvas::CreateWidget(
) noexcept
{
  const boost::shared_ptr<Dialog> w {
    new Dialog
  };
  return w;
}

void ribi::xnz::QtXeNonZeroCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_dialog->OnKeyPress(Key::up);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_dialog->OnKeyPress(Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_dialog->OnKeyPress(Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_dialog->OnKeyPress(Key::right);
      break;
    case Qt::Key_Space: case Qt::Key_Return:
      m_dialog->OnKeyPress(Key::shoot);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
  SetCanvas(m_dialog->GetTextCanvas());
}

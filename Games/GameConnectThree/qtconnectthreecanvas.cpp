#include "qtconnectthreecanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>
#include <QTimer>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "connectthreewidget.h"
#pragma GCC diagnostic pop

ribi::QtConnectThreeCanvas::QtConnectThreeCanvas(
  const int size)
  : QtCanvas(CreateCanvas(size,size)),
    m_dialog(CreateWidget(size))
{
  //m_dialog->m_signal_game_over.connect(
  //  boost::bind(&ribi::QtConnectThreeCanvas::OnGameOver,this)
  //);
  //m_dialog->m_signal_game_won.connect(
  //  boost::bind(&ribi::QtConnectThreeCanvas::OnGameWon,this)
  //);
}

ribi::QtConnectThreeCanvas::~QtConnectThreeCanvas() noexcept
{

}

const boost::shared_ptr<ribi::Canvas> ribi::QtConnectThreeCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  assert(canvas);
  return canvas;
}

const boost::shared_ptr<ribi::ConnectThreeWidget> ribi::QtConnectThreeCanvas::CreateWidget(
  const int size) noexcept
{
  const boost::shared_ptr<ConnectThreeWidget> w {
    new ConnectThreeWidget(size)
  };
  return w;
}

void ribi::QtConnectThreeCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_dialog->OnKeyPress(ribi::ConnectThreeWidget::Key::up);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_dialog->OnKeyPress(ribi::ConnectThreeWidget::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_dialog->OnKeyPress(ribi::ConnectThreeWidget::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_dialog->OnKeyPress(ribi::ConnectThreeWidget::Key::right);
      break;
    case Qt::Key_Space: case Qt::Key_Return:
      m_dialog->OnKeyPress(ribi::ConnectThreeWidget::Key::select);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
  SetCanvas(m_dialog->ToTextCanvas());
}

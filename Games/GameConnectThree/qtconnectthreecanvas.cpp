#include "qtconnectthreecanvas.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>
#include <QTimer>

#include "qtcanvas.h"
#include "textcanvas.h"
#include "connectthreewidget.h"
#pragma GCC diagnostic pop

ribi::con3::QtConnectThreeCanvas::QtConnectThreeCanvas(
  const std::bitset<3>& is_player_human,
  const int width, const int height
)
  : QtCanvas(CreateCanvas(width,height)),
    m_dialog(CreateWidget(is_player_human,width,height))
{
  //m_dialog->m_signal_game_over.connect(
  //  boost::bind(&ribi::con3::QtConnectThreeCanvas::OnGameOver,this)
  //);
  //m_dialog->m_signal_game_won.connect(
  //  boost::bind(&ribi::con3::QtConnectThreeCanvas::OnGameWon,this)
  //);
}

ribi::con3::QtConnectThreeCanvas::~QtConnectThreeCanvas() noexcept
{

}

const boost::shared_ptr<ribi::Canvas> ribi::con3::QtConnectThreeCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  assert(canvas);
  return canvas;
}

const boost::shared_ptr<ribi::con3::ConnectThreeWidget> ribi::con3::QtConnectThreeCanvas::CreateWidget(
  const std::bitset<3>& is_player_human,
  const int width,
  const int height
) noexcept
{
  const boost::shared_ptr<ConnectThreeWidget> w {
    new ConnectThreeWidget(is_player_human,width,height)
  };
  return w;
}

void ribi::con3::QtConnectThreeCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_dialog->OnKeyPress(ribi::con3::ConnectThreeWidget::Key::up);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_dialog->OnKeyPress(ribi::con3::ConnectThreeWidget::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_dialog->OnKeyPress(ribi::con3::ConnectThreeWidget::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_dialog->OnKeyPress(ribi::con3::ConnectThreeWidget::Key::right);
      break;
    case Qt::Key_Space: case Qt::Key_Return:
      m_dialog->OnKeyPress(ribi::con3::ConnectThreeWidget::Key::select);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
  SetCanvas(m_dialog->ToTextCanvas());
}

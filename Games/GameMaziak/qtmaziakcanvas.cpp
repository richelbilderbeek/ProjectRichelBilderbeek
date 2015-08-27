#include "qtmaziakcanvas.h"

#ifdef USE_QTCANVAS


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QKeyEvent>
#include <QTimer>

#include "qtcanvas.h"
 
#include "maziakmaindialog.h"
#pragma GCC diagnostic pop

ribi::maziak::QtMaziakCanvas::QtMaziakCanvas(
  const int size)
  : QtCanvas(CreateCanvas(size,size)),
    m_dialog(CreateWidget(size)),
    m_timer_enemy(new QTimer),
    m_timer_press_key(new QTimer),
    m_timer_show_solution(new QTimer),
    m_view_height(9),
    m_view_width(9)
{
  m_dialog->m_signal_game_over.connect(
    boost::bind(&ribi::maziak::QtMaziakCanvas::OnGameOver,this)
  );
  m_dialog->m_signal_game_won.connect(
    boost::bind(&ribi::maziak::QtMaziakCanvas::OnGameWon,this)
  );
  m_dialog->m_signal_start_showing_solution.connect(
    boost::bind(&ribi::maziak::QtMaziakCanvas::OnTimerStartShowingSolution,this)
  );

  m_timer_press_key->setInterval(100);
  m_timer_enemy->setInterval(1000);
  m_timer_show_solution->setInterval(5000);

  QObject::connect(m_timer_press_key.get(),&QTimer::timeout,
    this,&ribi::maziak::QtMaziakCanvas::OnTimerPressKey);
  QObject::connect(m_timer_enemy.get(),&QTimer::timeout,
    this,&ribi::maziak::QtMaziakCanvas::OnTimerEnemy);
  QObject::connect(m_timer_show_solution.get(),&QTimer::timeout,
    this,&ribi::maziak::QtMaziakCanvas::OnTimerStopShowingSolution);

  m_timer_press_key->start();
  m_timer_enemy->start();

  OnTimerPressKey();
}

ribi::maziak::QtMaziakCanvas::~QtMaziakCanvas() noexcept
{
  m_timer_enemy->stop();
  m_timer_press_key->stop();
  m_timer_show_solution->stop();
}

const boost::shared_ptr<ribi::Canvas> ribi::maziak::QtMaziakCanvas::CreateCanvas(
  const int width, const int height) noexcept
{
  const boost::shared_ptr<Canvas> canvas {
    new TextCanvas(width,height)
  };
  assert(canvas);
  return canvas;
}

const boost::shared_ptr<ribi::maziak::MainDialog> ribi::maziak::QtMaziakCanvas::CreateWidget(
  const int size) noexcept
{
  const boost::shared_ptr<MainDialog> w {
    new MainDialog(size)
  };
  return w;
}

void ribi::maziak::QtMaziakCanvas::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_dialog->OnKeyPress(ribi::maziak::Key::up);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_dialog->OnKeyPress(ribi::maziak::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_dialog->OnKeyPress(ribi::maziak::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_dialog->OnKeyPress(ribi::maziak::Key::right);
      break;
    case Qt::Key_Escape: case Qt::Key_Q:
      close();
  }
}

void ribi::maziak::QtMaziakCanvas::keyReleaseEvent(QKeyEvent *e)
{
  switch(e->key())
  {
    case Qt::Key_Up: case Qt::Key_W:
      m_dialog->OnKeyRelease(ribi::maziak::Key::up);
      break;
    case Qt::Key_Down: case Qt::Key_S:
      m_dialog->OnKeyRelease(ribi::maziak::Key::down);
      break;
    case Qt::Key_Left: case Qt::Key_A:
      m_dialog->OnKeyRelease(ribi::maziak::Key::left);
      break;
    case Qt::Key_Right: case Qt::Key_D:
      m_dialog->OnKeyRelease(ribi::maziak::Key::right);
      break;
  }
}

void ribi::maziak::QtMaziakCanvas::OnTimerPressKey()
{
  m_dialog->OnTimerPressKeys();
  m_dialog->AnimateFighting();
  m_dialog->RespondToCurrentSquare();
  SetTextCanvas(m_dialog->ToTextCanvas(m_view_width,m_view_height));
}

void ribi::maziak::QtMaziakCanvas::OnTimerEnemy()
{
  m_dialog->AnimateFighting();
  m_dialog->AnimateEnemiesAndPrisoners(m_view_width,m_view_height);
  SetTextCanvas(m_dialog->ToTextCanvas(m_view_width,m_view_height));
}

void ribi::maziak::QtMaziakCanvas::OnTimerStopShowingSolution()
{
  m_dialog->SetShowSolution(false);
  m_timer_show_solution->stop();
  SetTextCanvas(m_dialog->ToTextCanvas(m_view_width,m_view_height));
}

void ribi::maziak::QtMaziakCanvas::OnTimerStartShowingSolution()
{
  m_timer_show_solution->start();
  SetTextCanvas(m_dialog->ToTextCanvas(m_view_width,m_view_height));
}

void ribi::maziak::QtMaziakCanvas::OnGameOver()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  //m_text_canvas->PutText(1,1,"GAME");
  //m_text_canvas->PutText(1,2,"OVER");
  //SetCanvas(m_text_canvas);
}

void ribi::maziak::QtMaziakCanvas::OnGameWon()
{
  m_timer_press_key->stop();
  m_timer_enemy->stop();
  m_timer_show_solution->stop();
  //m_text_canvas->PutText(1,1,"WELL");
  //m_text_canvas->PutText(1,2,"DONE");
  //SetCanvas(m_text_canvas);
}

#endif // USE_QTCANVAS

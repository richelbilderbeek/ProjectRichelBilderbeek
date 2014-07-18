#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtknokfightermainwidget.h"

#include <cassert>

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "qtknokfighterbackground.h"
#include "qtknokfighterplayer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtKnokfighterMainWidget::QtKnokfighterMainWidget(QWidget *parent) :
  QGraphicsView(parent),
  m_background(new QtKnokfighterBackground(800,600)),
  m_players(
    {
      boost::shared_ptr<QtKnokfighterPlayer>(new QtKnokfighterPlayer(QtKnokfighterPlayer::Name::richel)),
      boost::shared_ptr<QtKnokfighterPlayer>(new QtKnokfighterPlayer(QtKnokfighterPlayer::Name::joost))
    }
  ),
  m_scene(new QGraphicsScene(this))
{
  #ifndef NDEBUG
  Test();
  #endif
  this->setScene(m_scene);

  //Add the background
  {
    m_scene->addItem(m_background);
    this->setSceneRect(0,0,600,400);
  }

  //Add our heroes
  {
    m_players[0]->setPos(400.0,200.0);
    m_players[1]->setPos(500.0,300.0);
    m_scene->addItem(m_players[0].get());
    m_scene->addItem(m_players[1].get());
  }
  //Set the main timer
  {
    QTimer * const timer = new QTimer(this);
    QObject::connect(
      timer,&QTimer::timeout,
      m_scene,&QGraphicsScene::advance
    );
    QObject::connect(
      timer,&QTimer::timeout,
      this,
      &ribi::QtKnokfighterMainWidget::do_main_timer
    );
    timer->setInterval(20);
    timer->start();
  }
}

void ribi::QtKnokfighterMainWidget::do_main_timer()
{
  //v is the background moving speed. Setting this to e.g. 0.1
  //causes the background to keep the player centered more gradually
  const double v = 0.1;
  double delta_x = 0.0;
  double delta_y = 0.0;
  std::for_each(m_players.begin(),m_players.end(),
    [&delta_x,&delta_y,v,this](const boost::shared_ptr<QtKnokfighterPlayer>& player)
    {
      delta_x += v * (player->pos().x() + (player->pixmap().width() / 2) - this->sceneRect().center().x());
      delta_y += v * (player->pos().y() + (player->pixmap().height() / 2) - this->sceneRect().center().y());
    }
  );

  //const double delta_x =  v * (m_player->pos().x() + (m_player->pixmap().width() / 2) - this->sceneRect().center().x());
  //const double delta_y =  v * (m_player->pos().y() + (m_player->pixmap().height() / 2) - this->sceneRect().center().y());
  this->setSceneRect(this->sceneRect().translated(delta_x,delta_y));
  //Do not let the sceneRect go beyond the edges of the scene
  if (sceneRect().x() < 0.0)
  {
    this->setSceneRect(this->sceneRect().translated( -sceneRect().x() , 0.0));
  }
  if (sceneRect().y() < 0.0)
  {
    this->setSceneRect(this->sceneRect().translated(0.0, -sceneRect().y()));
  }
  if (sceneRect().right() > m_background->pixmap().width())
  {
    this->setSceneRect(this->sceneRect().translated(-sceneRect().right() + m_background->pixmap().width(), 0.0));

  }
  if (sceneRect().bottom() > m_background->pixmap().height())
  {
    this->setSceneRect(this->sceneRect().translated(0.0,-sceneRect().bottom() + m_background->pixmap().height()));

  }
}

void ribi::QtKnokfighterMainWidget::keyPressEvent(QKeyEvent *event)
{
  switch(event->key())
  {
    case Qt::Key_Up   : m_players[0]->setPos(m_players[0]->pos().x() +  0, m_players[0]->pos().y() - 10); break;
    case Qt::Key_Right: m_players[0]->setPos(m_players[0]->pos().x() + 10, m_players[0]->pos().y() +  0); break;
    case Qt::Key_Down : m_players[0]->setPos(m_players[0]->pos().x() +  0, m_players[0]->pos().y() + 10); break;
    case Qt::Key_Left : m_players[0]->setPos(m_players[0]->pos().x() - 10, m_players[0]->pos().y() +  0); break;
    case Qt::Key_W    : m_players[1]->setPos(m_players[1]->pos().x() +  0, m_players[1]->pos().y() - 10); break;
    case Qt::Key_D    : m_players[1]->setPos(m_players[1]->pos().x() + 10, m_players[1]->pos().y() +  0); break;
    case Qt::Key_S    : m_players[1]->setPos(m_players[1]->pos().x() +  0, m_players[1]->pos().y() + 10); break;
    case Qt::Key_A    : m_players[1]->setPos(m_players[1]->pos().x() - 10, m_players[1]->pos().y() +  0); break;
  }

}

#ifndef NDEBUG
void ribi::QtKnokfighterMainWidget::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtKnokfighterMainWidget::Test");
  QtKnokfighterBackground(800,600);
  {
    boost::shared_ptr<QtKnokfighterPlayer> p(new QtKnokfighterPlayer(QtKnokfighterPlayer::Name::richel));
    assert(p);
  }
  {
    boost::shared_ptr<QtKnokfighterPlayer> p(new QtKnokfighterPlayer(QtKnokfighterPlayer::Name::joost));
    assert(p);
  }

  TRACE("Finished ribi::QtKnokfighterMainWidget::Test successfully");
}
#endif

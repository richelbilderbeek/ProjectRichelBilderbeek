#include <cassert>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "qttrongamedialog.h"

#include "tronplayer.h"
#include "ui_qttrongamedialog.h"
#include "tronworldtype.h"
#pragma GCC diagnostic pop

ribi::tron::QtTronGameDialog::QtTronGameDialog(
  QWidget *parent, const std::vector<boost::shared_ptr<Player> > players)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTronGameDialog),
    m_image(new QImage(320,200,QImage::Format_RGB32)),
    m_players(players),
    m_timer(new QTimer(this))
{
  ui->setupUi(this);

  Player::m_world.reset(new WorldTypeDonut(320,200));
  QObject::connect(m_timer,&QTimer::timeout,this,&ribi::tron::QtTronGameDialog::OnTimer);
  m_timer->start(20);
}

ribi::tron::QtTronGameDialog::~QtTronGameDialog() noexcept
{
  delete ui;
}

void ribi::tron::QtTronGameDialog::resizeEvent(QResizeEvent*)
{

}

void ribi::tron::QtTronGameDialog::OnTimer()
{
  for(boost::shared_ptr<Player> player: m_players)
  {
    //Move players
    player->Advance();

    //Draw players
    #ifdef TODO_RJCB
    m_image->setPixel(
      player->GetX(),player->GetY(),
      player->GetColor()
    );
    #endif
  }
  ui->label->setPixmap(QPixmap::fromImage(*m_image));
}

const std::vector<boost::shared_ptr<ribi::tron::Player> > ribi::tron::QtTronGameDialog::CreatePlayers()
{
  std::vector<boost::shared_ptr<Player> > v;
  {
    boost::shared_ptr<Player> p(new ClassicPlayer(159,100,3,qRgb(255,0,0)));
    v.push_back(p);
  }
  {
    boost::shared_ptr<Player> p(new ClassicPlayer(161,100,1,qRgb(0,255,0)));
    v.push_back(p);
  }
  return v;
}

#include <cassert>
#include <cstdlib>

#include <boost/foreach.hpp>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "dialoggame.h"
#include "player.h"
#include "ui_dialoggame.h"
#include "worldtype.h"

DialogGame::DialogGame(QWidget *parent, const std::vector<boost::shared_ptr<Player> >& players)
  : QDialog(parent, Qt::Window),
    ui(new Ui::DialogGame),
    m_timer(new QTimer(this)),
    m_pixmap(0),
    m_width(320),
    m_height(200),
    m_players(players)
{
  ui->setupUi(this);

  Player::m_world.reset(new WorldTypeDonut(m_width,m_height));
  QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(repaint()));
  m_timer->start(20);
}

DialogGame::~DialogGame()
{
  delete ui;
}

void DialogGame::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void DialogGame::resizeEvent(QResizeEvent*)
{

}

void DialogGame::paintEvent(QPaintEvent *)
{
  static bool must_init = true;

  QPainter painter(this);

  if (must_init)
  {
    //QPixmap pixmap(m_width,m_height);
    m_pixmap = new QPixmap(m_width,m_height);
    QImage image = m_pixmap->toImage();
    for (int y=0; y!=m_height; ++y)
    {
      for (int x=0; x!=m_width; ++x)
      {
        image.setPixel(QPoint(x,y),QColor(0,0,0).rgb());
      }
    }
    #ifndef NDEBUG
      QPixmap * const p = m_pixmap;
    #endif
    *m_pixmap = m_pixmap->fromImage(image);
    #ifndef NDEBUG
      assert(m_pixmap == p);
    #endif

    painter.drawPixmap(ui->widget->rect(),*m_pixmap);
    must_init = false;
  }
  else
  {
    QImage image = m_pixmap->toImage();

    BOOST_FOREACH(boost::shared_ptr<Player> player, m_players)
    {
      //Move players
      player->Advance();

      //Draw players
      image.setPixel(
        QPoint(player->GetX(),player->GetY()),
        QColor(player->m_r,player->m_g,player->m_b).rgb());
    }

    #ifndef NDEBUG
      QPixmap * const p = m_pixmap;
    #endif
    *m_pixmap = m_pixmap->fromImage(image);
    #ifndef NDEBUG
      assert(m_pixmap == p);
    #endif
    painter.drawPixmap(ui->widget->rect(),*m_pixmap);
    must_init = false;

  }
}

const std::vector<boost::shared_ptr<Player> > CreatePlayers()
{
  std::vector<boost::shared_ptr<Player> > v;
  {
    boost::shared_ptr<Player> p(new ClassicPlayer(159,100,3,255,0,0));
    v.push_back(p);
  }
  {
    boost::shared_ptr<Player> p(new ClassicPlayer(161,100,1,0,255,0));
    v.push_back(p);
  }
  return v;
}

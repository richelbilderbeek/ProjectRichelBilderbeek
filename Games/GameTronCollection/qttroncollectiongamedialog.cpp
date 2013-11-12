#include <cassert>
#include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "qttroncollectiongamedialog.h"

#include "player.h"
#include "ui_qttroncollectiongamedialog.h"
#include "worldtype.h"
#pragma GCC diagnostic pop

ribi::QtTronCollectionGameDialog::QtTronCollectionGameDialog(
  QWidget *parent, const std::vector<boost::shared_ptr<Player> > players)
  : QDialog(parent, Qt::Window),
    ui(new Ui::QtTronCollectionGameDialog),
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

ribi::QtTronCollectionGameDialog::~QtTronCollectionGameDialog()
{
  delete ui;
}

void ribi::QtTronCollectionGameDialog::resizeEvent(QResizeEvent*)
{

}

void ribi::QtTronCollectionGameDialog::paintEvent(QPaintEvent *)
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

const std::vector<boost::shared_ptr<ribi::Player> > ribi::QtTronCollectionGameDialog::CreatePlayers()
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

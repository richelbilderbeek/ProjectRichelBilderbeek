#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include <QImage>
#include <QPainter>

#include "qttankbattaliongamewidget.h"
#pragma GCC diagnostic pop

QtGameWidget::QtGameWidget(QWidget *parent)
 : QWidget(parent),
   m_sprites(CreateSprites())
{

}

const QtGameWidget::SpriteMap QtGameWidget::CreateSprites() const
{
  SpriteMap m;
  m[TankBattalion::arena] = boost::shared_ptr<QImage>(new QImage(":/images/Arena.png"));
  m[TankBattalion::player_down] = boost::shared_ptr<QImage>(new QImage(":/images/PlayerDown.png"));
  m[TankBattalion::player_left] = boost::shared_ptr<QImage>(new QImage(":/images/PlayerLeft.png"));
  m[TankBattalion::player_right] = boost::shared_ptr<QImage>(new QImage(":/images/PlayerRight.png"));
  m[TankBattalion::player_up] = boost::shared_ptr<QImage>(new QImage(":/images/PlayerUp.png"));
  return m;
}

const boost::shared_ptr<QImage> QtGameWidget::GetImage(const TankBattalion::SpriteType& s) const
{
  const SpriteMap::const_iterator i
    = m_sprites.find(s);
  assert(i!=m_sprites.end());
  return i->second;
}

void QtGameWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  const int width = this->width();
  const int height = this->height();
  const double scale_x
    = static_cast<double>(width)
    / TankBattalion::GetArenaWidth();
  const double scale_y
    = static_cast<double>(height)
    / TankBattalion::GetArenaHeight();
  painter.setBackgroundMode(Qt::TransparentMode);
  painter.drawImage(
    this->rect(),
    *GetImage(TankBattalion::arena).get());

  painter.drawImage(
    QRect(0,0,scale_x * 16.0, scale_y * 16.0),
    *GetImage(TankBattalion::player_left).get());
}

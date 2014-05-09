#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttankbattaliongamewidget.h"

#include <cassert>
#include <iostream>

#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QPainter>

#include "trace.h"
#pragma GCC diagnostic pop

QtGameWidget::QtGameWidget(QWidget *parent)
 : QWidget(parent),
   m_direction{Direction::down},
   m_keys{},
   m_sprites(CreateSprites()),
   m_x{0},
   m_y{0}
{
  {
    QTimer * const timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(20);
    timer->start();
  }
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
    m_x = (this->rect().center().x() / 2) - (32 / 2);
    m_y = (this->rect().center().y() / 2) - (32 / 2);
  }
}

const QtGameWidget::SpriteMap QtGameWidget::CreateSprites() const
{
  SpriteMap m;
  m[TankBattalion::arena] = boost::shared_ptr<QImage>(new QImage(":/GameTankBattalion/images/GameTankBattalion/Arena.png"));
  m[TankBattalion::player_down] = boost::shared_ptr<QImage>(new QImage(":/GameTankBattalion/images/GameTankBattalionPlayerDown.png"));
  m[TankBattalion::player_left] = boost::shared_ptr<QImage>(new QImage(":/GameTankBattalion/images/GameTankBattalionPlayerLeft.png"));
  m[TankBattalion::player_right] = boost::shared_ptr<QImage>(new QImage(":/GameTankBattalion/images/GameTankBattalionPlayerRight.png"));
  m[TankBattalion::player_up] = boost::shared_ptr<QImage>(new QImage(":/GameTankBattalion/images/GameTankBattalionPlayerUp.png"));
  return m;
}

const boost::shared_ptr<QImage> QtGameWidget::GetImage(const TankBattalion::SpriteType& s) const
{
  const SpriteMap::const_iterator i
    = m_sprites.find(s);
  assert(i!=m_sprites.end());
  return i->second;
}

void QtGameWidget::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up:
      TRACE("Pressed up");
      m_keys.insert(Key::up);
      m_direction = Direction::up;
      break;
    case Qt::Key_Right:
      TRACE("Pressed right");
      m_keys.insert(Key::right);
      m_direction = Direction::right;
      break;
    case Qt::Key_Down:
      TRACE("Pressed down");
      m_keys.insert(Key::down);
      m_direction = Direction::down;
      break;
    case Qt::Key_Left:
      TRACE("Pressed left");
      m_keys.insert(Key::left);
      m_direction = Direction::left;
      break;
  }
}

void QtGameWidget::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_keys.erase(Key::up); break;
    case Qt::Key_Right: m_keys.erase(Key::right); break;
    case Qt::Key_Down: m_keys.erase(Key::down); break;
    case Qt::Key_Left: m_keys.erase(Key::left); break;
  }
}

void QtGameWidget::OnTimer()
{
  for (auto k: m_keys)
  {
    switch (k)
    {
      case Key::up   : --m_y; break;
      case Key::right: ++m_x; break;
      case Key::down : ++m_y; break;
      case Key::left : --m_x; break;
    }
  }
  repaint();
}

void QtGameWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  std::string s = ":/GameTankBattalion/images/GameTankBattalionPlayer";
  switch (m_direction)
  {
    case Direction::up   : s += "Up.png"; break;
    case Direction::right: s += "Right.png"; break;
    case Direction::down : s += "Down.png"; break;
    case Direction::left : s += "Left.png"; break;
  }
  std::cout << s << std::endl;
  QPixmap p(s.c_str());
  assert(p.height() > 0);
  assert(p.width() > 0);
  painter.drawPixmap(m_x,m_y,16,16,p);

  /*
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
  */
}

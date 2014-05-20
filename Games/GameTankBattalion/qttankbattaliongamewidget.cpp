#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttankbattaliongamewidget.h"

#include <cassert>
#include <iostream>

#include <boost/make_shared.hpp>

#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QImage>
#include <QPainter>

#include "tankbattalionhelper.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::taba::QtGameWidget::QtGameWidget(QWidget *parent)
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

ribi::taba::QtGameWidget::SpriteMap ribi::taba::QtGameWidget::CreateSprites() const
{
  SpriteMap m;
  m[SpriteType::arena       ] = boost::make_shared<QPixmap>(":/GameTankBattalion/images/GameTankBattalionArena.png"     );
  m[SpriteType::player_down ] = boost::make_shared<QPixmap>(":/GameTankBattalion/images/GameTankBattalionPlayerDown.png" );
  m[SpriteType::player_left ] = boost::make_shared<QPixmap>(":/GameTankBattalion/images/GameTankBattalionPlayerLeft.png" );
  m[SpriteType::player_right] = boost::make_shared<QPixmap>(":/GameTankBattalion/images/GameTankBattalionPlayerRight.png");
  m[SpriteType::player_up   ] = boost::make_shared<QPixmap>(":/GameTankBattalion/images/GameTankBattalionPlayerUp.png"   );
  assert(static_cast<int>(m.size()) == static_cast<int>(SpriteType::n_types));
  #ifndef NDEBUG
  for (auto p:m) { assert(p.second->width() > 0 && "Picture must exist"); }
  #endif
  return m;
}

boost::shared_ptr<QPixmap> ribi::taba::QtGameWidget::GetPixmap(const SpriteType& s) const
{
  const SpriteMap::const_iterator i
    = m_sprites.find(s);
  assert(i!=m_sprites.end());
  return i->second;
}

void ribi::taba::QtGameWidget::keyPressEvent(QKeyEvent * e)
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

void ribi::taba::QtGameWidget::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up: m_keys.erase(Key::up); break;
    case Qt::Key_Right: m_keys.erase(Key::right); break;
    case Qt::Key_Down: m_keys.erase(Key::down); break;
    case Qt::Key_Left: m_keys.erase(Key::left); break;
  }
}

void ribi::taba::QtGameWidget::OnTimer()
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

void ribi::taba::QtGameWidget::paintEvent(QPaintEvent *)
{
  //168 wide / 8 = 21
  //176 heigh / 8 = 22
  //Bricks are 8x8, sprites are 16x16
  QPainter painter(this);

  const auto arena = GetPixmap(SpriteType::arena);
  painter.drawPixmap(rect(),*arena);

  const double scale_x
    = static_cast<double>(rect().width())
    / static_cast<double>(arena->width())
  ;
  const double scale_y
    = static_cast<double>(rect().height())
    / static_cast<double>(arena->height())
  ;



  const auto p = GetPixmap(Helper().ToPlayerSpriteType(m_direction));
  assert(p->height() > 0);
  assert(p->width() > 0);
  painter.drawPixmap(
    QRect(
      m_x * scale_x,
      m_y * scale_y,
      p->width() * scale_x,
      p->height() * scale_y
    )
    ,*p
  );
}

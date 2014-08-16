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

#include "tankbattalionarena.h"
#include "tankbattaliongamewidget.h"
#include "tankbattalionhelper.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::taba::QtGameWidget::QtGameWidget(QWidget *parent)
 : QWidget(parent),
   m_sprites(CreateSprites()),
   m_widget{new GameWidget}
{
  {
    QTimer * const timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    timer->setInterval(20);
    timer->start();
  }
  /*
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );
  }
  */
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
  const bool verbose = false;
  switch (e->key())
  {
    case Qt::Key_Up:
      if (verbose) { TRACE("Pressed up"); }
      m_widget->PressKey(Key::up);
      break;
    case Qt::Key_Right:
      if (verbose) { TRACE("Pressed right"); }
      m_widget->PressKey(Key::right);
      break;
    case Qt::Key_Down:
      if (verbose) { TRACE("Pressed down"); }
      m_widget->PressKey(Key::down);
      break;
    case Qt::Key_Left:
      if (verbose) { TRACE("Pressed left"); }
      m_widget->PressKey(Key::left);
      break;
  }
}

void ribi::taba::QtGameWidget::keyReleaseEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_Up   : m_widget->ReleaseKey(Key::up); break;
    case Qt::Key_Right: m_widget->ReleaseKey(Key::right); break;
    case Qt::Key_Down : m_widget->ReleaseKey(Key::down); break;
    case Qt::Key_Left : m_widget->ReleaseKey(Key::left); break;
  }
}

void ribi::taba::QtGameWidget::OnTimer()
{
  m_widget->OnTimer();
  repaint();
}

void ribi::taba::QtGameWidget::paintEvent(QPaintEvent *)
{
  //168 wide / 8 = 21
  //176 heigh / 8 = 22
  //Bricks are 8x8, sprites are 16x16
  QPainter painter(this);

  const int block_width  = 8;
  const int block_height = 8;
  const int arena_width  = Arena::GetColumns() * block_width;
  const int arena_height = Arena::GetRows()    * block_height;
  const auto n_rows = m_widget->GetArena()->GetRows();
  const auto n_cols = m_widget->GetArena()->GetColumns();
  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      //assert(y < static_cast<int>(v.size()));
      //assert(x < static_cast<int>(v[y].size()));
      //m_widget->GetArena()->Set(x,y,s[index]);
      //v[y][x] = static_cast<int>(s[index]);
      //++index;
      assert(!"TODO");
    }
  }

  const double scale_x
    = static_cast<double>(rect().width())
    / static_cast<double>(arena_width)
  ;
  const double scale_y
    = static_cast<double>(rect().height())
    / static_cast<double>(arena_height)
  ;



  const auto p = GetPixmap(Helper().ToPlayerSpriteType(m_widget->GetDirection()));
  assert(p->height() > 0);
  assert(p->width() > 0);
  painter.drawPixmap(
    QRect(
      m_widget->GetPlayerX() * scale_x,
      m_widget->GetPlayerY() * scale_y,
      p->width() * scale_x,
      p->height() * scale_y
    )
    ,*p
  );
}

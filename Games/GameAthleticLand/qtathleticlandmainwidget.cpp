#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtathleticlandmainwidget.h"

#include <QPaintEvent>
#include <QPainter>

#include "athleticlandplayer.h"
#include "qtathleticlandresources.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::athl::QtAthleticLandMainWidget::QtAthleticLandMainWidget()
  : m_player(new Player)
{

}

void ribi::athl::QtAthleticLandMainWidget::OnKeyPress(
  const ribi::athl::QtAthleticLandMainWidget::Key key)
{
  if (key == Key::left)
  {
    this->m_player->PressKeyLeft();
  }
  else if (key == Key::right)
  {
    this->m_player->PressKeyRight();
  }
  this->repaint();
}

void ribi::athl::QtAthleticLandMainWidget::paintEvent(QPaintEvent *)
{
  QPainter p(this);

  QtAthleticLandResources resources;
  p.drawPixmap(0,0,this->width(),this->height(),resources.GetBackground());

  //Background size (width x height) is 512x300 pixels per default
  const double scale_x
    = static_cast<double>(this->width())
    / static_cast<double>(resources.GetBackground().width());
  const double scale_y
    = static_cast<double>(this->height())
    / static_cast<double>(resources.GetBackground().height());

  const PlayerState state = m_player->GetState();
  const double player_y
    = static_cast<double>(this->height()) * m_player->GetY();
  const double player_x
    = static_cast<double>(this->width()) * m_player->GetX();
  const double player_height
    = static_cast<double>(resources.GetPlayer(state).height()) * scale_x;
  const double player_width
    = static_cast<double>(resources.GetPlayer(state).width()) * scale_y;

  p.drawPixmap(
    player_x,
    player_y,
    player_width,
    player_height,
    resources.GetPlayer(m_player->GetState())
  );
}

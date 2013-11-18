




#include <algorithm>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <QPixmap>
#include "athleticlandarea.h"
#include "athleticlandbackground.h"
#include "athleticlandplayer.h"
//#include "athleticlandplayerstate.h"
#include "athleticlandsprite.h"
#pragma GCC diagnostic pop

/*
boost::shared_ptr<ribi::athl::Player> ribi::athl::Area::m_player;

ribi::athl::Area::Area(const boost::shared_ptr<Background> background)
  :
    m_area_finished(false),
    m_background(background),
    m_sprites{}
{
  AddPlayer();
  Start();
}

void ribi::athl::Area::Start()
{
  m_player->SetToStartingPosition(m_background.get());
  m_area_finished = false;
}

void ribi::athl::Area::Restart()
{
  m_player->SetToStartingPosition(m_background.get());
  //Restart all sprites
  std::for_each(m_sprites.begin(),m_sprites.end(),
    boost::mem_fn(&Sprite::Restart));
}

void ribi::athl::Area::AddPlayer()
{
  m_player.reset(new Player);
}

bool ribi::athl::Area::HasDied() const
{
  return m_player->HasDied();
}

void ribi::athl::Area::Tick()
{
  //Move all sprites
  std::for_each(m_sprites.begin(),m_sprites.end(),
    boost::mem_fn(&Sprite::Move));

  //Check for collisions
  typedef std::vector<boost::shared_ptr<Sprite> >::iterator Iterator;
  const Iterator j = m_sprites.end();
  for (Iterator i = m_sprites.begin(); i!=j; ++i)
  {
    if ((*i)->DoesCollide(*m_player.get()))
    {
      (*i)->OnCollide(*m_player.get());
      if (m_player->HasDied())
      {
        return;
      }
    }
  }

  m_player->RespondToBackground(m_background.get());

  if (m_player->GetX() + m_player->GetWidth() > m_background->m_width)
  {
    //Restart the current area, also sets the player to starting position
    Restart();
    //Set area to be finished
    m_area_finished = true;
  }

  m_player->Tick();
}

void ribi::athl::Area::InitBuffer(QPixmap * const buffer) const
{
  //const int width  = m_background->m_width;
  //const int height = m_background->m_height;
  //buffer->Picture->Bitmap->Width  = width;
  //buffer->Picture->Bitmap->Height = height;
}

void ribi::athl::Area::Draw(QPixmap * const buffer) const
{
  //Draw background on buffer
  m_background->Draw(buffer);

  //Draw all sprites on buffer
  std::for_each(m_sprites.begin(),m_sprites.end(),
    boost::bind(&Sprite::Draw,_1,buffer));


  //Draw player on buffer
  m_player->Draw(buffer);
}

void ribi::athl::Area::PressKeyLeft()
{
  m_player->PressKeyLeft();
}

void ribi::athl::Area::PressKeyRight()
{
  m_player->PressKeyRight();
}

void ribi::athl::Area::PressKeyJump()
{
  m_player->PressKeyJump();
}

void ribi::athl::Area::PressNoKey()
{
  m_player->PressNoKey();
}

void ribi::athl::Area::AddRock()
{
  const int x = m_background->m_right_x;
  const int y = m_background->m_walk_height ;
  boost::shared_ptr<Sprite> s(new RockSprite(x,y));
  s.reset(new RockSprite(x,y - s->m_height)); //Move rock up
  m_sprites.push_back(s);
}

void ribi::athl::Area::AddRollingBall()
{
  const int x = m_background->m_width + 50;
  const int y = m_background->m_walk_height;
  boost::shared_ptr<Sprite> s(new RollingBallSprite(x,y,-1.0));
  s.reset(new RollingBallSprite(x,y - s->m_height,-10.0)); //Move roling ball up
  m_sprites.push_back(s);
}

*/






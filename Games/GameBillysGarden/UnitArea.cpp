//---------------------------------------------------------------------------


#pragma hdrstop

#include <algorithm>
#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <ExtCtrls.hpp>
#include "UnitArea.h"
#include "UnitBackground.h"
#include "UnitPlayer.h"
//#include "UnitPlayerState.h"
#include "UnitSprite.h"
//---------------------------------------------------------------------------
boost::shared_ptr<Player> Area::m_player;
//---------------------------------------------------------------------------
Area::Area(const boost::shared_ptr<Background> background)
  : m_background(background),
    m_area_finished(false)
{
  AddPlayer();
  Start();
}
//---------------------------------------------------------------------------
void Area::Start()
{
  m_player->SetToStartingPosition(m_background.get());
  m_area_finished = false;
}
//---------------------------------------------------------------------------
void Area::Restart()
{
  m_player->SetToStartingPosition(m_background.get());
  //Restart all sprites
  std::for_each(m_sprites.begin(),m_sprites.end(),
    boost::mem_fn(&Sprite::Restart));
}
//---------------------------------------------------------------------------
void Area::AddPlayer()
{
  m_player.reset(new Player);
}
//---------------------------------------------------------------------------
const bool Area::HasDied() const
{
  return m_player->HasDied();
}
//---------------------------------------------------------------------------
void Area::Tick()
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
//---------------------------------------------------------------------------
void Area::InitBuffer(Extctrls::TImage* const buffer) const
{
  const int width  = m_background->m_width;
  const int height = m_background->m_height;
  buffer->Picture->Bitmap->Width  = width;
  buffer->Picture->Bitmap->Height = height;
}
//---------------------------------------------------------------------------
void Area::Draw(Extctrls::TImage* const buffer) const
{
  //Draw background on buffer
  m_background->Draw(buffer->Canvas);

  //Draw all sprites on buffer
  std::for_each(m_sprites.begin(),m_sprites.end(),
    boost::bind(&Sprite::Draw,_1,buffer->Canvas));


  //Draw player on buffer
  m_player->Draw(buffer->Canvas);
}
//---------------------------------------------------------------------------
void Area::PressKeyLeft()
{
  m_player->PressKeyLeft();
}
//---------------------------------------------------------------------------
void Area::PressKeyRight()
{
  m_player->PressKeyRight();
}
//---------------------------------------------------------------------------
void Area::PressKeyJump()
{
  m_player->PressKeyJump();
}
//---------------------------------------------------------------------------
void Area::PressNoKey()
{
  m_player->PressNoKey();
}
//---------------------------------------------------------------------------
void Area::AddRock()
{
  const int x = m_background->m_right_x;
  const int y = m_background->m_walk_height ;
  boost::shared_ptr<Sprite> s(new RockSprite(x,y));
  s.reset(new RockSprite(x,y - s->m_height)); //Move rock up
  m_sprites.push_back(s);
}
//---------------------------------------------------------------------------
void Area::AddRollingBall()
{
  const int x = m_background->m_width + 50;
  const int y = m_background->m_walk_height;
  boost::shared_ptr<Sprite> s(new RollingBallSprite(x,y,-1.0));
  s.reset(new RollingBallSprite(x,y - s->m_height,-10.0)); //Move roling ball up
  m_sprites.push_back(s);
}
//---------------------------------------------------------------------------




#pragma package(smart_init)

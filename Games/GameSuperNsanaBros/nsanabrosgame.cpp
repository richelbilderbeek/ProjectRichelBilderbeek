#include "nsanabrosgame.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"


#include "nsanabrossprite.h"
#include "nsanabrosstlheader.h"
#pragma GCC diagnostic pop

const double ribi::NsanaBrosGame::m_width  = 20.0;
const double ribi::NsanaBrosGame::m_height = 16.0;
const double ribi::NsanaBrosGame::m_dy_gravity = 0.01;

ribi::NsanaBrosGame::NsanaBrosGame()
  : m_signal_repaint{},
    m_keys(new NsanaBrosKeys),
    m_player(new NsanaBrosPlayer),
    m_sprites(CreateTestSprites())
{

}

const std::vector<boost::shared_ptr<ribi::NsanaBrosSprite> > ribi::NsanaBrosGame::CreateTestSprites()
{
  const std::vector<boost::shared_ptr<NsanaBrosSprite> > v
  = {
    //Ceiling
    boost::shared_ptr<NsanaBrosSprite>(
      new NsanaBrosSprite(0.0,0.0,m_width,1.0,255,196,0)),
    //Left wall
    boost::shared_ptr<NsanaBrosSprite>(
      new NsanaBrosSprite(0.0,1.0,1.0,m_height - 2.0,255,196,0)),
    //Right wall
    boost::shared_ptr<NsanaBrosSprite>(
      new NsanaBrosSprite(m_width-1.0,1.0,1.0,m_height - 2.0,255,196,0)),
    //Floor
    boost::shared_ptr<NsanaBrosSprite>(
      new NsanaBrosSprite(0.0,m_height-1.0,m_width,1.0,255,196,0)),
    //1st platform
    boost::shared_ptr<NsanaBrosSprite>(
      new NsanaBrosSprite(4.0,m_height-5.0,m_width-8.0,1.0,255,196,0))
  };
  return v;
}

///GetHeight returns the height of the world in the number of blocks
int ribi::NsanaBrosGame::GetHeight()
{
  return m_height;
}

///GetWidth returns the width of the world in the number of blocks
int ribi::NsanaBrosGame::GetWidth()
{
  return m_width;
}

const boost::shared_ptr<const ribi::NsanaBrosKeys> ribi::NsanaBrosGame::GetKeys() const
{
  //delete m_keys.get(); //Should not compile
  return m_keys;
}

const boost::shared_ptr<const ribi::NsanaBrosPlayer> ribi::NsanaBrosGame::GetPlayer() const
{
  return m_player;
}

const std::vector<boost::shared_ptr<const ribi::NsanaBrosSprite> > ribi::NsanaBrosGame::GetSprites() const
{
  std::vector<boost::shared_ptr<const NsanaBrosSprite> > v;
  for(const boost::shared_ptr<const NsanaBrosSprite> s: m_sprites)
  {
    v.push_back(s);
  }
  //v[0]->Translate(1.0,1.0); //Should not compile
  //delete v[0]; //Should not compile
  return v;
}

void ribi::NsanaBrosGame::KeyPress(const int key)
{
  m_keys->KeyPress(key);
}

void ribi::NsanaBrosGame::KeyRelease(const int key)
{
  m_keys->KeyRelease(key);
}

///OnTimer() performs a tick in the game in which sprites move
///OnTimer is called by XtNsanaBrosGameDialog, as these
///libraries supply a ticking timer
void ribi::NsanaBrosGame::OnTimer()
{
  //Let the player start a jump, move left, etc
  m_player->RespondToKeys(GetKeys());

  //Get the player's new velocities
  double dx = m_player->GetDx();
  double dy = m_player->GetDy();

  //Bounce into walls, etc...
  bool is_falling = true;
  {
    const std::vector<boost::shared_ptr<const NsanaBrosSprite> > sprites = GetSprites();
    bool done = false;
    while (!done)
    {
      done = true;
      for(const boost::shared_ptr<const NsanaBrosSprite> sprite: sprites)
      {
        if (
          sprite->GetCollisionVectorFromPoint(
            m_player->GetSprite()->GetLeft(),
            m_player->GetSprite()->GetBottom() + 0.01)
          != std::make_pair(0.0,0.0)
          ||
          sprite->GetCollisionVectorFromPoint(
            m_player->GetSprite()->GetRight(),
            m_player->GetSprite()->GetBottom() + 0.01)
          != std::make_pair(0.0,0.0))
        {
          is_falling = false;
        }

        const std::pair<double,double> p
          = sprite->GetCollisionVector(m_player->GetSprite());
        if (p.first != 0.0 || p.second != 0.0)
        {
          done = false;
        }
        if (p.second < 0.0)
        {
          dy = 0.0;
          m_keys->KeyRelease(NsanaBrosKeys::GetKeyUp());
        }
        if (p.second > 0.0)
        {
          dy = 0.0;
          m_keys->KeyRelease(NsanaBrosKeys::GetKeyDown());
        }
        if (p.first < 0.0)
        {
          dx = 0.0;
          m_keys->KeyRelease(NsanaBrosKeys::GetKeyLeft());
        }
        if (p.first > 0.0)
        {
          dx = 0.0;
          m_keys->KeyRelease(NsanaBrosKeys::GetKeyRight());
        }
        m_player->Translate(p.first,p.second);
      }
    }
  }

  //Gravity
  if (is_falling) dy += m_dy_gravity;

  //Set the player's new velocities
  m_player->SetDx(dx);
  m_player->SetDy(dy);

  //Move the player
  m_player->Move();
}

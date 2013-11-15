#include <cassert>
//#include <numeric>
#include <cmath>

#include "athleticlandcollisionbehaviour.h"
#include "athleticlandsprites.h"
#include "athleticlandmovementpattern.h"
#include "athleticlandplayer.h"
#include "athleticlandsprite.h"

Sprite::Sprite(QPixmap * const image)
  : m_image(image),
    m_width(image->Picture->Bitmap->Width),
    m_height(image->Picture->Bitmap->Height)
{
  assert(image);
  assert(m_width == m_image->Picture->Bitmap->Width);
  assert(m_height == m_image->Picture->Bitmap->Height);
}

const bool Sprite::DoesCollide(const Player& p) const
{
  //Is one of the sprites' corners in Player?
  const int s_x1  = static_cast<int>(GetX());
  const int s_x2 = s_x1 + m_width;
  const int s_y1 = static_cast<int>(GetY());
  const int s_y2 = s_y1 + m_height;

  const int p_x1 = p.GetX();
  const int p_y1 = p.GetY();
  const int p_x2 = p_x1 + p.GetWidth();
  const int p_y2 = p_y1 + p.GetHeight();

  return
    //Is top-left pixel of sprite in player?
     ( (s_x1 > p_x1 && s_x1 < p_x2 && s_y1 > p_y1 && s_y1 < p_y2)
    //Is top-right pixel of sprite in player?
    || (s_x2 > p_x1 && s_x2 < p_x2 && s_y1 > p_y1 && s_y1 < p_y2)
    //Is bottom-left pixel of sprite in player?
    || (s_x1 > p_x1 && s_x1 < p_x2 && s_y2 > p_y1 && s_y2 < p_y2)
    //Is bottom-right pixel of sprite in player?
    || (s_x2 > p_x1 && s_x2 < p_x2 && s_y2 > p_y1 && s_y2 < p_y2) );
}

void Sprite::OnCollide(Player& p)
{
  if (m_collision_behaviour) m_collision_behaviour->OnCollision(p);
}

const Rect Sprite::GetRect() const
{
  const int x1 = static_cast<int>(GetX());
  const int y1 = static_cast<int>(GetY());
  const int x2 = x1 + m_width;
  const int y2 = y1 + m_height;
  return TRect(x1,y1,x2,y2);
}

void MovingSprite::Draw(QPixmap * const canvas) const
{
  const int x = static_cast<int>(m_x);
  const int y = static_cast<int>(m_y);
  canvas->Draw(x,y,m_image->Picture->Graphic);
}

void MovingSprite::Move()
{
  assert(m_movement_pattern);
  m_movement_pattern->Move();
}

void MovingSprite::Restart()
{
  m_movement_pattern->Restart();
}

void NonMovingSprite::Draw(QPixmap * const canvas) const
{
  canvas->Draw(m_x,m_y,m_image->Picture->Graphic);
}

RockSprite::RockSprite(const int x, const int y)
  : NonMovingSprite(x,y,FormSprites->ImageRock)
{
  m_collision_behaviour.reset(new LethalCollision);
}

RollingBallSprite::RollingBallSprite(const int x, const int y, const double dx)
  : MovingSprite(x,y,FormSprites->ImageBall),
    m_dx(dx)
{
  m_movement_pattern.reset(new ComplexMovePattern);
  m_collision_behaviour.reset(new LethalCollision);

  const int dist_x = this->m_width + x;
  const int cnt = static_cast<int>( static_cast<double>(dist_x) / std::fabs(dx) );

  m_movement_pattern->AddStraightLineMovement(m_x,m_y,cnt,dx,0.0);
  m_movement_pattern->AddTeleportMovement(m_x,m_y,x,y);

}







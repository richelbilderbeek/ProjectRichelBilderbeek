#include <cassert>

#include "athleticlandcollisionbehaviour.h"
#include "athleticlandplayer.h"
#include "rectangle.h"

/*
void ribi::athl::LethalCollision::OnCollision(Player& p)
{
  p.Die();
}

ribi::athl::MovePlayerAwayCollision::MovePlayerAwayCollision(
  const int x1,
  const int y1,
  const int width,
  const int height)
  :
    m_x1(x1),
    m_x2(x1 + width),
    m_y1(y1),
    m_y2(y1 + height)
{
  assert(width > 0);
  assert(height > 0);
}

void ribi::athl::MovePlayerAwayCollision::OnCollision(Player& p)
{
  //Extract player coordinats
  const int p_x1 = p.GetX();
  const int p_y1 = p.GetY();
  const int p_x2 = p_x1 + p.GetWidth();
  const int p_y2 = p_y1 + p.GetHeight();
  const Rect r(m_x1,m_y1,m_x2,m_y2);
  //Set the deltas of player (1) and this sprite (2) to zero
  int dx = 0;
  int dy = 0;

  if (!( p_x2  < m_x1 || p_x1 > m_x2 || p_y2 < m_y1  || p_y1  > m_y2))
  {
    if (InRect(p_x1,p_y1,r)==true) { ++dx; ++dy; }
    if (InRect(p_x2,p_y1,r)==true) { --dx; ++dy; }
    if (InRect(p_x1,p_y2,r)==true) { ++dx; --dy; }
    if (InRect(p_x2,p_y2,r)==true) { --dx; --dy; }
    //If all 4 edges are collision
    if (dx == 0 && dy == 0)
    {
      ++dx;
      ++dy;
    }
  }
  p.Move(dx,dy);
}

bool ribi::athl::InRect(const int x, const int y, const Rect& r)
{
  return x >= r.GetX() && x < r.GetRight() && y >= r.GetY() && y < r.GetBottom();
}

void ribi::athl::MoveAway(Rect& r1, Rect& r2)
{
  int dx1 = 0;
  int dy1 = 0;
  int dx2 = 0;
  int dy2 = 0;

  //No collision
  //if (r1.Left   < 0) ++dx1;
  //if (r1.Top    < 0) ++dy1;
  //if (r1.Right  > ClientWidth ) --dx1;
  //if (r1.Bottom > ClientHeight) --dy1;
  //if (r2.Left   < 0) ++dx2;
  //if (r2.Top    < 0) ++dy2;
  //if (r2.Right  > ClientWidth ) --dx2;
  //if (r2.Bottom > ClientHeight) --dy2;

  if (!( r1.GetRight()  < r2.GetX() || r1.GetX() > r2.GetRight()
    || r1.GetBottom() < r2.GetY()  || r1.GetY() > r2.GetBottom()))
  {
    if (InRect(r1.GetLeft() ,r1.GetTop()   ,r2)) { ++dx1; ++dy1; --dx2; --dy2;}
    if (InRect(r1.GetRight(),r1.GetTop()   ,r2)) { --dx1; ++dy1; ++dx2; --dy2;}
    if (InRect(r1.GetLeft() ,r1.GetBottom(),r2)) { ++dx1; --dy1; --dx2; ++dy2;}
    if (InRect(r1.GetRight(),r1.GetBottom(),r2)) { --dx1; --dy1; ++dx2; ++dy2;}
    //If all 4 edges are collision
    if (dx1 == 0 && dy1 == 0)
    {
      ++dx1;
      ++dy1;
      --dx2;
      --dy2;
    }
  }
  r1.Translate(dx1,dy1);
  r2.Translate(dx2,dy2);
}

bool ribi::athl::DoCollide(const Rect& a, const Rect& b)
{
  const int a_x1 = a.GetLeft();
  const int a_x2 = a.GetRight();
  const int a_y1 = a.GetTop();
  const int a_y2 = a.GetBottom();
  const int b_x1 = b.GetLeft();
  const int b_x2 = b.GetRight();
  const int b_y1 = b.GetTop();
  const int b_y2 = b.GetBottom();

  return (
     //Top-left of a in b?
     (a_x1 > b_x1 && a_x1 < b_x2 && a_y1 > b_y1 && a_y1 < b_y2)
     //Top-right of a in b?
  || (a_x2 > b_x1 && a_x2 < b_x2 && a_y1 > b_y1 && a_y1 < b_y2)
     //Bottom-left of a in b?
  || (a_x1 > b_x1 && a_x1 < b_x2 && a_y2 > b_y1 && a_y2 < b_y2)
     //Bottom-right of a in b?
  || (a_x2 > b_x1 && a_x2 < b_x2 && a_y2 > b_y1 && a_y2 < b_y2) );

}

*/

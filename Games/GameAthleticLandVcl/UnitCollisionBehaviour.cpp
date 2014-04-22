//---------------------------------------------------------------------------


#pragma hdrstop

#include <cassert>
#include <Types.hpp>
#include "UnitCollisionBehaviour.h"
#include "UnitPlayer.h"
//---------------------------------------------------------------------------
void LethalCollision::OnCollision(Player& p)
{
  p.Die();
}
//---------------------------------------------------------------------------
MovePlayerAwayCollision::MovePlayerAwayCollision(
  const int x1, const y1, const int width, const int height)
  : m_x1(x1), m_y1(y1), m_x2(x1 + width), m_y2(y1 + height)
{
  assert(width > 0);
  assert(height > 0);
}
//---------------------------------------------------------------------------
void MovePlayerAwayCollision::OnCollision(Player& p)
{
  //Extract player coordinats
  const int p_x1 = p.GetX();
  const int p_y1 = p.GetY();
  const int p_x2 = p_x1 + p.GetWidth();
  const int p_y2 = p_y1 + p.GetHeight();
  const TRect r(m_x1,m_y1,m_x2,m_y2);
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
//---------------------------------------------------------------------------
const bool InRect(const int x, const int y, const Types::TRect& r)
{
  return (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom);
}
//---------------------------------------------------------------------------
void MoveAway(Types::TRect& r1, Types::TRect& r2)
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

  if (!( r1.Right  < r2.Left || r1.Left > r2.Right
    || r1.Bottom < r2.Top  || r1.Top  > r2.Bottom))
  {
    if (InRect(r1.Left ,r1.Top   ,r2)==true) { ++dx1; ++dy1; --dx2; --dy2;}
    if (InRect(r1.Right,r1.Top   ,r2)==true) { --dx1; ++dy1; ++dx2; --dy2;}
    if (InRect(r1.Left ,r1.Bottom,r2)==true) { ++dx1; --dy1; --dx2; ++dy2;}
    if (InRect(r1.Right,r1.Bottom,r2)==true) { --dx1; --dy1; ++dx2; ++dy2;}
    //If all 4 edges are collision
    if (dx1 == 0 && dy1 == 0)
    {
      ++dx1;
      ++dy1;
      --dx2;
      --dy2;
    }
  }
  r1.Left   += dx1;
  r1.Right  += dx1;
  r1.Top    += dy1;
  r1.Bottom += dy1;
  r2.Left   += dx2;
  r2.Right  += dx2;
  r2.Top    += dy2;
  r2.Bottom += dy2;
}
//---------------------------------------------------------------------------
const bool DoCollide(const Types::TRect& a, const Types::TRect& b)
{
  const int a_x1 = a.Left;
  const int a_x2 = a.Right;
  const int a_y1 = a.Top;
  const int a_y2 = a.Bottom;
  const int b_x1 = b.Left;
  const int b_x2 = b.Right;
  const int b_y1 = b.Top;
  const int b_y2 = b.Bottom;

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
//---------------------------------------------------------------------------
#pragma package(smart_init)

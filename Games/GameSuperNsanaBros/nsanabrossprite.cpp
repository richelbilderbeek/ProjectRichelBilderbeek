#include "nsanabrossprite.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numeric>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include "nsanabroskeys.h"
#include "nsanabrosstlheader.h"
#pragma GCC diagnostic pop

ribi::NsanaBrosSprite::NsanaBrosSprite(
  const double x,
  const double y,
  const double width,
  const double height,
  const int red,
  const int green,
  const int blue)
  : m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_red(red),
    m_green(green),
    m_blue(blue)
{
  assert(GetRed() >=   0);
  assert(GetRed()  < 256);
  assert(GetGreen() >=   0);
  assert(GetGreen()  < 256);
  assert(GetBlue() >=   0);
  assert(GetBlue()  < 256);
}

///GetCollisionVector returns the smallest translation vector
///needed to end a collision with this sprite. A
///translation vector of (0,0) denotes no collision.
const std::pair<double,double> ribi::NsanaBrosSprite::GetCollisionVectorFromPoint(const double x, const double y) const
{
  const double right  = m_x + m_width;
  const double bottom = m_y + m_height;
  if (x > m_x && x < right && y > m_y && y < bottom)
  {
    const double d_left  = std::abs(x - m_x);
    const double d_right = std::abs(x - right);
    const double d_up   = std::abs(y - m_y);
    const double d_down = std::abs(y - bottom);
    if (std::min(d_down,d_up) < std::min(d_left,d_right))
    {
      const double dx = 0.0;
      const double dy = (d_up < d_down ? -d_up : d_down);
      assert(GetCollisionVectorFromPoint(x + dx, y + dy) == std::make_pair(0.0,0.0));
      return std::make_pair(dx,dy);
    }
    else
    {
      const double dx = (d_left < d_right ? -d_left : d_right);
      const double dy = 0.0;
      assert(GetCollisionVectorFromPoint(x + dx, y + dy) == std::make_pair(0.0,0.0));
      return std::make_pair(dx,dy);
    }
  }
  return std::make_pair(0.0,0.0);
}

///GetCollisionVector returns the smallest translation vector
///needed to end a collision with this sprite. A
///translation vector of (0,0) denotes no collision.
const std::pair<double,double> ribi::NsanaBrosSprite::GetCollisionVector(
  const boost::shared_ptr<const NsanaBrosSprite> sprite) const
{
  const std::pair<double,double> p1 = GetCollisionVectorFromPoint(sprite->GetLeft() ,sprite->GetTop());
  const std::pair<double,double> p2 = GetCollisionVectorFromPoint(sprite->GetLeft() ,sprite->GetBottom());
  const std::pair<double,double> p3 = GetCollisionVectorFromPoint(sprite->GetRight(),sprite->GetTop());
  const std::pair<double,double> p4 = GetCollisionVectorFromPoint(sprite->GetRight(),sprite->GetBottom());
  return std::make_pair(
    p1.first  + p2.first  + p3.first  + p4.first,
    p1.second + p2.second + p3.second + p4.second);
}


bool ribi::NsanaBrosSprite::IsInRect(const double x, const double y, const NsanaBrosSprite& r)
{
  return x >= r.GetX()
      && x  < r.GetX() + r.GetWidth()
      && y >= r.GetY()
      && y  < r.GetY() + r.GetHeight();
}

void ribi::NsanaBrosSprite::BothMoveAway(NsanaBrosSprite& r1, NsanaBrosSprite& r2)
{
  int dx1 = 0;
  int dy1 = 0;
  int dx2 = 0;
  int dy2 = 0;
  const double r1_left   = r1.GetX();
  const double r1_top    = r1.GetY();
  const double r1_right  = r1.GetX() + r1.GetWidth();
  const double r1_bottom = r1.GetY() + r1.GetHeight();
  const double r2_left   = r2.GetX();
  const double r2_top    = r2.GetY();
  const double r2_right  = r2.GetX() + r2.GetWidth();
  const double r2_bottom = r2.GetY() + r2.GetHeight();
  const double maxx = NsanaBrosGame::GetWidth();
  const double maxy = NsanaBrosGame::GetHeight();

  //No collision
  if (r1_left   <  0.0) ++dx1;
  if (r1_top    <  0.0) ++dy1;
  if (r1_right  > maxx) --dx1;
  if (r1_bottom > maxy) --dy1;
  if (r2_left   <  0.0) ++dx2;
  if (r2_top    <  0.0) ++dy2;
  if (r2_right  > maxx) --dx2;
  if (r2_bottom > maxy) --dy2;


  if (!( r1_right  < r2_left
      || r1_left   > r2_right
      || r1_bottom < r2_top
      || r1_top    > r2_bottom))
  {
    if (IsInRect(r1_left ,r1_top   ,r2)) { ++dx1; ++dy1; --dx2; --dy2;}
    if (IsInRect(r1_right,r1_top   ,r2)) { --dx1; ++dy1; ++dx2; --dy2;}
    if (IsInRect(r1_left ,r1_bottom,r2)) { ++dx1; --dy1; --dx2; ++dy2;}
    if (IsInRect(r1_right,r1_bottom,r2)) { --dx1; --dy1; ++dx2; ++dy2;}
    //If all 4 edges are collision
    if (dx1 == 0 && dy1 == 0)
    {
      ++dx1;
      ++dy1;
      --dx2;
      --dy2;
    }
  }
  r1.Translate(
    boost::numeric_cast<double>(dx1),
    boost::numeric_cast<double>(dy1));
  r2.Translate(
    boost::numeric_cast<double>(dx2),
    boost::numeric_cast<double>(dy2));

}

void ribi::NsanaBrosSprite::MoveAway(const NsanaBrosSprite& r1, NsanaBrosSprite& r2)
{
  int dx2 = 0;
  int dy2 = 0;
  const double r1_left   = r1.GetLeft();
  const double r1_top    = r1.GetTop();
  const double r1_right  = r1.GetRight();
  const double r1_bottom = r1.GetBottom();
  const double r2_left   = r2.GetLeft();
  const double r2_top    = r2.GetTop();
  const double r2_right  = r2.GetRight();
  const double r2_bottom = r2.GetBottom();
  const double maxx = NsanaBrosGame::GetWidth();
  const double maxy = NsanaBrosGame::GetHeight();

  //No collision
  if (r2_left   <  0.0) ++dx2;
  if (r2_top    <  0.0) ++dy2;
  if (r2_right  > maxx) --dx2;
  if (r2_bottom > maxy) --dy2;


  if (!( r1_right  < r2_left
      || r1_left   > r2_right
      || r1_bottom < r2_top
      || r1_top    > r2_bottom))
  {
    if (IsInRect(r1_left ,r1_top   ,r2)) { --dx2; --dy2;}
    if (IsInRect(r1_right,r1_top   ,r2)) { ++dx2; --dy2;}
    if (IsInRect(r1_left ,r1_bottom,r2)) { --dx2; ++dy2;}
    if (IsInRect(r1_right,r1_bottom,r2)) { ++dx2; ++dy2;}
    //If all 4 edges are collision
    if (dx2 == 0 && dy2 == 0)
    {
      --dx2;
      --dy2;
    }
  }
  r2.Translate(
    boost::numeric_cast<double>(dx2),
    boost::numeric_cast<double>(dy2));
}

///Translate translates the sprite's coordinats
void ribi::NsanaBrosSprite::Translate(const double dx, const double dy)
{
  m_x += dx;
  m_y += dy;
}

std::ostream& ribi::operator<<(std::ostream& os, const NsanaBrosSprite& s)
{
  os
    << "Coordinat: ("
    << s.GetLeft()
    << ","
    << s.GetTop()
    << ")\n"
    << "Size: "
    << s.GetWidth()
    << " x "
    << s.GetHeight()
    << "\n"
    << "Color: ("
    << s.GetRed()
    << ","
    << s.GetGreen()
    << ","
    << s.GetBlue()
    << ")\n";
  return os;
}


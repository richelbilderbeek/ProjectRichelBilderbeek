#include "xenonzeroarea.h"

#include <cassert>
#include <iostream>
#include <iterator>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "textcanvas.h"
#include "xenonzerosprite.h"
#pragma GCC diagnostic pop

ribi::xnz::Area::Area(const int width,const int height)
  : mArea(new TextCanvas(width,height))
{
  assert(width > 0);
  assert(height > 0);

  DrawEdge();
}

const boost::shared_ptr<ribi::TextCanvas> ribi::xnz::Area::CreateTextCanvas() const noexcept
{
  const boost::shared_ptr<ribi::TextCanvas> copy {
    new TextCanvas(mArea->GetCanvas(),mArea->GetCoordinatSystem())
  };
  assert(copy);
  return copy;
}

void ribi::xnz::Area::DrawEdge()
{
  const int maxx = GetWidth();
  const int maxy = GetHeight();
  //Create an initial edged screen
  Sprite::mMaxx = maxx - 1;
  Sprite::mMaxy = maxy - 1;
  //Top row
  for (int x=0; x!=maxx; ++x)
  {
    mArea->PutChar(x,0,'*');
    mArea->PutChar(x,maxy-1,'*');
  }

  for (int y=0; y!=maxy; ++y)
  {
    mArea->PutChar(0,y,'*');
    mArea->PutChar(maxx-1,y,'*');
  }
}

void ribi::xnz::Area::DrawLife(const double fraction)
{
  const int x = GetWidth() - 2 - 3;
  const int y = 2;
  const int height = GetHeight() / 2;

  {
    //The edges
    mArea->PutChar(x+0,y,'[');
    mArea->PutChar(x+1,y,'-');
    mArea->PutChar(x+2,y,']');
    mArea->PutChar(x+0,y+height,'[');
    mArea->PutChar(x+1,y+height,'-');
    mArea->PutChar(x+2,y+height,']');
  }

  for (int i=1; i!=height; ++i) //Not the edges
  {
    const double f
      = 1.0 - static_cast<double>(i)
      / static_cast<double>(height);
    mArea->PutChar(x+0,y+i,'[');
    mArea->PutChar(x+1,y+i,f > fraction ? ' ' : '*');
    mArea->PutChar(x+2,y+i,']');
  }
}

void ribi::xnz::Area::Draw(const int x, const int y, const Container& g)
{
  const int graphicHeight = g.size();
  if (graphicHeight == 0) return;
  const int graphicWidth = g[0].size();

  const int areaWidth = this->GetWidth();
  const int areaHeight = this->GetHeight();

  for (int j=0; j!=graphicHeight; ++j)
  {
    if (y+j<0 || y+j>=areaHeight) continue;
    for (int i=0; i!=graphicWidth; ++i)
    {
      if (x+i < 0 || x+i>=areaWidth) continue;
      assert(mArea->IsInRange(x+y,y+j));
      mArea->PutChar(x+y,y+j,g[j][i]);
    }
  }
}


int ribi::xnz::Area::GetHeight() const noexcept
{
  return mArea->GetHeight();
}

int ribi::xnz::Area::GetWidth() const noexcept { return mArea->GetWidth(); }

std::ostream& ribi::xnz::operator<<(std::ostream& os, const Area& a)
{
  os << (*a.CreateTextCanvas());
  return os;
}

int ribi::xnz::Area::GetInRange(const int x, const int min, const int max)
{
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

#include "gamexenonzeroarea.h"

#include <cassert>
#include <iostream>
#include <iterator>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gamexenonzerosprite.h"
#pragma GCC diagnostic pop

namespace xnz {

Area::Area(const int width,const int height)
  : mArea(height,std::string(width,' '))
{
  assert(width > 0);
  assert(height > 0);

  DrawEdge();


}

void Area::DrawEdge()
{
  //Create an initial edged screen
  Sprite::mMaxx = GetWidth() - 1;
  Sprite::mMaxy = GetHeight() - 1;

  const std::string edge = std::string(GetWidth(),'*');
  const std::string nonEdge = "*" + std::string(GetWidth()-2,' ') + "*";
  mArea[0] = edge;
  for (int i=0; i!=GetHeight()-2; ++i) mArea[1+i] = nonEdge;
  mArea[GetHeight() - 1] = edge;
}

void Area::DrawLife(const double fraction)
{
  const int x = GetWidth() - 2 - 3;
  const int y = 2;
  const int height = GetHeight() / 2;

  {
    //The edges
    const std::string s = "[-]";
    std::copy( s.begin(), s.end(), mArea[y].begin() + x);
    std::copy( s.begin(), s.end(), mArea[y+height].begin() + x);
  }

  for (int i=1; i!=height; ++i) //Not the edges
  {
    const double f
      = 1.0 - static_cast<double>(i)
      / static_cast<double>(height);
    const std::string s = (f > fraction ? "[ ]" : "[*]");
    std::copy( s.begin(), s.end(), mArea[y+i].begin() + x);
  }
}

void Area::Draw(const int x, const int y, const Container& g)
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
      assert(y+j>=0);
      assert(y+j < static_cast<int>(mArea.size() ) );
      assert(x+i>=0);
      assert(x+i < static_cast<int>(mArea[0].size() ) );
      mArea[y+j][x+i] = g[j][i];
    }
  }

  /*
  const Iterator begin = &mArea[ GetInRange(x,0,mArea.size()) ];
  const Iterator end   = &mArea[ GetInRange(x,0,mArea.size()) ];
  assert(begin >= mArea.begin() );
  assert(begin <= mArea.end() );
  assert(end >= mArea.begin() );
  assert(end <= mArea.end() );
  std::for_each(
  */
}

std::ostream& operator<<(std::ostream& os, const Area& a)
{
  const Area::Container& v = a.GetArea();
  std::copy(
    v.begin(),
    v.end(),
    std::ostream_iterator<std::string>(os,"\n"));
  return os;
}

int Area::GetInRange(const int x, const int min, const int max)
{
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

} //~namespace xnz

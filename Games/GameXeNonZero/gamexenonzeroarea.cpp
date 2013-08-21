#include "gamexenonzeroarea.h"

#include <cassert>
#include <iostream>
#include <iterator>

#include "gamexenonzerosprite.h"


namespace xenon_zero {

Area::Area(const int width,const int height)
  : mArea(height,std::string(width,' ')),
    mWidth(width),
    mHeight(height)
{
  assert(static_cast<int>(mArea.size()) == mHeight);
  assert(mArea.size() > 0);
  assert(static_cast<int>(mArea[0].size()) == mWidth);

  DrawEdge();


}

void Area::DrawEdge()
{
  //Create an initial edged screen
  Sprite::mMaxx = mWidth  - 1;
  Sprite::mMaxy = mHeight - 1;

  assert(static_cast<int>(mArea.size()) == mHeight);
  assert(mArea.size() > 0);
  assert(static_cast<int>(mArea[0].size()) == mWidth);

  const std::string edge = std::string(mWidth,'*');
  const std::string nonEdge = "*" + std::string(mWidth-2,' ') + "*";
  mArea[0] = edge;
  for (int i=0; i!=mHeight-2; ++i) mArea[1+i] = nonEdge;
  mArea[mHeight - 1] = edge;
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

  const int areaWidth = this->mWidth;
  const int areaHeight = this->mHeight;

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

int GetInRange(const int x, const int min, const int max)
{
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

/*
BitBlitLine::BitBlitLine(const std::string& source, const int x)
  : mSource(source), mX(x)
{
  assert(mX >= 0);
  assert(mSource.empty() == false);
}

void BitBlitLine::operator()(std::string& dest) const
{
  //Copy source on dest, but do not write beyond bounds of dest
  const int maxCopyLength = dest.size() - mX;


  const std::string::const_iterator begin = mSource.begin();
  const std::string::const_iterator end = mSource.begin() + maxCopyLength;
  const std::string::iterator destBegin = dest.begin() + mX;

  assert(end <= mSource.end());
  assert(destBegin <= dest.end());
  assert(destBegin + maxCopyLength <= dest.end());
  assert(!"TODO?");
  //std::copy(begin,end,dest);
}

BitBlitter::BitBlitter(
  const Area::Graphic& source,
  const int x,
  const int y)
  : mSource(source), mX(x), mY(y)
{
  assert(mX >= 0);

}


void BitBlitter::operator()(Area& dest) const
{
  //
  //std::for_each( dest.begin(), dest.end(), BitBlitLine(
  const int height = mSource.size();
  for (int i=0; i!=height; ++i)
  {
    assert(!"TODO?");

  }

}
*/

} //~namespace xenon_zero

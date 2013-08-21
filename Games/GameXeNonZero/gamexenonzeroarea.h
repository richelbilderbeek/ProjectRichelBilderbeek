#ifndef GAMEXENONZEROAREA_H
#define GAMEXENONZEROAREA_H

#include <string>
#include <vector>

namespace xenon_zero {

struct Area
{

  typedef std::vector<std::string> Container;
  typedef Container Graphic;
  typedef Container::const_iterator ConstIterator;
  typedef Container::iterator Iterator;

  Area(const int width,const int height);

  void DrawEdge();
  void DrawLife(const double fraction);
  void Draw(const int x, const int y, const Container& graphic);
  const Container& GetArea() const { return mArea; }

  int GetWidth() const { return mWidth; }
  int GetHeight() const { return mHeight; }
  const int mWidth;
  const int mHeight;

  private:
  std::vector<std::string> mArea;


};

std::ostream& operator<<(std::ostream& os, const Area& a);

int GetInRange(const int x, const int min, const int max);

/*
struct BitBlitLine : public std::unary_function<void,std::string>
{
  BitBlitLine(const std::string& source, const int x);
  void operator()(std::string& dest) const;
  const std::string& mSource;
  const int mX;
};

struct BitBlitter : public std::unary_function<void,std::string>
{
  BitBlitter(
    const Area::Graphic& source,
    const int x,
    const int y);
  void operator()(Area& dest) const;
  const Area::Graphic& mSource;
  const int mX;
  const int mY;
};
*/


} //~namespace xenon_zero

#endif

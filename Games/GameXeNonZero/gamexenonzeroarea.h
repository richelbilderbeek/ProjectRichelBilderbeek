#ifndef GAMEXENONZEROAREA_H
#define GAMEXENONZEROAREA_H

#include <string>
#include <vector>
#include <boost/checked_delete.hpp>

namespace xnz {

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

  ///Get the area
  const Container& GetArea() const { return mArea; }

  ///Get the area's height in characters
  int GetHeight() const { return static_cast<int>(mArea.size()); }

  ///Get the area's width in characters
  int GetWidth() const { return mArea.empty() ? 0 : static_cast<int>(mArea[0].size()); }


  private:
  ~Area() {}
  friend void boost::checked_delete<>(Area* x);

  std::vector<std::string> mArea;

  static int GetInRange(const int x, const int min, const int max);

};

std::ostream& operator<<(std::ostream& os, const Area& a);


} //~namespace xnz

#endif

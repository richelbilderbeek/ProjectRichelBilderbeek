#ifndef GAMEXENONZEROAREA_H
#define GAMEXENONZEROAREA_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TextCanvas;

namespace xnz {

struct Area
{
  typedef std::vector<std::string> Container;
  typedef Container Graphic;
  typedef Container::const_iterator ConstIterator;
  typedef Container::iterator Iterator;

  Area(const int width,const int height);

  ///Get the area
  //const Container& GetArea() const { return mArea; }

  ///Create a copy of the Area
  const boost::shared_ptr<TextCanvas> CreateTextCanvas() const noexcept;

  void DrawEdge();
  void DrawLife(const double fraction);
  ///Draw a sprite at x,y
  void Draw(const int x, const int y, const Container& graphic);

  ///Get the area's height in characters
  int GetHeight() const noexcept;

  ///Get the area's width in characters
  int GetWidth() const noexcept;


  private:
  ~Area() {}
  friend void boost::checked_delete<>(Area* x);

  //std::vector<std::string> mArea;
  boost::shared_ptr<TextCanvas> mArea;

  static int GetInRange(const int x, const int min, const int max);

};

std::ostream& operator<<(std::ostream& os, const Area& a);

} //~namespace xnz

} //~namespace ribi

#endif

#ifndef TEXTCANVAS_H
#define TEXTCANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "canvas.h"
#pragma GCC diagnostic pop

namespace ribi {

///The TextCanvas is an ASCII art tool to write text
///The Canvas has a coordinat system of (0,0)-(width,height)
///similar to the possible character position on a screen.
///All texts written beyond the range of Canvas is not stored.
///Yet, if for example a text is written at an off-screen coordinat,
///the part that makes it to the Canvas is stored
struct TextCanvas : public Canvas
{
  ///The number of characters the Canvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0 and 0
  TextCanvas(
    const int width  = 1,
    const int height = 1,
    const CanvasCoordinatSystem coordinatSystem = CanvasCoordinatSystem::screen
  );

  TextCanvas(
    const std::vector<std::string>& canvas,
    const CanvasCoordinatSystem coordinatSystem
  );

  ~TextCanvas() noexcept {}

  ///Does the (x,y) coordinat exist?
  bool CanGetChar(const int x, const int y) const noexcept { return IsInRange(x,y); }
  bool CanPutChar(const int x, const int y) const noexcept { return IsInRange(x,y); }

  ///Clears the canvas
  void Clear() noexcept;

  const std::vector<std::string>& GetCanvas() const noexcept { return m_canvas; }

  CanvasCoordinatSystem GetCoordinatSystem() const noexcept { return m_coordinat_system; }

  char GetChar(const int x, const int y) const noexcept;

  ///Obtain the height of the canvas is characters
  int GetHeight() const noexcept { return m_canvas.size(); }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the width of the canvas is characters
  int GetWidth() const noexcept { return (GetHeight()==0 ? 0 : m_canvas[0].size() ); }

  ///Check if a coordinat is in the range of the Canvas
  bool IsInRange(const int x, const int y) const noexcept;

  void Load(const std::vector<std::string>& v) noexcept { m_canvas = v; }

  ///Put a canvas on the canvas
  void PutCanvas(
    const int left, const int top,
    const boost::shared_ptr<const TextCanvas>& canvas
  ) noexcept;

  ///Put a character on the Canvas
  ///If the character is not in range, nothing happens
  void PutChar(const int x, const int y, const char c) noexcept;

  ///Put text to the Canvas
  //
  //  Canvas::DrawText(1,1,"Hello world") results in (I added dots for spaces, for clarity):
  //
  //  .............
  //  .Hello world.
  //  .............
  //
  void PutText(const int x, const int y, const std::string& text) noexcept;

  ///Set the coordinat system used
  void SetCoordinatSystem(const CanvasCoordinatSystem coordinatSystem) noexcept;

  ///Convert to a single string, lines seperated with '\n'
  std::string ToString() const noexcept;

  ///Convert to a collection of strings
  std::vector<std::string> ToStrings() const noexcept;

  private:
  ///The Canvas its internal data
  std::vector<std::string> m_canvas;

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  CanvasCoordinatSystem m_coordinat_system;

  //From http://www.richelbilderbeek.nl/CppMinElement.htm
  template <class Container>
  static const typename Container::value_type::value_type MinElement(const Container& v);

  //From http://www.richelbilderbeek.nl/CppMaxElement.htm
  template <class Container>
  static const typename Container::value_type::value_type MaxElement(const Container& v);

  ///Plot a surface on screen
  ///if as_screen_coordinat_system is true, the origin is in the top left
  ///corner of the screen, else it is in the bottom left of the screen,
  ///as is usual in graphs
  //From http://www.richelbilderbeek.nl/CppPlotSurface.htm
  static void PlotSurface(
    std::ostream& os,
    const std::vector<std::vector<double> >& v,
    const bool use_normal_color_system,
    const bool as_screen_coordinat_system);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const TextCanvas& canvas);

};

std::ostream& operator<<(std::ostream& os, const TextCanvas& canvas);
bool operator==(const TextCanvas& lhs, const TextCanvas& rhs) noexcept;
bool operator!=(const TextCanvas& lhs, const TextCanvas& rhs) noexcept;

} //~namespace ribi

#endif

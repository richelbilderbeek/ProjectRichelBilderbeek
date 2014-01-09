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
struct TextCanvas
{
  ///The number of characters the Canvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0 and 0
  TextCanvas(
    const int width  = 1,
    const int height = 1,
    const Canvas::CoordinatSystem coordinatSystem = Canvas::CoordinatSystem::screen);

  ///Clears the canvas
  void Clear() noexcept;

  ///Obtain the height of the canvas is characters
  int GetHeight() const noexcept { return mCanvas.size(); }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the width of the canvas is characters
  int GetWidth() const noexcept { return (GetHeight()==0 ? 0 : mCanvas[0].size() ); }

  ///Put a character on the Canvas
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
  void SetCoordinatSystem(const Canvas::CoordinatSystem coordinatSystem) noexcept;

  ///This signal is emitted when any member variable changes
  boost::signals2::signal<void(TextCanvas*)> m_signal_changed;

  private:
  ///The Canvas its internal data
  std::vector<std::string> mCanvas;

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  Canvas::CoordinatSystem mCoordinatSystem;

  ///Check if a coordinat is in the range of the Canvas
  bool IsInRange(const int x, const int y) const;

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

} //~namespace ribi

#endif

#ifndef MULTICANVAS_H
#define MULTICANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "canvas.h"
#include "canvascolorsystem.h"
#include "canvascoordinatsystem.h"
#pragma GCC diagnostic pop

struct QRegExp;

namespace ribi {

///A MultiCanvas is an ASCII art class for displaying
///multiple layers of Canvas classes
struct MultiCanvas : public Canvas
{
  MultiCanvas(
    const std::vector<boost::shared_ptr<Canvas>>& canvases
  );

  ///Obtain the height of the canvas is characters
  int GetHeight() const noexcept;

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the width of the canvas is characters
  int GetWidth() const noexcept;

  ///Convert the MultiCanvas to std::strings
  const std::vector<std::string> ToStrings() const noexcept;

  private:
  const std::vector<boost::shared_ptr<Canvas>> m_canvases;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const MultiCanvas& c);

} //~namespace ribi

#endif

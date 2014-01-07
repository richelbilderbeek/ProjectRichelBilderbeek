#ifndef IMAGECANVAS_H
#define IMAGECANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "canvas.h"
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

///ImageCanvas converts an image to a Canvas
struct ImageCanvas
{
  ///The number of characters the Canvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0.0 and 0.0
  ImageCanvas(
    const std::string& filename,
    const int n_cols,
    const Canvas::ColorSystem colorSystem         = Canvas::ColorSystem::normal,
    const Canvas::CoordinatSystem coordinatSystem = Canvas::CoordinatSystem::screen);

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  const boost::shared_ptr<Canvas> ToCanvas() const noexcept;

  private:
  const Canvas::ColorSystem mColorSystem;
  const Canvas::CoordinatSystem mCoordinatSystem;
  const std::string m_filename;
  const int m_n_cols;

  ///Returns a Y-X-ordered std::vector of greynesses.
  static const std::vector<std::vector<double> >
    ConvertToGreyYx(const QImage * const i);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const ImageCanvas& canvas);

};

std::ostream& operator<<(std::ostream& os, const ImageCanvas& canvas);

} //~namespace ribi

#endif

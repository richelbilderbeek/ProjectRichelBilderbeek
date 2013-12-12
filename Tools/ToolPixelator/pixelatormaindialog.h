#ifndef PIXELATORMAINDIALOG_H
#define PIXELATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <vector>
#include <QPixmap>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct PixelatorMainDialog
{
  static QPixmap DoPixelate(const QPixmap& source, const int pixel_size) noexcept;

  private:

  //Get a pixel's greyness
  //From http://www.richelbilderbeek.nl
  static QRgb GetPixel(
    const QImage& image,
    const int x,
    const int y) noexcept;

  //Get a line of pixel's average greyness
  //From x1 to (not including) x2
  //From http://www.richelbilderbeek.nl
  static QRgb GetPixel(
    const QImage& image,
    const int x1,
    const int x2,
    const int y) noexcept;

  //Get a square of pixels' average greyness
  //From http://www.richelbilderbeek.nl
  static QRgb GetPixel(
    const QImage& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2) noexcept;

  //Set a square of pixels' color
  //From http://www.richelbilderbeek.nl
  static void SetPixel(
    QImage& image,
    const int x1,
    const int y1,
    const int x2,
    const int y2,
    const QRgb color) noexcept;

  //Set a line of pixel's color
  //From http://www.richelbilderbeek.nl/CppSetPixel.htm
  static void SetPixel(
    QImage& image,
    const int x1,
    const int x2,
    const int y,
    const QRgb color) noexcept;

  //Set a pixel's color
  //From http://www.richelbilderbeek.nl/CppSetPixel.htm
  static void SetPixel(
    QImage& image,
    const int x,
    const int y,
    const QRgb color) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi


#endif

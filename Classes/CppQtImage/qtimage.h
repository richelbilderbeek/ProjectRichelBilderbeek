#ifndef QTIMAGE_H
#define QTIMAGE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#pragma GCC diagnostic pop

namespace ribi {

///Some handy functions on QImage
struct QtImage
{
  QtImage() noexcept;
  QImage Difference(const QImage& base, const QImage& to_xor) noexcept;
  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  //Render a QGraphicsItem to a QImage
  QImage Paint(const QGraphicsItem& item) noexcept;


  QImage Xor(const QImage& base, const QImage& to_xor) noexcept;
  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace ribi

#endif // QTIMAGE_H

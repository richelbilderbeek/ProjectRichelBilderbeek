#ifndef VALENTINECARDDECRYPTERMAINDIALOG_H
#define VALENTINECARDDECRYPTERMAINDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include <QImage>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct TextCanvas;

struct ValentineCardDecrypterMainDialog
{
  ValentineCardDecrypterMainDialog();
  const boost::shared_ptr<TextCanvas> ToSymbolsAsString(const std::string& s) const noexcept;
  const boost::shared_ptr<QImage> ToSymbolsAsImage(const std::string& s) const noexcept;

  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi


#endif

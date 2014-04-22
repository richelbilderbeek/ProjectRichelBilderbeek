#ifndef SECRETMESSAGEMAINDIALOG_H
#define SECRETMESSAGEMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct QImage;
typedef unsigned int QRgb;

namespace ribi {
namespace sema {

struct MainDialog
{
  MainDialog();

  const boost::shared_ptr<QImage> CreateSecretMessageRed(
    const boost::shared_ptr<const QImage>& plain,
    const boost::shared_ptr<const QImage>& secret
  ) const noexcept;

  const boost::shared_ptr<QImage> ExtractMessageRed(
    const boost::shared_ptr<const QImage>& secret
  ) const noexcept;

  bool IsWhite(const QRgb& rgb) const noexcept;


  private:
  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace sema
} //~namespace ribi

#endif // SECRETMESSAGEMAINDIALOG_H

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

struct ThresholdFiltererMainDialog
{
  static QPixmap DoThresholdFiltering(const QPixmap& source, const int threshold) noexcept;
};

} //~namespace ribi


#endif

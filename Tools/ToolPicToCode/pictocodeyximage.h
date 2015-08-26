#ifndef PICTOCODEYXIMAGE_H
#define PICTOCODEYXIMAGE_H

#include <vector>

#include "pictocodepixel.h"

struct QImage;

namespace ribi {
namespace p2c {

struct YxImage
{
  YxImage() : m_v{} {}
  YxImage(const QImage& qt_image);
  std::vector<std::vector<Pixel> > m_v;
  int width() const { return m_v[0].size(); }
  int height() const { return m_v.size(); }
};

YxImage ImageToImage(const QImage& qt_image);

} //~namespace p2c
} //~namespace ribi

#endif // PICTOCODEYXIMAGE_H

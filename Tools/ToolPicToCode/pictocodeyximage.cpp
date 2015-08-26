#include "pictocodeyximage.h"

#include <QImage>

ribi::p2c::YxImage::YxImage(const QImage& qt_image)
  : m_v{}
{
  const int width  = qt_image.width();
  const int height = qt_image.height();

  m_v.resize(height,std::vector<Pixel>(width));

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const line
      = static_cast<const unsigned char *>(qt_image.scanLine(y));
    for (int x=0; x!=width; ++x)
    {
      m_v[y][x].a = static_cast<int>(line[(x*4)+3]);
      m_v[y][x].r = static_cast<int>(line[(x*4)+2]);
      m_v[y][x].g = static_cast<int>(line[(x*4)+1]);
      m_v[y][x].b = static_cast<int>(line[(x*4)+0]);
    }
  }
}

ribi::p2c::YxImage ribi::p2c::ImageToImage(const QImage& qt_image)
{
  const int width  = qt_image.width();
  const int height = qt_image.height();

  YxImage image;
  image.m_v.resize(height,std::vector<Pixel>(width));

  for (int y=0; y!=height; ++y)
  {
    const unsigned char * const line
      = static_cast<const unsigned char *>(qt_image.scanLine(y));
    for (int x=0; x!=width; ++x)
    {
      image.m_v[y][x].a = static_cast<int>(line[(x*4)+3]);
      image.m_v[y][x].r = static_cast<int>(line[(x*4)+2]);
      image.m_v[y][x].g = static_cast<int>(line[(x*4)+1]);
      image.m_v[y][x].b = static_cast<int>(line[(x*4)+0]);
    }
  }
  return image;
}

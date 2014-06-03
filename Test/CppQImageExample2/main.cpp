#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#pragma GCC diagnostic pop

QImage CreateImage(const int width, const int height, const int z) noexcept
{
  QImage image(width,height,QImage::Format_ARGB32);
  for (int y=0;y!=height;++y)
  {
    for (int x=0;x!=width;++x)
    {
      image.setPixel(
        x,y,
        qRgb((x+z+0)%256,(y+z+0)%256,(x+y+z)%256) //Color
      );
    }
  }
  return image;
}

void DrawImage(
  QImage& target, const QImage& source,
  const int left, const int top
) noexcept
{
  const int width = source.width();
  const int height = source.height();
  for (int y=0; y!=height; ++y)
  {
    for (int x=0; x!=width; ++x)
    {
      target.setPixel(left+x,top+y,source.pixel(x,y));
    }
  }
}

int main()
{
  QImage a = CreateImage(256,256,64);
  const QImage b = CreateImage(196,156,196);
  DrawImage(a,b,32,64);
  a.save("CppQImageExample2.png");
}

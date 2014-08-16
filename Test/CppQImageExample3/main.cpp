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

QImage DrawTiled(
  const int n_cols, const int n_rows,
  const QImage& a, const QImage& b
) noexcept
{
  assert(a.width()  == b.width());
  assert(a.height() == b.height());
  const int block_width  = a.width();
  const int block_height = a.height();
  const int width  = n_rows * block_width;
  const int height = n_cols * block_height;
  QImage result(width,height,QImage::Format_ARGB32);
  for (int y=0; y!=n_rows; ++y)
  {
    for (int x=0; x!=n_cols; ++x)
    {
      DrawImage(
        result,
        (std::rand() >> 4) % 2 ? a : b,
        block_width * x,
        block_width * y
      );
    }
  }
  return result;
}

int main()
{
  const QImage a = CreateImage(64,64,0);
  const QImage b = CreateImage(64,64,128);
  const QImage c = DrawTiled(4,4,a,b);
  c.save("CppQImageExample3.png");
}

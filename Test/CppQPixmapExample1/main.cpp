#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QImage>
#include <QPixmap>
#pragma GCC diagnostic pop

QPixmap CreatePixmap(const int width, const int height, const int z)
{
  QPixmap pixmap(width,height);
  QImage image = pixmap.toImage();
  for (int y=0;y!=height;++y)
  {
    for (int x=0;x!=width;++x)
    {
      image.setPixel(
        QPoint(x,y), //Position
        qRgb((x+z+0)%256,(y+z+0)%256,(x+y+z)%256) //Color

        /*
        QColor( //Color
          (x+z+0)%256,
          (y+z+0)%256,
          (x+y+z)%256)
        .rgb()
        */
      );
    }
  }
  pixmap = QPixmap::fromImage(image);
  return pixmap;
}

int main()
{
  //Cannot create a QPixmap here, because of the following error:
  //
  //  QPixmap: Must construct a QApplication before a QPaintDevice
  //

  //QPixmap pixmap = CreatePixmap(32,32,128);

  //pixmap.save("CppQPixmapExample1.png");
  //QImage image = pixmap.toImage();
  //image.save("CppQPixmapExample1.png");


}

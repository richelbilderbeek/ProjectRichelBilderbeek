#include "image.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <QBitmap>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#pragma GCC diagnostic pop

Image::Image(const QString& filename)
{
  //MouseTracking must be set to true, to make Image clickable
  this->setMouseTracking(true);
  //Set the image
  QPixmap pixmap(filename);
  std::clog << "Using pixmap file '" << filename.toStdString() << "'\n";
  assert(!pixmap.isNull());
  //Set transparency (white, in this example)
  const QBitmap mask = pixmap.createMaskFromColor(QColor(255,255,255,0).rgb());
  pixmap.setMask(mask);
  this->setPixmap(pixmap);
}

void Image::mousePressEvent( QMouseEvent *)
{
  std::clog << "emitting onClick()\n";
  emit onClick();
}

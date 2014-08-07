#include "secretmessagemaindialog.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QFile>
#include <QImage>

#include "fileio.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::sema::MainDialog::MainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

//Makes all red pixels even, except when there's a message pixel
//From http://www.richelbilderbeek.nl/CppAddMessageRed.htm
const boost::shared_ptr<QImage> ribi::sema::MainDialog::CreateSecretMessageRed(
  const boost::shared_ptr<const QImage>& original,
  const boost::shared_ptr<const QImage>& message
) const noexcept
{
  const int width  { std::min(original->width() ,message->width() ) };
  const int height { std::min(original->height(),message->height()) };
  const boost::shared_ptr<QImage> result {
    new QImage(width,height,QImage::Format_RGB32)
  };
  assert(original!=0 && "Image is NULL");
  assert(message!=0 && "Image is NULL");
  assert(result!=0 && "Image is NULL");
  //Get the pixel offsets
  const int dx1 = (original->width()  - width ) / 2;
  const int dx2 = (message->width()   - width ) / 2;
  const int dy1 = (original->height() - height) / 2;
  const int dy2 = (message->height()  - height) / 2;
  assert(dx1 >= 0);
  assert(dx2 >= 0);
  assert(dy1 >= 0);
  assert(dy2 >= 0);

  for (int y=0; y!=height; ++y)
  {
    for(int x=0; x!=width; ++x)
    {
      const int x1 = dx1 + x;
      const int x2 = dx2 + x;
      const int x3 = x;
      assert(x1 >= 0);
      assert(x2 >= 0);
      assert(x3 >= 0);
      assert(x1 < original->width());
      assert(x2 < message->width());
      assert(x3 < result->width()  );
      const int y1 = dy1 + y;
      const int y2 = dy2 + y;
      const int y3 = y;
      assert(y1 >= 0);
      assert(y2 >= 0);
      assert(y3 >= 0);
      assert(y1 < original->height());
      assert(y2 < message->height());
      assert(y3 < result->height());
      //Get original's pixel
      QRgb pixel = original->pixel(x1,y1);
      int r = qRed(pixel);
      const int g = qGreen(pixel);
      const int b = qBlue(pixel);
      //Make colors even by increment, watch out for 256
      if (r%2 != 0)
      {
        if (r == 255) {--r;}
        else { ++r; }
      }
      assert(r%2 == 0);
      assert(r <= 254);
      //Add message
      if (IsWhite(message->pixel(x2,y2))) ++r;
      //Write to result image
      result->setPixel(x3,y3,qRgb(r,g,b));
    }
  }
  return result;
}

const boost::shared_ptr<QImage> ribi::sema::MainDialog::ExtractMessageRed(
  const boost::shared_ptr<const QImage>& original
) const noexcept
{
  const int width  { original->width()  };
  const int height { original->height() };
  const boost::shared_ptr<QImage> result {
    new QImage(width,height,QImage::Format_RGB32)
  };
  assert(original && "Image is NULL");
  assert(result && "Image is NULL");

  //Get sizes and set size
  for (int y=0; y!=height; ++y)
  {
    for(int x=0; x!=width; ++x)
    {
      //Get original's pixel
      const QRgb color { original->pixel(x,y) };
      const int r = qRed(color);
      //const int g = qGreen(color);
      //const int b = qBlue(color);
      //Make colors even by increment, watch out for 256
      if (r%2 == 0)
      {
        //No message pixel
        result->setPixel(x,y,qRgb(0,0,0));
      }
      else
      {
        //Message pixel
        result->setPixel(x,y,qRgb(255,255,255));
      }
    }
  }
  return result;
}

bool ribi::sema::MainDialog::IsWhite(const QRgb& rgb) const noexcept
{
  const int r = qRed(rgb);
  const int g = qGreen(rgb);
  const int b = qBlue(rgb);
  const int sum = static_cast<int>(r)
    + static_cast<int>(g)
    + static_cast<int>(b);
  return (sum / 3 > 127);
}

#ifndef NDEBUG
void ribi::sema::MainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const std::string source_file { fileio::FileIo().GetTempFileName(".png") };
  const std::string message_file { fileio::FileIo().GetTempFileName(".png") };
  //const std::string result_file { fileio::FileIo().GetTempFileName(".png") };
  {
    QFile qt_source_file(":/secretmessage/images/ToolSecretMessageWhite.png");
    qt_source_file.copy(source_file.c_str());
  }
  {
    QFile qt_message_file(":/secretmessage/images/ToolSecretMessageR.png");
    qt_message_file.copy(message_file.c_str());
  }
  assert(fileio::FileIo().IsRegularFile(source_file));
  const boost::shared_ptr<QImage> source { new QImage(source_file.c_str()) };
  assert(fileio::FileIo().IsRegularFile(message_file));
  const boost::shared_ptr<QImage> message { new QImage(message_file.c_str()) };
  const boost::shared_ptr<QImage> result { MainDialog().CreateSecretMessageRed(source,message) };
  assert(*result != *source);
  const boost::shared_ptr<QImage> message_again { MainDialog().ExtractMessageRed(result) };
  assert(message_again);
  fileio::FileIo().DeleteFile(source_file);
  fileio::FileIo().DeleteFile(message_file);
}
#endif


#include "qtimage.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QPainter>

#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtImage::QtImage() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif // NDEBUG
}

QImage ribi::QtImage::Difference(const QImage& base, const QImage& to_xor) noexcept
{
  QImage result{base};
  {
    QPainter painter(&result);
    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    painter.drawImage(0,0,to_xor);
  }
  return result;
}

std::string ribi::QtImage::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtImage::GetVersionHistory() noexcept
{
  return {
    "2014-08-05: Version 1.0: initial version",
  };
}

#ifndef NDEBUG
void ribi::QtImage::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Default-construction of QtImage"); }
  {
    const QtImage q;
  }
  if (verbose) { TRACE("QImage pixel manipultion"); }
  {
    QImage q(1,1,QImage::Format_RGB32);
    q.setPixel(0,0,qRgb(1,2,3));
    assert(q.pixel(0,0) == qRgb(1,2,3));
  }
}
#endif

QImage ribi::QtImage::Xor(const QImage& base, const QImage& to_xor) noexcept
{
  QImage result{base};
  {
    QPainter painter(&result);
    //painter.setCompositionMode(QPainter::CompositionMode_Xor);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.drawImage(0,0,to_xor);
  }
  return result;
}


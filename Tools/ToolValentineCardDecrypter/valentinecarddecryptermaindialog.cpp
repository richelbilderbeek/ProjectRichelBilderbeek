#include "valentinecarddecryptermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/math/constants/constants.hpp>

#include "textcanvas.h"
#include "trace.h"
#include "testtimer.h"
#include "valentinecardsymbol.h"
#include "valentinecardsymbols.h"
#pragma GCC diagnostic pop

ribi::ValentineCardDecrypterMainDialog::ValentineCardDecrypterMainDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
void ribi::ValentineCardDecrypterMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ValentineCardSymbol(0);
    ValentineCardSymbols();
    TextCanvas();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ValentineCardDecrypterMainDialog d;
  {
    const boost::shared_ptr<TextCanvas> canvas {
      d.ToSymbolsAsString(" ")
    };
    const boost::shared_ptr<TextCanvas> expected {
      new TextCanvas(
        { "   ","   ","   " },
        CanvasCoordinatSystem::screen
      )
    };
    if (*canvas != *expected)
    {
      TRACE("ERROR");
      TRACE(*canvas);
      TRACE(*expected);
      TRACE("BREAK");
    }
    assert(*canvas == *expected);
  }
  {
    const boost::shared_ptr<TextCanvas> canvas {
      d.ToSymbolsAsString("?")
    };
    const boost::shared_ptr<TextCanvas> expected {
      new TextCanvas(
        { "+-+","|x ","+  " },
        CanvasCoordinatSystem::screen
      )
    };
    assert(*canvas == *expected);
  }
}
#endif

const boost::shared_ptr<ribi::TextCanvas> ribi::ValentineCardDecrypterMainDialog::ToSymbolsAsString(const std::string& s) const noexcept
{
  const std::vector<boost::shared_ptr<ValentineCardSymbol>> v {
    ValentineCardSymbols().TextToSymbols(s)
  };
  const int sz = static_cast<int>(v.size());
  if (sz == 0) return nullptr;

  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas((sz * 3) + sz - 1, 3) //Add spaces
  };
  assert(canvas);
  for (int i=0; i!=sz; ++i)
  {
    assert(i < static_cast<int>(v.size()));
    assert(v[i]);
    assert(v[i]->ToTextCanvas());
    const boost::shared_ptr<TextCanvas> text { v[i]->ToTextCanvas() };
    assert(text);
    assert(text->GetHeight() == 3);
    assert(text->GetWidth() == 3);
    for (int row = 0; row!=3; ++row)
    {
      for (int col = 0; col!=3; ++col)
      {
        canvas->PutChar((4*i) + col,row,text->GetChar(col,row));
      }
      const int col = 3;
      canvas->PutChar((4*i) + col,row,' ');
    }
  }
  return canvas;
}

const boost::shared_ptr<QImage> ribi::ValentineCardDecrypterMainDialog::ToSymbolsAsImage(const std::string& s) const noexcept
{
  const std::vector<boost::shared_ptr<ValentineCardSymbol>> v {
    ValentineCardSymbols().TextToSymbols(s)
  };
  const int sz = static_cast<int>(v.size());
  boost::shared_ptr<QImage> image {
    new QImage((sz * 7) + sz - 1, 7,QImage::Format::Format_RGB32)
  };
  assert(image);
  for (int i=0; i!=sz; ++i)
  {
    const boost::shared_ptr<ValentineCardSymbol> s { v[i] };
    assert(s);
    const boost::shared_ptr<QImage> image_char { s->ToImage() };
    for (int row = 0; row!=7; ++row)
    {
      for (int col = 0; col!=7; ++col)
      {
        image->setPixel((8*i) + col,row,image_char->pixel(col,row));
      }
      if (i + 1 != sz)
      {
        const int col = 7;
        image->setPixel((8*i) + col,row,qRgb(255,255,255));
      }
    }
  }
  return image;
}

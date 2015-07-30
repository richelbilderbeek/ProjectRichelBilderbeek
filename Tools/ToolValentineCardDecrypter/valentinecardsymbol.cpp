#include "valentinecardsymbol.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include <QImage>

#include "fileio.h"
#include "textcanvas.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::ValentineCardSymbol::ValentineCardSymbol(
  const std::array<bool,4> lines,
  const ValentineCardSymbol::CenterSymbol center_symbol
)
  : m_center_symbol(center_symbol),
    m_lines(lines)
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::ValentineCardSymbol::ValentineCardSymbol(
  const int value
)
  : m_center_symbol{CenterSymbol::none},
    m_lines{ {false,true,true,false} }
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(value < 27);
  switch (value / 9)
  {
    case 0: m_center_symbol = CenterSymbol::none ; break;
    case 1: m_center_symbol = CenterSymbol::dot  ; break;
    case 2: m_center_symbol = CenterSymbol::cross; break;
    default: assert(!"Should not get here");
      throw std::logic_error("ribi::ValentineCardSymbol::ValentineCardSymbol(const int value): unknown value");
  }
  const int i = value % 9;
  const bool a = i / 3 >= 1;
  const bool b = i % 3 <= 1;
  const bool c = i / 3 <= 1;
  const bool d = i % 3 >= 1;
  m_lines = { a, b, c, d };
}

int ribi::ValentineCardSymbol::CalcValue() const noexcept
{
  int symbol_value = -1;
  switch (GetCenterSymbol())
  {
    case CenterSymbol::none : symbol_value = 0; break;
    case CenterSymbol::dot  : symbol_value = 1; break;
    case CenterSymbol::cross: symbol_value = 2; break;
    default: assert(!"Should not get here");
      throw std::logic_error("ribi::ValentineCardSymbol::CalcValue: unknown CenterSymbol");
  }
  const int lines_value {
      ( GetLines()[0] ? 3 : 0)
    + (!GetLines()[1] ? 1 : 0)
    + (!GetLines()[2] ? 3 : 0)
    + ( GetLines()[3] ? 1 : 0)
  };
  return (symbol_value * 9) + lines_value;
}

std::string ribi::ValentineCardSymbol::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::ValentineCardSymbol::GetVersionHistory() noexcept
{
  return {
    "2014-02-17: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::ValentineCardSymbol::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::fileio::FileIo();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  {
    assert(ValentineCardSymbol( { false, true, true,false }, CenterSymbol::none ).CalcValue() == 0);
    assert(ValentineCardSymbol( { false, true, true, true }, CenterSymbol::none ).CalcValue() == 1);
    assert(ValentineCardSymbol( { false,false, true, true }, CenterSymbol::none ).CalcValue() == 2);
    assert(ValentineCardSymbol( {  true, true, true,false }, CenterSymbol::none ).CalcValue() == 3);
    assert(ValentineCardSymbol( {  true, true, true, true }, CenterSymbol::none ).CalcValue() == 4);
    assert(ValentineCardSymbol( {  true,false, true, true }, CenterSymbol::none ).CalcValue() == 5);
    assert(ValentineCardSymbol( {  true, true,false,false }, CenterSymbol::none ).CalcValue() == 6);
    assert(ValentineCardSymbol( {  true, true,false, true }, CenterSymbol::none ).CalcValue() == 7);
    assert(ValentineCardSymbol( {  true,false,false, true }, CenterSymbol::none ).CalcValue() == 8);

    assert(ValentineCardSymbol( { false, true, true,false }, CenterSymbol::dot ).CalcValue() ==  9);
    assert(ValentineCardSymbol( { false, true, true, true }, CenterSymbol::dot ).CalcValue() == 10);
    assert(ValentineCardSymbol( { false,false, true, true }, CenterSymbol::dot ).CalcValue() == 11);
    assert(ValentineCardSymbol( {  true, true, true,false }, CenterSymbol::dot ).CalcValue() == 12);
    assert(ValentineCardSymbol( {  true, true, true, true }, CenterSymbol::dot ).CalcValue() == 13);
    assert(ValentineCardSymbol( {  true,false, true, true }, CenterSymbol::dot ).CalcValue() == 14);
    assert(ValentineCardSymbol( {  true, true,false,false }, CenterSymbol::dot ).CalcValue() == 15);
    assert(ValentineCardSymbol( {  true, true,false, true }, CenterSymbol::dot ).CalcValue() == 16);
    assert(ValentineCardSymbol( {  true,false,false, true }, CenterSymbol::dot ).CalcValue() == 17);

    assert(ValentineCardSymbol( { false, true, true,false }, CenterSymbol::cross ).CalcValue() == 18);
    assert(ValentineCardSymbol( { false, true, true, true }, CenterSymbol::cross ).CalcValue() == 19);
    assert(ValentineCardSymbol( { false,false, true, true }, CenterSymbol::cross ).CalcValue() == 20);
    assert(ValentineCardSymbol( {  true, true, true,false }, CenterSymbol::cross ).CalcValue() == 21);
    assert(ValentineCardSymbol( {  true, true, true, true }, CenterSymbol::cross ).CalcValue() == 22);
    assert(ValentineCardSymbol( {  true,false, true, true }, CenterSymbol::cross ).CalcValue() == 23);
    assert(ValentineCardSymbol( {  true, true,false,false }, CenterSymbol::cross ).CalcValue() == 24);
    assert(ValentineCardSymbol( {  true, true,false, true }, CenterSymbol::cross ).CalcValue() == 25);
    assert(ValentineCardSymbol( {  true,false,false, true }, CenterSymbol::cross ).CalcValue() == 26);
  }
  for (int i=0; i!=27; ++i)
  {
    assert(ValentineCardSymbol(i).CalcValue() == i);
    assert(ValentineCardSymbol(i).ToImage());
    const std::string filename = fileio::FileIo().GetTempFileName(
      boost::lexical_cast<std::string>(i) + ".png");
    ValentineCardSymbol(i).ToImage()->save(filename.c_str());
  }
}
#endif

const boost::shared_ptr<QImage> ribi::ValentineCardSymbol::ToImage() const noexcept
{
  const boost::shared_ptr<QImage> image {
    new QImage(7,7,QImage::Format_ARGB32)
  };
  // +-----+
  // |     |
  // | x x |
  // |  x  |
  // | x x |
  // |     |
  // +-----+
  //
  // +-----+0
  // |     |1
  // |     |2
  // |  x  |3
  // |     |4
  // |     |5
  // +-----+6
  // +-+ +0+
  // | | 3 1
  // +-+ +2+
  //Corners
  const QRgb white { qRgb(0,0,0) };
  const QRgb black { qRgb(255,255,255) };
  for (int y=0; y!=7; ++y)
  {
    for (int x=0; x!=7; ++x)
    {
      image->setPixel(x,y,black);
    }
  }

  image->setPixel(0,0, m_lines[0] || m_lines[3] ? white : black);
  image->setPixel(6,0, m_lines[0] || m_lines[1] ? white : black);
  image->setPixel(0,6, m_lines[2] || m_lines[3] ? white : black);
  image->setPixel(6,6, m_lines[1] || m_lines[2] ? white : black);
  //Edges
  {
    const QRgb color { m_lines[0] ? white : black };
    for (int x=1; x!=6; ++x) image->setPixel(x,0,color);
  }
  {
    const QRgb color { m_lines[1] ? white : black };
    for (int y=1; y!=6; ++y) image->setPixel(6,y,color);
  }
  {
    const QRgb color { m_lines[2] ? white : black };
    for (int x=1; x!=6; ++x) image->setPixel(x,6,color);
  }
  {
    const QRgb color { m_lines[3] ? white : black };
    for (int y=1; y!=6; ++y) image->setPixel(0,y,color);
  }
  switch (m_center_symbol)
  {
    case CenterSymbol::none :
      break;
    case CenterSymbol::dot  :
      image->setPixel(3,3,white);
      break;
    case CenterSymbol::cross:
      image->setPixel(2,2,white);
      image->setPixel(3,3,white);
      image->setPixel(4,4,white);
      image->setPixel(2,4,white);
      image->setPixel(4,2,white);
      break;
  }
  return image;
}

const boost::shared_ptr<ribi::TextCanvas> ribi::ValentineCardSymbol::ToTextCanvas() const noexcept
{
  const boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(3,3)
  };
  // +-+ +0+
  // | | 3 1
  // +-+ +2+
  //Corners
  canvas->PutChar(0,0, m_lines[0] || m_lines[3] ? '+' : ' ');
  canvas->PutChar(2,0, m_lines[0] || m_lines[1] ? '+' : ' ');
  canvas->PutChar(0,2, m_lines[2] || m_lines[3] ? '+' : ' ');
  canvas->PutChar(2,2, m_lines[1] || m_lines[2] ? '+' : ' ');
  //Edges
  canvas->PutChar(1,0, m_lines[0] ? '-' : ' ');
  canvas->PutChar(0,1, m_lines[3] ? '|' : ' ');
  canvas->PutChar(2,1, m_lines[1] ? '|' : ' ');
  canvas->PutChar(1,2, m_lines[2] ? '-' : ' ');
  // +-+ +-+ +-+
  // | | |.| |x|
  // +-+ +-+ +-+
  switch (m_center_symbol)
  {
    case CenterSymbol::none : canvas->PutChar(1,1,' '); break;
    case CenterSymbol::dot  : canvas->PutChar(1,1,'.'); break;
    case CenterSymbol::cross: canvas->PutChar(1,1,'x'); break;
  }
  return canvas;
}


bool ribi::operator<(const ribi::ValentineCardSymbol& lhs, const ribi::ValentineCardSymbol& rhs) noexcept
{
  return lhs.CalcValue() < rhs.CalcValue();
}

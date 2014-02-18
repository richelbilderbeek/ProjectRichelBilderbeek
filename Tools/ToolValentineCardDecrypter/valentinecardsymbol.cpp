#include "valentinecardsymbol.h"

#include <cassert>
#include "textcanvas.h"

ribi::ValentineCardSymbol::ValentineCardSymbol(
  const std::array<bool,4> lines,
  const ValentineCardSymbol::CenterSymbol center_symbol
)
  : m_center_symbol(center_symbol),
    m_lines(lines)
{

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
  canvas->PutChar(0,0, m_lines[0] || m_lines[3] ? '+', ' ');
  canvas->PutChar(0,2, m_lines[0] || m_lines[1] ? '+', ' ');
  canvas->PutChar(2,0, m_lines[2] || m_lines[3] ? '+', ' ');
  canvas->PutChar(2,2, m_lines[1] || m_lines[2] ? '+', ' ');
  //Edges
  canvas->PutChar(1,0, m_lines[0] ? '-', ' ');
  canvas->PutChar(0,1, m_lines[3] ? '|', ' ');
  canvas->PutChar(2,1, m_lines[1] ? '|', ' ');
  canvas->PutChar(1,2, m_lines[2] ? '-', ' ');
  // +-+ +-+ +-+
  // | | |.| |x|
  // +-+ +-+ +-+
  switch (m_center_symbol)
  {
    case CenterSymbol::none: canvas->PutChar(1,1,' ');
    case CenterSymbol::dot: canvas->PutChar(1,1,'.');
    case CenterSymbol::cross: canvas->PutChar(1,1,'x');
  }
  return canvas;
}

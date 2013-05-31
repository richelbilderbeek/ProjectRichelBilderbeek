#include "chesswidget.h"

#include <cassert>
#include <thread>

#include "chessboard.h"
#include "chesspiece.h"
#include "chessgame.h"
#include "chesssquare.h"
#include "chesssquareselector.h"
#include "trace.h"

namespace Chess {

ChessWidget::ChessWidget(const Rect& geometry)
  : m_selector(new SquareSelector)
{
  #ifndef NDEBUG
  ChessWidget::Test();
  #endif

  m_selector->m_signal_changed.connect(
    boost::bind(
      &ChessWidget::OnChanged,
      this));

  this->SetGeometry(geometry);
}

ChessWidget::~ChessWidget()
{
  //All done automatically
}

void ChessWidget::ClickPixel(const int x,const int y)
{
  try
  {
    const Square square(8 * x / this->GetGeometry().GetWidth(), 8 * y / this->GetGeometry().GetHeight());
    this->Click(square);
  }
  catch (std::exception& e)
  {
    //No problem
  }
}

const std::string ChessWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ChessWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

void ChessWidget::OnChanged() const
{
  m_signal_graphic_changed();
}

void ChessWidget::PressKey(const Chess::ChessWidget::Key key)
{
  switch (key)
  {
    case Key::up    : m_selector->MoveUp(); break;
    case Key::right : m_selector->MoveRight(); break;
    case Key::down  : m_selector->MoveDown(); break;
    case Key::left  : m_selector->MoveLeft(); break;
    case Key::select: this->Click(*m_selector->GetCursor()); break;
    default: assert(!"Should not get here");
  }
}

void ChessWidget::Test()
{
  //Testing Chess::Widget exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::thread t(
    []
    {
      {
        boost::shared_ptr< ::Widget > w(new ::Widget);
        w->SetGeometry(Rect(0,0,100,100));
      }
      //Nothing to test
    }
  );
  t.join();
}

} //~ namespace Chess


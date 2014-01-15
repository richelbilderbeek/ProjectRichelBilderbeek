#include "chesswidget.h"

#include <cassert>

#ifdef MXE_SUPPORTS_THREADS
#include <thread>
#endif

#include "chessboard.h"
#include "chesspiece.h"
#include "chessgame.h"
#include "chesssquare.h"
#include "chesssquarefactory.h"
#include "chesssquareselector.h"
#include "trace.h"

ribi::Chess::ChessWidget::ChessWidget(const Rect& geometry)
  : m_signal_graphic_changed{},
    m_selector{new SquareSelector}
{
  #ifndef NDEBUG
  ribi::Chess::ChessWidget::Test();
  #endif

  m_selector->m_signal_changed.connect(
    boost::bind(
      &ribi::Chess::ChessWidget::OnChanged,
      this
    )
  );

  this->SetGeometry(geometry);
}

ribi::Chess::ChessWidget::~ChessWidget() noexcept
{
  //All done automatically
}

void ribi::Chess::ChessWidget::ClickPixel(const int x,const int y)
{
  try
  {
    const boost::shared_ptr<Square> square {
      SquareFactory::Create(
        File(8 * x / this->GetGeometry().GetWidth()),
        Rank(8 * y / this->GetGeometry().GetHeight())
      )
    };
    assert(square);
    this->Click(square);
  }
  catch (std::exception& e)
  {
    //No problem
  }
}

const std::string ribi::Chess::ChessWidget::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::Chess::ChessWidget::GetVersionHistory()
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}

void ribi::Chess::ChessWidget::OnChanged() const
{
  m_signal_graphic_changed();
}

void ribi::Chess::ChessWidget::PressKey(const ChessWidget::Key key)
{
  switch (key)
  {
    case Key::up    : m_selector->MoveUp(); break;
    case Key::right : m_selector->MoveRight(); break;
    case Key::down  : m_selector->MoveDown(); break;
    case Key::left  : m_selector->MoveLeft(); break;
    case Key::select: this->Click(m_selector->GetCursor()); break;
    default: assert(!"Should not get here");
  }
}

void ribi::Chess::ChessWidget::Test() noexcept
{
  //Testing Chess::Widget exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
  #endif
    {
      {
        boost::shared_ptr<Widget > w(new Widget);
        w->SetGeometry(Rect(0,0,100,100));
      }
      //Nothing to test
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.join();
  #endif

}

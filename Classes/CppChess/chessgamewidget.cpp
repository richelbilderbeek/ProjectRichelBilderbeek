#include "chessgamewidget.h"

#include <cassert>
#include <string>
#ifdef MXE_SUPPORTS_THREADS
#include <thread>
#endif

#include "chessboard.h"
#include "chessgame.h"
#include "chesspiece.h"
#include "chesssquarefactory.h"
#include "chesssquareselector.h"
#include "chessmovefactory.h"
#include "geometry.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

//ribi::Chess::GameWidget::GameWidget()
//  : Chess::Widget(Rect(0,0,0,0))
//{
//  assert(!"Should not call this function");
//  throw std::logic_error("Must not call ribi::Chess::GameWidget::GameWidget()");
//}

ribi::Chess::GameWidget::GameWidget(boost::shared_ptr<Chess::Game> game, const Rect& geometry)
  : ChessWidget(geometry), m_game(game)
{
  #ifndef NDEBUG
  ribi::Chess::GameWidget::Test();
  #endif
}

void ribi::Chess::GameWidget::Click(const boost::shared_ptr<const Square> square)
{
  m_selector->Click(square,this); //BUG ?

  //Moves will only occur when there is both a cursor and a selected square
  if (!m_selector->GetSelected()) return;

  const boost::shared_ptr<const ribi::Chess::Square> from {
    m_selector->GetSelected()
  };
  const boost::shared_ptr<const ribi::Chess::Square> to {
    m_selector->GetCursor()
  };

  if (this->CanDoMove(from,to))
  {
    DoMove(from,to);
  }
}

bool ribi::Chess::GameWidget::CanDoMove(
  const boost::shared_ptr<const Square> from,
  const boost::shared_ptr<const Square> to) const noexcept
{
  //Construct all possible Moves
  assert(m_selector->GetSelected());
  const Chess::Board::PiecePtr piece = m_game->GetBoard()->GetPiece(from);
  assert(piece);
  boost::shared_ptr<const Move> move;
  for (int i=0; i!=32; ++i)
  {
    std::string s
      = boost::lexical_cast<std::string>(piece->GetNameChar())
      + from->ToStr()
      + ( (i / 1) % 2 ? " " : "x")
      + to->ToStr();
    switch ( (i / 2) % 4)
    {
      case 0: s += "e.p."; break;
      case 1: s += "+"; break;
      case 2: s += "#"; break;
      case 3: break;
      default: break;
    }
    const boost::shared_ptr<const Move> maybe_move {
      MoveFactory::Create(s)
    };
    if (m_game->CanDoMove(maybe_move)) move = maybe_move;
  }
  if (!move) return false;
  return true;
}

void ribi::Chess::GameWidget::DoMove(
  const boost::shared_ptr<const Square> from,
  const boost::shared_ptr<const Square> to)
{
  assert(CanDoMove(from,to));

  //Construct all possible Moves
  const Chess::Board::PiecePtr piece = m_game->GetBoard()->GetPiece(from);
  assert(piece);
  boost::shared_ptr<const Move> move;
  for (int i=0; i!=32; ++i)
  {
    std::string s
      = boost::lexical_cast<std::string>(piece->GetNameChar())
      + from->ToStr()
      + ( (i / 1) % 2 ? " " : "x")
      + to->ToStr();
    switch ( (i / 2) % 4)
    {
      case 0: s += "e.p."; break;
      case 1: s += "+"; break;
      case 2: s += "#"; break;
      case 3: break;
      default: break;
    }

    const boost::shared_ptr<const Move> maybe_move {
      MoveFactory::Create(s)
    };
    if (m_game->CanDoMove(maybe_move)) move = maybe_move;
    if (move) break;
  }
  assert(move);

  m_game->DoMove(move);

  m_signal_graphic_changed();

}

void ribi::Chess::GameWidget::Test() noexcept
{
  //Testing Chess::Piece exactly once
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
  #endif
    {
      {
        boost::shared_ptr<Chess::Game> game(new Chess::Game);
        boost::shared_ptr<Chess::ChessWidget> w(new GameWidget(game,Geometry().CreateRect(0,0,100,100)));
        w->ClickPixel(-1,-1);
        w->ClickPixel(1000,1000);
      }
      {
        boost::shared_ptr<Chess::Game> game(new Chess::Game);
        boost::shared_ptr<Chess::GameWidget> widget(new Chess::GameWidget(game,Geometry().CreateRect(0,0,100,100)));
        assert(widget->GetSelector()->GetCursor()->GetFile() == Chess::File("a"));
        assert(widget->GetSelector()->GetCursor()->GetRank() == Chess::Rank("1"));
        assert(!widget->GetSelector()->GetSelected());
        //Check clicking: cursor will always follow
        for (int x=0;x!=8;++x)
        {
          for (int y=0;y!=8;++y)
          {
            const boost::shared_ptr<Square> square {
              SquareFactory::Create(
                File(x),Rank(y)
              )
            };
            widget->Click(square);
            assert(*widget->GetSelector()->GetCursor() == *square);
          }
        }
        //Check selection: Board::Widget will select any Chess::Piece, Board::Game only those of the active player
        //Click on own piece, selecting it
        {
          const boost::shared_ptr<Square> square {
            SquareFactory::Create("b1")
          };
          widget->Click(square);
        }
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("b1"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory::Create("b1"));

        //Click on empty square, selected piece remains
        widget->Click(SquareFactory::Create("d4"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("d4"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory::Create("b1"));

        //Click on selected square, undoing selection
        widget->Click(SquareFactory::Create("b1"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("b1"));
        assert(!widget->GetSelector()->GetSelected());

        //Click on enemy square, Chess::Board will select it
        widget->Click(SquareFactory::Create("h8"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("g8"));
        assert(!widget->GetSelector()->GetSelected());

        //Playing e7-e5 must succeed for a Board, must fail for a Game
        assert( game->GetBoard()->GetPiece(SquareFactory::Create("e7")));
        assert(!game->GetBoard()->GetPiece(SquareFactory::Create("e5")));
        widget->Click(SquareFactory::Create("e7"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("e7"));
        assert(!widget->GetSelector()->GetSelected());

        widget->Click(SquareFactory::Create("e5"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("e5"));
        assert(!widget->GetSelector()->GetSelected());
        assert( game->GetBoard()->GetPiece(SquareFactory::Create("e7")));
        assert(!game->GetBoard()->GetPiece(SquareFactory::Create("e5")));

        //Playing e2-e4 must succeed for both Board and Game
        assert( game->GetBoard()->GetPiece(SquareFactory::Create("e2")));
        assert(!game->GetBoard()->GetPiece(SquareFactory::Create("e4")));
        widget->Click(SquareFactory::Create("e2"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("e2"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory::Create("e2"));

        widget->Click(SquareFactory::Create("e4"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory::Create("e4"));
        assert(!widget->GetSelector()->GetSelected());
        assert(!game->GetBoard()->GetPiece(SquareFactory::Create("e2")));
        assert( game->GetBoard()->GetPiece(SquareFactory::Create("e4")));
      }
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  #endif
}

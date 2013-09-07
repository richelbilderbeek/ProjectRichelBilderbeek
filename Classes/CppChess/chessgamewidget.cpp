#include "chessgamewidget.h"

#include <cassert>
#include <string>
#include <thread>

#include "chessboard.h"
#include "chessgame.h"
#include "chesspiece.h"
#include "chesssquareselector.h"

namespace Chess {

//GameWidget::GameWidget()
//  : Chess::Widget(Rect(0,0,0,0))
//{
//  assert(!"Should not call this function");
//  throw std::logic_error("Must not call GameWidget::GameWidget()");
//}

GameWidget::GameWidget(boost::shared_ptr<Chess::Game> game, const Rect& geometry)
  : ChessWidget(geometry), m_game(game)
{
  #ifndef NDEBUG
  GameWidget::Test();
  #endif
}

void GameWidget::Click(const Chess::Square& square)
{
  m_selector->Click(square,this);

  //Moves will only occur when there is both a cursor and a selected square
  if (!m_selector->GetSelected()) return;

  const Chess::Square from = *m_selector->GetSelected();
  const Chess::Square to = *m_selector->GetCursor();

  if (this->CanDoMove(from,to))
  {
    DoMove(from,to);
  }


}

bool GameWidget::CanDoMove(const Chess::Square& from, const Chess::Square& to) const
{
  //Construct all possible Moves
  assert(m_selector->GetSelected());
  const Chess::Board::PiecePtr piece = m_game->GetBoard()->GetPiece(from);
  assert(piece);
  boost::scoped_ptr<Move> move;
  for (int i=0; i!=32; ++i)
  {
    std::string s
      = std::to_string(piece->GetNameChar())
      + from.ToStr()
      + ( (i / 1) % 2 ? " " : "x")
      + to.ToStr();
    switch ( (i / 2) % 4)
    {
      case 0: s += "e.p."; break;
      case 1: s += "+"; break;
      case 2: s += "#"; break;
      case 3: break;
      default: break;
    }
    const Move maybe_move(s);
    if (m_game->CanDoMove(maybe_move)) move.reset(new Move(maybe_move));
  }
  if (!move) return false;
  return true;
}

void GameWidget::DoMove(const Chess::Square& from, const Chess::Square& to)
{
  assert(CanDoMove(from,to));

  //Construct all possible Moves
  const Chess::Board::PiecePtr piece = m_game->GetBoard()->GetPiece(from);
  assert(piece);
  boost::scoped_ptr<Move> move;
  for (int i=0; i!=32; ++i)
  {
    std::string s
      = std::to_string(piece->GetNameChar())
      + from.ToStr()
      + ( (i / 1) % 2 ? " " : "x")
      + to.ToStr();
    switch ( (i / 2) % 4)
    {
      case 0: s += "e.p."; break;
      case 1: s += "+"; break;
      case 2: s += "#"; break;
      case 3: break;
      default: break;
    }
    const Move maybe_move(s);
    if (m_game->CanDoMove(maybe_move)) move.reset(new Move(maybe_move));
    if (move) break;
  }
  assert(move);

  m_game->DoMove(*move);

  m_signal_graphic_changed();

}

void GameWidget::Test()
{
  //Testing Chess::Piece exactly once
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  std::thread t(
    []
    {
      {
        boost::shared_ptr<Chess::Game> game(new Chess::Game);
        boost::shared_ptr<Chess::ChessWidget> w(new GameWidget(game,Rect(0,0,100,100)));
        w->ClickPixel(-1,-1);
        w->ClickPixel(1000,1000);
      }
      {
        boost::shared_ptr<Chess::Game> game(new Chess::Game);
        boost::shared_ptr<Chess::GameWidget> widget(new Chess::GameWidget(game,Rect(0,0,100,100)));
        assert(widget->GetSelector()->GetCursor()->GetFile() == Chess::File("a"));
        assert(widget->GetSelector()->GetCursor()->GetRank() == Chess::Rank("1"));
        assert(!widget->GetSelector()->GetSelected());
        //Check clicking: cursor will always follow
        for (int x=0;x!=8;++x)
        {
          for (int y=0;y!=8;++y)
          {
            widget->Click(Square(x,y));
            assert(*widget->GetSelector()->GetCursor() == Chess::Square(x,y));
          }
        }
        //Check selection: Board::Widget will select any Chess::Piece, Board::Game only those of the active player
        //Click on own piece, selecting it
        widget->Click(Square("b1"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("b1"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("b1"));

        //Click on empty square, selected piece remains
        widget->Click(Square("d4"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("d4"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("b1"));

        //Click on selected square, undoing selection
        widget->Click(Square("b1"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("b1"));
        assert(!widget->GetSelector()->GetSelected());

        //Click on enemy square, Chess::Board will select it
        widget->Click(Square("h8"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("g8"));
        assert(!widget->GetSelector()->GetSelected());

        //Playing e7-e5 must succeed for a Board, must fail for a Game
        assert( game->GetBoard()->GetPiece(Square("e7")));
        assert(!game->GetBoard()->GetPiece(Square("e5")));
        widget->Click(Square("e7"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e7"));
        assert(!widget->GetSelector()->GetSelected());

        widget->Click(Square("e5"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e5"));
        assert(!widget->GetSelector()->GetSelected());
        assert( game->GetBoard()->GetPiece(Square("e7")));
        assert(!game->GetBoard()->GetPiece(Square("e5")));

        //Playing e2-e4 must succeed for both Board and Game
        assert( game->GetBoard()->GetPiece(Square("e2")));
        assert(!game->GetBoard()->GetPiece(Square("e4")));
        widget->Click(Square("e2"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e2"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("e2"));

        widget->Click(Square("e4"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e4"));
        assert(!widget->GetSelector()->GetSelected());
        assert(!game->GetBoard()->GetPiece(Square("e2")));
        assert( game->GetBoard()->GetPiece(Square("e4")));
      }
    }
  );
}

#include "chessboardwidget.h"

#include <cassert>
#include <exception>
#include <future>
#include <boost/lexical_cast.hpp>

#include "chessboard.h"
#include "chesspiece.h"
#include "chessplayer.h"
#include "chesssquareselector.h"
#include "chesswidget.h"
#include "rectangle.h"
#include "trace.h"
namespace Chess {

//BoardWidget::BoardWidget()
//  : Chess::Widget(Rect(0,0,0,0))
//{
//  assert(!"Should not call this function");
//  throw std::logic_error("Must not call BoardWidget::BoardWidget()");
//}

BoardWidget::BoardWidget(boost::shared_ptr<Chess::Board> board,const Rect& geometry)
  : Chess::ChessWidget(geometry),
    m_board(board)
{
  #ifndef NDEBUG
  BoardWidget::Test();
  #endif
}

bool BoardWidget::CanDoMove(const Chess::Square& from, const Chess::Square& to) const
{
  //A Widget can do a move if it is valid for one of the two players
  return this->GetBoard()->CanDoMove(move,Chess::Player::white)
    || this->GetBoard()->CanDoMove(move,Chess::Player::black);
}

bool BoardWidget::CanSelect(const Chess::Square& square) const
{
  //A BoardWidget can always select a Piece
  return
       this->GetBoard()->GetPiece(square);
    //&& this->GetBoard()->GetPiece(square)->GetColor()
    //  == this->GetActivePlayer();
}

void BoardWidget::Click(const Chess::Square& square)
{

  m_selector->Click(square,this->CanSelect(square));

  //Moves will only occur when there is both a cursor and a selected square
  if (!m_selector->GetSelected()) return;

  //Construct all possible Moves
  assert(m_selector->GetSelected());
  const Chess::Board::PiecePtr piece = m_board->GetPiece(*m_selector->GetSelected());
  TRACE(square.ToStr());
  #ifndef NDEBUG
  if (!piece)
  {
    TRACE(m_selector->GetSelected()->ToStr());
    TRACE(square);
    std::clog << *this->GetBoard() << '\n';
  }
  #endif
  assert(piece);
  boost::scoped_ptr<Move> move;
  for (int i=0; i!=32; ++i)
  {
    std::string s
      = boost::lexical_cast<std::string>(piece->GetNameChar())
      + m_selector->GetSelected()->ToStr()
      + ( (i / 1) % 2 ? " " : "x")
      + m_selector->GetCursor()->ToStr();
    switch ( (i / 2) % 4)
    {
      case 0: s += "e.p."; break;
      case 1: s += "+"; break;
      case 2: s += "#"; break;
      case 3: break;
      default: break;
    }
    try
    {
      const Move maybe_move(s);
      if (this->CanDoMove(maybe_move)) move.reset(new Move(maybe_move));
    }
    catch (std::exception& e)
    {
      //No problem
    }
  }
  if (!move) return;
  assert(m_board->CanDoMove(*move,m_player));
  m_board->DoMove(*move,m_player);

  m_signal_graphic_changed();
}

void BoardWidget::DoMove(const Chess::Square&, const Chess::Square&)
{

}

void BoardWidget::SetActivePlayer(const Player player)
{
  if (player != m_player)
  {
    m_player = player;
    m_selector.reset(new SquareSelector);
  }
}

void BoardWidget::Test()
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
        boost::shared_ptr<Chess::Board> board(new Chess::Board(Chess::Board::GetInitialSetup()));
        boost::shared_ptr<Chess::ChessWidget> w(new BoardWidget(board,Rect(0,0,100,100)));
        w->ClickPixel(-1,-1);
        w->ClickPixel(1000,1000);
      }
      {
        const Rect geometry(0,0,100,100);
        boost::shared_ptr<Chess::Board> board(new Chess::Board(Chess::Board::GetInitialSetup()));
        boost::shared_ptr<Chess::BoardWidget> widget(new Chess::BoardWidget(board,geometry));
        //assert(widget->GetSelector()->GetCursor() == Chess::SquareSelector::GetInitialSquare());
        assert(widget->GetSelector()->GetCursor()->GetFile() == Chess::SquareSelector::GetInitialSquare()->GetFile());
        assert(widget->GetSelector()->GetCursor()->GetRank() == Chess::SquareSelector::GetInitialSquare()->GetRank());
        //assert(widget->GetSelector()->GetCursor()->GetFile() == Chess::File("a"));
        //assert(widget->GetSelector()->GetCursor()->GetRank() == Chess::Rank("1"));
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

        //Click on empty square, selection is removed
        widget->Click(Square("d4"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("d4"));
        assert(!widget->GetSelector()->GetSelected());
        //assert(*widget->GetSelector()->GetSelected() == Chess::Square("b1"));

        //Click on own piece again, selecting it
        widget->Click(Square("b1"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("b1"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("b1"));

        //Click on selected square, undoing selection
        widget->Click(Square("b1"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("b1"));
        assert(!widget->GetSelector()->GetSelected());

        //Click on square with black piece. Note: a Widget can select every piece
        widget->Click(Square("h8"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("h8"));
        assert( widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("h8"));

        //Playing e7-e5 must succeed for a Board, must fail for a Game
        assert( board->GetPiece(Square("e7")));
        assert(!board->GetPiece(Square("e5")));
        widget->Click(Square("e7"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e7"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("e7"));

        widget->Click(Square("e5"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e5"));
        assert(!widget->GetSelector()->GetSelected());
        assert(!board->GetPiece(Square("e7")));
        assert( board->GetPiece(Square("e5")));

        //Playing e2-e4 must succeed for both Board and Game
        assert( board->GetPiece(Square("e2")));
        assert(!board->GetPiece(Square("e4")));
        widget->Click(Square("e2"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e2"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == Chess::Square("e2"));

        widget->Click(Square("e4"));
        assert(*widget->GetSelector()->GetCursor() == Chess::Square("e4"));
        assert(!widget->GetSelector()->GetSelected());
        assert(!board->GetPiece(Square("e2")));
        assert( board->GetPiece(Square("e4")));
      }

    }
  );
  t.join();
}

} //~namespace Chess


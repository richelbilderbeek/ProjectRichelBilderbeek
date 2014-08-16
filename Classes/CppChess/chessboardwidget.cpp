#include "chessboardwidget.h"

#include <cassert>
#include <exception>

#ifdef MXE_SUPPORTS_THREADS
#include <future>
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lexical_cast.hpp>

#include "chessboard.h"
#include "chessboardfactory.h"
#include "chesspiece.h"
#include "chessplayer.h"
#include "chesssquarefactory.h"
#include "chesssquareselector.h"
#include "chessmovefactory.h"
#include "chesswidget.h"
#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop

//ribi::Chess::BoardWidget::BoardWidget()
//  : Chess::Widget(Rect(0,0,0,0))
//{
//  assert(!"Should not call this function");
//  throw std::logic_error("Must not call ribi::Chess::BoardWidget::BoardWidget()");
//}

ribi::Chess::BoardWidget::BoardWidget(boost::shared_ptr<Chess::Board> board,const Rect& geometry)
  : Chess::ChessWidget(geometry),
    m_board(board),
    m_player(Player::white)
{
  #ifndef NDEBUG
  ribi::Chess::BoardWidget::Test();
  #endif
}

bool ribi::Chess::BoardWidget::CanDoMove(
  const boost::shared_ptr<const Chess::Square> from,
  const boost::shared_ptr<const Chess::Square> to) const noexcept
{
  const boost::shared_ptr<Move> move {
    MoveFactory::Create(from,to)
  };
  //A Widget can do a move if it is valid for one of the two players
  return this->GetBoard()->CanDoMove(move,Chess::Player::white)
    || this->GetBoard()->CanDoMove(move,Chess::Player::black);
}

bool ribi::Chess::BoardWidget::CanSelect(
  const boost::shared_ptr<const Chess::Square> square) const noexcept
{
  //A BoardWidget can always select a Piece
  return this->GetBoard()->GetPiece(square).get();
    //&& this->GetBoard()->GetPiece(square)->GetColor()
    //  == this->GetActivePlayer();
}

void ribi::Chess::BoardWidget::Click(const boost::shared_ptr<const Chess::Square> square) noexcept
{

  m_selector->Click(square,this->CanSelect(square));

  //Moves will only occur when there is both a cursor and a selected square
  if (!m_selector->GetSelected()) return;

  //Construct all possible Moves
  assert(m_selector->GetSelected());
  const Chess::Board::PiecePtr piece = m_board->GetPiece(m_selector->GetSelected());
  TRACE(square->ToStr());
  #ifndef NDEBUG
  if (!piece)
  {
    TRACE(m_selector->GetSelected()->ToStr());
    TRACE(square);
    std::clog << *this->GetBoard() << '\n';
  }
  #endif
  assert(piece);
  boost::shared_ptr<const Move> move;
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
      const boost::shared_ptr<const Move> maybe_move {
        MoveFactory::Create(s)
      };
      if (this->CanDoMove(maybe_move->From(),maybe_move->To())) move = maybe_move;
    }
    catch (std::exception& e)
    {
      //No problem
    }
  }
  if (!move) return;
  assert(m_board->CanDoMove(move,m_player));
  m_board->DoMove(move,m_player);

  m_signal_graphic_changed();
}


void ribi::Chess::BoardWidget::DoMove(
  const boost::shared_ptr<const Square>,
  const boost::shared_ptr<const Square>)
{
  assert(!"TODO");
}


void ribi::Chess::BoardWidget::SetActivePlayer(const Player player)
{
  if (player != m_player)
  {
    m_player = player;
    m_selector.reset(new SquareSelector);
  }
}

void ribi::Chess::BoardWidget::Test() noexcept
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

        const auto board(BoardFactory::Create());
        //boost::shared_ptr<Chess::BoardWidget> w
        //  = boost::make_shared<Chess::BoardWidget>(board,Geometry().CreateRect(0.0,0.0,100.0,100.0));
        auto w(boost::make_shared<Chess::BoardWidget>(board,Geometry().CreateRect(0.0,0.0,100.0,100.0)));
        w->ClickPixel(-1,-1);
        w->ClickPixel(1000,1000);
      }
      {
        const Rect geometry(Geometry().CreateRect(0,0,100,100));
        const auto board(BoardFactory::Create());
        //boost::shared_ptr<Chess::BoardWidget> widget
        //  = boost::make_shared<Chess::BoardWidget>(board,geometry);
        auto widget(boost::make_shared<Chess::BoardWidget>(board,geometry));

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
            const boost::shared_ptr<const Square> square {
              SquareFactory().Create(File(x),Rank(y))
            };
            widget->Click(square);
            assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create(File(x),Rank(y)));
          }
        }
        //Check selection: Board::Widget will select any Chess::Piece, Board::Game only those of the active player
        //Click on own piece, selecting it
        widget->Click(SquareFactory().Create("b1"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("b1"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory().Create("b1"));

        //Click on empty square, selection is removed
        widget->Click(SquareFactory().Create("d4"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("d4"));
        assert(!widget->GetSelector()->GetSelected());
        //assert(*widget->GetSelector()->GetSelected() == Chess::Square("b1"));

        //Click on own piece again, selecting it
        widget->Click(SquareFactory().Create("b1"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("b1"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory().Create("b1"));

        //Click on selected square, undoing selection
        widget->Click(SquareFactory().Create("b1"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("b1"));
        assert(!widget->GetSelector()->GetSelected());

        //Click on square with black piece. Note: a Widget can select every piece
        widget->Click(SquareFactory().Create("h8"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("h8"));
        assert( widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory().Create("h8"));

        //Playing e7-e5 must succeed for a Board, must fail for a Game
        assert( board->GetPiece(SquareFactory().Create("e7")));
        assert(!board->GetPiece(SquareFactory().Create("e5")));
        widget->Click(SquareFactory().Create("e7"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("e7"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory().Create("e7"));

        widget->Click(SquareFactory().Create("e5"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("e5"));
        assert(!widget->GetSelector()->GetSelected());
        assert(!board->GetPiece(SquareFactory().Create("e7")));
        assert( board->GetPiece(SquareFactory().Create("e5")));

        //Playing e2-e4 must succeed for both Board and Game
        assert( board->GetPiece(SquareFactory().Create("e2")));
        assert(!board->GetPiece(SquareFactory().Create("e4")));
        widget->Click(SquareFactory().Create("e2"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("e2"));
        assert(widget->GetSelector()->GetSelected());
        assert(*widget->GetSelector()->GetSelected() == *SquareFactory().Create("e2"));

        widget->Click(SquareFactory().Create("e4"));
        assert(*widget->GetSelector()->GetCursor() == *SquareFactory().Create("e4"));
        assert(!widget->GetSelector()->GetSelected());
        assert(!board->GetPiece(SquareFactory().Create("e2")));
        assert( board->GetPiece(SquareFactory().Create("e4")));
      }

    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.join();
  #endif
}

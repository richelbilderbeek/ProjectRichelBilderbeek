#include "chessboard.h"

#include <algorithm>
#include <cassert>

#ifdef SADC_USE_THREADS
#include <thread>
#endif

#include "chessboardfactory.h"
#include "chessbitboard.h"
#include "chessmoves.h"
#include "chessmovefactory.h"
#include "chesspiece.h"
#include "chesspiecefactory.h"
#include "chessplayer.h"
#include "chesssquarefactory.h"
#include "chessscore.h"
#include "trace.h"

namespace Chess {

void Board::Test()
{
  //Testing boost::shared_ptr<Chess::Board> exactly once
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Chess::Board");
      //Chess::BitBoard::Test();
      //Chess::Move::Test();
      {
        FTRACE("Test Board operator=");
        const boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        assert(b);
        boost::shared_ptr<Chess::Board> c(BoardFactory::DeepCopy(*b));
        assert(c);
        assert(IsEqual(*b,*c));
        c->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        assert(!IsEqual(*b,*c));
        const boost::shared_ptr<Chess::Board> d(c);
        assert( IsEqual(*c,*d));
        assert(!IsEqual(*b,*d));
      }
      {
        FTRACE("Test Board operator== with fresh boards");
        const boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        boost::shared_ptr<Chess::Board> c(BoardFactory::Create());
        assert(IsEqual(*b,*c));
        c->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        assert(!IsEqual(*b,*c));
        const boost::shared_ptr<Chess::Board> d(c);
        assert(IsEqual(*c,*d));
        assert(!IsEqual(*b,*d));
      }

      {
        FTRACE("Test Board operator== with fresh boards");
        const boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        boost::shared_ptr<Chess::Board> c(BoardFactory::Create());
        assert(IsEqual(*b,*c));
        c->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        assert(!IsEqual(*b,*c));
        const boost::shared_ptr<Chess::Board> d(c);
        assert(IsEqual(*c,*d));
        assert(!IsEqual(*b,*d));
      }

      {
        FTRACE("Test GetMoves from initial position squares");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        assert(!b->CanDoMove(*MoveFactory::Create("Ra8 a6"),Player::black));
        assert(!b->CanDoMove(*MoveFactory::Create("Ra8 a6"),Player::white));
        assert(b->GetMoves(*SquareFactory::Create("a1")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("b1")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("c1")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("d1")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("e1")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("f1")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("g1")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("h1")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("a2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("b2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("c2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("d2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("e2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("f2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("g2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("h2")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("a8")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("b8")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("c8")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("d8")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("e8")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("f8")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("g8")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("h8")).size() == 0);
        assert(b->GetMoves(*SquareFactory::Create("a7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("b7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("c7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("d7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("e7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("f7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("g7")).size() == 2);
        assert(b->GetMoves(*SquareFactory::Create("h7")).size() == 2);
      }
      {
        FTRACE("Test GetVisibleSquares in the initial position");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        const BitBoard c = b->GetVisibleSquares(Player::white);

        assert(c.Get(*SquareFactory::Create("a1"))); assert(c.Get(*SquareFactory::Create("a2"))); assert(c.Get(*SquareFactory::Create("a3"))); assert(c.Get(*SquareFactory::Create("a4")));
        assert(c.Get(*SquareFactory::Create("b1"))); assert(c.Get(*SquareFactory::Create("b2"))); assert(c.Get(*SquareFactory::Create("b3"))); assert(c.Get(*SquareFactory::Create("b4")));
        assert(c.Get(*SquareFactory::Create("c1"))); assert(c.Get(*SquareFactory::Create("c2"))); assert(c.Get(*SquareFactory::Create("c3"))); assert(c.Get(*SquareFactory::Create("c4")));
        assert(c.Get(*SquareFactory::Create("d1"))); assert(c.Get(*SquareFactory::Create("d2"))); assert(c.Get(*SquareFactory::Create("d3"))); assert(c.Get(*SquareFactory::Create("d4")));
        assert(c.Get(*SquareFactory::Create("e1"))); assert(c.Get(*SquareFactory::Create("e2"))); assert(c.Get(*SquareFactory::Create("e3"))); assert(c.Get(*SquareFactory::Create("e4")));
        assert(c.Get(*SquareFactory::Create("f1"))); assert(c.Get(*SquareFactory::Create("f2"))); assert(c.Get(*SquareFactory::Create("f3"))); assert(c.Get(*SquareFactory::Create("f4")));
        assert(c.Get(*SquareFactory::Create("g1"))); assert(c.Get(*SquareFactory::Create("g2"))); assert(c.Get(*SquareFactory::Create("g3"))); assert(c.Get(*SquareFactory::Create("g4")));
        assert(c.Get(*SquareFactory::Create("h1"))); assert(c.Get(*SquareFactory::Create("h2"))); assert(c.Get(*SquareFactory::Create("h3"))); assert(c.Get(*SquareFactory::Create("h4")));
        assert(!c.Get(*SquareFactory::Create("a5"))); assert(!c.Get(*SquareFactory::Create("a6"))); assert(!c.Get(*SquareFactory::Create("a7"))); assert(!c.Get(*SquareFactory::Create("a8")));
        assert(!c.Get(*SquareFactory::Create("b5"))); assert(!c.Get(*SquareFactory::Create("b6"))); assert(!c.Get(*SquareFactory::Create("b7"))); assert(!c.Get(*SquareFactory::Create("b8")));
        assert(!c.Get(*SquareFactory::Create("c5"))); assert(!c.Get(*SquareFactory::Create("c6"))); assert(!c.Get(*SquareFactory::Create("c7"))); assert(!c.Get(*SquareFactory::Create("c8")));
        assert(!c.Get(*SquareFactory::Create("d5"))); assert(!c.Get(*SquareFactory::Create("d6"))); assert(!c.Get(*SquareFactory::Create("d7"))); assert(!c.Get(*SquareFactory::Create("d8")));
        assert(!c.Get(*SquareFactory::Create("e5"))); assert(!c.Get(*SquareFactory::Create("e6"))); assert(!c.Get(*SquareFactory::Create("e7"))); assert(!c.Get(*SquareFactory::Create("e8")));
        assert(!c.Get(*SquareFactory::Create("f5"))); assert(!c.Get(*SquareFactory::Create("f6"))); assert(!c.Get(*SquareFactory::Create("f7"))); assert(!c.Get(*SquareFactory::Create("f8")));
        assert(!c.Get(*SquareFactory::Create("g5"))); assert(!c.Get(*SquareFactory::Create("g6"))); assert(!c.Get(*SquareFactory::Create("g7"))); assert(!c.Get(*SquareFactory::Create("g8")));
        assert(!c.Get(*SquareFactory::Create("h5"))); assert(!c.Get(*SquareFactory::Create("h6"))); assert(!c.Get(*SquareFactory::Create("h7"))); assert(!c.Get(*SquareFactory::Create("h8")));
        b->DoMove(*MoveFactory::Create("e2 e3"),Player::white);
        const BitBoard d = b->GetVisibleSquares(Player::black);
        assert(d.Get(*SquareFactory::Create("a5"))); assert(d.Get(*SquareFactory::Create("a6"))); assert(d.Get(*SquareFactory::Create("a7"))); assert(d.Get(*SquareFactory::Create("a8")));
        assert(d.Get(*SquareFactory::Create("b5"))); assert(d.Get(*SquareFactory::Create("b6"))); assert(d.Get(*SquareFactory::Create("b7"))); assert(d.Get(*SquareFactory::Create("b8")));
        assert(d.Get(*SquareFactory::Create("c5"))); assert(d.Get(*SquareFactory::Create("c6"))); assert(d.Get(*SquareFactory::Create("c7"))); assert(d.Get(*SquareFactory::Create("c8")));
        assert(d.Get(*SquareFactory::Create("d5"))); assert(d.Get(*SquareFactory::Create("d6"))); assert(d.Get(*SquareFactory::Create("d7"))); assert(d.Get(*SquareFactory::Create("d8")));
        assert(d.Get(*SquareFactory::Create("e5"))); assert(d.Get(*SquareFactory::Create("e6"))); assert(d.Get(*SquareFactory::Create("e7"))); assert(d.Get(*SquareFactory::Create("e8")));
        assert(d.Get(*SquareFactory::Create("f5"))); assert(d.Get(*SquareFactory::Create("f6"))); assert(d.Get(*SquareFactory::Create("f7"))); assert(d.Get(*SquareFactory::Create("f8")));
        assert(d.Get(*SquareFactory::Create("g5"))); assert(d.Get(*SquareFactory::Create("g6"))); assert(d.Get(*SquareFactory::Create("g7"))); assert(d.Get(*SquareFactory::Create("g8")));
        assert(d.Get(*SquareFactory::Create("h5"))); assert(d.Get(*SquareFactory::Create("h6"))); assert(d.Get(*SquareFactory::Create("h7"))); assert(d.Get(*SquareFactory::Create("h8")));
        assert(!d.Get(*SquareFactory::Create("a1"))); assert(!d.Get(*SquareFactory::Create("a2"))); assert(!d.Get(*SquareFactory::Create("a3"))); assert(!d.Get(*SquareFactory::Create("a4")));
        assert(!d.Get(*SquareFactory::Create("b1"))); assert(!d.Get(*SquareFactory::Create("b2"))); assert(!d.Get(*SquareFactory::Create("b3"))); assert(!d.Get(*SquareFactory::Create("b4")));
        assert(!d.Get(*SquareFactory::Create("c1"))); assert(!d.Get(*SquareFactory::Create("c2"))); assert(!d.Get(*SquareFactory::Create("c3"))); assert(!d.Get(*SquareFactory::Create("c4")));
        assert(!d.Get(*SquareFactory::Create("d1"))); assert(!d.Get(*SquareFactory::Create("d2"))); assert(!d.Get(*SquareFactory::Create("d3"))); assert(!d.Get(*SquareFactory::Create("d4")));
        assert(!d.Get(*SquareFactory::Create("e1"))); assert(!d.Get(*SquareFactory::Create("e2"))); assert(!d.Get(*SquareFactory::Create("e3"))); assert(!d.Get(*SquareFactory::Create("e4")));
        assert(!d.Get(*SquareFactory::Create("f1"))); assert(!d.Get(*SquareFactory::Create("f2"))); assert(!d.Get(*SquareFactory::Create("f3"))); assert(!d.Get(*SquareFactory::Create("f4")));
        assert(!d.Get(*SquareFactory::Create("g1"))); assert(!d.Get(*SquareFactory::Create("g2"))); assert(!d.Get(*SquareFactory::Create("g3"))); assert(!d.Get(*SquareFactory::Create("g4")));
        assert(!d.Get(*SquareFactory::Create("h1"))); assert(!d.Get(*SquareFactory::Create("h2"))); assert(!d.Get(*SquareFactory::Create("h3"))); assert(!d.Get(*SquareFactory::Create("h4")));
      }

      {
        FTRACE("Test valid moves in the initial position");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        {
          const std::vector<std::string> v
          =
          {
            "a2 a3", "a2 a4", "b2 b3", "b2 b4",
            "c2 c3", "c2 c4", "d2 d3", "d2 d4",
            "e2 e3", "e2 e4", "f2 f3", "f2 f4",
            "g2 g3", "g2 g4", "h2 h3", "h2 h4",
            "Nb1 a3", "Nb1 c3", "Ng1 f3", "Ng1 h3",
            "1-0", "0-1", "1/2-1/2"
          };
          std::for_each(v.begin(),v.end(),
            [b](const std::string& s)
            {
              if (!b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
              assert(b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white));
            }
          );
        }
        assert(b->GetMoves(*Chess::SquareFactory::Create("a1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b1")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c1")).size() == 0);
        assert(!b->CanDoMove(*MoveFactory::Create("Qd1 d8"),Player::white));
        assert(!b->CanDoMove(*MoveFactory::Create("Qd1 d7"),Player::white));
        assert(b->GetMoves(*Chess::SquareFactory::Create("d1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g1")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("a2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("a8")).size() == 0);
        /*
        assert(b->GetMoves(*Chess::SquareFactory::Create("b8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("a7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g7")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h7")).size() == 0);
        */
        assert(b->GetMoves(Player::white).size() == 20);

        assert(!b->IsCheck(Player::white));
        assert(!b->IsCheckmate(Player::white));
      }

      {
        FTRACE("Test moves in the initial position (short notation)");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        {
          const std::vector<std::string> v
          =
          {
            "a3", "a4", "b3", "b4",
            "c3", "c4", "d3", "d4",
            "e3", "e4", "f3", "f4",
            "g3", "g4", "h3", "h4",
            "Na3", "Nc3", "Nf3", "Nh3"
          };
          std::for_each(v.begin(),v.end(),
            [b](const std::string& s)
            {
              if (!b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
              assert(b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white));
            }
          );
        }
      }

      {
        FTRACE("Test a Pawn on the board at e2");
        const Board::Pieces v =
        {
          PieceFactory::CreatePawn(Color::white,*Chess::SquareFactory::Create("e2")),
          PieceFactory::CreatePawn(Color::white,*Chess::SquareFactory::Create("d3")),
          PieceFactory::CreatePawn(Color::black,*Chess::SquareFactory::Create("f3"))
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert( b->CanDoMove(*MoveFactory::Create("e2 e3"),Player::white));
        assert( b->CanDoMove(*MoveFactory::Create("e2 e4"),Player::white));
        assert( b->CanDoMove(*MoveFactory::Create("e2xf3"),Player::white));
        assert(!b->CanDoMove(*MoveFactory::Create("e2xd3"),Player::white));
      }

      {
        FTRACE("Test a Pawn on the board at e2, blocked by an opponent");
        const Board::Pieces v =
        {
          PieceFactory::CreatePawn(Color::white,Chess::SquareFactory::Create("e2")),
          PieceFactory::CreatePawn(Color::black,Chess::SquareFactory::Create("e3"))
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert(!b->CanDoMove(*MoveFactory::Create("e2 e3"),Player::white));
        assert(!b->CanDoMove(*MoveFactory::Create("e2 e4"),Player::white));
      }

      {
        FTRACE("Test a Pawn on the board at h4, blocked by an opponent");
        const Board::Pieces v =
        {
          PieceFactory::CreatePawn(Color::white,Chess::SquareFactory::Create("h4")),
          PieceFactory::CreatePawn(Color::black,Chess::SquareFactory::Create("h5"))
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert(!b->CanDoMove(*MoveFactory::Create("h4 h5"),Player::white));
      }

      {
        FTRACE("Test a Knight on the board at d4");
        const Board::Pieces v =
        {
          PieceFactory::CreateKnight(Color::white,Chess::SquareFactory::Create("d4")),
          PieceFactory::CreatePawn(Color::white,Chess::SquareFactory::Create("c6")),
          PieceFactory::CreatePawn(Color::black,Chess::SquareFactory::Create("e6"))
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert( b->CanDoMove(*MoveFactory::Create("Nd4 b5"),Player::white));
        assert( b->CanDoMove(*MoveFactory::Create("Nd4 f5"),Player::white));
        assert(!b->CanDoMove(*MoveFactory::Create("Nd4xc6"),Player::white));
        assert( b->CanDoMove(*MoveFactory::Create("Nd4xe6"),Player::white));
      }


      {
        FTRACE("Test valid moves for black after 1. e2 e4");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        b->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        {
          const std::vector<std::string> v
          =
          {
            "a7 a6", "a7 a5", "b7 b6", "b7 b5",
            "c7 c6", "c7 c5", "d7 d6", "d7 d5",
            "e7 e6", "e7 e5", "f7 f6", "f7 f5",
            "g7 g6", "g7 g5", "h7 h6", "h7 h5",
            "Nb8 a6", "Nb8 c6", "Ng8 f6", "Ng8 h6",
            "1-0", "0-1", "1/2-1/2"
          };
          std::for_each(v.begin(),v.end(),
            [b](const std::string& s)
            {
              if (!b->CanDoMove(*Chess::MoveFactory::Create(s),Player::black)) { TRACE(s); }
              assert(b->CanDoMove(*Chess::MoveFactory::Create(s),Player::black));
            }
          );
        }
        assert(b->GetMoves(*Chess::SquareFactory::Create("a8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b8")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g8")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h8")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("a7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g7")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h7")).size() == 2);
        assert(b->GetMoves(Player::black).size() == 20);
        assert(!b->IsCheck(Player::black));
        assert(!b->IsCheckmate(Player::black));
      }

      {
        FTRACE("Test valid moves for white after 1. e2 e4 e7 e5");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        b->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        b->DoMove(*MoveFactory::Create("e7 e5"),Player::black);
        {
          const std::vector<std::string> v
          =
          {
            "a2 a3", "a2 a4", "b2 b3", "b2 b4",
            "c2 c3", "c2 c4", "d2 d3", "d2 d4",
            "Ke1 e2","f2 f3", "f2 f4",
            "g2 g3", "g2 g4", "h2 h3", "h2 h4",
            "Nb1 a3", "Nb1 c3", "Ng1 f3", "Ng1 h3",
            "Bf1 e2", "Bf1 d3", "Bf1 c4", "Bf1 b5", "Bf1 a6",
            "Qd1 e2", "Qd1 f3", "Qd1 g4", "Qd1 h5",
            "1-0", "0-1", "1/2-1/2"
          };
          std::for_each(v.begin(),v.end(),
            [b](const std::string& s)
            {
              if (!b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
              assert(b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white));
            }
          );
        }
        assert(b->GetMoves(*Chess::SquareFactory::Create("a1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b1")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d1")).size() == 4);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e1")).size() == 1);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f1")).size() == 5);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g1")).size() == 3);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h1")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("a2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("b2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("c2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("d2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("e4")).size() == 0);
        assert(b->GetMoves(*Chess::SquareFactory::Create("f2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("g2")).size() == 2);
        assert(b->GetMoves(*Chess::SquareFactory::Create("h2")).size() == 2);
        assert(b->GetMoves(Player::white).size() == 29);
        assert(!b->IsCheck(Player::white));
        assert(!b->IsCheckmate(Player::white));
      }

      {
        FTRACE("Test Board copy constructor");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        assert( b->GetPiece(*SquareFactory::Create("e2")));
        assert(!b->GetPiece(*SquareFactory::Create("e4")));
        b->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        const boost::shared_ptr<Chess::Board> c(b);
        assert(IsEqual(*b,*c));
        assert(!b->GetPiece(*SquareFactory::Create("e2")));
        assert( b->GetPiece(*SquareFactory::Create("e4")));
        assert(!c->GetPiece(*SquareFactory::Create("e2")));
        assert( c->GetPiece(*SquareFactory::Create("e4")));
        b->DoMove(*MoveFactory::Create("e7 e5"),Player::black);
        assert(!IsEqual(*b,*c));
        assert( b->GetPiece(*SquareFactory::Create("e5")));
        assert(!b->GetPiece(*SquareFactory::Create("e7")));
        assert(!c->GetPiece(*SquareFactory::Create("e5")));
        assert( c->GetPiece(*SquareFactory::Create("e7")));
      }
      {
        FTRACE("Test EmptyBetween on single piece");
        const Pieces pieces
          =
          {
            boost::shared_ptr<Piece>(new PieceKing(Color::white,Chess::SquareFactory::Create("b2"))))
          };
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create(pieces));
        assert( b->EmptyBetween(Square("a1"),Square("c1")));
        assert( b->EmptyBetween(Square("c1"),Square("a1")));
        assert( b->EmptyBetween(Square("a1"),Square("a3")));
        assert( b->EmptyBetween(Square("a3"),Square("a1")));
        assert(!b->EmptyBetween(Square("a1"),Square("c3")));
        assert(!b->EmptyBetween(Square("c3"),Square("a1")));
        assert(!b->EmptyBetween(Square("b1"),Square("b3")));
        assert(!b->EmptyBetween(Square("b3"),Square("b1")));
        assert(!b->EmptyBetween(Square("a2"),Square("c2")));
        assert(!b->EmptyBetween(Square("c2"),Square("a2")));
        assert( b->EmptyBetween(Square("d1"),Square("d8")));
        assert( b->EmptyBetween(Square("d8"),Square("d1")));
        assert( b->EmptyBetween(Square("a4"),Square("h4")));
        assert( b->EmptyBetween(Square("h4"),Square("a4")));
        assert( b->EmptyBetween(Square("b5"),Square("f1")));
        assert( b->EmptyBetween(Square("f1"),Square("b5")));
      }

      {
        FTRACE("Test EmptyBetween after 3rd move of white in Kasparov against the World game");
        const Pieces pieces
          =
          {
            PiecePtr(new PieceRook(Color::white,Chess::SquareFactory::Create("a1")))),
            PiecePtr(new PieceKnight(Color::white,Chess::SquareFactory::Create("c3")))),
            PiecePtr(new PieceBishop(Color::white,Chess::SquareFactory::Create("c1")))),
            PiecePtr(new PieceQueen(Color::white,Chess::SquareFactory::Create("d1")))),
            PiecePtr(new PieceKing(Color::white,Chess::SquareFactory::Create("e1")))),
            PiecePtr(new PieceBishop(Color::white,Chess::SquareFactory::Create("b5")))),
            PiecePtr(new PieceKnight(Color::white,Chess::SquareFactory::Create("g1")))),
            PiecePtr(new PieceRook(Color::white,Chess::SquareFactory::Create("h1")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("a2")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("b2")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("c2")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("d2")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("e4")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("f2")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("g2")))),
            PieceFactory::CreatePawn((Color::white,Chess::SquareFactory::Create("h2")))),
            PiecePtr(new PieceRook(Color::black,Chess::SquareFactory::Create("a8")))),
            PiecePtr(new PieceKnight(Color::black,Chess::SquareFactory::Create("b8")))),
            PiecePtr(new PieceBishop(Color::black,Chess::SquareFactory::Create("c8")))),
            PiecePtr(new PieceQueen(Color::black,Chess::SquareFactory::Create("d8")))),
            PiecePtr(new PieceKing(Color::black,Chess::SquareFactory::Create("e8")))),
            PiecePtr(new PieceBishop(Color::black,Chess::SquareFactory::Create("f8")))),
            PiecePtr(new PieceKnight(Color::black,Chess::SquareFactory::Create("g8")))),
            PiecePtr(new PieceRook(Color::black,Chess::SquareFactory::Create("h8")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("a7")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("b7")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("c5")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("d6")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("e7")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("f7")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("g7")))),
            PieceFactory::CreatePawn((Color::black,Chess::SquareFactory::Create("h7"))))
          };
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create(pieces));
        assert( b->EmptyBetween(Square("b5"),Square("e8")));
        assert( b->EmptyBetween(Square("e8"),Square("b5")));
        assert( b->EmptyBetween(Square("b5"),Square("f1")));
        assert( b->EmptyBetween(Square("f1"),Square("b5")));
      }

      {
        FTRACE("Test IsCheck from setup 1");
        const Pieces pieces
          =
          {
            boost::shared_ptr<Piece>(new PieceKing(Color::white,Chess::SquareFactory::Create("a1")))),
            boost::shared_ptr<Piece>(new PieceKing(Color::black,Chess::SquareFactory::Create("h8")))),
            boost::shared_ptr<Piece>(new PieceRook(Color::white,Chess::SquareFactory::Create("a8")))),
            boost::shared_ptr<Piece>(new PieceRook(Color::black,Chess::SquareFactory::Create("h1"))))
          };
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create(pieces));
        assert(b->IsCheck(Player::white));
        assert(b->IsCheck(Player::black));
      }
      {
        FTRACE("Test IsCheck by playing");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        b->DoMove(*MoveFactory::Create("e2 e4"),Player::white);
        b->DoMove(*MoveFactory::Create("d7 d6"),Player::black);
        FTRACE("Test that the move ending is check can be done");
        assert(b->CanDoMove(*MoveFactory::Create("Bf1 b5+"),Player::white));
        FTRACE("Do the move ending is check");
        b->DoMove(*MoveFactory::Create("Bf1 b5+"),Player::white);
        FTRACE("Test that the board detects check");
        assert(b->IsCheck(Player::black));
      }


      {
        FTRACE("Test invalid moves in the initial position");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        {
          const std::vector<std::string> v
          =
          {
            "a7 a6", "a7 a5", "b7 b5", "b7 b5",
            "c7 c6", "c7 c5", "d7 d5", "d7 d5",
            "e7 e6", "e7 e5", "f7 f5", "f7 f5",
            "g7 g6", "g7 g5", "h7 h5", "h7 h5",
            "Nb8 a6", "Nb8 c6", "Ng8 f6", "Ng8 h6",
            "a2xa3", "a2 a4+", "b2 b3#", "b2xb4",
            "c2 c3+", "c2 c4#", "d2 d3e.p.", "d2xd4e.p.",
            "0-0", "0-0-0", "O-O", "O-O-O",
            "0-0+", "0-0-0+", "O-O+", "O-O-O+",
            "0-0#", "0-0-0#", "O-O#", "O-O-O#",
          };
          std::for_each(v.begin(),v.end(),
            [b](const std::string& s)
            {
              try
              {
                Move move(s);
                if (b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
                assert(!b->CanDoMove(*Chess::MoveFactory::Create(s),Player::white));
              }
              catch (std::exception& e)
              {
                //OK
              }
            }
          );
        }
      }

      /*
      {
        FTRACE("Test Fools mate");
        boost::shared_ptr<Chess::Board> b;
        {
          const std::vector<std::string> v = Moves::GetGameFoolsMate();
          std::for_each(v.begin(),v.end(),
            [b](const std::string& s)
            {
              if (!b->CanDoMove(s) { TRACE(s); }
              assert(b->CanDoMove(s));
              b->DoMove(s);
            }
          );
          assert(b.Score());
          assert(b.Score().IsWhiteWinner());
        }
      }
      */

      {
        FTRACE("Test Shephards mate");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        Player player = Player::white;
        {
          const std::vector<std::string> v = Moves::GetGameShephardsMate();
          std::for_each(v.begin(),v.end(),
            [&b,&player](const std::string& s)
            {
              if (!b->CanDoMove(*Chess::MoveFactory::Create(s),player)) { TRACE(s); }
              assert(b->CanDoMove(*Chess::MoveFactory::Create(s),player));
              b->DoMove(Chess::Move(s),player);
              player = (player == Player::white ? Player::black : Player::white);
            }
          );
        }
      }

      {
        FTRACE("Test Kasparov Versus The World match");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        Player player = Player::white;
        {
          const std::vector<std::string> v = Moves::GetGameKasparovVersusTheWorld();
          const std::size_t sz = v.size();
          for (std::size_t i = 0; i!=sz; ++i)
          {
            const std::string s = v[i];
            TRACE(b);
            if (!b->CanDoMove(*Chess::MoveFactory::Create(s),player)) { TRACE(s);  }
            assert(b->CanDoMove(*Chess::MoveFactory::Create(s),player));
            b->DoMove(Chess::Move(s),player);
            player = (player == Player::white ? Player::black : Player::white);
          }
        }
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

} //~namespace Chess


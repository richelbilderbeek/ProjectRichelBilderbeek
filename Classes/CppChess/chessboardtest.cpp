#include "chessboard.h"

#include <algorithm>
#include <cassert>

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

#ifndef NDEBUG
void ribi::Chess::Board::Test()
{
  //Testing boost::shared_ptr<Chess::Board> exactly once
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
      FTRACE("Test Chess::Board");
      //Chess::Bitribi::Chess::Board::Test();
      //Chess::Move::Test();
      {
        FTRACE("Test Board operator=");
        const boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        assert(b);
        boost::shared_ptr<Chess::Board> c(BoardFactory::DeepCopy(*b));
        assert(c);
        assert(*b == *c);
        c->DoMove(MoveFactory::Create("e2 e4"),Player::white);
        assert(*b != *c);
        const boost::shared_ptr<Chess::Board> d(c);
        assert(*c == *d);
        assert(*b != *d);
      }
      {
        FTRACE("Test Board operator== with fresh boards");
        const boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        boost::shared_ptr<Chess::Board> c(BoardFactory::Create());
        assert((*b == *c));
        c->DoMove(MoveFactory::Create("e2 e4"),Player::white);
        assert((*b != *c));
        const boost::shared_ptr<Chess::Board> d(c);
        assert((*c == *d));
        assert((*b != *d));
      }

      {
        FTRACE("Test Board operator== with fresh boards");
        const boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        boost::shared_ptr<Chess::Board> c(BoardFactory::Create());
        assert((*b == *c));
        c->DoMove(MoveFactory::Create("e2 e4"),Player::white);
        assert((*b != *c));
        const boost::shared_ptr<Chess::Board> d(c);
        assert((*c == *d));
        assert((*b != *d));
      }

      {
        FTRACE("Test GetMoves from initial position squares");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        assert(!b->CanDoMove(MoveFactory::Create("Ra8 a6"),Player::black));
        assert(!b->CanDoMove(MoveFactory::Create("Ra8 a6"),Player::white));
        assert(b->GetMoves(SquareFactory::Create("a1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("b1")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("d1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("e1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("g1")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("a2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("b2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("d2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("e2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("f2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("g2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("a8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("b8")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("d8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("e8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("g8")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("a7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("b7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("d7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("e7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("f7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("g7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h7")).size() == 2);
      }
      {
        FTRACE("Test GetVisibleSquares in the initial position");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        const BitBoard c = b->GetVisibleSquares(Player::white);

        assert(c.Get(SquareFactory::Create("a1"))); assert(c.Get(SquareFactory::Create("a2"))); assert(c.Get(SquareFactory::Create("a3"))); assert(c.Get(SquareFactory::Create("a4")));
        assert(c.Get(SquareFactory::Create("b1"))); assert(c.Get(SquareFactory::Create("b2"))); assert(c.Get(SquareFactory::Create("b3"))); assert(c.Get(SquareFactory::Create("b4")));
        assert(c.Get(SquareFactory::Create("c1"))); assert(c.Get(SquareFactory::Create("c2"))); assert(c.Get(SquareFactory::Create("c3"))); assert(c.Get(SquareFactory::Create("c4")));
        assert(c.Get(SquareFactory::Create("d1"))); assert(c.Get(SquareFactory::Create("d2"))); assert(c.Get(SquareFactory::Create("d3"))); assert(c.Get(SquareFactory::Create("d4")));
        assert(c.Get(SquareFactory::Create("e1"))); assert(c.Get(SquareFactory::Create("e2"))); assert(c.Get(SquareFactory::Create("e3"))); assert(c.Get(SquareFactory::Create("e4")));
        assert(c.Get(SquareFactory::Create("f1"))); assert(c.Get(SquareFactory::Create("f2"))); assert(c.Get(SquareFactory::Create("f3"))); assert(c.Get(SquareFactory::Create("f4")));
        assert(c.Get(SquareFactory::Create("g1"))); assert(c.Get(SquareFactory::Create("g2"))); assert(c.Get(SquareFactory::Create("g3"))); assert(c.Get(SquareFactory::Create("g4")));
        assert(c.Get(SquareFactory::Create("h1"))); assert(c.Get(SquareFactory::Create("h2"))); assert(c.Get(SquareFactory::Create("h3"))); assert(c.Get(SquareFactory::Create("h4")));
        assert(!c.Get(SquareFactory::Create("a5"))); assert(!c.Get(SquareFactory::Create("a6"))); assert(!c.Get(SquareFactory::Create("a7"))); assert(!c.Get(SquareFactory::Create("a8")));
        assert(!c.Get(SquareFactory::Create("b5"))); assert(!c.Get(SquareFactory::Create("b6"))); assert(!c.Get(SquareFactory::Create("b7"))); assert(!c.Get(SquareFactory::Create("b8")));
        assert(!c.Get(SquareFactory::Create("c5"))); assert(!c.Get(SquareFactory::Create("c6"))); assert(!c.Get(SquareFactory::Create("c7"))); assert(!c.Get(SquareFactory::Create("c8")));
        assert(!c.Get(SquareFactory::Create("d5"))); assert(!c.Get(SquareFactory::Create("d6"))); assert(!c.Get(SquareFactory::Create("d7"))); assert(!c.Get(SquareFactory::Create("d8")));
        assert(!c.Get(SquareFactory::Create("e5"))); assert(!c.Get(SquareFactory::Create("e6"))); assert(!c.Get(SquareFactory::Create("e7"))); assert(!c.Get(SquareFactory::Create("e8")));
        assert(!c.Get(SquareFactory::Create("f5"))); assert(!c.Get(SquareFactory::Create("f6"))); assert(!c.Get(SquareFactory::Create("f7"))); assert(!c.Get(SquareFactory::Create("f8")));
        assert(!c.Get(SquareFactory::Create("g5"))); assert(!c.Get(SquareFactory::Create("g6"))); assert(!c.Get(SquareFactory::Create("g7"))); assert(!c.Get(SquareFactory::Create("g8")));
        assert(!c.Get(SquareFactory::Create("h5"))); assert(!c.Get(SquareFactory::Create("h6"))); assert(!c.Get(SquareFactory::Create("h7"))); assert(!c.Get(SquareFactory::Create("h8")));
        b->DoMove(MoveFactory::Create("e2 e3"),Player::white);
        const BitBoard d = b->GetVisibleSquares(Player::black);
        assert(d.Get(SquareFactory::Create("a5"))); assert(d.Get(SquareFactory::Create("a6"))); assert(d.Get(SquareFactory::Create("a7"))); assert(d.Get(SquareFactory::Create("a8")));
        assert(d.Get(SquareFactory::Create("b5"))); assert(d.Get(SquareFactory::Create("b6"))); assert(d.Get(SquareFactory::Create("b7"))); assert(d.Get(SquareFactory::Create("b8")));
        assert(d.Get(SquareFactory::Create("c5"))); assert(d.Get(SquareFactory::Create("c6"))); assert(d.Get(SquareFactory::Create("c7"))); assert(d.Get(SquareFactory::Create("c8")));
        assert(d.Get(SquareFactory::Create("d5"))); assert(d.Get(SquareFactory::Create("d6"))); assert(d.Get(SquareFactory::Create("d7"))); assert(d.Get(SquareFactory::Create("d8")));
        assert(d.Get(SquareFactory::Create("e5"))); assert(d.Get(SquareFactory::Create("e6"))); assert(d.Get(SquareFactory::Create("e7"))); assert(d.Get(SquareFactory::Create("e8")));
        assert(d.Get(SquareFactory::Create("f5"))); assert(d.Get(SquareFactory::Create("f6"))); assert(d.Get(SquareFactory::Create("f7"))); assert(d.Get(SquareFactory::Create("f8")));
        assert(d.Get(SquareFactory::Create("g5"))); assert(d.Get(SquareFactory::Create("g6"))); assert(d.Get(SquareFactory::Create("g7"))); assert(d.Get(SquareFactory::Create("g8")));
        assert(d.Get(SquareFactory::Create("h5"))); assert(d.Get(SquareFactory::Create("h6"))); assert(d.Get(SquareFactory::Create("h7"))); assert(d.Get(SquareFactory::Create("h8")));
        assert(!d.Get(SquareFactory::Create("a1"))); assert(!d.Get(SquareFactory::Create("a2"))); assert(!d.Get(SquareFactory::Create("a3"))); assert(!d.Get(SquareFactory::Create("a4")));
        assert(!d.Get(SquareFactory::Create("b1"))); assert(!d.Get(SquareFactory::Create("b2"))); assert(!d.Get(SquareFactory::Create("b3"))); assert(!d.Get(SquareFactory::Create("b4")));
        assert(!d.Get(SquareFactory::Create("c1"))); assert(!d.Get(SquareFactory::Create("c2"))); assert(!d.Get(SquareFactory::Create("c3"))); assert(!d.Get(SquareFactory::Create("c4")));
        assert(!d.Get(SquareFactory::Create("d1"))); assert(!d.Get(SquareFactory::Create("d2"))); assert(!d.Get(SquareFactory::Create("d3"))); assert(!d.Get(SquareFactory::Create("d4")));
        assert(!d.Get(SquareFactory::Create("e1"))); assert(!d.Get(SquareFactory::Create("e2"))); assert(!d.Get(SquareFactory::Create("e3"))); assert(!d.Get(SquareFactory::Create("e4")));
        assert(!d.Get(SquareFactory::Create("f1"))); assert(!d.Get(SquareFactory::Create("f2"))); assert(!d.Get(SquareFactory::Create("f3"))); assert(!d.Get(SquareFactory::Create("f4")));
        assert(!d.Get(SquareFactory::Create("g1"))); assert(!d.Get(SquareFactory::Create("g2"))); assert(!d.Get(SquareFactory::Create("g3"))); assert(!d.Get(SquareFactory::Create("g4")));
        assert(!d.Get(SquareFactory::Create("h1"))); assert(!d.Get(SquareFactory::Create("h2"))); assert(!d.Get(SquareFactory::Create("h3"))); assert(!d.Get(SquareFactory::Create("h4")));
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
              if (!b->CanDoMove(Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
              assert(b->CanDoMove(Chess::MoveFactory::Create(s),Player::white));
            }
          );
        }
        assert(b->GetMoves(SquareFactory::Create("a1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("b1")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c1")).size() == 0);
        assert(!b->CanDoMove(MoveFactory::Create("Qd1 d8"),Player::white));
        assert(!b->CanDoMove(MoveFactory::Create("Qd1 d7"),Player::white));
        assert(b->GetMoves(SquareFactory::Create("d1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("e1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("g1")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("a2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("b2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("d2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("e2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("f2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("g2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("a8")).size() == 0);
        /*
        assert(b->GetMoves(SquareFactory::Create("b8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("c8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("d8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("e8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("g8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("h8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("a7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("b7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("c7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("d7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("e7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("g7")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("h7")).size() == 0);
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
              if (!b->CanDoMove(Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
              assert(b->CanDoMove(Chess::MoveFactory::Create(s),Player::white));
            }
          );
        }
      }

      {
        FTRACE("Test a Pawn on the board at e2");
        const ribi::Chess::Board::Pieces v =
        {
          PieceFactory::Create('.',Color::white,"e2"),
          PieceFactory::Create('.',Color::white,"d3"),
          PieceFactory::Create('.',Color::black,"f3")
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert( b->CanDoMove(MoveFactory::Create("e2 e3"),Player::white));
        assert( b->CanDoMove(MoveFactory::Create("e2 e4"),Player::white));
        assert( b->CanDoMove(MoveFactory::Create("e2xf3"),Player::white));
        assert(!b->CanDoMove(MoveFactory::Create("e2xd3"),Player::white));
      }

      {
        FTRACE("Test a Pawn on the board at e2, blocked by an opponent");
        const ribi::Chess::Board::Pieces v =
        {
          PieceFactory::Create('.',Color::white,"e2"),
          PieceFactory::Create('.',Color::black,"e3")
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert(!b->CanDoMove(MoveFactory::Create("e2 e3"),Player::white));
        assert(!b->CanDoMove(MoveFactory::Create("e2 e4"),Player::white));
      }

      {
        FTRACE("Test a Pawn on the board at h4, blocked by an opponent");
        const ribi::Chess::Board::Pieces v =
        {
          PieceFactory::Create('.',Color::white,"h4"),
          PieceFactory::Create('.',Color::black,"h5")
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert(!b->CanDoMove(MoveFactory::Create("h4 h5"),Player::white));
      }

      {
        FTRACE("Test a Knight on the board at d4");
        const ribi::Chess::Board::Pieces v =
        {
          PieceFactory::Create('N',Color::white,"d4"),
          PieceFactory::Create('.',Color::white,"c6"),
          PieceFactory::Create('.',Color::black,"e6")
        };
        boost::shared_ptr<Board> b(BoardFactory::Create(v));
        assert( b->CanDoMove(MoveFactory::Create("Nd4 b5"),Player::white));
        assert( b->CanDoMove(MoveFactory::Create("Nd4 f5"),Player::white));
        assert(!b->CanDoMove(MoveFactory::Create("Nd4xc6"),Player::white));
        assert( b->CanDoMove(MoveFactory::Create("Nd4xe6"),Player::white));
      }


      {
        FTRACE("Test valid moves for black after 1. e2 e4");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        b->DoMove(MoveFactory::Create("e2 e4"),Player::white);
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
              if (!b->CanDoMove(Chess::MoveFactory::Create(s),Player::black)) { TRACE(s); }
              assert(b->CanDoMove(Chess::MoveFactory::Create(s),Player::black));
            }
          );
        }
        assert(b->GetMoves(SquareFactory::Create("a8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("b8")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("d8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("e8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("g8")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h8")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("a7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("b7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("d7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("e7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("f7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("g7")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h7")).size() == 2);
        assert(b->GetMoves(Player::black).size() == 20);
        assert(!b->IsCheck(Player::black));
        assert(!b->IsCheckmate(Player::black));
      }

      {
        FTRACE("Test valid moves for white after 1. e2 e4 e7 e5");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        b->DoMove(MoveFactory::Create("e2 e4"),Player::white);
        b->DoMove(MoveFactory::Create("e7 e5"),Player::black);
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
              if (!b->CanDoMove(Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
              assert(b->CanDoMove(Chess::MoveFactory::Create(s),Player::white));
            }
          );
        }
        assert(b->GetMoves(SquareFactory::Create("a1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("b1")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("d1")).size() == 4);
        assert(b->GetMoves(SquareFactory::Create("e1")).size() == 1);
        assert(b->GetMoves(SquareFactory::Create("f1")).size() == 5);
        assert(b->GetMoves(SquareFactory::Create("g1")).size() == 3);
        assert(b->GetMoves(SquareFactory::Create("h1")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("a2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("b2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("c2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("d2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("e4")).size() == 0);
        assert(b->GetMoves(SquareFactory::Create("f2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("g2")).size() == 2);
        assert(b->GetMoves(SquareFactory::Create("h2")).size() == 2);
        assert(b->GetMoves(Player::white).size() == 29);
        assert(!b->IsCheck(Player::white));
        assert(!b->IsCheckmate(Player::white));
      }

      {
        FTRACE("Test Board copy constructor");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        assert( b->GetPiece(SquareFactory::Create("e2")));
        assert(!b->GetPiece(SquareFactory::Create("e4")));
        b->DoMove(MoveFactory::Create("e2 e4"),Player::white);
        const boost::shared_ptr<Chess::Board> c(b);
        assert(*b == *c);
        assert(!b->GetPiece(SquareFactory::Create("e2")));
        assert( b->GetPiece(SquareFactory::Create("e4")));
        assert(!c->GetPiece(SquareFactory::Create("e2")));
        assert( c->GetPiece(SquareFactory::Create("e4")));
        b->DoMove(MoveFactory::Create("e7 e5"),Player::black);
        assert(*b != *c);
        assert( b->GetPiece(SquareFactory::Create("e5")));
        assert(!b->GetPiece(SquareFactory::Create("e7")));
        assert(!c->GetPiece(SquareFactory::Create("e5")));
        assert( c->GetPiece(SquareFactory::Create("e7")));
      }
      {
        FTRACE("Test EmptyBetween on single piece");
        const Pieces pieces
          =
          {
            PieceFactory::Create('K',Color::white,"b2")
          };
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create(pieces));
        assert( b->EmptyBetween(SquareFactory::Create("a1"),SquareFactory::Create("c1")));
        assert( b->EmptyBetween(SquareFactory::Create("c1"),SquareFactory::Create("a1")));
        assert( b->EmptyBetween(SquareFactory::Create("a1"),SquareFactory::Create("a3")));
        assert( b->EmptyBetween(SquareFactory::Create("a3"),SquareFactory::Create("a1")));
        assert(!b->EmptyBetween(SquareFactory::Create("a1"),SquareFactory::Create("c3")));
        assert(!b->EmptyBetween(SquareFactory::Create("c3"),SquareFactory::Create("a1")));
        assert(!b->EmptyBetween(SquareFactory::Create("b1"),SquareFactory::Create("b3")));
        assert(!b->EmptyBetween(SquareFactory::Create("b3"),SquareFactory::Create("b1")));
        assert(!b->EmptyBetween(SquareFactory::Create("a2"),SquareFactory::Create("c2")));
        assert(!b->EmptyBetween(SquareFactory::Create("c2"),SquareFactory::Create("a2")));
        assert( b->EmptyBetween(SquareFactory::Create("d1"),SquareFactory::Create("d8")));
        assert( b->EmptyBetween(SquareFactory::Create("d8"),SquareFactory::Create("d1")));
        assert( b->EmptyBetween(SquareFactory::Create("a4"),SquareFactory::Create("h4")));
        assert( b->EmptyBetween(SquareFactory::Create("h4"),SquareFactory::Create("a4")));
        assert( b->EmptyBetween(SquareFactory::Create("b5"),SquareFactory::Create("f1")));
        assert( b->EmptyBetween(SquareFactory::Create("f1"),SquareFactory::Create("b5")));
      }

      {
        FTRACE("Test EmptyBetween after 3rd move of white in Kasparov against the World game");
        const Pieces pieces
          =
          {

            PieceFactory::Create('R',Color::white,"a1"),
            PieceFactory::Create('N',Color::white,"c3"),
            PieceFactory::Create('B',Color::white,"c1"),
            PieceFactory::Create('Q',Color::white,"d1"),
            PieceFactory::Create('K',Color::white,"e1"),
            PieceFactory::Create('B',Color::white,"b5"),
            PieceFactory::Create('N',Color::white,"g1"),
            PieceFactory::Create('R',Color::white,"h1"),
            PieceFactory::Create('.',Color::white,"a2"),
            PieceFactory::Create('.',Color::white,"b2"),
            PieceFactory::Create('.',Color::white,"c2"),
            PieceFactory::Create('.',Color::white,"d2"),
            PieceFactory::Create('.',Color::white,"e4"),
            PieceFactory::Create('.',Color::white,"f2"),
            PieceFactory::Create('.',Color::white,"g2"),
            PieceFactory::Create('.',Color::white,"h2"),
            PieceFactory::Create('R',Color::black,"a8"),
            PieceFactory::Create('N',Color::black,"b8"),
            PieceFactory::Create('B',Color::black,"c8"),
            PieceFactory::Create('Q',Color::black,"d8"),
            PieceFactory::Create('K',Color::black,"e8"),
            PieceFactory::Create('B',Color::black,"f8"),
            PieceFactory::Create('N',Color::black,"g8"),
            PieceFactory::Create('R',Color::black,"h8"),
            PieceFactory::Create('.',Color::black,"a7"),
            PieceFactory::Create('.',Color::black,"b7"),
            PieceFactory::Create('.',Color::black,"c5"),
            PieceFactory::Create('.',Color::black,"d6"),
            PieceFactory::Create('.',Color::black,"e7"),
            PieceFactory::Create('.',Color::black,"f7"),
            PieceFactory::Create('.',Color::black,"g7"),
            PieceFactory::Create('.',Color::black,"h7")
          };
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create(pieces));
        assert( b->EmptyBetween(SquareFactory::Create("b5"),SquareFactory::Create("e8")));
        assert( b->EmptyBetween(SquareFactory::Create("e8"),SquareFactory::Create("b5")));
        assert( b->EmptyBetween(SquareFactory::Create("b5"),SquareFactory::Create("f1")));
        assert( b->EmptyBetween(SquareFactory::Create("f1"),SquareFactory::Create("b5")));
      }

      {
        FTRACE("Test IsCheck from setup 1");
        const Pieces pieces
          =
          {
            PieceFactory::Create('K',Color::white,"a1"),
            PieceFactory::Create('K',Color::black,"h8"),
            PieceFactory::Create('R',Color::white,"a8"),
            PieceFactory::Create('R',Color::black,"h1")
          };
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create(pieces));
        assert(b->IsCheck(Player::white));
        assert(b->IsCheck(Player::black));
      }
      {
        FTRACE("Test IsCheck by playing");
        boost::shared_ptr<Chess::Board> b(BoardFactory::Create());
        b->DoMove(MoveFactory::Create("e2 e4"),Player::white);
        b->DoMove(MoveFactory::Create("d7 d6"),Player::black);
        FTRACE("Test that the move ending is check can be done");
        assert(b->CanDoMove(MoveFactory::Create("Bf1 b5+"),Player::white));
        FTRACE("Do the move ending is check");
        b->DoMove(MoveFactory::Create("Bf1 b5+"),Player::white);
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
                const boost::shared_ptr<const Move> move { MoveFactory::Create(s) };
                if (b->CanDoMove(Chess::MoveFactory::Create(s),Player::white)) { TRACE(s); }
                assert(!b->CanDoMove(Chess::MoveFactory::Create(s),Player::white));
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
              if (!b->CanDoMove(Chess::MoveFactory::Create(s),player)) { TRACE(s); }
              assert(b->CanDoMove(Chess::MoveFactory::Create(s),player));
              b->DoMove(MoveFactory::Create(s),player);
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
            if (!b->CanDoMove(Chess::MoveFactory::Create(s),player)) { TRACE(s);  }
            assert(b->CanDoMove(Chess::MoveFactory::Create(s),player));
            b->DoMove(MoveFactory::Create(s),player);
            player = (player == Player::white ? Player::black : Player::white);
          }
        }
      }
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.detach();
  #endif
}
#endif

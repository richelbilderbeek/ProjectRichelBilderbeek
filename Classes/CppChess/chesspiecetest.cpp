#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "chesspiece.h"

#include <cassert>
#include <future>

#include "chessmove.h"
#include "chessmovefactory.h"
#include "chessmoves.h"
#include "chesssquarefactory.h"
#include "chesspiecefactory.h"
#include "trace.h"
#pragma GCC diagnostic pop

///Is there an elemnt in v for IsEqual(*p,*v)
template <class T, class U>
bool IsPresent(boost::shared_ptr<T> p,const std::vector<boost::shared_ptr<U> > v)
{
  assert(p);
  return std::count_if(v.begin(),v.end(),
    [p](const boost::shared_ptr<T> q)
    {
      assert(q);
      return *p == *q;
    }
  ) > 0;
}

void ribi::Chess::Piece::Test()
{
  //Testing Chess::Piece exactly once
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
      FTRACE("Test Chess::Piece");
      {
        const boost::shared_ptr<Square> s = SquareFactory::Create("e4");
        assert(s);
        const boost::shared_ptr<Square> t = SquareFactory::Create("e4");
        assert(t);
        const boost::shared_ptr<Piece> p = PieceFactory::Create('B',Color::white,s);
        assert(p);
        const boost::shared_ptr<Piece> q = PieceFactory::Create('B',Color::white,t);
        assert(q);
        assert(*p == *q);

      }
      ribi::Chess::PieceBishop::Test();
      ribi::Chess::PieceKing::Test();
      ribi::Chess::PieceKnight::Test();
      ribi::Chess::PiecePawn::Test();
      ribi::Chess::PieceQueen::Test();
      ribi::Chess::PieceRook::Test();
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

void ribi::Chess::PieceBishop::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Bishop for valid moves");
      {
        const std::vector<std::string> v = Moves::GetValidBishopMoves();

        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            const boost::shared_ptr<const Move> move
              = MoveFactory::Create(s);
            assert(move);
            {
              boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::white,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::black,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::indeterminate,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::white,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::black,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
          }
        );
      }
      FTRACE("Test Bishop for invalid moves")
      {
        const std::vector<std::string> v = Moves::GetInvalidBishopMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              const boost::shared_ptr<const Move> move
                = MoveFactory::Create(s);
              assert(move);
              {
                boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::white,boost::shared_ptr<Square>()));
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::black,boost::shared_ptr<Square>()));
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::indeterminate,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::white,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceBishop(Chess::Color::black,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
            }
            catch (std::exception& e)
            {
              //Move is correctly determined to be invalid
            }
          }
        );
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

void ribi::Chess::PieceKing::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test King for valid moves")
      {
        const std::vector<std::string> v = Moves::GetValidKingMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            const boost::shared_ptr<const Move> move
              = MoveFactory::Create(s);
            assert(move);
            {
              boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::white,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::black,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::indeterminate,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::white,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::black,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
          }
        );
      }

      FTRACE("Test King for invalid moves")
      {
        const std::vector<std::string> v = Moves::GetInvalidKingMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              const boost::shared_ptr<const Move> move
                = MoveFactory::Create(s);
              assert(move);
              {
                boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
                if (p->CanDoMove(move)) { TRACE(s); }
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceKing(Chess::Color::indeterminate,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

void ribi::Chess::PieceKnight::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Knight for valid moves");
      {
        const std::vector<std::string> v = Moves::GetValidKnightMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            const boost::shared_ptr<const Move> move
              = MoveFactory::Create(s);
            assert(move);
            {
              boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::white,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::black,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::indeterminate,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::white,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::black,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
          }
        );
      }

      FTRACE("Test Knight for invalid moves")
      {
        const std::vector<std::string> v = Moves::GetInvalidKnightMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              const boost::shared_ptr<const Move> move
                = MoveFactory::Create(s);
              assert(move);
              {
                boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
                if (p->CanDoMove(move)) { TRACE(s); }
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceKnight(Chess::Color::indeterminate,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }
      FTRACE("Test Knight for generating its own moves");
      {
        const boost::shared_ptr<Square> square = SquareFactory::Create("d4");
        assert(square);
        boost::shared_ptr<Piece> piece = PieceFactory::Create('N',Color::white,square);
        assert(piece);
        const std::vector<boost::shared_ptr<Move> > moves = piece->GetMoves();
        assert(moves.size() == 8 * 3); //*3 due to non-check, check and checkmate moves
        const boost::shared_ptr<const Move> move = MoveFactory::Create("Nd4 c2");
        assert(move);
        assert(IsPresent(move,moves));
        //assert(std::find(moves.begin(),moves.end(),move) != moves.end());
      }
      {
        const boost::shared_ptr<Square> square = SquareFactory::Create("a1");
        assert(square);
        boost::shared_ptr<Piece> piece = PieceFactory::Create('N',Color::white,square);
        assert(piece);
        const std::vector<boost::shared_ptr<Move> > moves = piece->GetMoves();
        assert(moves.size() == 2 * 3); //*3 due to non-check, check and checkmate moves
        const boost::shared_ptr<const Move> move = MoveFactory::Create("Na1 b3");
        assert(move);
        assert(IsPresent(move,moves));
        //assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("Na1 b3")) != moves.end());
      }
      {
        const boost::shared_ptr<Square> square = SquareFactory::Create("b1");
        assert(square);
        boost::shared_ptr<Piece> piece = PieceFactory::Create('N',Color::black,square);
        assert(piece);
        const std::vector<boost::shared_ptr<Move> > moves = piece->GetMoves();
        assert(moves.size() == 3 * 3); //*3 due to non-check, check and checkmate moves
        const boost::shared_ptr<const Move> move = MoveFactory::Create("Nb1 c3");
        assert(move);
        assert(IsPresent(move,moves));
        //assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("Nb1 c3")) != moves.end());
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

void ribi::Chess::PiecePawn::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Pawn for valid moves")
      for (int i=0; i!=3; ++i)
      {
        const Chess::Color color = (i == 0 ? Color::indeterminate : (i == 1 ? Color::white : Color::black));
        const std::vector<std::string> v = Moves::GetValidPawnMoves(color);
        std::for_each(v.begin(),v.end(),
          [color](const std::string& s)
          {
            const boost::shared_ptr<const Move> move
              = MoveFactory::Create(s);
            assert(move);
            {
              boost::shared_ptr<Piece> p(new PiecePawn(color,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PiecePawn(color,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
          }
        );
      }

      FTRACE("Test Pawn for invalid moves")
      for (int i=0; i!=3; ++i)
      {
        const Chess::Color color = (i == 0 ? Color::indeterminate : (i == 1 ? Color::white : Color::black));
        const std::vector<std::string> v = Moves::GetInvalidPawnMoves(Color::indeterminate);
        std::for_each(v.begin(),v.end(),
          [color](const std::string& s)
          {
            try
            {
              const boost::shared_ptr<const Move> move
                = MoveFactory::Create(s);
              assert(move);
              {
                boost::shared_ptr<Piece> p(new PiecePawn(color,boost::shared_ptr<Square>()));
                if (p->CanDoMove(move)) { TRACE(s); }
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PiecePawn(color,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }

      FTRACE("Test Pawn intimately");
      {
        boost::shared_ptr<Piece> p(new PiecePawn(Chess::Color::white,boost::shared_ptr<Square>()));
        assert(p);
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a2 a3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a2 a4");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a2 a1Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a7 a8Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a4");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a1Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a8Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
      }

      {
        boost::shared_ptr<Piece> p(new PiecePawn(Chess::Color::black,boost::shared_ptr<Square>()));
        assert(p);
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a2 a3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a2 a4");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a2 a1Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a7 a8Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a4");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a1Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("a8Q");
          assert(move);
          assert(p->CanDoMove(move));
        }
      }


      {
        //const boost::shared_ptr<const Square> square = SquareFactory::Create("e4");
        //assert(square);
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('.',Chess::Color::indeterminate,"e4");
        assert(p);

        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4 e5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xd5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xf5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4 e3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xd3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xf3");
          assert(move);
          assert(p->CanDoMove(move));
        }
      }
      {
        //const boost::shared_ptr<const Square> square = SquareFactory::Create("e4");
        //assert(square);
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('.',Chess::Color::white,"e4");
        assert(p);
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4 e5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xd5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xf5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4 e3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xd3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xf3");
          assert(move);
          assert(p->CanDoMove(move));
        }

      }
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('.',Chess::Color::black,"e4");
        assert(p);
        //boost::shared_ptr<Piece> p(new PiecePawn(Chess::Color::black,boost::shared_ptr<Square>(new Square("e4"))));

        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4 e5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xd4");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xf5");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4 e3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xd3");
          assert(move);
          assert(p->CanDoMove(move));
        }
        {
          const boost::shared_ptr<const Move> move = MoveFactory::Create("e4xf3");
          assert(move);
          assert(p->CanDoMove(move));
        }
      }

      FTRACE("Test Pawn at e4 for generating its own moves");
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('.',Chess::Color::indeterminate,"e4");
        assert(p);
        //const PiecePawn p(Color::indeterminate,boost::shared_ptr<Square>(new Square("e4")));
        const std::vector<boost::shared_ptr<Move> > moves = p->GetMoves();

        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4 e5")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xd5")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xf5")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4 e3")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xd3")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xf3")) != moves.end());
        assert(moves.size() == 6 * 3); //*3 due to non-check, check and checkmate moves
      }
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('.',Chess::Color::white,"e4");
        assert(p);
        //PiecePawn p(Color::white,boost::shared_ptr<Square>(new Square("e4")));
        const std::vector<boost::shared_ptr<Move> > moves = p->GetMoves();
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4 e5")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xd5")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xf5")) != moves.end());
        assert(moves.size() == 3 * 3); //*3 due to non-check, check and checkmate moves
      }
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('.',Chess::Color::black,"e4");
        assert(p);
        //PiecePawn p(Color::black,boost::shared_ptr<Square>(new Square("e4")));
        const std::vector<boost::shared_ptr<Move> > moves = p->GetMoves();
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4 e3")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xd3")) != moves.end());
        assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("e4xf3")) != moves.end());
        assert(moves.size() == 3 * 3); //*3 due to non-check, check and checkmate moves
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

void ribi::Chess::PieceQueen::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Queen for valid moves");
      {
        const std::vector<std::string> v = Moves::GetValidQueenMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            const boost::shared_ptr<const Move> move
              = MoveFactory::Create(s);
            assert(move);
            {
              boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::white,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::black,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::indeterminate,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::white,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::black,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
          }
        );
      }
      FTRACE("Test Queen for invalid moves");
      {
        const std::vector<std::string> v = Moves::GetInvalidQueenMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              const boost::shared_ptr<const Move> move
                = MoveFactory::Create(s);
              assert(move);
              {
                boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
                if (p->CanDoMove(move)) { TRACE(s); }
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceQueen(Chess::Color::indeterminate,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }

      FTRACE("Test Queen for generating its own moves");
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('Q',Chess::Color::white,"d4");
        assert(p);
        //PieceQueen q(Color::white,boost::shared_ptr<Square>(new Square("d4")));
        const std::vector<boost::shared_ptr<Move> > moves = p->GetMoves();
        assert(moves.size() == 27 * 3); //*3 due to non-check, check and checkmate moves
        const boost::shared_ptr<const Move> move = MoveFactory::Create("Qd4 h8");
        assert(move);
        assert(IsPresent(move,moves));
        //assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("Qd4 h8")) != moves.end());
      }
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('Q',Chess::Color::white,"a1");
        assert(p);
        //PieceQueen q(Color::white,boost::shared_ptr<Square>(new Square("a1")));
        const std::vector<boost::shared_ptr<Move> > moves = p->GetMoves();
        assert(moves.size() == 21 * 3); //*3 due to non-check, check and checkmate moves
        const boost::shared_ptr<const Move> move = MoveFactory::Create("Qa1 h1");
        assert(move);
        assert(IsPresent(move,moves));
        //assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("Qa1 h1")) != moves.end());
      }
      {
        const boost::shared_ptr<const Piece> p = PieceFactory::Create('Q',Chess::Color::black,"b1");
        assert(p);
        //PieceQueen q(Color::white,boost::shared_ptr<Square>(new Square("b1")));
        const std::vector<boost::shared_ptr<Move> > moves = p->GetMoves();
        assert(moves.size() == 21 * 3); //*3 due to non-check, check and checkmate moves
        const boost::shared_ptr<const Move> move = MoveFactory::Create("Qb1 b8");
        assert(move);
        assert(IsPresent(move,moves));
        //assert(std::find(moves.begin(),moves.end(),MoveFactory::Create("Qb1 b8")) != moves.end());
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

void ribi::Chess::PieceRook::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Test Rook for valid moves");
      {
        const std::vector<std::string> v = Moves::GetValidRookMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            const boost::shared_ptr<const Move> move
              = MoveFactory::Create(s);
            assert(move);
            {
              boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::white,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::black,boost::shared_ptr<Square>()));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::indeterminate,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::white,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
            {
              boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::black,Move::ParseFrom(s)));
              assert(p->CanDoMove(move));
            }
          }
        );
      }
      FTRACE("Test Rook for invalid moves");
      {
        const std::vector<std::string> v = Moves::GetInvalidRookMoves();
        std::for_each(v.begin(),v.end(),
          [](const std::string& s)
          {
            try
            {
              const boost::shared_ptr<const Move> move
                = MoveFactory::Create(s);
              assert(move);
              {
                boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::indeterminate,boost::shared_ptr<Square>()));
                if (p->CanDoMove(move)) { TRACE(s); }
                assert(!p->CanDoMove(move));
              }
              {
                boost::shared_ptr<Piece> p(new PieceRook(Chess::Color::indeterminate,Move::ParseFrom(s)));
                assert(!p->CanDoMove(move));
              }
            }
            catch (std::exception& e)
            {
              //OK!
            }
          }
        );
      }
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

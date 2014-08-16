#include "chessmove.h"

#include <cassert>

#include "chessmoves.h"
#include "chesspiece.h"
#include "chesssquarefactory.h"
#include "testtimer.h"
#include "trace.h"


#ifndef NDEBUG
void ribi::Chess::Move::Test() noexcept
{
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  {
    Chess::Square::Test();
    Chess::Piece::Test();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Test Chess::Move operators and copy constructors"); }
  {
    Chess::Move m("a2 a3");
    Chess::Move n("a2 a3");
    assert(m == n);
  }
  {
    Chess::Move m("a2 a3");
    Chess::Move n("a3 a2");
    assert(m != n);
  }
  {
    Chess::Move m("a2 a3");
    Chess::Move n(m);
    assert(m == n);
  }

  if (verbose) { TRACE("Test Chess::Move parsing of the square the piece is moving from"); }

  assert((*Move::ParseFrom( "a2 a3")==*SquareFactory().Create(Chess::File("a"),Chess::Rank("2"))));
  assert((*Move::ParseFrom("Bb3 c5")==*SquareFactory().Create(Chess::File("b"),Chess::Rank("3"))));
  assert((*Move::ParseFrom("Kc4 d4")==*SquareFactory().Create(Chess::File("c"),Chess::Rank("4"))));
  assert((*Move::ParseFrom("Nd5 e6")==*SquareFactory().Create(Chess::File("d"),Chess::Rank("5"))));
  assert((*Move::ParseFrom("Qe6 f7")==*SquareFactory().Create(Chess::File("e"),Chess::Rank("6"))));
  assert((*Move::ParseFrom("Rf7 h7")==*SquareFactory().Create(Chess::File("f"),Chess::Rank("7"))));
  assert(!ribi::Chess::Move::ParseFrom("a3"));
  assert(!ribi::Chess::Move::ParseFrom("0-0"));
  assert(!ribi::Chess::Move::ParseFrom("0-0+"));
  assert(!ribi::Chess::Move::ParseFrom("0-0#"));
  assert(!ribi::Chess::Move::ParseFrom("O-O"));
  assert(!ribi::Chess::Move::ParseFrom("O-O+"));
  assert(!ribi::Chess::Move::ParseFrom("O-O#"));
  assert(!ribi::Chess::Move::ParseFrom("0-0-0"));
  assert(!ribi::Chess::Move::ParseFrom("0-0-0+"));
  assert(!ribi::Chess::Move::ParseFrom("0-0-0#"));
  assert(!ribi::Chess::Move::ParseFrom("O-O-O"));
  assert(!ribi::Chess::Move::ParseFrom("O-O-O+"));
  assert(!ribi::Chess::Move::ParseFrom("O-O-O#"));

  if (verbose) { TRACE("Testing valid capture moves"); }
  {
    const std::vector<std::string> v = Moves::GetValidCaptureMoves();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        if (!ribi::Chess::Move::ParseIsCapture(s)) { TRACE(s); }
        assert(ribi::Chess::Move::ParseIsCapture(s));
      }
    );
  }
  if (verbose) { TRACE("Testing valid castling moves"); }
  {
    const std::vector<std::string> v = Moves::GetValidCastlingMoves();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        if (!ribi::Chess::Move::ParseIsCastling(s)) { TRACE(s); }
        assert(ribi::Chess::Move::ParseIsCastling(s));
      }
    );
  }

  assert(!ribi::Chess::Move::ParseIsCastling("a3"));

  if (verbose) { TRACE("Testing valid moves that result in check"); }
  {
    const std::vector<std::string> v = Moves::GetValidCheckMoves();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        if (!ribi::Chess::Move::ParseIsCheck(s)) { TRACE(s); }
        assert(ribi::Chess::Move::ParseIsCheck(s));
      }
    );
  }
  assert(!ribi::Chess::Move::ParseIsCheck("a2 a3"));
  assert(!ribi::Chess::Move::ParseIsCheck("a2xb3"));
  assert(!ribi::Chess::Move::ParseIsCheck("Ba3"));
  assert(!ribi::Chess::Move::ParseIsCheck("Ba2 b3"));
  assert(!ribi::Chess::Move::ParseIsCheck("Ba2xb3"));
  assert(!ribi::Chess::Move::ParseIsCheck("a2 a3#"));
  assert(!ribi::Chess::Move::ParseIsCheck("a2xb3#"));
  assert(!ribi::Chess::Move::ParseIsCheck("Ba3#"));
  assert(!ribi::Chess::Move::ParseIsCheck("Ba2 b3#"));
  assert(!ribi::Chess::Move::ParseIsCheck("Ba2xb3#"));
  assert(!ribi::Chess::Move::ParseIsCheck("O-O"));
  assert(!ribi::Chess::Move::ParseIsCheck("O-O-O"));
  assert(!ribi::Chess::Move::ParseIsCheck("0-0"));
  assert(!ribi::Chess::Move::ParseIsCheck("0-0-0"));
  assert(!ribi::Chess::Move::ParseIsCheck("O-O#"));
  assert(!ribi::Chess::Move::ParseIsCheck("O-O-O#"));
  assert(!ribi::Chess::Move::ParseIsCheck("0-0#"));
  assert(!ribi::Chess::Move::ParseIsCheck("0-0-0#"));

  if (verbose) { TRACE("Testing valid moves that result in checkmate"); }
  assert(ribi::Chess::Move::ParseIsCheckmate("a3#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("a2 a3#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("a2xb3#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("Ba3#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("Ba2 b3#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("Ba2xb3#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("O-O#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("O-O-O#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("0-0#"));
  assert(ribi::Chess::Move::ParseIsCheckmate("0-0-0#"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("a2 a3"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("a2xb3"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("Ba3"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("Ba2 b3"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("Ba2xb3"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("a2 a3+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("a2xb3+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("Ba3+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("Ba2 b3+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("Ba2xb3+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("O-O"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("O-O-O"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("0-0"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("0-0-0"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("O-O+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("O-O-O+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("0-0+"));
  assert(!ribi::Chess::Move::ParseIsCheckmate("0-0-0+"));

  if (verbose) { TRACE("Testing valid en passant moves"); }
  {
    const std::vector<std::string> v = Moves::GetValidEnPassantMoves();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        assert(ribi::Chess::Move::ParseIsEnPassant(s));
      }
    );
  }

  if (verbose) { TRACE("Testing invalid en passant moves"); }
  {
    const std::vector<std::string> v = Moves::GetInvalidEnPassantMoves();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        if (ribi::Chess::Move::ParseIsEnPassant(s)) TRACE(s);
        assert(!ribi::Chess::Move::ParseIsEnPassant(s));
      }
    );
  }


  if (verbose) { TRACE("Testing valid moves that end in a promotion"); }
  {
    const std::vector<std::string> v = Moves::GetValidPromotionMoves();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        assert(ribi::Chess::Move::ParseIsPromotion(s));
      }
    );
  }
  if (verbose) { TRACE("Testing ParseTo"); }

  ///Test parsing of the square the piece is moving to
  assert((*Move::ParseTo("a2 a3")==*SquareFactory().Create(Chess::File("a"),Chess::Rank("3"))));
  assert((*Move::ParseTo(   "a3")==*SquareFactory().Create(Chess::File("a"),Chess::Rank("3"))));
  assert((*Move::ParseTo("Bb3 c5")==*SquareFactory().Create(Chess::File("c"),Chess::Rank("5"))));
  assert((*Move::ParseTo("Kc4 d4")==*SquareFactory().Create(Chess::File("d"),Chess::Rank("4"))));
  assert((*Move::ParseTo("Nd5 e6")==*SquareFactory().Create(Chess::File("e"),Chess::Rank("6"))));
  assert((*Move::ParseTo("Qe6 f7")==*SquareFactory().Create(Chess::File("f"),Chess::Rank("7"))));
  assert((*Move::ParseTo("Rf7 h7")==*SquareFactory().Create(Chess::File("h"),Chess::Rank("7"))));
  assert(!ribi::Chess::Move::ParseTo("0-0"));
  assert(!ribi::Chess::Move::ParseTo("0-0+"));
  assert(!ribi::Chess::Move::ParseTo("0-0#"));
  assert(!ribi::Chess::Move::ParseTo("O-O"));

  assert(!ribi::Chess::Move::ParseTo("O-O+"));
  assert(!ribi::Chess::Move::ParseTo("O-O#"));
  assert(!ribi::Chess::Move::ParseTo("0-0-0"));
  assert(!ribi::Chess::Move::ParseTo("0-0-0+"));
  assert(!ribi::Chess::Move::ParseTo("0-0-0#"));
  assert(!ribi::Chess::Move::ParseTo("O-O-O"));
  assert(!ribi::Chess::Move::ParseTo("O-O-O+"));
  assert(!ribi::Chess::Move::ParseTo("O-O-O#"));

  if (verbose) { TRACE("Testing ParsePiece"); }
  assert(ribi::Chess::Move::ParsePiece("Ba1 b2")->GetNameChar() == 'B');
  assert(ribi::Chess::Move::ParsePiece("Ka1 b1")->GetNameChar() == 'K');
  assert(ribi::Chess::Move::ParsePiece("Na1 b3")->GetNameChar() == 'N');
  assert(ribi::Chess::Move::ParsePiece("Qa1 b1")->GetNameChar() == 'Q');
  assert(ribi::Chess::Move::ParsePiece("Ra1 b1")->GetNameChar() == 'R');
  assert(ribi::Chess::Move::ParsePiece("a2 a4")->GetNameChar() == '.');

  #ifdef FIX_ISSUE_240
  try
  {
    const auto piece(Chess::Move("0-0").Piece());
    assert(!"Should not get here");
  }
  catch (std::logic_error&)
  {
    //OK
  }
  try
  {
    const auto piece(Chess::Move("O-O-O").Piece());
    assert(!"Should not get here");
  }
  catch (std::logic_error&)
  {
    //OK
  }
  #endif // FIX_ISSUE_240

  if (verbose) { TRACE("Test complete moves for validity"); }
  //Test valid moves being valid as a move: the history of the chessgame must point out
  //if the move is valid in its context
  {
    const std::vector<std::string> v
     = {
      "a2 a3", "a2 a4", "a3 a4", "a4 a5", "a5 a6", "a6 a7", //white pawn at A file all its movements without promotion
      "a2xb3", "a3xb4", "a4xb5", "a5xb6", "a6xb7",          //white pawn at A file all its captures without promotion
      "a7 a6", "a7 a5", "a6 a5", "a5 a4", "a4 a3", "a3 a2", //black pawn at A file all its movements without promotion
      //Short notation
      #ifdef RIBI_CHESS_ALLOW_SHORT_NOTATION
      "a2", "a3", "a4", "a4", "a5", "a6", "a7", //pawn at A file all its movements without promotion
      "b2", "b3", "b4", "b4", "b5", "b6", "b7", //pawn at B file all its movements without promotion
      "c2", "c3", "c4", "c4", "c5", "c6", "c7", //pawn at C file all its movements without promotion
      "d2", "d3", "d4", "d4", "d5", "d6", "d7", //pawn at D file all its movements without promotion
      "e2", "e3", "e4", "e4", "e5", "e6", "e7", //pawn at E file all its movements without promotion
      "f2", "f3", "f4", "f4", "f5", "f6", "f7", //pawn at F file all its movements without promotion
      "g2", "g3", "g4", "g4", "g5", "g6", "g7", //pawn at G file all its movements without promotion
      "h2", "h3", "h4", "h4", "h5", "h6", "h7", //pawn at H file all its movements without promotion
      #endif
      "O-O","O-O-O","0-0","0-0-0",     //Castling
      "O-O+","O-O-O+","0-0+","0-0-0+", //Castling
      "O-O#","O-O-O#","0-0#","0-0-0#", //Castling
      "1-0","0-1","1/2-1/2"

    };
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        try
        {
          Chess::Move m(s);
        }
        catch (std::exception& e)
        {
          TRACE(s);
          TRACE(e.what());
          assert(!"Should not get here");
        }
      }
    );
  }
  //Test invalid moves being invalid
  {
    std::vector<std::string> v
     =
      {
        "B0-0" , "B0-0-0", "BO-O", "BO-O-O",
        "B0-0+", "B0-0-0+", "BO-O+", "BO-O-O+",
        "B0-0#", "B0-0-0#", "BO-O#", "BO-O-O#"
        //"ND4xe6"
      };
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        try
        {
          Chess::Move m(s);
          TRACE(s);
          TRACE(m.ToStr());
          assert(!"Should not get here");
        }
        catch (std::exception& e)
        {
          //OK
        }
      }
    );
  }
  #ifdef FIX_ISSUE_240
  if (verbose) { TRACE("Test complete moves intimately"); }
  {
    const Chess::Move m("a3");
    assert(!m.From()); //From is unknown
    assert(!m.IsCapture());
    assert(!m.IsCastling());
    assert(!m.IsCheck());
    assert(!m.IsCheckmate());
    assert(!m.IsPromotion());
    assert(m.Piece());
    assert(dynamic_cast<Chess::PiecePawn*>(m.Piece().get()));
    assert(!m.PiecePromotion());
    assert((*m.To().get()==*SquareFactory().Create("a3")));
  }

  if (verbose) { TRACE("Test Kasparov against the world match"); }
  {
    const std::vector<std::string> v = Chess::Moves::GetGameKasparovVersusTheWorld();
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        try
        {
          //TRACE(s);
          Chess::Move m(s);
        }
        catch (std::exception& e)
        {
          TRACE(s);
          TRACE(e.what());
          assert(!"Should not get here");
        }
      }
    );
  }
  #endif // FIX_ISSUE_240
}
#endif

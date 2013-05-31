
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

#include <boost/multi_array.hpp>
//#include <boost/foreach.hpp>

#include "chessbitboard.h"
#include "chessboard.h"
#include "chessboardfactory.h"
#include "chesscastling.h"
#include "chesshelper.h"
#include "chessfile.h"
#include "chessmove.h"
#include "chesssquarefactory.h"
#include "chessmovefactory.h"
#include "chesspiece.h"
#include "chesspiecefactory.h"
#include "chessplayer.h"
#include "chessrank.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "trace.h"

namespace Chess {

Board::Board(const Pieces& pieces)
  : m_pieces(pieces)
{
  #ifndef NDEBUG
  Test();
  #endif
}

/*
Board::Board(const Board& other)
  //: m_move_history(other.m_move_history)
{
  #ifndef NDEBUG
  Test();
  #endif

  //Copy all Pieces
  //m_pieces = other.m_pieces;
  std::for_each(other.m_pieces.begin(), other.m_pieces.end(),
    [this](const PiecePtr& p)
    {
      assert(p);
      PiecePtr q(p->Clone());
      assert(p != q);
      assert(IsEqual(*p,*q));
      this->m_pieces.insert(q);
    }
  );
  assert(this->m_pieces.size() == other.m_pieces.size());
  assert(IsEqual(this->GetPieces(),other.GetPieces()));
  assert(IsEqual(*this,other));
}
*/

bool Board::CanDoCastling(const Castling castling, const Player player) const
{
  //Cannot castle when in check
  if (IsCheck(player)) return false;
  //Check King
  {
    const boost::shared_ptr<const Square> king_square = SquareFactory::Create(player == Player::white ? std::string("e1") : std::string("e8"));
    assert(king_square);
    const ConstPiecePtr king = GetPiece(*king_square);
    //Is there a King at the king's square?
    if (!king) return false;
    //Check if King has moved
    if (king->GetLastMove()) return false;
  }
  //Check Rook
  {
    const boost::shared_ptr<Square> rook_square = SquareFactory::Create(player == Player::white
      ? (castling == Castling::kingside ? std::string("h1") : std::string("a1"))
      : (castling == Castling::kingside ? std::string("h8") : std::string("a8")) );
    assert(rook_square);
    const ConstPiecePtr rook = GetPiece(*rook_square);
    //Is there a Rook at the rook's square?
    if (!rook) return false;
    //Check if Rook has moved
    if (rook->GetLastMove()) return false;
  }
  //Check squares in between King and Rook
  {
    const std::vector<boost::shared_ptr<Square > > squares
      = CreateSquaresBetweenKingAndRook(player,castling);
    //Check if these squares are empty
    if (std::count_if(squares.begin(),squares.end(),
      [this](const boost::shared_ptr<Square>& square)
      {
        assert(square);
        return GetPiece(*square);
      }
    ) > 0)
    {
      return false;
    }
    //Check if the King needs to move through check
    const BitBoard bitboard = this->GetVisibleSquares(player == Player::white ? Player::black : Player::white);
    if (std::count_if(squares.begin(),squares.end(),
      [bitboard](const boost::shared_ptr<Square>& square)
      {
        assert(square);
        return bitboard.Get(*square);
      }
    ) > 0)
    {
      return false;
    }
  }
  return true;
}

bool Board::CanDoMove(const Move& move, const Player player) const
{
  if (move.Score())
  {
    FTRACE("Scores are always valid moves on a Board");
    return true;
  }
  //Deduce from square if not a castling nor score
  if (!move.From() && move.To())
  {
    assert(move.To());
    //Check all player's pieces if they can move to that location
    //Collect all moves that end in the Move::To()
    std::vector<boost::shared_ptr<Move> > moves = CompleteMove(move,player);
    if (moves.empty())
    {
      FTRACE("No moves with this destination");
      return false;
    }
    //The Move without a From is invalid if
    // * there is no valid move with that From
    // * there are more moves with that From
    std::vector<boost::shared_ptr<Move> > valid;
    std::copy_if(moves.begin(),moves.end(),std::back_inserter(valid),
      [this,player](const boost::shared_ptr<Move> m)
      {
        assert(m);
        return CanDoMove(*m,player);
      }
    );
    if (valid.empty())
    {
      FTRACE("No valid moves with this destination");
      return false;
    }
    if (valid.size() > 1)
    {
      FTRACE("Multiple moves possible to reach the destination square");
      std::for_each(valid.begin(),valid.end(),[](const boost::shared_ptr<Move> m) { TRACE(m); } );
      return false;
    }
    //There is exactly one Move found: test the complete move
    assert(valid[0]);
    return CanDoMove(*valid[0],player);
  }
  //Each move here is complete, i.e. a simple move has a from and to value
  if (move.From())
  {
    const ConstPiecePtr p = this->GetPiece(*move.From());
    assert(p);
    assert(p->GetSquare());
    assert(IsEqual(*p->GetSquare(),*move.From()));
    if (p->GetColor() != player)
    {
      FTRACE("Cannot move opponent's pieces");
      return false;
    }
    if (!p->CanDoMove(move))
    {
      FTRACE("Piece can never do this move");
      return false;
    }
    if (p->GetNameChar() != move.Piece()->GetNameChar())
    {
      FTRACE("There is a different Piece on the square than as indicated by the Move");
      return false;
    }
    #ifndef NDEBUG
    {
      assert(p->CanDoMove(move));
      boost::shared_ptr<Board> b(BoardFactory::DeepCopy(*this));
      assert(IsEqual(*b,*this));
      const ConstPiecePtr q = b->GetPiece(*move.From());
      assert(p);
      assert(q);
      assert(q && p);
      if (!IsEqual(*q,*p))
      {
        TRACE(p->ToStr());
        TRACE(q->ToStr());
        TRACE("BREAK");
      }
      assert(IsEqual(*q,*p));
      assert(q->CanDoMove(move));

    }
    #endif
    assert(move.Piece());
    if (move.Piece()->GetNameChar() != p->GetNameChar())
    {
      FTRACE("Type of piece in move is different than in reality");
      return false;
    }
    assert(move.From());
    assert(move.To());
    //Check for pieces blocking moves that span multiple squares
    if (!dynamic_cast<const PieceKnight*>(p.get()) && !EmptyBetween(*move.From(),*move.To()))
    {
      FTRACE("There are pieces blocking the move");
      return false;
    }
  }
  if (move.IsCastling())
  {
    assert(CanStrToCastling(move.GetStr()));
    const Castling castling = StrToCastling(move.GetStr());
    return CanDoCastling(castling,player);
  }
  //Check for capture
  if (move.To())
  {
    //Or it is a capture, or a move to an empty square
    if (move.IsCapture())
    {
      if (move.IsEnPassant())
      {
        //En-passant capture
        if (GetPiece(*move.To()))
        {
          FTRACE("Cannot en-passant capture an occupied square");
          return false;
        }
        ///TODO
        //Determine captured square

        //Can only do en passant if at the captured squares there's an opponent

        //Can only do en passant if at the captured squares there's an opponent that has moved the last turn
        return true;
      }
      else
      {
        //Regular capture
        if (!GetPiece(*move.To()))
        {
          FTRACE("Cannot capture an empty square");
          return false;
        }
        if (GetPiece(*move.To())->GetColor() == GetPiece(*move.From())->GetColor())
        {
          FTRACE("Cannot capture own piece");
          return false;
        }
      }
    }
    else
    {
      //Move is not a capture
      if (GetPiece(*move.To()))
      {
        FTRACE("Cannot move to an occupied square");
        return false;
      }
      if (move.IsEnPassant())
      {
        FTRACE("Cannot perform an en passant capture without the move being a capture");
        return false;
      }
    }
  }
  //Check if move puts opponent in check
  {
    boost::shared_ptr<Board> b(BoardFactory::DeepCopy(*this));
    if (move.From())
    {
      assert(move.From());
      assert(b->GetPiece(*move.From()));
      assert(b->GetPiece(*move.From())->CanDoMove(move));
      b->GetPiece(*move.From())->DoMove(move);
    }
    else
    {
      assert(move.IsCastling());
      assert(CanStrToCastling(move.GetStr()));
      const Castling castling = StrToCastling(move.GetStr());
      assert(CanDoCastling(castling,player));
      b->DoCastling(castling,player);
    }
    const bool check_in_real = b->IsCheck(player == Player::white ? Player::black : Player::white);
    if (check_in_real)
    {
      if (!move.IsCheck() && !move.IsCheckmate())
      {
        FTRACE("The move does not indicate a check, but in reality it does put the opponent into check");
        return false;
      }
    }
    else
    {
      //No check in reality
      if (move.IsCheck())
      {
        FTRACE("The move indicates a check, but it does not put opponent into check");
        return false;
      }
    }
  }

  //Check if move will put current player in check
  {
    boost::shared_ptr<Board> b(BoardFactory::DeepCopy(*this));
    if (move.From())
    {
      assert(move.From());
      assert(GetPiece(*move.From()));
      assert(b->GetPiece(*move.From()));
      assert(GetPiece(*move.From())->CanDoMove(move));
      assert(IsEqual(*b,*this));
      #ifndef NDEBUG
      if (!b->GetPiece(*move.From())->CanDoMove(move))
      {
        TRACE(*this);
        TRACE(b);
        TRACE(move);
      }

      #endif
      assert(b->GetPiece(*move.From())->CanDoMove(move));
      b->GetPiece(*move.From())->DoMove(move);
      //Does this check the player that tries do the move
    }
    else
    {
      assert(move.IsCastling());
      assert(CanStrToCastling(move.GetStr()));
      const Castling castling = StrToCastling(move.GetStr());
      assert(CanDoCastling(castling,player));
      b->DoCastling(castling,player);
    }
    if (b->IsCheck(player))
    {
      FTRACE("Move is forbidden, because it puts the current player into check");
      return false;
    }

  }
  //Check for move ending in checkmate
  {
    //Do move on cloned chessboard
    boost::shared_ptr<Board> b(BoardFactory::DeepCopy(*this));
    if (move.From())
    {
      assert(move.From());
      assert(b->GetPiece(*move.From()));
      b->GetPiece(*move.From())->DoMove(move);
    }
    else
    {
      assert(CanStrToCastling(move.GetStr()));
      boost::shared_ptr<Board> b(BoardFactory::DeepCopy(*this));
      const Castling castling = StrToCastling(move.GetStr());
      assert(b->CanDoCastling(castling,player));
      b->DoCastling(castling,player);
    }
    //Is opponent in checkmate?
    const bool checkmate_in_real = b->IsCheckmate(player == Player::white ? Player::black : Player::white);
    if (checkmate_in_real != move.IsCheckmate())
    {
      if (checkmate_in_real)
      {
        FTRACE("The move does not indicate a checkmate, but in reality it does put the opponent into checkmate");
      }
      else
      {
        FTRACE("The move indicates a checkmate, but it does not put opponent into checkmate");
      }
      return false;
    }
  }
  return true;
}

const std::vector<boost::shared_ptr<Move> > Board::CompleteMove(const Move& move, const Player player) const
{
  assert(!move.From());
  assert(move.To());
  assert(!move.Score());
  //Deduce from square if not a castling nor score

  //Check all player's pieces if they can move to that location
  //Collect all mives that end in the Move::To()
  std::vector<boost::shared_ptr<Move> > moves;
  //Check all Pieces
  std::for_each(m_pieces.begin(),m_pieces.end(),
    [&moves,this,&move,player](const PiecePtr& piece)
    {
      //Check for this player its pieces only that are of the same type as the move
      assert(move.Piece());
      if (piece->GetColor() == player && move.Piece()->GetNameChar() == piece->GetNameChar() )
      {
        //Obtain this right-colored piece its moves
        const std::vector<boost::shared_ptr<Move> > pms = piece->GetMoves();
        std::for_each(pms.begin(),pms.end(),
          [&moves,this,&move,player](const boost::shared_ptr<Move> n)
          {
            assert(n);
            //If the Move has a To, goes to the right To and is valid...
            if (n->To() && IsEqual(*n->To(),*move.To()) && this->CanDoMove(*n,player))
            {
              FTRACE(n);
              //Store this Move
              moves.push_back(n);
            }
          }
        );
      }
    }
  );
  return moves;
}


const std::vector<boost::shared_ptr<Square > > Board::CreateSquaresBetweenKingAndRook(
  const Player player,const Castling castling)
{
  std::vector<boost::shared_ptr<Square > > v;
  if (player == Player::white)
  {
    if (castling == Castling::kingside)
    {
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("f1");
        assert(s);
        v.push_back(s);
      }
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("g1");
        assert(s);
        v.push_back(s);
      }
    }
    else
    {
      assert(castling == Castling::queenside);
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("b1");
        assert(s);
        v.push_back(s);
      }
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("c1");
        assert(s);
        v.push_back(s);
      }
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("d1");
        assert(s);
        v.push_back(s);
      }
    }
  }
  else
  {
    assert(player == Player::black);
    if (castling == Castling::kingside)
    {
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("f8");
        assert(s);
        v.push_back(s);
      }
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("g8");
        assert(s);
        v.push_back(s);
      }
    }
    else
    {
      assert(castling == Castling::queenside);
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("b8");
        assert(s);
        v.push_back(s);
      }
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("c8");
        assert(s);
        v.push_back(s);
      }
      {
        const boost::shared_ptr<Square > s = SquareFactory::Create("d8");
        assert(s);
        v.push_back(s);
      }
    }
  }
  return v;
}

void Board::DoCastling(const Castling castling, const Player player)
{
  assert(CanDoCastling(castling,player));
  //Get King
  {
    const boost::shared_ptr<const Square> king_from_square
      = SquareFactory::Create(player == Player::white ? std::string("e1") : std::string("e8"));
    assert(king_from_square);
    //const Square king_to_square = (player == Player::white
    //  ? (castling == Castling::kingside ? Square("g1") : Square("c1"))
    //  : (castling == Castling::kingside ? Square("g8") : Square("c8")) );
    const PiecePtr king = GetPiece(*king_from_square);
    assert(king);
    const boost::shared_ptr<Chess::Move> castling_move
      = Chess::MoveFactory::Create(CastlingToStr(castling));
    assert(castling_move);
    king->DoMove(*castling_move);
  }
  //Check Rook
  {
    const boost::shared_ptr<Square> rook_square
      = SquareFactory::Create(player == Player::white
      ? (castling == Castling::kingside ? std::string("h1") : std::string("a1"))
      : (castling == Castling::kingside ? std::string("h8") : std::string("a8")) );
    assert(rook_square);
    const PiecePtr rook = GetPiece(*rook_square);
    assert(rook);
    const boost::shared_ptr<Chess::Move> castling_move
      = Chess::MoveFactory::Create(CastlingToStr(castling));
    assert(castling_move);
    rook->DoMove(*castling_move);
  }
}

void Board::DoMove(const Move& move,const Player player)
{
  assert(CanDoMove(move,player));
  if (!move.From() && move.To())
  {
    assert(move.To());
    //Check all player's pieces if they can move to that location
    //Collect all moves that end in the Move::To()
    std::vector<boost::shared_ptr<Move> > moves = CompleteMove(move,player);
    //The Move without a From is invalid if
    // * there is no valid move with that From
    // * there are more moves with that From
    assert(moves.size() == 1);
    //There is exactly one Move found: test the complete move
    assert(moves[0]);
    return DoMove(*moves[0],player);
  }

  if (move.From())
  {
    PiecePtr p = GetPiece(*move.From());
    assert(p);
    assert(p->CanDoMove(move));
    p->DoMove(move);
  }
  else if (move.IsCastling())
  {
    assert(CanStrToCastling(move.GetStr()));
    const Castling castling = StrToCastling( move.GetStr() );
    assert(CanDoCastling(castling,player));
    DoCastling(castling,player);
  }
  else
  {
    assert(!"Should not get here");
  }
}

bool Board::EmptyBetween(const Square& a, const Square& b) const
{
  const int dx = a.GetFile().ToInt() - b.GetFile().ToInt();
  const int dy = a.GetRank().ToInt() - b.GetRank().ToInt();
  //Are there squares in between to check for being occupied?
  assert(dx != 0 || dy != 0);
  //Squares are adjacent (horizontally, vertically or diagonally)
  if (dx + dy == 1) return true;

  const int step_x = (dx > 0 ? 1 : (dx < 0 ? -1 : 0));
  const int step_y = (dy > 0 ? 1 : (dy < 0 ? -1 : 0));
  const int n_steps = std::max(std::abs(dx),std::abs(dy));
  for (int i=1; i!=n_steps; ++i)
  {
    const int x = b.GetFile().ToInt() + (i * step_x);
    const int y = b.GetRank().ToInt() + (i * step_y);
    assert(x >= 0);
    assert(y >= 0);
    assert(x  < 8);
    assert(y  < 8);
    const boost::shared_ptr<const Square> square = SquareFactory::Create(File(x),Rank(y));
    assert(square);
    assert(!IsEqual(*square,a));
    assert(!IsEqual(*square,b));
    if (this->GetPiece(*square)) return false;
  }
  return true;
}

//Color Board::GetActivePlayer() const
//{
//  return (m_moves.size() % 2 ? Color::black : Color::white);
//}

const Board::PiecePtr Board::GetPiece(const Square& square)
{
  const auto i = std::find_if(m_pieces.begin(),m_pieces.end(),
    [&square](const PiecePtr& p)
    {
      return IsEqual(*p->GetSquare(),square);
    }
  );

  if (i == m_pieces.end()) { Board::PiecePtr p; assert(!p); return p; }
  else { assert(*i); return *i; }
}

const Board::ConstPiecePtr Board::GetPiece(const Square& square) const
{
  const auto i = std::find_if(m_pieces.begin(),m_pieces.end(),
    [&square](const PiecePtr& p)
    {
      return IsEqual(*p->GetSquare(),square);
    }
  );

  if (i == m_pieces.end()) { Board::ConstPiecePtr p; assert(!p); return p; }
  else
  {
    Board::ConstPiecePtr p(*i);
    assert(p);
    assert(IsEqual(*p->GetSquare(),square));
    assert(IsEqual(*p, *(*i)));
    assert(p->GetSquare());
    return p;
  }
}

const Board::ConstPieces Board::GetPieces() const
{
  return AddConst(this->GetPieces());
  /*
  ConstPieces v;
  std::transform(m_pieces.begin(),m_pieces.end(),std::inserter(v,v.begin()),
    [](const Board::PiecePtr& piece)
    {
      ConstPiecePtr p = piece->Clone();
      assert(IsEqual(*p,*piece));
      assert(p != piece);
      return p;
    }
  );
  return v;
  */
}

const Board::Pieces Board::GetInitialSetup()
{
  //C++0x initializer list
  Board::Pieces v;
  const auto colors { Color::black, Color::white };
  std::for_each(colors.begin(),colors.end(),
    [&v](const Color color)
    {
      //Pawns
      {
        const Chess::Rank rank = color == Color::white ? Rank(2) : Rank(7);
        for (int i=0; i!=8; ++i)
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File(i),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('.',color,*s);
          assert(p);
          v.insert(p);
        }
      }
      {
        //Royalty
        const Chess::Rank rank = color == Color::white ? Rank(1) : Rank(8);
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("a"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('R',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("b"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('N',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("c"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('B',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("d"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('Q',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("e"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('K',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("f"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('B',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("g"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('N',color,*s);
          assert(p);
          v.insert(p);
        }
        {
          const boost::shared_ptr<Square> s(SquareFactory::Create(Chess::File("h"),rank));
          assert(s);
          const boost::shared_ptr<Piece> p = PieceFactory::Create('R',color,*s);
          assert(p);
          v.insert(p);
        }
      }
    }
  );
  return v;
}

const std::vector<boost::shared_ptr<Move> > Board::GetMoves(const Player player) const
{
  std::vector<boost::shared_ptr<Move> > v;

  std::for_each(m_pieces.begin(),m_pieces.end(),
    [this,&v,player](const PiecePtr& p)
    {
      if (p->GetColor() == player)
      {
        assert(p->GetSquare());

        //Obtain all valid moves from the square the piece is standing on
        const std::vector<boost::shared_ptr<Move> > w = this->GetMoves(*p->GetSquare());

        std::copy(w.begin(),w.end(),std::back_inserter(v));
      }
    }
  );

  return v;
}

const std::vector<boost::shared_ptr<Move> > Board::GetMoves(const Square& square) const
{
  const ConstPiecePtr piece = GetPiece(square);
  ///TODO: In Traitor's Chess you can move Pieces of the opponent
  //if (!piece || piece->GetColor() != this->GetActivePlayer()) return std::vector<boost::shared_ptr<Move> >();
  if (!piece) return std::vector<boost::shared_ptr<Move> >();
  const Player player = ColorToPlayer(piece->GetColor());

  const std::vector<boost::shared_ptr<Move> > all_moves = piece->GetMoves();
  std::vector<boost::shared_ptr<Move> > moves;
  std::copy_if(all_moves.begin(), all_moves.end(),
    std::back_inserter(moves),
    [this,player](const boost::shared_ptr<Move> move)
    {
      assert(move);
      return this->CanDoMove(*move,player);
    }
  );
  return moves;
}

const std::string Board::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> Board::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

const BitBoard Board::GetVisibleSquares(const Player player) const
{
  //Collect the Pieces we want to know their sights of
  std::vector<PiecePtr> pieces;
  std::copy_if(m_pieces.begin(), m_pieces.end(),
   std::back_inserter(pieces),
    [player](const PiecePtr& p)
    {
      return p->GetColor() == player;
    }
  );
  //Collect the Squares the Pieces can move to on a BitBoard
  Chess::BitBoard b;
  std::for_each(
    pieces.begin(),pieces.end(),
    [this,&b](const PiecePtr& p)
    {
      assert(p->GetSquare());
      const std::vector<boost::shared_ptr<Move> > moves = this->GetMoves(*p->GetSquare());
      std::for_each(moves.begin(),moves.end(),
        [&b](const boost::shared_ptr<Move> m)
        {
          assert(m->To());
          b.Set(*m->To(),true);
        }
      );
      //Copy the locations of the pieces
      b.Set(*p->GetSquare(),true);
    }
  );
  return b;
}

bool Board::IsCheck(const Player player) const
{
  //Find the king of the player
  const auto king_ptr = std::find_if(
    m_pieces.begin(),m_pieces.end(),
    [player,this](const Chess::Board::PiecePtr& p)
    {
      return p->GetColor() == player
        && dynamic_cast<PieceKing*>(p.get());
    }
  );
  //No King, so this player cannot be in check
  if (king_ptr == m_pieces.end())
  {
    FTRACE("No king");
    return false;
  }

  const PiecePtr king = *king_ptr;
  assert(king);

  //Collect the visible squares seen from the opponent
  //DO NOT USE GETVISIBLESQUARES: THIS LEADS TO RECURSION

  //Check if an opponent's piece looks at the current player's King
  const int cnt = std::count_if(m_pieces.begin(),m_pieces.end(),
    [king,this](const Chess::Board::PiecePtr& p)
    {
      assert(p);
      //Must not be of same color
      if (p->GetColor() == king->GetColor()) return false;
      //There must be a Move to the King's square
      const auto moves = p->GetMoves();
      const auto move = std::find_if(moves.begin(),moves.end(),
        [king](const boost::shared_ptr<Move> m)
        {
          return IsEqual(*m->To(),*king->GetSquare());
        }
      );
      if (move == moves.end()) return false;
      //A Knight always makes a successful attack
      if (dynamic_cast<PieceKnight*>(p.get())) return true;
      //All squares between King and attacker must be empty
      assert(king->GetSquare());
      assert(p->GetSquare());
      return EmptyBetween(*king->GetSquare(),*p->GetSquare());
    }
  );

  //Return if there is at least one piece attacking the King
  return cnt > 0;
}

bool Board::IsCheckmate(const Player player) const
{
  if (!IsCheck(player))
  {
    FTRACE("Move is no checkmate, because the king is not in check");
    return false;
  }

  //Find the king of the player
  const auto king_ptr = std::find_if(
    m_pieces.begin(),m_pieces.end(),
    [player,this](const Chess::Board::PiecePtr& p)
    {
      return p->GetColor() == player
        && dynamic_cast<PieceKing*>(p.get());
    }
  );
  //No King, so this player cannot be in check
  if (king_ptr == m_pieces.end())
  {
    TRACE("No king");
    return false;
  }

  //Get all moves
  const std::vector<boost::shared_ptr<Move> > moves = GetMoves(player);

  //Check if all of them end in check
  const int cnt = std::count_if(moves.begin(),moves.end(),
    [this,player](const boost::shared_ptr<Move> move)
    {
      boost::shared_ptr<Board> b(BoardFactory::DeepCopy(*this));
      assert(move);
      assert(b->CanDoMove(*move,player));
      //if (!b.CanDoMove(move,player)) return false;
      b->DoMove(*move,player);
      if (b->IsCheck(player)) return false;
      return true;
    }
  );

  //If there are no possible moves, player is in checkmate
  if (cnt > 0)
  {
    FTRACE("Opponent can escape checkmate");
  }
  return cnt == 0;
}

/*
bool Board::IsValid(const boost::shared_ptr<Move> move) const
{
  assert(move.To());
  //Check if non-Knight Piece does not go through occupied squares
  if (move.Piece() && !dynamic_cast<PieceKnight*>(move.Piece().get())
    && ( std::abs(move.To()->GetFile().ToInt() - move.From()->GetFile().ToInt()) > 1
      || std::abs(move.To()->GetRank().ToInt() - move.From()->GetRank().ToInt()) > 1)
    )
  {
    const int dx = move.To()->GetFile().ToInt() - move.From()->GetFile().ToInt();
    const int dy = move.To()->GetRank().ToInt() - move.From()->GetRank().ToInt();
    const int step_x = (dx > 0 ? 1 : (dx < 0 ? -1 : 0));
    const int step_y = (dy > 0 ? 1 : (dy < 0 ? -1 : 0));
    const int n_steps = std::max(std::abs(dx),std::abs(dy));
    for (int i=1; i!=n_steps; ++i)
    {
      const int x = move.From()->GetFile().ToInt() + (i * step_x);
      const int y = move.From()->GetRank().ToInt() + (i * step_y);
      if (GetPiece(Square(File(x),Rank(y)))) return false;
    }
  }
  //If the move is a capture, but there is nothing to capture, the move is invalid in this context
  if (move.IsCapture() && !GetPiece(*move.To())) return false;
  //If the square to move to is occupied...
  if (GetPiece(*move.To()))
  {
    //Cannot capture a piece of own color
    ///TODO But this is possible in Cannibal Chess
    //if (GetPiece(*move.To())->GetColor() == GetActivePlayer()) return false;

    if (GetPiece(*move.From())->GetColor() != GetPiece(*move.To())->GetColor()) return move.IsCapture();
  }
  //move.IsCapture
  //move.IsCastling()

  //Does move result in the player ending in check?
  return true;
}
*/

bool IsEqual(const Board& lhs, const Board& rhs)
{
  //if (lhs.GetMoveHistory() != rhs.GetMoveHistory())
  //{
  //  return false;
  //}
  return IsEqual(lhs.GetPieces(),rhs.GetPieces());
}


bool IsEqual(const Board::ConstPieces& lhs,const Board::ConstPieces& rhs)
{
  if (lhs.size() != rhs.size()) return false;
  //Count unfound pieces
  return std::count_if(lhs.begin(),lhs.end(),
    [rhs](const Board::ConstPiecePtr& p)
    {
      assert(std::count_if(rhs.begin(),rhs.end(),
        [p](const Board::ConstPiecePtr& q)
        {
          return IsEqual(*p,*q);
        }
      ) < 2);

      return std::count_if(rhs.begin(),rhs.end(),
        [p](const Board::ConstPiecePtr& q)
        {
          return IsEqual(*p,*q);
        }
      ) == 1;
    }
  ) == static_cast<int>(lhs.size());
}


std::ostream& operator<<(std::ostream& os, const Board& board)
{
  const int maxx = 8;
  const int maxy = 8;

  boost::multi_array<std::string, 2> v(boost::extents[maxx][maxy]);
  for (int y=0;y!=maxy;++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      if (((x+y)%2)==0)
      {
        v[x][y] = "..";
      }
      else
      {
        v[x][y] = "__";
      }
    }
  }
  std::for_each(board.m_pieces.begin(),board.m_pieces.end(),
    [&v](const Board::PiecePtr& piece)
    {
      assert(piece);
      assert(piece->GetSquare());
      const int x = piece->GetSquare()->GetFile().ToInt();
      const int y = piece->GetSquare()->GetRank().ToInt();
      const std::string s
        = std::string(piece->GetColor() == Color::white ? "w" : "b")
        + boost::lexical_cast<std::string>(piece->GetNameChar());
      v[x][y] = s;
    }
  );

  for (int y=0;y!=maxy;++y)
  {
    for (int x=0; x!=maxx; ++x)
    {
      os << " " << v[x][y];
    }
    os << "\n";
  }

  return os;
}

} //~ namespace Chess


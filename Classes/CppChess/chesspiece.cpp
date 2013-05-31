#include "chesspiece.h"

#include <cassert>
#include <iostream>

#ifdef SADC_USE_THREADS
#include <thread>
#endif

#include "chesscolor.h"
#include "chessmove.h"
#include "chessmovefactory.h"
#include "chessmoves.h"
#include "chesssquarefactory.h"
#include "chessrank.h"
#include "chesssquare.h"

#include "trace.h"

namespace Chess {

Piece::Piece(
  const Color color,
  const boost::shared_ptr<Square> &square)
 : m_color(color),
   m_square(square)
{
  #ifndef NDEBUG
  Piece::Test();
  #endif
}

const std::vector<boost::shared_ptr<Move> > Piece::AddCheckAndCheckmate(const std::vector<boost::shared_ptr<Move> >& v)
{
  std::vector<boost::shared_ptr<Move> > w;
  std::for_each(v.begin(),v.end(),
    [&w](const boost::shared_ptr<Move>& move)
    {
      assert(move);
      assert(!move->IsCheck());
      assert(!move->IsCheckmate());
      //assert(!move->IsScore());
      w.push_back(move);
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          move->ToStr() + std::string("+")
        );
        assert(m);
        w.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          move->ToStr() + std::string("#")
        );
        assert(m);
        w.push_back(m);
      }
    }
  );
  assert(w.size() == v.size() * 3);
  return w;
}

void Piece::DoMove(const Chess::Move& move)
{
  assert(CanDoMove(move));
  m_square = move.To();
  m_last_move = MoveFactory::DeepCopy(move);
}

Color Piece::GetColor() const
{
  return m_color;
}

const boost::shared_ptr<Square>& Piece::GetSquare() const
{
  return m_square;
}

const std::string Piece::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> Piece::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

const std::string Piece::ToStr() const
{
  return Chess::ColorToStr(GetColor())
    + std::string(" ")
    + this->GetName()
    + " at "
    + (this->GetSquare() ? this->GetSquare()->ToStr() : "an indetermined position");
}

PieceBishop::PieceBishop(
  const Color color,
  const boost::shared_ptr<Square>& square)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);
}

bool PieceBishop::CanDoMove(const Chess::Move& move) const
{
  if (!move.Piece() || !dynamic_cast<PieceBishop*>(move.Piece().get()))
  {
    //Not a Bishop move
    return false;
  }
  assert(
    (
         (!move.From() && !GetSquare())
      || (move.From() && !GetSquare())
      || (move.From() && GetSquare() && IsEqual(*move.From(),*this->GetSquare()))
    )
    && "Assume Move and Bishop to have the same start position");
  assert(move.Piece() && dynamic_cast<PieceBishop*>(move.Piece().get())
    && "Assume this is a Bishop move");
  assert(move.To() && "All Bishop moves have a to field");
  assert(!move.IsCastling() && "Bishop moves are not castling moves");
  assert(!move.Score() && "Bishop moves are not final scores");


  if (move.From())
  {
    const int dx = move.From()->GetFile().ToInt() - move.To()->GetFile().ToInt();
    if (dx == 0) return false;
    const int dy = move.From()->GetRank().ToInt() - move.To()->GetRank().ToInt();
    return std::abs(dx) == std::abs(dy);
  }
  else
  {
    return move.To();
  }
}

const boost::shared_ptr<Piece> PieceBishop::Clone() const
{
  const Color color = this->GetColor();
  assert(this->GetSquare());
  const boost::shared_ptr<Square> square = SquareFactory::DeepCopy(*this->GetSquare());
  assert(square);
  const boost::shared_ptr<Piece> p(new PieceBishop(color,square));
  assert(p);
  return p;
}

const std::vector<boost::shared_ptr<Move> > PieceBishop::GetMoves() const
{
  std::vector<boost::shared_ptr<Move> > v;
  for (int i=1; i!=8; ++i)
  {
    //North-east
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() - i)
      );
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr()
        );
        v.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + "x" + s->ToStr()
        );
        assert(m);
        v.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr() + "+"
        );
        assert(m);
        v.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + "x" + s->ToStr() + "+"
        );
        assert(m);
        v.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr() + "#"
        );
        assert(m);
        v.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + "x" + s->ToStr() + "#"
        );
        assert(m);
        v.push_back(m);
      }
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //South-east
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + i)
      );
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      assert(m);
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //South-west
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() - i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //North-west
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() - i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() - i)
      );
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }

  }
  //Triple number of moves by adding check and checkmate
  v = AddCheckAndCheckmate(v);

  return v;
}

/*
PieceEmpty::PieceEmpty()
  : Piece(Color::indeterminate,Square(0,0))
{
  assert(GetColor() == Color::indeterminate);
}

const std::vector<Square> PieceEmpty::GetMoves() const
{
  return std::vector<Square>();
}

bool PieceEmpty::CanDoMove(const Chess::Move& move) const
{

}
*/

PieceKing::PieceKing(
  const Color color,
  const boost::shared_ptr<Square>& square)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);

}

bool PieceKing::CanDoMove(const Chess::Move& move) const
{
  if (!move.Piece() || !dynamic_cast<PieceKing*>(move.Piece().get()))
  {
    //Not a King move
    return false;
  }
  assert(
    (
         (!move.From() && !GetSquare())
      || (move.From() && !GetSquare())
      || (move.From() && GetSquare() && IsEqual(*move.From(),*this->GetSquare()))
    )
    && "Assume Move and Piece to have the same start position");
  assert(move.Piece() && dynamic_cast<Piece*>(move.Piece().get())
    && "Assume this is a King move");
  assert(move.To() && "All King moves have a to field");
  assert(!move.IsCastling() && "King moves are not castling moves");
  assert(!move.Score() && "King moves are not final scores");

  if (move.From())
  {
    const int dx = move.From()->GetFile().ToInt() - move.To()->GetFile().ToInt();
    const int dy = move.From()->GetRank().ToInt() - move.To()->GetRank().ToInt();

    if (dx == 0 && dy == 0) return false;
    return std::abs(dx) <= 1 && std::abs(dy) <= 1;
  }
  else
  {
    return move.To();
  }
}

const boost::shared_ptr<Piece> PieceKing::Clone() const
{
  const boost::shared_ptr<Piece> p(new PieceKing(*this));
  return p;
}

const std::vector<boost::shared_ptr<Move> > PieceKing::GetMoves() const
{
  std::vector<boost::shared_ptr<Move> > v;
  std::vector<std::pair<int,int> > ds
    = { {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1} };
  std::for_each(ds.begin(), ds.end(),
    [&v,this](const std::pair<int,int>& p)
    {
      try
      {
        const boost::shared_ptr<Square> s = SquareFactory::Create(
          Chess::File(this->GetSquare()->GetFile().ToInt() + p.first),
          Chess::Rank(this->GetSquare()->GetRank().ToInt() + p.second)
        );

        boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar())
          + this->GetSquare()->ToStr()
          + " "
          + s->ToStr());
        v.push_back(m);
      }
      catch (std::exception& e)
      {
        //No problem
      }
    }
  );
  //Triple number of moves by adding check and checkmate
  v = AddCheckAndCheckmate(v);
  return v;
}

PieceKnight::PieceKnight(
  const Chess::Color color,
  const boost::shared_ptr<Square>& square)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);

}

bool PieceKnight::CanDoMove(const Chess::Move& move) const
{
  if (!move.Piece() || !dynamic_cast<PieceKnight*>(move.Piece().get()))
  {
    //Not a Knight move
    return false;
  }
  assert(
    (
         (!move.From() && !GetSquare())
      || (move.From() && !GetSquare())
      || (move.From() && GetSquare() && IsEqual(*move.From(),*this->GetSquare()))
    )
    && "Assume Move and Knight to have the same start position");
  assert(move.Piece() && dynamic_cast<PieceKnight*>(move.Piece().get())
    && "Assume this is a Knight move");
  assert(move.To() && "All Knight moves have a to field");
  assert(!move.IsCastling() && "Knight moves are not castling moves");
  assert(!move.Score() && "Knight moves are not final scores");

  if (move.From())
  {
    const int dx = move.From()->GetFile().ToInt() - move.To()->GetFile().ToInt();
    const int dy = move.From()->GetRank().ToInt() - move.To()->GetRank().ToInt();
    return
         (std::abs(dx) == 1 || std::abs(dx) == 2)
      && (std::abs(dy) == 1 || std::abs(dy) == 2)
      &&  std::abs(dx) != std::abs(dy);
  }
  else
  {
    return true;
  }
}

const boost::shared_ptr<Piece> PieceKnight::Clone() const
{
  const boost::shared_ptr<Piece> p(new PieceKnight(*this));
  return p;
}

const std::vector<boost::shared_ptr<Move> > PieceKnight::GetMoves() const
{
  std::vector<boost::shared_ptr<Move> > v;
  std::vector<std::pair<int,int> > ds
    = { {1,2}, {2,1}, {-1,2}, {-2,1}, {1,-2}, {2,-1}, {-1,-2}, {-2,-1} };
  std::for_each(ds.begin(), ds.end(),
    [&v,this](const std::pair<int,int>& p)
    {
      try
      {
        const boost::shared_ptr<Square> s = SquareFactory::Create(
          Chess::File(this->GetSquare()->GetFile().ToInt() + p.first),
          Chess::Rank(this->GetSquare()->GetRank().ToInt() + p.second)
        );

        boost::shared_ptr<Move> m = MoveFactory::Create(
          boost::lexical_cast<std::string>(this->GetNameChar())
          + this->GetSquare()->ToStr()
          + " "
          + s->ToStr());
        v.push_back(m);
      }
      catch (std::exception& e)
      {
        //No problem
      }
    }
  );
  //Triple number of moves by adding check and checkmate
  v = AddCheckAndCheckmate(v);
  return v;
}

PiecePawn::PiecePawn(
  const Color color,
  const boost::shared_ptr<Square>& square)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);
}

bool PiecePawn::CanDoMove(const Chess::Move& move) const
{
  if (!move.Piece() || !dynamic_cast<PiecePawn*>(move.Piece().get()))
  {
    //Not a Pawn move
    return false;
  }

  assert(
    (
         (!move.From() && !GetSquare())
      || (move.From() && !GetSquare())
      || (move.From() && GetSquare() && IsEqual(*move.From(),*this->GetSquare()))
    )
    && "Assume Move and PiecePawn to have the same start position");
  assert(move.Piece() && dynamic_cast<PiecePawn*>(move.Piece().get())
    && "Assume this is a Pawn move");
  assert(move.To() && "All Pawn moves have a to field");
  assert(!move.IsCastling() && "Pawn moves are not castling moves");
  assert((!move.IsEnPassant() || (move.IsEnPassant() && move.IsCapture()))
    && "Assume that all en passant captures are captures");

  //Do all checks when the 'from' Square is known
  if (move.From())
  {
    const int dx = move.To()->GetFile().ToInt() - move.From()->GetFile().ToInt();
    if (std::abs(dx) > 1) return false;
    if (std::abs(dx) == 1 && !move.IsCapture()) return false;
    if (dx == 0 && move.IsCapture()) return false;

    const int dy = move.To()->GetRank().ToInt() - move.From()->GetRank().ToInt();
    if (std::abs(dy) > 2) return false; //A pawn move two squares at most

    if (this->GetColor() == Color::white)
    {
      if (dy <= 0) return false; //A white pawn must move forward
      if (move.From()->GetRank() == Rank(std::string("2")) && dy == 2) return true;
      if (!(move.From()->GetRank() == Rank(std::string("2"))) && dy == 2) return false;
      return dy == 1;
    }
    else if (this->GetColor() == Color::black)
    {
      if (dy >= 0) return false; //A black pawn must move backward in the y direction
      if (move.From()->GetRank() == Rank(std::string("7")) && dy == -2) return true;
      if (!(move.From()->GetRank() == Rank(std::string("7"))) && dy == -2) return false;
      return dy == -1;
    }
    else if (this->GetColor() == Color::indeterminate)
    {
      if (move.From()->GetRank() == Rank(std::string("2")) && dy ==  2) return true;
      if (move.From()->GetRank() == Rank(std::string("7")) && dy == -2) return true;
      if (!(move.From()->GetRank() == Rank(std::string("2"))) && dy ==  2) return false;
      if (!(move.From()->GetRank() == Rank(std::string("7"))) && dy == -2) return false;
    }
  }

  if (move.IsEnPassant())
  {
    if (!move.IsCapture()) return false;
    if (GetColor() == Color::indeterminate)
    {
      return
        (move.From()->GetRank().ToStr() == std::string("4")
          && move.To()->GetRank().ToStr() == std::string("3"))
        || ( move.From()->GetRank().ToStr() == std::string("5")
          && move.To()->GetRank().ToStr() == std::string("6"));
    }
    if (GetColor() == Color::white)
    {
      return ( move.From()->GetRank().ToStr() == std::string("5")
          && move.To()->GetRank().ToStr() == std::string("6"));
    }
    if (GetColor() == Color::black)
    {
      return move.From()->GetRank().ToStr() == std::string("4")
          && move.To()->GetRank().ToStr() == std::string("3");
    }
  }

  //Pawn moves in the right direction when from is known
  if (this->GetColor() == Color::white && move.To()->GetRank() == Chess::Rank("1"))
  {
    return false;
  }
  if (this->GetColor() == Color::black && move.To()->GetRank() == Chess::Rank("8"))
  {
    return false;
  }

  if (move.To()->GetRank() == Chess::Rank("1") || move.To()->GetRank() == Chess::Rank("8"))
  {
    return move.IsPromotion();
  }
  return true;
}

const boost::shared_ptr<Piece> PiecePawn::Clone() const
{
  const boost::shared_ptr<Piece> p(new PiecePawn(*this));
  return p;
}

const std::vector<boost::shared_ptr<Move> > PiecePawn::GetMoves() const
{
  std::vector<boost::shared_ptr<Move> > v;

  std::vector<std::pair<int,int> > ds;
  if (GetColor() != Color::black)
  {
    //Add white moves
    ds.push_back( {  0, 2 } );
    ds.push_back( {  0, 1 } );
    ds.push_back( { -1, 1 } );
    ds.push_back( {  1, 1 } );
  }
  if (GetColor() != Color::white)
  {
    //Add black moves
    ds.push_back( {  0,-2 } );
    ds.push_back( {  0,-1 } );
    ds.push_back( { -1,-1 } );
    ds.push_back( {  1,-1 } );
  }

  std::for_each(ds.begin(), ds.end(),
    [&v,this](const std::pair<int,int>& p)
    {
      try
      {
        const boost::shared_ptr<Square> s = SquareFactory::Create(
          Chess::File(this->GetSquare()->GetFile().ToInt() + p.first),
          Chess::Rank(this->GetSquare()->GetRank().ToInt() + p.second)
        );

        //TRACE(p.first); TRACE(p.second);
        boost::shared_ptr<Move> m = MoveFactory::Create(this->GetSquare()->ToStr()
          + (p.first == 0 ? std::string(" ") : std::string("x"))
          + s->ToStr());
        //TRACE(m);
        v.push_back(m);
      }
      catch (std::exception& e)
      {
        //TRACE(e.what());
        //No problem
      }
    }
  );
  //Triple number of moves by adding check and checkmate
  v = AddCheckAndCheckmate(v);
  return v;
}

PieceQueen::PieceQueen(
  const Color color,
  const boost::shared_ptr<Square>& square)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);

}

bool PieceQueen::CanDoMove(const Chess::Move& move) const
{
  if (!move.Piece() || !dynamic_cast<PieceQueen*>(move.Piece().get()))
  {
    //Not a Queen move
    return false;
  }
  assert(
    (
         (!move.From() && !GetSquare())
      || (move.From() && !GetSquare())
      || (move.From() && GetSquare() && IsEqual(*move.From(),*this->GetSquare()))
    )
    && "Assume Move and Queen to have the same start position");
  assert(move.Piece() && dynamic_cast<PieceQueen*>(move.Piece().get())
    && "Assume this is a Queen move");
  assert(move.To() && "All Queen moves have a to field");
  assert(!move.IsCastling() && "Queen moves are not castling moves");
  assert(!move.Score() && "Queen moves are not final scores");

  if (move.From())
  {
    const int dx = move.From()->GetFile().ToInt() - move.To()->GetFile().ToInt();
    const int dy = move.From()->GetRank().ToInt() - move.To()->GetRank().ToInt();
    if (dx == 0 && dy == 0) return false;
    return (dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy));
  }
  else
  {
    return true;
  }
}

const boost::shared_ptr<Piece> PieceQueen::Clone() const
{
  const boost::shared_ptr<Piece> p(new PieceQueen(*this));
  return p;
}

const std::vector<boost::shared_ptr<Move> > PieceQueen::GetMoves() const
{
  std::vector<boost::shared_ptr<Move> > v;
  for (int i=1; i!=8; ++i)
  {
    //North
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + 0),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() - i)
      );
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //North-east
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() - i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //East
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + 0));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //South-east
    try
    {

      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //South
    try
    {

      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + 0),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //South-west
    try
    {

      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() - i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //West
    try
    {

      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() - i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + 0));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //North-west
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() - i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() - i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }

  }
  //Triple number of moves by adding check and checkmate
  v = AddCheckAndCheckmate(v);
  return v;
}

PieceRook::PieceRook(
  const Color color,
  const boost::shared_ptr<Square>& square)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);

}

bool PieceRook::CanDoMove(const Chess::Move& move) const
{
  if (!move.Piece() || !dynamic_cast<PieceRook*>(move.Piece().get()))
  {
    //Not a Rook move
    return false;
  }
  assert(
    (
         (!move.From() && !GetSquare())
      || (move.From() && !GetSquare())
      || (move.From() && GetSquare() && IsEqual(*move.From(),*this->GetSquare()))
    )
    && "Assume Move and Rook to have the same start position");
  assert(move.Piece() && dynamic_cast<PieceRook*>(move.Piece().get())
    && "Assume this is a Rook move");
  assert(move.To() && "All Rook moves have a to field");
  assert(!move.IsCastling() && "Rook moves are not castling moves");
  assert(!move.Score() && "Rook moves are not final scores");

  if (move.IsEnPassant()) return false;

  if (move.From())
  {
    const int dx = move.From()->GetFile().ToInt() - move.To()->GetFile().ToInt();
    const int dy = move.From()->GetRank().ToInt() - move.To()->GetRank().ToInt();
    if (dx == 0 && dy == 0) return false;
    return (dx == 0 || dy == 0);
  }
  else
  {
    return true;
  }
}

const boost::shared_ptr<Piece> PieceRook::Clone() const
{
  const boost::shared_ptr<Piece> p(new PieceRook(*this));
  return p;
}

const std::vector<boost::shared_ptr<Move> > PieceRook::GetMoves() const
{
  std::vector<boost::shared_ptr<Move> > v;
  for (int i=1; i!=8; ++i)
  {
    //North
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + 0),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() - i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //East
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + 0));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //South
    try
    {
      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() + 0),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + i));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
    //West
    try
    {

      const boost::shared_ptr<Square> s = SquareFactory::Create(
        Chess::File(this->GetSquare()->GetFile().ToInt() - i),
        Chess::Rank(this->GetSquare()->GetRank().ToInt() + 0));
      const boost::shared_ptr<Move> m = MoveFactory::Create(boost::lexical_cast<std::string>(this->GetNameChar()) + this->GetSquare()->ToStr() + " " + s->ToStr());
      v.push_back(m);
    }
    catch (std::exception& e)
    {
      //No problem
    }
  }
  //Triple number of moves by adding check and checkmate
  v = AddCheckAndCheckmate(v);
  return v;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
  os << piece.ToStr();
  return os;
}

bool IsEqual(const Piece& lhs, const Piece& rhs)
{
  if (lhs.m_color != rhs.m_color) return false;
  if (static_cast<bool>(lhs.m_last_move) != static_cast<bool>(rhs.m_last_move)) return false;
  if (lhs.m_last_move)
  {
    assert(rhs.m_last_move);
    if (*lhs.m_last_move != *rhs.m_last_move)
    {
      return false;
    }
  }
  if (static_cast<bool>(lhs.m_square) != static_cast<bool>(rhs.m_square))
  {
    return false;
  }
  if (lhs.m_square)
  {
    assert(rhs.m_square);
    if (!IsEqual(*lhs.m_square,*rhs.m_square))
    {
      return false;
    }
  }
  return true;
}

} //~ namespace Chess


#include "chesspiece.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>

#include "chesscolor.h"
#include "chessmove.h"
#include "chessmovefactory.h"
#include "chessmoves.h"
#include "chesspiecefactory.h"
#include "chesssquarefactory.h"
#include "chessrank.h"
#include "chesssquare.h"

#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::Piece::Piece(
  const Color color,
  const boost::shared_ptr<const Square> &square)
 : m_color(color),
   m_last_move{},
   m_square(square)
{
  #ifndef NDEBUG
  ribi::Chess::Piece::Test();
  #endif
}

const std::vector<boost::shared_ptr<ribi::Chess::Move> >
  ribi::Chess::Piece::AddCheckAndCheckmate(const std::vector<boost::shared_ptr<Move> >& v)
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
          move->ToStr() + "+"
        );
        assert(m);
        w.push_back(m);
      }
      {
        const boost::shared_ptr<Move> m = MoveFactory::Create(
          move->ToStr() + "#"
        );
        assert(m);
        w.push_back(m);
      }
    }
  );
  assert(w.size() == v.size() * 3);
  return w;
}

void ribi::Chess::Piece::DoMove(const boost::shared_ptr<const Move> move)
{
  assert(CanDoMove(move));
  m_square = move->To();
  m_last_move = move;
}

ribi::Chess::Color ribi::Chess::Piece::GetColor() const noexcept
{
  return m_color;
}

boost::shared_ptr<const ribi::Chess::Square> ribi::Chess::Piece::GetSquare() const noexcept
{
  return m_square;
}

std::string ribi::Chess::Piece::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Chess::Piece::GetVersionHistory() noexcept
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}

std::string ribi::Chess::Piece::ToStr() const noexcept
{
  return Chess::ColorToStr(GetColor())
    + " "
    + this->GetName()
    + " at "
    + (this->GetSquare() ? this->GetSquare()->ToStr() : "an indetermined position");
}

ribi::Chess::PieceBishop::PieceBishop(
  const Color color,
  const boost::shared_ptr<const Square> square,
  const PieceFactory&
)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);
}

bool ribi::Chess::PieceBishop::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const noexcept
{
  if (!move->Piece() || !dynamic_cast<PieceBishop*>(move->Piece().get()))
  {
    //Not a Bishop move
    return false;
  }
  assert(
    (
         (!move->From() && !GetSquare())
      || (move->From() && !GetSquare())
      || (move->From() && GetSquare() && *move->From() == *this->GetSquare()  )
    )
    && "Assume Move and Bishop to have the same start position");
  assert(move->Piece() && dynamic_cast<PieceBishop*>(move->Piece().get())
    && "Assume this is a Bishop move");
  assert(move->To() && "All Bishop moves have a to field");
  assert(!move->IsCastling() && "Bishop moves are not castling moves");
  assert(!move->Score() && "Bishop moves are not final scores");


  if (move->From())
  {
    const int dx = move->From()->GetFile().ToInt() - move->To()->GetFile().ToInt();
    if (dx == 0) return false;
    const int dy = move->From()->GetRank().ToInt() - move->To()->GetRank().ToInt();
    return std::abs(dx) == std::abs(dy);
  }
  else
  {
    return move->To().get();
  }
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceBishop::Clone() const
{
  const auto p = PieceFactory().Create(GetNameChar(),GetColor(),GetSquare());
  assert(p);
  assert(*p       == *this && "Must be a copy");
  assert( p.get() !=  this && "Must be a deep copy");
  return p;
}

std::vector<boost::shared_ptr<ribi::Chess::Move> > ribi::Chess::PieceBishop::GetMoves() const noexcept
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

bool PieceEmpty::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const
{

}
*/

ribi::Chess::PieceKing::PieceKing(
  const Color color,
  const boost::shared_ptr<const Square> square,
  const PieceFactory&
)
  : Piece(color,square),
    m_has_moved{false}

{
  //assert(GetColor() != Color::indeterminate);

}

bool ribi::Chess::PieceKing::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const noexcept
{
  if (!move->Piece() || !dynamic_cast<PieceKing*>(move->Piece().get()))
  {
    //Not a King move
    return false;
  }
  assert(
    (
         (!move->From() && !GetSquare())
      || (move->From() && !GetSquare())
      || (move->From() && GetSquare() && *move->From() == *this->GetSquare())
    )
    && "Assume Move and Piece to have the same start position");
  assert(move->Piece() && dynamic_cast<Piece*>(move->Piece().get())
    && "Assume this is a King move");
  assert(move->To() && "All King moves have a to field");
  assert(!move->IsCastling() && "King moves are not castling moves");
  assert(!move->Score() && "King moves are not final scores");

  if (move->From())
  {
    const int dx = move->From()->GetFile().ToInt() - move->To()->GetFile().ToInt();
    const int dy = move->From()->GetRank().ToInt() - move->To()->GetRank().ToInt();

    if (dx == 0 && dy == 0) return false;
    return std::abs(dx) <= 1 && std::abs(dy) <= 1;
  }
  else
  {
    return move->To().get();
  }
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceKing::Clone() const
{
  //const boost::shared_ptr<Piece> p(new PieceKing(*this));
  const auto p = PieceFactory().Create(GetNameChar(),GetColor(),GetSquare());
  assert(p);
  assert(*p == *this && "Must be a copy");
  assert( p.get() !=  this && "Must be a deep copy");
  return p;
}

std::vector<boost::shared_ptr<ribi::Chess::Move> > ribi::Chess::PieceKing::GetMoves() const noexcept
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

ribi::Chess::PieceKnight::PieceKnight(
  const Chess::Color color,
  const boost::shared_ptr<const Square> square,
  const PieceFactory&
)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);

}

bool ribi::Chess::PieceKnight::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const noexcept
{
  if (!move->Piece() || !dynamic_cast<PieceKnight*>(move->Piece().get()))
  {
    //Not a Knight move
    return false;
  }
  assert(
    (
         (!move->From() && !GetSquare())
      || (move->From() && !GetSquare())
      || (move->From() && GetSquare() && (*move->From() == *this->GetSquare()))
    )
    && "Assume Move and Knight to have the same start position");
  assert(move->Piece() && dynamic_cast<PieceKnight*>(move->Piece().get())
    && "Assume this is a Knight move");
  assert(move->To() && "All Knight moves have a to field");
  assert(!move->IsCastling() && "Knight moves are not castling moves");
  assert(!move->Score() && "Knight moves are not final scores");

  if (move->From())
  {
    const int dx = move->From()->GetFile().ToInt() - move->To()->GetFile().ToInt();
    const int dy = move->From()->GetRank().ToInt() - move->To()->GetRank().ToInt();
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

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceKnight::Clone() const
{
  //const boost::shared_ptr<Piece> p(new PieceKnight(*this));
  const auto p = PieceFactory().Create(GetNameChar(),GetColor(),GetSquare());
  assert(p);
  assert(*p == *this && "Must be a copy");
  assert( p.get() !=  this && "Must be a deep copy");
  return p;
}

std::vector<boost::shared_ptr<ribi::Chess::Move> > ribi::Chess::PieceKnight::GetMoves() const noexcept
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

ribi::Chess::PiecePawn::PiecePawn(
  const Color color,
  const boost::shared_ptr<const Square> square,
  const PieceFactory&
)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);
}

bool ribi::Chess::PiecePawn::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const noexcept
{
  if (!move->Piece() || !dynamic_cast<PiecePawn*>(move->Piece().get()))
  {
    //Not a Pawn move
    return false;
  }

  assert(
    (
         (!move->From() && !GetSquare())
      || (move->From() && !GetSquare())
      || (move->From() && GetSquare() && (*move->From() == *this->GetSquare()))
    )
    && "Assume Move and PiecePawn to have the same start position");
  assert(move->Piece() && dynamic_cast<PiecePawn*>(move->Piece().get())
    && "Assume this is a Pawn move");
  assert(move->To() && "All Pawn moves have a to field");
  assert(!move->IsCastling() && "Pawn moves are not castling moves");
  assert((!move->IsEnPassant() || (move->IsEnPassant() && move->IsCapture()))
    && "Assume that all en passant captures are captures");

  //Do all checks when the 'from' Square is known
  if (move->From())
  {
    const int dx = move->To()->GetFile().ToInt() - move->From()->GetFile().ToInt();
    if (std::abs(dx) > 1) return false;
    if (std::abs(dx) == 1 && !move->IsCapture()) return false;
    if (dx == 0 && move->IsCapture()) return false;

    const int dy = move->To()->GetRank().ToInt() - move->From()->GetRank().ToInt();
    if (std::abs(dy) > 2) return false; //A pawn move two squares at most

    if (this->GetColor() == Color::white)
    {
      if (dy <= 0) return false; //A white pawn must move forward
      if (move->From()->GetRank() == Rank("2") && dy == 2) return true;
      if (!(move->From()->GetRank() == Rank("2")) && dy == 2) return false;
      return dy == 1;
    }
    else if (this->GetColor() == Color::black)
    {
      if (dy >= 0) return false; //A black pawn must move backward in the y direction
      if (move->From()->GetRank() == Rank("7") && dy == -2) return true;
      if (!(move->From()->GetRank() == Rank("7")) && dy == -2) return false;
      return dy == -1;
    }
    else if (this->GetColor() == Color::indeterminate)
    {
      if (move->From()->GetRank() == Rank("2") && dy ==  2) return true;
      if (move->From()->GetRank() == Rank("7") && dy == -2) return true;
      if (!(move->From()->GetRank() == Rank("2")) && dy ==  2) return false;
      if (!(move->From()->GetRank() == Rank("7")) && dy == -2) return false;
    }
  }

  if (move->IsEnPassant())
  {
    if (!move->IsCapture()) return false;
    if (GetColor() == Color::indeterminate)
    {
      return
        (move->From()->GetRank().ToStr() == "4"
          && move->To()->GetRank().ToStr() == "3")
        || ( move->From()->GetRank().ToStr() == "5"
          && move->To()->GetRank().ToStr() == "6");
    }
    if (GetColor() == Color::white)
    {
      return ( move->From()->GetRank().ToStr() == "5"
          && move->To()->GetRank().ToStr() == "6");
    }
    if (GetColor() == Color::black)
    {
      return move->From()->GetRank().ToStr() == "4"
          && move->To()->GetRank().ToStr() == "3";
    }
  }

  //Pawn moves in the right direction when from is known
  if (this->GetColor() == Color::white && move->To()->GetRank() == Chess::Rank("1"))
  {
    return false;
  }
  if (this->GetColor() == Color::black && move->To()->GetRank() == Chess::Rank("8"))
  {
    return false;
  }

  if (move->To()->GetRank() == Chess::Rank("1") || move->To()->GetRank() == Chess::Rank("8"))
  {
    return move->IsPromotion();
  }
  return true;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PiecePawn::Clone() const
{
  //const boost::shared_ptr<Piece> p(new PiecePawn(*this));
  const auto p = PieceFactory().Create(GetNameChar(),GetColor(),GetSquare());
  assert(p);
  assert(*p == *this && "Must be a copy");
  assert( p.get() !=  this && "Must be a deep copy");
  return p;
}

std::vector<boost::shared_ptr<ribi::Chess::Move> > ribi::Chess::PiecePawn::GetMoves() const noexcept
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
          + (p.first == 0 ? " " : "x")
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

ribi::Chess::PieceQueen::PieceQueen(
  const Color color,
  const boost::shared_ptr<const Square> square,
  const PieceFactory&
)
  : Piece(color,square)
{
  //assert(GetColor() != Color::indeterminate);

}

bool ribi::Chess::PieceQueen::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const noexcept
{
  if (!move->Piece() || !dynamic_cast<PieceQueen*>(move->Piece().get()))
  {
    //Not a Queen move
    return false;
  }
  assert(
    (
         (!move->From() && !GetSquare())
      || (move->From() && !GetSquare())
      || (move->From() && GetSquare() && (*move->From() == *this->GetSquare()))
    )
    && "Assume Move and Queen to have the same start position");
  assert(move->Piece() && dynamic_cast<PieceQueen*>(move->Piece().get())
    && "Assume this is a Queen move");
  assert(move->To() && "All Queen moves have a to field");
  assert(!move->IsCastling() && "Queen moves are not castling moves");
  assert(!move->Score() && "Queen moves are not final scores");

  if (move->From())
  {
    const int dx = move->From()->GetFile().ToInt() - move->To()->GetFile().ToInt();
    const int dy = move->From()->GetRank().ToInt() - move->To()->GetRank().ToInt();
    if (dx == 0 && dy == 0) return false;
    return (dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy));
  }
  else
  {
    return true;
  }
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceQueen::Clone() const
{
  //const boost::shared_ptr<Piece> p(new PieceQueen(*this));
  const auto p = PieceFactory().Create(GetNameChar(),GetColor(),GetSquare());
  assert(p);
  assert(*p == *this && "Must be a copy");
  assert( p.get() !=  this && "Must be a deep copy");
  return p;
}

std::vector<boost::shared_ptr<ribi::Chess::Move> > ribi::Chess::PieceQueen::GetMoves() const noexcept
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

ribi::Chess::PieceRook::PieceRook(
  const Color color,
  const boost::shared_ptr<const Square> square,
  const PieceFactory&
)
  : Piece(color,square),
    m_has_moved{false}
{
  //assert(GetColor() != Color::indeterminate);

}

bool ribi::Chess::PieceRook::CanDoMove(const boost::shared_ptr<const Chess::Move> move) const noexcept
{
  if (!move->Piece() || !dynamic_cast<PieceRook*>(move->Piece().get()))
  {
    //Not a Rook move
    return false;
  }
  assert(
    (
         (!move->From() && !GetSquare())
      || (move->From() && !GetSquare())
      || (move->From() && GetSquare() && (*move->From() == *this->GetSquare()))
    )
    && "Assume Move and Rook to have the same start position");
  assert(move->Piece() && dynamic_cast<PieceRook*>(move->Piece().get())
    && "Assume this is a Rook move");
  assert(move->To() && "All Rook moves have a to field");
  assert(!move->IsCastling() && "Rook moves are not castling moves");
  assert(!move->Score() && "Rook moves are not final scores");

  if (move->IsEnPassant()) return false;

  if (move->From())
  {
    const int dx = move->From()->GetFile().ToInt() - move->To()->GetFile().ToInt();
    const int dy = move->From()->GetRank().ToInt() - move->To()->GetRank().ToInt();
    if (dx == 0 && dy == 0) return false;
    return (dx == 0 || dy == 0);
  }
  else
  {
    return true;
  }
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceRook::Clone() const
{
  //const boost::shared_ptr<Piece> p(new PieceRook(*this));
  const auto p = PieceFactory().Create(GetNameChar(),GetColor(),GetSquare());
  assert(p);
  assert(*p == *this && "Must be a copy");
  assert( p.get() !=  this && "Must be a deep copy");
  return p;
}

std::vector<boost::shared_ptr<ribi::Chess::Move> > ribi::Chess::PieceRook::GetMoves() const noexcept
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

std::ostream& ribi::Chess::operator<<(std::ostream& os, const Piece& piece)
{
  os << piece.ToStr();
  return os;
}

bool ribi::Chess::operator==(const Piece& lhs, const Piece& rhs)
{

  if (lhs.GetColor() != rhs.GetColor()) return false;

  if (static_cast<bool>(lhs.GetLastMove()) != static_cast<bool>(rhs.GetLastMove())) return false;
  if (lhs.GetLastMove())
  {
    assert(rhs.GetLastMove());
    if (*lhs.GetLastMove() != *rhs.GetLastMove())
    {
      return false;
    }
  }
  if (static_cast<bool>(lhs.GetSquare()) != static_cast<bool>(rhs.GetSquare()))
  {
    return false;
  }
  if (lhs.GetSquare())
  {
    assert(rhs.GetSquare());
    if (*lhs.GetSquare() != *rhs.GetSquare())
    {
      return false;
    }
  }
  return true;
}

bool ribi::Chess::operator!=(const Piece& lhs, const Piece& rhs)
{
  return !(lhs == rhs);
}

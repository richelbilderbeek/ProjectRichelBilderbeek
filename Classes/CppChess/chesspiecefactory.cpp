#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "chesspiecefactory.h"

#include <stdexcept>

#include "chessmove.h"
#include "chessmovefactory.h"
#include "chesspiece.h"
#include "chesssquarefactory.h"
#pragma GCC diagnostic pop

const boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::Create(
  const char namechar,
  const Color color,
  const boost::shared_ptr<const Square> square) noexcept
{
  assert(square);
  boost::shared_ptr<Piece> p;
  switch(namechar)
  {
    case 'B': p.reset(new Chess::PieceBishop(color,square)); break;
    case 'K': p.reset(new Chess::PieceKing(color,square)); break;
    case 'N': p.reset(new Chess::PieceKnight(color,square)); break;
    case 'Q': p.reset(new Chess::PieceQueen(color,square)); break;
    case 'R': p.reset(new Chess::PieceRook(color,square)); break;
    case '.': p.reset(new Chess::PiecePawn(color,square)); break;
    default: assert(!"Should not get here");
  }
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::Create(
  const char namechar,
  const Color color,
  const std::string& square_str)
{
  const boost::shared_ptr<const Square> square {
    SquareFactory::Create(square_str)
  };
  assert(square);
  boost::shared_ptr<Piece> p;
  return Create(namechar,color,square);
}

const boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::CreateFromMove(const std::string& s)
{
  if (s.empty()) throw std::logic_error("ribi::Chess::PieceFactory::CreateFromMove exception: move must not be empty");
  const boost::shared_ptr<Move> move {
    MoveFactory::Create(s)
  };
  boost::shared_ptr<const Square> square {
    move->To()
  };
  if (!square) square = move->From();

  boost::shared_ptr<Piece> piece;
  const char c = s[0];
  switch(c)
  {
    case 'B': piece.reset(new Chess::PieceBishop(Chess::Color::indeterminate,square)); break;
    case 'K': piece.reset(new Chess::PieceKing(Chess::Color::indeterminate,square)); break;
    case 'N': piece.reset(new Chess::PieceKnight(Chess::Color::indeterminate,square)); break;
    case 'Q': piece.reset(new Chess::PieceQueen(Chess::Color::indeterminate,square)); break;
    case 'R': piece.reset(new Chess::PieceRook(Chess::Color::indeterminate,square)); break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
      piece.reset(new Chess::PiecePawn(Chess::Color::indeterminate,square)); break;
  }
  return piece;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::CreateFromPromotion(const std::string& s)
{
  if (s.empty()) throw std::logic_error("ribi::Chess::PieceFactory::CreateFromPromotion exception: move must not be empty");

  boost::shared_ptr<Chess::Piece> p;

  const char c = s[s.size() - 1];
  switch(c)
  {
    case 'B': p.reset(new Chess::PieceBishop(Chess::Color::indeterminate,boost::shared_ptr<Square>())); break;
    case 'K': p.reset(new Chess::PieceKing(Chess::Color::indeterminate,boost::shared_ptr<Square>())); break;
    case 'N': p.reset(new Chess::PieceKnight(Chess::Color::indeterminate,boost::shared_ptr<Square>())); break;
    case 'Q': p.reset(new Chess::PieceQueen(Chess::Color::indeterminate,boost::shared_ptr<Square>())); break;
    case 'R': p.reset(new Chess::PieceRook(Chess::Color::indeterminate,boost::shared_ptr<Square>())); break;
  }
  assert(p);
  return p;
}

const boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::DeepCopy(
  const boost::shared_ptr<const Piece> s) noexcept
{
  const boost::shared_ptr<ribi::Chess::Piece> t {
    PieceFactory::Create(
      s->GetNameChar(),
      s->GetColor(),
      s->GetSquare()
    )
  };
  assert(t);
  assert(*s == *t && "Must be a copy");
  assert(s != t && "Must be a deep copy");
  return t;
}

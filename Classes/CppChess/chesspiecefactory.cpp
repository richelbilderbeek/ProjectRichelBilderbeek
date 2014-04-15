#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "chesspiecefactory.h"

#include <stdexcept>

#include <boost/make_shared.hpp>

#include "chessmove.h"
#include "chessmovefactory.h"
#include "chesspiece.h"
#include "chesssquarefactory.h"
#pragma GCC diagnostic pop

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::Create(
  const char namechar,
  const Color color,
  const boost::shared_ptr<const Square> square) const noexcept
{
  assert(square);
  boost::shared_ptr<Piece> p;
  switch(namechar)
  {
    case 'B': return CreateBishop(color,square);
    case 'K': return CreateKing(color,square);
    case 'N': return CreateKnight(color,square);
    case 'Q': return CreateQueen(color,square);
    case 'R': return CreateRook(color,square);
    case '.': return CreatePawn(color,square);
    default: assert(!"Should not get here");
  }
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::Create(
  const char namechar,
  const Color color,
  const std::string& square_str
) const noexcept
{
  const boost::shared_ptr<const Square> square {
    SquareFactory::Create(square_str)
  };
  assert(square);
  boost::shared_ptr<Piece> p;
  return Create(namechar,color,square);
}

boost::shared_ptr<ribi::Chess::PieceBishop> ribi::Chess::PieceFactory::CreateBishop(
  const Color color,
  const boost::shared_ptr<const Square> square
) const noexcept
{
  //Cannot use boost::make_shared here, because I fail at making
  //boost::make_shared a friend
  const boost::shared_ptr<PieceBishop> p(
    new PieceBishop(color,square,*this)
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::CreateFromMove(
  const Color color,
  const std::string& s
) const noexcept
{
  if (s.empty()) throw std::logic_error("ribi::Chess::PieceFactory().CreateFromMove exception: move must not be empty");
  const boost::shared_ptr<Move> move {
    MoveFactory::Create(s)
  };
  #ifdef TODO_ISSUE_176
  assert(move);
  #else
  if (!move) throw std::logic_error("ribi::Chess::PieceFactory().CreateFromMove exception: move empty");
  #endif
  boost::shared_ptr<const Square> square {
    move->To()
  };
  if (!square) square = move->From();

  boost::shared_ptr<Piece> piece;
  const char c = s[0];
  switch(c)
  {
    case 'B': return CreateBishop(color,square);
    case 'K': return CreateKing(color,square);
    case 'N': return CreateKnight(color,square);
    case 'Q': return CreateQueen(color,square);
    case 'R': return CreateRook(color,square);
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
      return CreatePawn(color,square);
  }
  return piece;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::CreateFromPromotion(const std::string& s
) const noexcept
{
  if (s.empty()) throw std::logic_error("ribi::Chess::PieceFactory().CreateFromPromotion exception: move must not be empty");

  boost::shared_ptr<Chess::Piece> p;

  const char c = s[s.size() - 1];
  switch(c)
  {
    case 'B': return CreateBishop(Chess::Color::indeterminate,boost::shared_ptr<Square>());
    case 'K': return CreateKing(Chess::Color::indeterminate,boost::shared_ptr<Square>());
    case 'N': return CreateKnight(Chess::Color::indeterminate,boost::shared_ptr<Square>());
    case 'Q': return CreateQueen(Chess::Color::indeterminate,boost::shared_ptr<Square>());
    case 'R': return CreateRook(Chess::Color::indeterminate,boost::shared_ptr<Square>());
  }
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::PieceKing> ribi::Chess::PieceFactory::CreateKing(
  const Color color,
  const boost::shared_ptr<const Square> square
) const noexcept
{
  //Cannot use boost::make_shared here, because I fail at making
  //boost::make_shared a friend
  const boost::shared_ptr<PieceKing> p(
    new PieceKing(color,square,*this)
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::PieceKnight> ribi::Chess::PieceFactory::CreateKnight(
  const Color color,
  const boost::shared_ptr<const Square> square
) const noexcept
{
  //Cannot use boost::make_shared here, because I fail at making
  //boost::make_shared a friend
  const boost::shared_ptr<PieceKnight> p(
    new PieceKnight(color,square,*this)
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::PiecePawn> ribi::Chess::PieceFactory::CreatePawn(
  const Color color,
  const boost::shared_ptr<const Square> square
) const noexcept
{
  //Cannot use boost::make_shared here, because I fail at making
  //boost::make_shared a friend
  const boost::shared_ptr<PiecePawn> p(
    new PiecePawn(color,square,*this)
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::PieceQueen> ribi::Chess::PieceFactory::CreateQueen(
  const Color color,
  const boost::shared_ptr<const Square> square
) const noexcept
{
  //Cannot use boost::make_shared here, because I fail at making
  //boost::make_shared a friend
  const boost::shared_ptr<PieceQueen> p(
    new PieceQueen(color,square,*this)
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::PieceRook> ribi::Chess::PieceFactory::CreateRook(
  const Color color,
  const boost::shared_ptr<const Square> square
) const noexcept
{
  //Cannot use boost::make_shared here, because I fail at making
  //boost::make_shared a friend
  const boost::shared_ptr<PieceRook> p(
    new PieceRook(color,square,*this)
  );
  assert(p);
  return p;
}

boost::shared_ptr<ribi::Chess::Piece> ribi::Chess::PieceFactory::DeepCopy(
  const boost::shared_ptr<const Piece> original_piece
) const noexcept
{
  const auto cloned_piece(
    PieceFactory().Create(
      original_piece->GetNameChar(),
      original_piece->GetColor(),
      original_piece->GetSquare()
    )
  );
  assert(cloned_piece);
  assert(*original_piece == *cloned_piece && "Must be a copy");
  assert(original_piece != cloned_piece && "Must be a deep copy");
  return cloned_piece;
}

#include "chesspiecefactory.h"

#include "chesspiece.h"
namespace Chess {

boost::shared_ptr<Piece> Create(const char namechar,const Color color,const Square& square)
{
  boost::shared_ptr<Piece> p;
  switch(c)
  {
    case 'B': p.reset(new Chess::PieceBishop(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'K': p.reset(new Chess::PieceKing(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'N': p.reset(new Chess::PieceKnight(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'Q': p.reset(new Chess::PieceQueen(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'R': p.reset(new Chess::PieceRook(Chess::Color::indeterminate,ParseFrom(s))); break;
    case '.': p.reset(new Chess::PiecePawn(Chess::Color::indeterminate,ParseFrom(s))); break;
    default: assert(!"Should not get here");
  }
  assert(p);
  return p;
}

boost::shared_ptr<Piece> PieceFactory::CreateFromMove(const std::string& s)
{
  if (s.empty()) throw std::logic_error("PieceFactory::CreateFromMove exception: move must not be empty");

  const char c = s[0];
  switch(c)
  {
    case 'B': p.reset(new Chess::PieceBishop(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'K': p.reset(new Chess::PieceKing(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'N': p.reset(new Chess::PieceKnight(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'Q': p.reset(new Chess::PieceQueen(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'R': p.reset(new Chess::PieceRook(Chess::Color::indeterminate,ParseFrom(s))); break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
      p.reset(new Chess::PiecePawn(Chess::Color::indeterminate,ParseFrom(s))); break;
  }
}

boost::shared_ptr<Piece> PieceFactory::CreateFromPromotion(const std::string& s)
{
  if (s.empty()) throw std::logic_error("PieceFactory::CreateFromPromotion exception: move must not be empty");

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

} //~namespace Chess

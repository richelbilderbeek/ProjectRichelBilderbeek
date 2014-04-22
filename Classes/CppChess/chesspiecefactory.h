#ifndef CHESSPIECEFACTORY_H
#define CHESSPIECEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "chessfwd.h"
#include "chesscolor.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

struct PieceFactory
{
  PieceFactory() {}

  boost::shared_ptr<Piece> Create(
    const char namechar,
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  //For convenience
  boost::shared_ptr<Piece> Create(
    const char namechar,
    const Color color,
    const std::string& square
  ) const noexcept;

  boost::shared_ptr<PieceBishop> CreateBishop(
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  boost::shared_ptr<PieceKing> CreateKing(
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  boost::shared_ptr<PieceKnight> CreateKnight(
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  boost::shared_ptr<PiecePawn> CreatePawn(
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  boost::shared_ptr<PieceQueen> CreateQueen(
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  boost::shared_ptr<PieceRook> CreateRook(
    const Color color,
    const boost::shared_ptr<const Square> square
  ) const noexcept;

  boost::shared_ptr<Piece> CreateFromMove(
    const Color color,
    const std::string& s
  ) const noexcept;

  boost::shared_ptr<Piece> CreateFromPromotion(const std::string& s) const noexcept;

  boost::shared_ptr<Piece> DeepCopy(const boost::shared_ptr<const Piece> piece) const noexcept;
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSPIECEFACTORY_H

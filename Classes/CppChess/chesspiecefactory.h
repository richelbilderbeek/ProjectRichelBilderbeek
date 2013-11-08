#ifndef CHESSPIECEFACTORY_H
#define CHESSPIECEFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "chessfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

struct PieceFactory
{
  static boost::shared_ptr<Piece> Create(
    const char namechar,
    const Color color,
    const boost::shared_ptr<const Square> square) noexcept;
  static boost::shared_ptr<Piece> Create(
    const char namechar,
    const Color color,
    const std::string& square);

  static const boost::shared_ptr<Piece> CreateFromMove(const std::string& s);

  static boost::shared_ptr<Piece> CreateFromPromotion(const std::string& s);

  static boost::shared_ptr<PieceBishop> CreateBishop(const Color color,const boost::shared_ptr<Square>& square) noexcept;
  static boost::shared_ptr<PieceBishop> CreateBishop(const Color color,const std::string& square);

  static boost::shared_ptr<PieceKnight> CreateKnight(const Color color,const boost::shared_ptr<Square>& square) noexcept;
  static boost::shared_ptr<PieceKnight> CreateKnight(const Color color,const std::string& square);

  static boost::shared_ptr<PiecePawn> CreatePawn(const Color color,const boost::shared_ptr<Square>& square) noexcept;
  static boost::shared_ptr<PiecePawn> CreatePawn(const Color color,const std::string& square);

  static boost::shared_ptr<PieceRook> CreateRook(const Color color,const std::string& square);
  static boost::shared_ptr<PieceRook> CreateRook(const Color color,const boost::shared_ptr<Square>& square) noexcept;

  static boost::shared_ptr<Piece> DeepCopy(const Piece& piece);
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSPIECEFACTORY_H

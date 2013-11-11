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
  static const boost::shared_ptr<Piece> Create(
    const char namechar,
    const Color color,
    const boost::shared_ptr<const Square> square) noexcept;

  static const boost::shared_ptr<Piece> Create(
    const char namechar,
    const Color color,
    const std::string& square);

  static const boost::shared_ptr<Piece> CreateFromMove(const std::string& s);

  static boost::shared_ptr<Piece> CreateFromPromotion(const std::string& s);

  static const boost::shared_ptr<Piece> DeepCopy(const boost::shared_ptr<const Piece> piece) noexcept;
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSPIECEFACTORY_H

#ifndef CHESSPIECEFACTORY_H
#define CHESSPIECEFACTORY_H

#include <boost/shared_ptr.hpp>
#include "chessfwd.h"

namespace Chess {

struct PieceFactory
{
  static boost::shared_ptr<Piece> Create(const char namechar,const Color color,const Square& square);
  static boost::shared_ptr<Piece> Create(const char namechar,const Color color,const std::string& square);

  static boost::shared_ptr<Piece> CreateFromMove(const std::string& s);

  static boost::shared_ptr<Piece> CreateFromPromotion(const std::string& s);

  static boost::shared_ptr<Piece> CreateKnight(const Color color,const Square& square);
  static boost::shared_ptr<Piece> CreateKnight(const Color color,const boost::shared_ptr<Square>& square);

  static boost::shared_ptr<Piece> CreatePawn(const Color color,const Square& square);
  static boost::shared_ptr<Piece> CreatePawn(const Color color,const boost::shared_ptr<Square>& square);

  static boost::shared_ptr<Piece> DeepCopy(const Piece& piece);
};

} //~namespace Chess

#endif // CHESSPIECEFACTORY_H

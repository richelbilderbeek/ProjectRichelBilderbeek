#ifndef RIBI_CHESSCASTLING_H
#define RIBI_CHESSCASTLING_H

#include <iosfwd>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/xpressive/xpressive.hpp>

#include "chessfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

enum class Castling { kingside, queenside };

std::string CastlingToStr(const Castling castling);
bool CanStrToCastling(const std::string& s);
const boost::xpressive::sregex GetCastlingRegex();
//const Square GetCastlingKingSquare(const Castling castling, const Player player);
//const Square GetCastlingRookSquare(const Castling castling, const Player player);
Castling StrToCastling(const std::string& s);

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSCASTLING_H

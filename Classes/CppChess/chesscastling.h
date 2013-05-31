#ifndef CHESSCASTLING_H
#define CHESSCASTLING_H

#include <iosfwd>
#include <vector>

#include <boost/regex.hpp>

#include "chessfwd.h"

namespace Chess {

enum class Castling { kingside, queenside };

const std::string CastlingToStr(const Castling castling);
bool CanStrToCastling(const std::string& s);
const boost::regex GetCastlingRegex();
//const Square GetCastlingKingSquare(const Castling castling, const Player player);
//const Square GetCastlingRookSquare(const Castling castling, const Player player);
Castling StrToCastling(const std::string& s);

} //~namespace Chess

#endif // CHESSCASTLING_H

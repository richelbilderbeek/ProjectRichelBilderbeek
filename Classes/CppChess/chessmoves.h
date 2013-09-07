#ifndef CHESSMOVES_H
#define CHESSMOVES_H

#include <string>
#include <vector>
#include "chesscolor.h"

namespace ribi {
namespace Chess {

///Moves is a stateless struct containing collections of moves
struct Moves
{

  //All moves in the
  //'Kasparov against the world match'
  //http://en.wikipedia.org/wiki/Kasparov_versus_the_World
  static const std::vector<std::string> GetGameKasparovVersusTheWorld();

  //Game in which white wins by checkmate in three moves
  static const std::vector<std::string> GetGameShephardsMate();

  ///Obtain invalid moves that can be performed by a bishop
  static const std::vector<std::string> GetInvalidBishopMoves();

  ///Obtain invalid moves that involve a capture
  static const std::vector<std::string> GetInvalidCaptureMoves();

  ///Obtain invalid castling moves
  static const std::vector<std::string> GetInvalidCastlingMoves();

  ///Obtain invalid moves that result in check
  static const std::vector<std::string> GetInvalidCheckMoves();

  ///Obtain invalid moves that result in checkmate
  static const std::vector<std::string> GetInvalidCheckmateMoves();

  ///Obtain invalid en passant moves
  static const std::vector<std::string> GetInvalidEnPassantMoves();

  ///Obtain invalid moves that can be performed by a king
  static const std::vector<std::string> GetInvalidKingMoves();

  ///Obtain invalid moves that can be performed by a knight
  static const std::vector<std::string> GetInvalidKnightMoves();

  ///Obtain invalid moves that can be performed by a pawn
  static const std::vector<std::string> GetInvalidPawnMoves(const Chess::Color& color);

  ///Obtain invalid moves that end in a promotion
  static const std::vector<std::string> GetInvalidPromotionMoves();

  ///Obtain invalid moves that can be performed by a queen
  static const std::vector<std::string> GetInvalidQueenMoves();

  ///Obtain invalid moves that can be performed by a rook
  static const std::vector<std::string> GetInvalidRookMoves();

  ///Obtain all moves that can be performed by a bishop
  static const std::vector<std::string> GetValidBishopMoves();

  ///Obtain moves that involve a capture
  static const std::vector<std::string> GetValidCaptureMoves();

  ///Obtain all castling moves
  static const std::vector<std::string> GetValidCastlingMoves();

  ///Obtain valid moves that result in check
  static const std::vector<std::string> GetValidCheckMoves();

  ///Obtain valid moves that result in checkmate
  static const std::vector<std::string> GetValidCheckmateMoves();

  ///Obtain en passant moves
  static const std::vector<std::string> GetValidEnPassantMoves();

  ///Obtain all moves that can be performed by a king
  static const std::vector<std::string> GetValidKingMoves();

  ///Obtain all moves that can be performed by a knight
  static const std::vector<std::string> GetValidKnightMoves();

  ///Obtain all moves that can be performed by a pawn
  static const std::vector<std::string> GetValidPawnMoves(const Chess::Color& color);

  ///Obtain moves that end in a promotion
  static const std::vector<std::string> GetValidPromotionMoves();

  ///Obtain all moves that can be performed by a queen
  static const std::vector<std::string> GetValidQueenMoves();

  ///Obtain all moves that can be performed by a rook
  static const std::vector<std::string> GetValidRookMoves();

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();
};

} //~namespace Chess
} //~namespace ribi

#endif // CHESSMOVES_H

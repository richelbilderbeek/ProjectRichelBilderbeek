#ifndef RIBI_CHESSMOVES_H
#define RIBI_CHESSMOVES_H

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
  static std::vector<std::string> GetGameKasparovVersusTheWorld() noexcept;

  //Game in which white wins by checkmate in three moves
  static std::vector<std::string> GetGameShephardsMate() noexcept;

  ///Obtain invalid moves that can be performed by a bishop
  static std::vector<std::string> GetInvalidBishopMoves() noexcept;

  ///Obtain invalid moves that involve a capture
  static std::vector<std::string> GetInvalidCaptureMoves() noexcept;

  ///Obtain invalid castling moves
  static std::vector<std::string> GetInvalidCastlingMoves() noexcept;

  ///Obtain invalid moves that result in check
  static std::vector<std::string> GetInvalidCheckMoves() noexcept;

  ///Obtain invalid moves that result in checkmate
  static std::vector<std::string> GetInvalidCheckmateMoves() noexcept;

  ///Obtain invalid en passant moves
  static std::vector<std::string> GetInvalidEnPassantMoves() noexcept;

  ///Obtain invalid moves that can be performed by a king
  static std::vector<std::string> GetInvalidKingMoves() noexcept;

  ///Obtain invalid moves that can be performed by a knight
  static std::vector<std::string> GetInvalidKnightMoves() noexcept;

  ///Obtain invalid moves that can be performed by a pawn
  static std::vector<std::string> GetInvalidPawnMoves(const Chess::Color& color) noexcept;

  ///Obtain invalid moves that end in a promotion
  static std::vector<std::string> GetInvalidPromotionMoves() noexcept;

  ///Obtain invalid moves that can be performed by a queen
  static std::vector<std::string> GetInvalidQueenMoves() noexcept;

  ///Obtain invalid moves that can be performed by a rook
  static std::vector<std::string> GetInvalidRookMoves() noexcept;

  ///Obtain all moves that can be performed by a bishop
  static std::vector<std::string> GetValidBishopMoves() noexcept;

  ///Obtain moves that involve a capture
  static std::vector<std::string> GetValidCaptureMoves() noexcept;

  ///Obtain all castling moves
  static std::vector<std::string> GetValidCastlingMoves() noexcept;

  ///Obtain valid moves that result in check
  static std::vector<std::string> GetValidCheckMoves() noexcept;

  ///Obtain valid moves that result in checkmate
  static std::vector<std::string> GetValidCheckmateMoves() noexcept;

  ///Obtain en passant moves
  static std::vector<std::string> GetValidEnPassantMoves() noexcept;

  ///Obtain all moves that can be performed by a king
  static std::vector<std::string> GetValidKingMoves() noexcept;

  ///Obtain all moves that can be performed by a knight
  static std::vector<std::string> GetValidKnightMoves() noexcept;

  ///Obtain all moves that can be performed by a pawn
  static std::vector<std::string> GetValidPawnMoves(const Chess::Color& color) noexcept;

  ///Obtain moves that end in a promotion
  static std::vector<std::string> GetValidPromotionMoves() noexcept;

  ///Obtain all moves that can be performed by a queen
  static std::vector<std::string> GetValidQueenMoves() noexcept;

  ///Obtain all moves that can be performed by a rook
  static std::vector<std::string> GetValidRookMoves() noexcept;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;
};

} //~namespace Chess
} //~namespace ribi

#endif // RIBI_CHESSMOVES_H

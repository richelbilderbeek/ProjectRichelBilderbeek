#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <iosfwd>
#include <memory>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/xpressive/xpressive_fwd.hpp>
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "chesssquare.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

struct Move
{
  ///Parses a Move from char* (not yet supported by GCC)
  ///Move(const char * const s) : Move(std::string(s)) {}

  ///Obtain the square the piece is moving from
  const boost::shared_ptr<const Square> From() const noexcept { return m_from; }

  ///Obtain the Move in the notational form it was contructed with
  const std::string& GetStr() const { return m_str; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Obtain whether this move is a capture
  bool IsCapture() const { return m_is_capture; };

  ///Obtain whether this move performs a castling
  bool IsCastling() const;

  ///Obtain whether this move results in a check
  bool IsCheck() const { return m_is_check; };

  ///Obtain whether this move results in a checkmate
  bool IsCheckmate() const { return m_is_checkmate; };

  ///Obtain whether this move is an en passant capture
  bool IsEnPassant() const { return m_is_en_passant; }

  ///Obtain whether this move results in a promotion
  bool IsPromotion() const { return m_is_promotion; };

  ///Parse the string to obtain the square the piece is moving from, when known
  ///Examples:
  ///* 'a2 a3' results in a Square with 'a2'
  ///* 'a3' results in an empty Square
  static const boost::shared_ptr<Chess::Square> ParseFrom(const std::string& s);

  ///Obtain whether the string is a capture
  static bool ParseIsCapture(const std::string& s);

  ///Obtain whether the string results in a check
  static bool ParseIsCheck(const std::string& s);

  ///Obtain whether the string is a castling
  static bool ParseIsCastling(const std::string& s);

  ///Obtain whether the string results in a checkmate
  static bool ParseIsCheckmate(const std::string& s);

  ///Obtain whether the string results in an en passant capture
  static bool ParseIsEnPassant(const std::string& s);

  ///Obtain whether the string is a move that results in a promotion
  static bool ParseIsPromotion(const std::string& s);

  ///Parse the Piece from a string
  static const boost::shared_ptr<Chess::Piece> ParsePiece(const std::string& s);

  ///Parse the Piece the pawn is promoted to from a string
  static const boost::shared_ptr<Chess::Piece> ParsePiecePromotion(const std::string& s);

  ///Parse the Score from a string
  static const boost::shared_ptr<Chess::Score> ParseScore(const std::string& s);

  ///Parse the Square the Piece is moving to
  static const boost::shared_ptr<Chess::Square> ParseTo(const std::string& s);

  ///Obtain the piece type
  const boost::shared_ptr<Chess::Piece> Piece() const { return m_piece; };

  ///Obtain the piece type promoted to
  const boost::shared_ptr<Chess::Piece> PiecePromotion() const { return m_piece_promotion; };

  ///Obtain the score
  const boost::shared_ptr<Chess::Score> Score() const { return m_score; };


  #ifndef NDEBUG
  ///Tests all moves that are potentially valid,
  ///that is, there must be situations possible
  ///in which these are valid.
  static void Test();
  #endif

  ///Obtain the square the piece is moving to
  const boost::shared_ptr<const Square> To() const noexcept { return m_to; }

  ///Convert a Move to its long notational form
  const std::string ToStr() const;

  private:
  ///Parses a Move from std::string.
  explicit Move(const std::string& s);

  ~Move() {}

  #define CHESS_MOVE_NOT_USE_CONST
  #ifndef CHESS_MOVE_NOT_USE_CONST
  const boost::shared_ptr<Square> m_from;
  const bool m_is_capture;
  const bool m_is_castling;
  const bool m_is_check;
  const bool m_is_checkmate;
  const bool m_is_promotion;
  const boost::shared_ptr<Chess::Piece> m_piece;
  const boost::shared_ptr<Chess::Piece> m_piece_promotion;
  const boost::shared_ptr<Chess::Score> m_score;
  const std::string m_str;
  const boost::shared_ptr<Chess::Square> m_to;
  #else
  boost::shared_ptr<const Square> m_from;
  bool m_is_capture;
  bool m_is_castling;
  bool m_is_check;
  bool m_is_checkmate;
  bool m_is_en_passant;
  bool m_is_promotion;
  boost::shared_ptr<Chess::Piece> m_piece;
  boost::shared_ptr<Chess::Piece> m_piece_promotion;
  boost::shared_ptr<Chess::Score> m_score;

  ///The Move in the same notational form as given in the contructor
  std::string m_str;

  boost::shared_ptr<const Chess::Square> m_to;
  #endif
  ///Obtain all matches of regex in a certain string
  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static const std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const boost::xpressive::sregex& r);

  friend void boost::checked_delete<>(Move *);

  friend class MoveFactory;
  friend bool operator==(const Move& lhs, const Move& rhs);

};

bool operator==(const Move& lhs, const Move& rhs);
bool operator!=(const Move& lhs, const Move& rhs);
std::ostream& operator<<(std::ostream& os,const Move& m);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSMOVE_H

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <boost/checked_delete.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "chesscolor.h"
#include "chessfwd.h"
//#include "chesssquare.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace Chess {

//A Piece has
//- a (possibly undetermined) position
//- a (possibly undetermined) color
struct Piece
{
  virtual ~Piece() noexcept {}

  ///Determines if this Piece can possibly do this move
  virtual bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept = 0;

  ///Perform a Move on a Piece
  void DoMove(const boost::shared_ptr<const Move> move);

  ///Obtain the (possibily indeterminate) Color of a Piece
  Color GetColor() const noexcept;

  ///Obtain the last move this Piece did.
  boost::shared_ptr<const Move> GetLastMove() const noexcept { return m_last_move; }

  ///Returns all Moves to be done by a Piece.
  ///These moves are all valid (for example, on an empty board), but might be invalid in the current chessgame.
  virtual std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept = 0;

  ///Obtain the Square the piece is standing on
  boost::shared_ptr<const Square> GetSquare() const noexcept;

  ///Convert a Piece type to a its full name, e.g. 'knight'
  virtual std::string GetName() const noexcept = 0;

  ///Convert a Piece type to a its notational character, e.g 'N'
  virtual char GetNameChar() const noexcept = 0;

  ///Returns the color and symbol
  //const std::pair<char,char> GetSymbol() const;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  #ifndef NDEBUG
  ///Test all Pieces
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  protected:

  Piece(
    const Color color,
    const boost::shared_ptr<const Square>& square);

  ///Triple number of moves by adding check and checkmate
  static const std::vector<boost::shared_ptr<Move> > AddCheckAndCheckmate(const std::vector<boost::shared_ptr<Move> >& v);

  ///Clone a Piece
  virtual boost::shared_ptr<Piece> Clone() const = 0;

  private:

  ///The piece its color
  const Color m_color;

  ///The last move this Piece did.
  boost::shared_ptr<const Move> m_last_move;

  ///The piece its location
  boost::shared_ptr<const Square> m_square;

  friend void boost::checked_delete<>(Piece *);
};

struct PieceBishop : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;

  std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept;

  ///Convert a Piece type to a its notational character, e.g 'N'
  char GetNameChar() const noexcept { return 'B'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  std::string GetName() const noexcept { return "bishop"; }

  #ifndef NDEBUG
  ///Test Bishop
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  private:
  PieceBishop(
    const Color color,
    const boost::shared_ptr<const Square> square);
  PieceBishop(const PieceBishop&) = delete;
  PieceBishop& operator=(const PieceBishop&) = delete;

  ///Clone this Piece
  boost::shared_ptr<Piece> Clone() const;

  ~PieceBishop() noexcept {}

  friend void boost::checked_delete<>(PieceBishop *);
  friend struct PieceFactory;
  friend boost::shared_ptr<      PieceBishop> boost::make_shared<      PieceBishop>(const Color color,const boost::shared_ptr<const Square> square);
  friend boost::shared_ptr<const PieceBishop> boost::make_shared<const PieceBishop>(const Color color,const boost::shared_ptr<const Square> square);


  //friend boost::shared_ptr<PieceBishop> boost::make_shared<PieceBishop>(const PieceBishop&);
  //friend class boost::detail::sp_ms_deleter<PieceBishop>;
  //friend class boost::detail::sp_ms_deleter<const PieceBishop>;

};

struct PieceKing : public Piece
{

  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;

  std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept;
  //void Move(const Square& to);

  ///Convert a Piece type to a its notational character, e.g 'N'
  char GetNameChar() const noexcept { return 'K'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  std::string GetName() const noexcept { return "king"; }

  #ifndef NDEBUG
  ///Test PieceKing
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  private:
  PieceKing(
    const Color color,
    const boost::shared_ptr<const Square> square);

  ///Clone this Piece
  boost::shared_ptr<Piece> Clone() const;

  ~PieceKing() noexcept {}

  friend void boost::checked_delete<>(PieceKing *);

  ///Keep track of whether king has moved for castling
  bool m_has_moved;

  friend struct PieceFactory;
};

struct PieceKnight : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;


  ///Returns all Moves to be done by a Piece.
  ///These moves are all valid, but might be invalid in the current chessgame.
  std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept;

  char GetNameChar() const noexcept { return 'N'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  std::string GetName() const noexcept { return "knight"; }

  #ifndef NDEBUG
  ///Test PieceKnight
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  private:
  PieceKnight(
    const Color color,
    const boost::shared_ptr<const Square> square);

  ///Clone this Piece
  boost::shared_ptr<Piece> Clone() const;

  ~PieceKnight() noexcept {}
  friend void boost::checked_delete<>(PieceKnight *);
  friend struct PieceFactory;
};

struct PiecePawn : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;

  std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept;
  char GetNameChar() const noexcept { return '.'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  std::string GetName() const noexcept { return "pawn"; }

  #ifndef NDEBUG
  ///Test PiecePawn
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  private:
  PiecePawn(
    const Color color,
    const boost::shared_ptr<const Square> square);

  ///Clone this Piece
  boost::shared_ptr<Piece> Clone() const;

  ~PiecePawn() noexcept {}

  friend void boost::checked_delete<>(PiecePawn *);
  friend struct PieceFactory;
};

struct PieceQueen : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;

  std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept;
  char GetNameChar() const noexcept { return 'Q'; }

  ///Convert a Piece type to a its full name, e.g. 'king'
  std::string GetName() const noexcept { return "queen"; }

  #ifndef NDEBUG
  ///Test PieceQueen
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  private:

  PieceQueen(
    const Color color,
    const boost::shared_ptr<const Square> square);

  ///Clone this Piece
  boost::shared_ptr<Piece> Clone() const;

  ~PieceQueen() noexcept {}
  friend void boost::checked_delete<>(PieceQueen *);
  friend struct PieceFactory;
};

struct PieceRook : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;

  std::vector<boost::shared_ptr<Move> > GetMoves() const noexcept;

  char GetNameChar() const noexcept { return 'R'; }

  ///Convert a Piece type to a its full name, e.g. 'king'
  std::string GetName() const noexcept { return "rook"; }

  #ifndef NDEBUG
  ///Test PieceRook
  static void Test() noexcept;
  #endif

  ///Convert a Piece to std::string for operator<<
  std::string ToStr() const noexcept;

  private:
  PieceRook(
    const Color color,
    const boost::shared_ptr<const Square> square);

  ///Clone this Piece
  boost::shared_ptr<Piece> Clone() const;

  ~PieceRook() noexcept {}
  friend void boost::checked_delete<>(PieceRook *);

  ///Keep track of whether rook has moved for castling
  bool m_has_moved;

  friend struct PieceFactory;
};


bool operator==(const Piece& lhs, const Piece& rhs);
bool operator!=(const Piece& lhs, const Piece& rhs);
std::ostream& operator<<(std::ostream& os, const Piece& piece);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSPIECE_H

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>

#include "chesscolor.h"
#include "chessfwd.h"
//#include "chesssquare.h"

namespace ribi {
namespace Chess {

//A Piece has
//- a (possibly undetermined) position
//- a (possibly undetermined) color
struct Piece
{
  //Base classes must have a public destructor:
  //Herb Sutter, Andrei Alexandrescu. C++ coding standards:
  //101 rules, guidelines, and best practices.
  //ISBN: 0-32-111358-6. Item 50: 'Make base class destructors
  //public and virtual, or protected and nonvirtual'.
  virtual ~Piece() {}

  ///Determines if this Piece can possibly do this move
  virtual bool CanDoMove(const Chess::Move& move) const = 0;

  ///Perform a Move on a Piece
  void DoMove(const Chess::Move& move);

  ///Obtain the (possibily indeterminate) Color of a Piece
  Color GetColor() const;

  ///Obtain the last move this Piece did.
  const boost::shared_ptr<Move>& GetLastMove() const { return m_last_move; }

  ///Returns all Moves to be done by a Piece.
  ///These moves are all valid (for example, on an empty board), but might be invalid in the current chessgame.
  virtual const std::vector<boost::shared_ptr<Move> > GetMoves() const = 0;

  ///Obtain the Square the piece is standing on
  const boost::shared_ptr<Square>& GetSquare() const;

  ///Convert a Piece type to a its full name, e.g. 'knight'
  virtual const std::string GetName() const = 0;

  ///Convert a Piece type to a its notational character, e.g 'N'
  virtual char GetNameChar() const = 0;

  ///Returns the color and symbol
  //const std::pair<char,char> GetSymbol() const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  #ifndef NDEBUG
  ///Test all Pieces
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  protected:

  Piece(
    const Color color,
    const boost::shared_ptr<Square>& square);

  ///Triple number of moves by adding check and checkmate
  static const std::vector<boost::shared_ptr<Move> > AddCheckAndCheckmate(const std::vector<boost::shared_ptr<Move> >& v);

  ///Clone a Piece
  virtual const boost::shared_ptr<Piece> Clone() const = 0;

  private:

  ///The piece its color
  const Color m_color;

  ///The last move this Piece did.
  boost::shared_ptr<Move> m_last_move;

  ///The piece its location
  boost::shared_ptr<Square> m_square;

  friend bool IsEqual(const Piece& lhs, const Piece& rhs);

  friend void boost::checked_delete<>(Piece *);
};

struct PieceBishop : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const Chess::Move& move) const;

  const std::vector<boost::shared_ptr<Move> > GetMoves() const;

  ///Convert a Piece type to a its notational character, e.g 'N'
  char GetNameChar() const { return 'B'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  const std::string GetName() const { return "bishop"; }

  #ifndef NDEBUG
  ///Test Bishop
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  private:
  PieceBishop(
    const Color color,
    const boost::shared_ptr<Square>& square);
  PieceBishop(const PieceBishop&) = delete;
  PieceBishop& operator=(const PieceBishop&) = delete;

  ///Clone this Piece
  const boost::shared_ptr<Piece> Clone() const;

  ~PieceBishop() {}

  friend void boost::checked_delete<>(PieceBishop *);
};

struct PieceKing : public Piece
{

  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const Chess::Move& move) const;

  const std::vector<boost::shared_ptr<Move> > GetMoves() const;
  //void Move(const Square& to);

  ///Convert a Piece type to a its notational character, e.g 'N'
  char GetNameChar() const { return 'K'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  const std::string GetName() const { return "king"; }

  #ifndef NDEBUG
  ///Test PieceKing
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  private:
  PieceKing(
    const Color color,
    const boost::shared_ptr<Square>& square);

  ///Clone this Piece
  const boost::shared_ptr<Piece> Clone() const;

  ~PieceKing() {}

  friend void boost::checked_delete<>(PieceKing *);

  ///Keep track of whether king has moved for castling
  bool m_has_moved;

};

struct PieceKnight : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const Chess::Move& move) const;


  ///Returns all Moves to be done by a Piece.
  ///These moves are all valid, but might be invalid in the current chessgame.
  const std::vector<boost::shared_ptr<Move> > GetMoves() const;

  char GetNameChar() const { return 'N'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  const std::string GetName() const { return "knight"; }

  #ifndef NDEBUG
  ///Test PieceKnight
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  private:
  PieceKnight(
    const Color color,
    const boost::shared_ptr<Square>& square);

  ///Clone this Piece
  const boost::shared_ptr<Piece> Clone() const;

  ~PieceKnight() {}
  friend void boost::checked_delete<>(PieceKnight *);
};

struct PiecePawn : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const Chess::Move& move) const;


  const std::vector<boost::shared_ptr<Move> > GetMoves() const;
  char GetNameChar() const { return '.'; }

  ///Convert a Piece type to a its full name, e.g. 'knight'
  const std::string GetName() const { return "pawn"; }

  #ifndef NDEBUG
  ///Test PiecePawn
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  private:
  PiecePawn(
    const Color color,
    const boost::shared_ptr<Square>& square);

  ///Clone this Piece
  const boost::shared_ptr<Piece> Clone() const;

  ~PiecePawn() {}

  friend void boost::checked_delete<>(PiecePawn *);
};

struct PieceQueen : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const Chess::Move& move) const;

  const std::vector<boost::shared_ptr<Move> > GetMoves() const;
  char GetNameChar() const { return 'Q'; }

  ///Convert a Piece type to a its full name, e.g. 'king'
  const std::string GetName() const { return "queen"; }

  #ifndef NDEBUG
  ///Test PieceQueen
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  private:

  PieceQueen(
    const Color color,
    const boost::shared_ptr<Square>& square);

  ///Clone this Piece
  const boost::shared_ptr<Piece> Clone() const;

  ~PieceQueen() {}
  friend void boost::checked_delete<>(PieceQueen *);
};

struct PieceRook : public Piece
{
  ///Determines if this Piece can possibly do this move
  bool CanDoMove(const Chess::Move& move) const;

  const std::vector<boost::shared_ptr<Move> > GetMoves() const;

  char GetNameChar() const { return 'R'; }

  ///Convert a Piece type to a its full name, e.g. 'king'
  const std::string GetName() const { return "rook"; }

  #ifndef NDEBUG
  ///Test PieceRook
  static void Test();
  #endif

  ///Convert a Piece to std::string for operator<<
  const std::string ToStr() const;

  private:
  PieceRook(
    const Color color,
    const boost::shared_ptr<Square>& square);

  ///Clone this Piece
  const boost::shared_ptr<Piece> Clone() const;

  ~PieceRook() {}
  friend void boost::checked_delete<>(PieceRook *);

  ///Keep track of whether rook has moved for castling
  bool m_has_moved;

};


bool operator==(const Piece& lhs, const Piece& rhs); //FORBID
bool operator!=(const Piece& lhs, const Piece& rhs); //FORBID
bool IsEqual(const Piece& lhs, const Piece& rhs);
std::ostream& operator<<(std::ostream& os, const Piece& piece);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSPIECE_H

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iosfwd>
#include <set>
#include <vector>

#include <boost/logic/tribool.hpp>
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "chesscolor.h"
#include "chessmove.h"
//#include "chesspiece.h"

namespace Chess {

struct Piece;

///Chess::Board is a class for a chessboard without gaming rules.
///Rules that handled by Chess::Board normally are:
/// - en passant
/// - castling
///Chess::Game is the class that uses a Chess::Board and adds these rules
///Rules that must be handled by Chess::Game are:
/// - keeping track of which player's turn it is
/// - determining a winner or draw
struct Board
{
  typedef boost::shared_ptr<Piece> PiecePtr;
  typedef boost::shared_ptr<const Piece> ConstPiecePtr;
  typedef std::set<PiecePtr> Pieces;
  typedef std::set<ConstPiecePtr> ConstPieces;

  Board(const Board& rhs) = delete; //BUG: this one was missing (and abused)
  Board& operator=(const Board& rhs) = delete;

  ///Check if a Move is valid to play in the current context
  ///Player must be indicated, because without castling would be ambigious
  ///Note that e2-e4 is only valid for the white player
  bool CanDoMove(const Move& move, const Player player) const;

  ///Do a Move that is valid to play in the current context
  ///Player must be indicated, because without castling would be ambigious
  ///Note that e2-e4 is only valid for the white player
  void DoMove(const Move& move, const Player player);

  //bool IsVisible(const Square& s);

  //const BoardVisibleType GetInSight(const Piece::Color color) const;
  //const Piece GetPiece(const int x, const int y) const;

  ///Create Pieces in their startup positions
  static const Pieces GetInitialSetup();

  ///Get the Move history
  //const std::vector<boost::shared_ptr<Move> >& GetMoveHistory() const { return m_move_history; }

  ///Collect all moves that are possible for a Piece at a certain Square.
  ///If there is no Piece at that Square, no Moves are returned
  const std::vector<boost::shared_ptr<Move> > GetMoves(const Square& square) const;

  ///Collect all moves that are possible
  const std::vector<boost::shared_ptr<Move> > GetMoves(const Player player) const;

  ///Find a Piece at a certain Square.
  ///If there is no Piece at that Square, an empty Piece is returned
  const PiecePtr GetPiece(const Square& square);

  ///Find a Piece at a certain Square.
  ///If there is no Piece at that Square, an empty Piece is returned
  const ConstPiecePtr GetPiece(const Square& square) const;

  ///Obtain all read-only Piece instances
  const ConstPieces GetPieces() const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Get all squares that are visible by a player with the requested color.
  ///If the Color is set to Color::indeterminate, both players' sights
  ///are returned
  const BitBoard GetVisibleSquares(const Player player) const;

  ///Is, in the current position, the player being in check?
  bool IsCheck(const Player player) const;

  ///Is the current position the active player being in checkmate?
  bool IsCheckmate(const Player player) const;

  ///The Score if the game has ended by agreement (instead of by checkmate)
  //const boost::shared_ptr<Chess::Score>& Score() const;

  private:
  ///Construct a Board in the initial position, allowed by BoardFactory only
  Board(const Pieces& pieces);

  ~Board() {}

  ///All the Pieces
  Pieces m_pieces;

  ///The history of all Moves
  ///REMOVED: client has to keep track of these him/herself
  //std::vector<boost::shared_ptr<Move> > m_move_history;

  ///Check if a Player can do a castling
  bool CanDoCastling(const Castling castling, const Player player) const;

  ///Let a Player do a castling
  void DoCastling(const Castling castling, const Player player);

  ///Given a Move with a certain destination, deduce all Moves (with a starting position added)
  ///that have the same destination
  const std::vector<boost::shared_ptr<Move> > CompleteMove(const Move& move, const Player player) const;

  static const std::vector<boost::shared_ptr<Square > > CreateSquaresBetweenKingAndRook(
    const Player player,const Castling castling);

  ///Check if all squares between two Squares are empty (e
  ///Squares must be on one line
  bool EmptyBetween(const Square& a, const Square& b) const;

  ///Checks if the Move is valid in this situation
  ///??? REPLACE BY USING CANDOMOVE
  //bool IsValid(const Move& move) const;

  #ifndef NDEBUG
  ///Tests the Board2d class
  static void Test();
  #endif

  //friend bool operator==(const Board& lhs, const Board& rhs);
  friend class BoardFactory;
  friend std::ostream& operator<<(std::ostream& os, const Board& board);
  friend void boost::checked_delete<>(Board *);
};

bool IsEqual(const Board& lhs, const Board& rhs);
bool IsEqual(const Board::ConstPieces& lhs,const Board::ConstPieces& rhs);

bool operator==(const Board& lhs, const Board& rhs); //FORBID
bool operator!=(const Board& lhs, const Board& rhs); //FORBID
bool operator==(const Board::ConstPieces& lhs,const Board::ConstPieces& rhs); //FORBID


std::ostream& operator<<(std::ostream& os, const Board& board);

} //~ namespace Chess

#endif // CHESSBOARD_H

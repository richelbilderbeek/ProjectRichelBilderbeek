#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <iosfwd>
//#include <set>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/logic/tribool.hpp>
#include <boost/shared_ptr.hpp>

#include "chessfwd.h"
#include "chesscolor.h"
#include "chessmove.h"
//#include "chesspiece.h"
#pragma GCC diagnostic pop

namespace ribi {

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
struct Game
{
  typedef boost::shared_ptr<Piece> PiecePtr;
  typedef std::vector<PiecePtr> Pieces;

  ///Construct a Game in the initial position
  Game();

  ///Copy a Game
  //Game(const Game& other);

  ///Check if a Move is valid to play in the current context
  bool CanDoMove(const boost::shared_ptr<const Move> move) const;

  ///Check if this game can be played
  static bool CanDoGame(const std::vector<std::string>& moves);
  static int CanDoGameUntil(const std::vector<std::string>& moves);

  ///Do a Move that is valid to play in the current context
  void DoMove(const boost::shared_ptr<const Move> move);

  //bool IsVisible(const Square& s);

  //const GameVisibleType GetInSight(const Piece::Color color) const;
  //const Piece GetPiece(const int x, const int y) const;

  ///Whose turn is it?
  Player GetActivePlayer() const;

  ///Get the Chess::Board used for the Game
  const boost::shared_ptr<Chess::Board> GetBoard() const { return m_board; }

  ///Collect all moves that are possible for a Piece at a certain Square.
  ///If there is no Piece at that Square, no Moves are returned
  const std::vector<boost::shared_ptr<Move> > GetMoves(const boost::shared_ptr<const Square> square) const;

  ///Collect all moves that are possible
  const std::vector<boost::shared_ptr<Move> > GetMoves() const;

  ///Find a Piece at a certain Square.
  ///If there is no Piece at that Square, an empty Piece is returned
  const PiecePtr GetPiece(const boost::shared_ptr<const Square> square) const;

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  ///Get all squares that are visible by a player with the requested color.
  ///If the Color is set to Color::indeterminate, both players' sights
  ///are returned
  const BitBoard GetVisibleSquares() const;

  ///Is, in the current position, the active player being in check?
  bool IsCheck() const;

  ///Is the current position the active player being in checkmate?
  bool IsCheckmate() const;

  ///The Score if the game has ended by agreement (instead of by checkmate)
  const boost::shared_ptr<Chess::Score>& Score() const;


  #ifndef NDEBUG
  ///Tests the Game class
  static void Test();
  #endif

  private:
  ///The Chess::Board used for the Game
  const boost::shared_ptr<Chess::Board> m_board;

  std::vector<boost::shared_ptr<const Chess::Move> > m_moves;

  ///The Score if the game has ended by agreement (instead of by checkmate)
  boost::shared_ptr<Chess::Score> m_score;

  friend bool operator==(const Game& lhs, const Game& rhs);
};

bool operator==(const Game& lhs, const Game& rhs);
bool operator!=(const Game& lhs, const Game& rhs);

} //~namespace Chess
} //~namespace ribi

#endif // CHESSGAME_H

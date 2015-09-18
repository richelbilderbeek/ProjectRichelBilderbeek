#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "tictactoeplayer.h"
#include "tictactoewinner.h"
#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

///Manages a Board to follow the rules
struct Game
{
  Game() noexcept;

  ///Can the current player put his/her character at (x,y)?
  bool CanDoMove(const int x, const int y) const noexcept;

  ///DoMove lets the current player put his/her token at a certain position on the board.
  void DoMove(const int x, const int y) noexcept;

  boost::shared_ptr<const Board> GetBoard() const noexcept;

  ///GetCurrentPlayer returns whose turn it is.
  Player GetCurrentPlayer() const noexcept { return m_current_player; }

  ///GetCurrentTurn returns the turn number.
  int GetCurrentTurn() const noexcept;

  ///GetSummarizedState returns an integer summarizing the
  ///state, which is both tic-tac-toe board and whose turn it is.
  ///In trinary, for lowest order digit:\n
  ///# : content\n
  ///0-8: board
  ///9 : current turn\n
  ///The current turn is stored as:\n
  ///[#] : description\n
  /// 0  : ERROR\n
  /// 1  : player1\n
  /// 2  : player2\n
  int GetSummarizedState() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  Winner GetWinner() const noexcept;

  void Restart() noexcept;

  ///SetSummarizedState sets the game its state
  void SetSummarizedState(const int state) noexcept;

  ///Just display it as a string
  std::string ToTextCanvas() const noexcept;

  boost::signals2::signal<void(Game*)> m_signal_changed;

  private:
  boost::shared_ptr<Board> m_board;
  Player m_current_player;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os,const Game& t) noexcept;
bool operator==(const Game& lhs, const Game& rhs) noexcept;

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEGAME_H

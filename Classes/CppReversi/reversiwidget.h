#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#include <string>
#include <stack>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include "reversifwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace reversi {

///Widget is higher level interface of the Reversi Board:
///Widget keeps track of the current player its turn and allows undoing of moves
struct Widget
{
  enum { empty   = 0};
  enum { player1 = 1};
  enum { player2 = 2};
  enum { draw = 3};

  Widget(const int size = 10);

  bool CanDoMove(const boost::shared_ptr<const Move> move) const noexcept;

  void DoMove(const boost::shared_ptr<const Move> move) noexcept;

  const boost::shared_ptr<const Board> GetBoard() const noexcept { return m_board; }
  const boost::shared_ptr<      Board> GetBoard()       noexcept { return m_board; }

  int GetCurrentPlayer() const noexcept { return m_current_player; }

  const std::vector<boost::shared_ptr<Move>> GetValidMoves() const noexcept;

  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
  int GetWinner() const noexcept;

  void Undo();

  private:
  boost::shared_ptr<Board> m_board;
  int m_current_player;

  //The undo stack:
  //first: the Widget before the Move
  //second: the last Move done in the game
  std::stack<std::pair<boost::shared_ptr<Widget>,boost::shared_ptr<const Move>>> m_undo;

  bool CanDoMove(const int x, const int y) const noexcept;
  bool CanDoMovePass() const noexcept;

  ///Create the delta-x and delta-y to search in the 8 directions
  static const std::vector<std::pair<int,int>> CreateDeltas() noexcept;

  void DoMove(const int x, const int y) noexcept;
  void DoMovePass() noexcept;

  int GetOtherPlayer() const noexcept;

  //Simply sets a square
  //void Set(const int x, const int y, const int state) noexcept;

  void TogglePlayer();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

bool operator==(const Widget& lhs, const Widget& rhs);
bool operator!=(const Widget& lhs, const Widget& rhs);

std::ostream& operator<<(std::ostream& os, const Widget& r);

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIWIDGET_H

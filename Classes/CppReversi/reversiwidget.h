#ifndef REVERSIWIDGET_H
#define REVERSIWIDGET_H

#include <string>
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

  bool CanDoMove(const int x, const int y) const noexcept;
  bool CanDoMovePass() const noexcept;
  void DoMove(const int x, const int y) noexcept;
  void DoMovePass() noexcept;

  //void DoMove(const boost::shared_ptr<Move> move) const noexcept;

  const boost::shared_ptr<const Board> GetBoard() const noexcept { return m_board; }

  int GetCurrentPlayer() const noexcept { return m_current_player; }

  const std::vector< std::pair<int,int> > GetValidMoves() const noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;
  int GetWinner() const noexcept;

  private:
  boost::shared_ptr<Board> m_board;
  int m_current_player;


  ///Create the delta-x and delta-y to search in the 8 directions
  static const std::vector<std::pair<int,int>> CreateDeltas() noexcept;


  int GetOtherPlayer() const noexcept;

  //Simply sets a square
  void Set(const int x, const int y, const int state) noexcept;

  void TogglePlayer();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

std::ostream& operator<<(std::ostream& os, const Widget& r);

} //~namespace reversi
} //~namespace ribi

#endif // REVERSIWIDGET_H

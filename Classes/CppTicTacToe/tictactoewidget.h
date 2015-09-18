#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "tictactoefwd.h"
#include "tictactoekey.h"
#include "tictactoeplayer.h"
#include "tictactoewinner.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

///User interaction focused TicTacToe game
struct Widget
{
  Widget();

  bool CanSelect(const int x, const int y) const noexcept;

  void DoMove() noexcept;

  Player GetCurrentPlayer() const noexcept;

  boost::shared_ptr<const Game> GetGame() const noexcept { return m_game; }

  int GetSummarizedState() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  Winner GetWinner() const noexcept;

  void PressKey(const Key key) noexcept;

  void Restart() noexcept;

  void Select(const int x, const int y) noexcept;

  std::string ToTextCanvas() const noexcept;

  ///Signal emitted when the widget is changed
  boost::signals2::signal<void ()> m_signal_changed;

  private:

  const boost::shared_ptr<Game> m_game;

  int m_x;
  int m_y;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tictactoe
} //~namespace ribi


#endif // TICTACTOEWIDGET_H

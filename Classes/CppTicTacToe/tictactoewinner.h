#ifndef TICTACTOEWINNER_H
#define TICTACTOEWINNER_H

#include <string>

namespace ribi {
namespace tictactoe {

enum class Winner
{
  player1,
  player2,
  draw,
  no_winner
};

std::string WinnerToStr(const Winner winner) noexcept;
std::string WinnerToName(const Winner winner) noexcept;

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEWINNER_H

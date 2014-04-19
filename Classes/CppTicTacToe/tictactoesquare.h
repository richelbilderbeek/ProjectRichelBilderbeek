#ifndef TICTACTOESQUARE_H
#define TICTACTOESQUARE_H

#include <iostream>
#include <string>

namespace ribi {
namespace tictactoe {

enum class Square
{
  empty,
  player1,
  player2
};

std::string SquareToStr(const Square square) noexcept;
int SquareToState(const Square square) noexcept;
Square StateToSquare(const int state);

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOESQUARE_H

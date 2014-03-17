#ifndef TICTACTOEPLAYER_H
#define TICTACTOEPLAYER_H

namespace ribi {
namespace tictactoe {

enum class Player
{
  player1,
  player2
};

int PlayerToState(const Player player) noexcept;
Player StateToPlayer(const int state);

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEPLAYER_H

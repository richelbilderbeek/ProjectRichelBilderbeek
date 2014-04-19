#include "tictactoeplayer.h"

#include <cassert>
#include <stdexcept>

int ribi::tictactoe::PlayerToState(const ribi::tictactoe::Player player) noexcept
{
  switch (player)
  {
    case Player::player1: return 1;
    case Player::player2: return 2;
  }
  assert(!"Should not get here");
  throw std::logic_error("TicTacToe::PlayerToState: unknown player");
}

ribi::tictactoe::Player ribi::tictactoe::StateToPlayer(const int state)
{
  switch (state)
  {
    case 1: return Player::player1;
    case 2: return Player::player2;
  }
  assert(!"Should not get here");
  throw std::logic_error("TicTacToe::StateToPlayer: invalid state");
}

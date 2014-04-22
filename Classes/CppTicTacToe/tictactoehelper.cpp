#include "tictactoehelper.h"

#include <cassert>
#include <stdexcept>

ribi::tictactoe::Player ribi::tictactoe::Helper::GetOtherPlayer(
  const ribi::tictactoe::Player player
) const noexcept
{
  switch (player)
  {
    case Player::player1: return Player::player2;
    case Player::player2: return Player::player1;
  }
  assert(!"Should not get here");
  throw std::logic_error("GetOtherPlayer: unknown player");
}

int ribi::tictactoe::Helper::IntPower(const int base, const int exponent) const noexcept
{
  assert(exponent != 0
    && "When calculating IntPower(x,0) the result "
       "might be zero or one, depending on the context");
  assert(exponent > 0);

  int result = base;
  for (int i=1; i!=exponent; ++i)
  {
    result*=base;
  }
  return result;
}

ribi::tictactoe::Square ribi::tictactoe::Helper::PlayerToSquare(const ribi::tictactoe::Player player) const noexcept
{
  switch (player)
  {
    case Player::player1: return Square::player1;
    case Player::player2: return Square::player2;
  }
  assert(!"Should not get here");
  throw std::logic_error("PlayerToSquare: unknown player");
}

ribi::tictactoe::Player ribi::tictactoe::Helper::SquareToPlayer(const ribi::tictactoe::Square square) const
{
  switch (square)
  {
    case Square::empty  : assert(!"Cannot convert empty square to player");
    case Square::player1: return Player::player1;
    case Square::player2: return Player::player2;
  }
  assert(!"Should not get here");
  throw std::logic_error("SquareToPlayer: unknown square");
}


ribi::tictactoe::Winner ribi::tictactoe::Helper::SquareToWinner(const ribi::tictactoe::Square square) const
{
  switch (square)
  {
    case Square::empty  : assert(!"Cannot convert empty square to winner");
    case Square::player1: return Winner::player1;
    case Square::player2: return Winner::player2;
  }
  assert(!"Should not get here");
  throw std::logic_error("SquareToWinner: unknown square");
}

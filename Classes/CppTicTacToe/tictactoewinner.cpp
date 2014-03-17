#include "tictactoewinner.h"

#include <cassert>
#include <stdexcept>

std::string ribi::tictactoe::WinnerToStr(const ribi::tictactoe::Winner winner) noexcept
{
  switch (winner)
  {
    case Winner::player1  : return "X";
    case Winner::player2  : return "O";
    case Winner::draw     : //return "*";
    case Winner::no_winner: //return " ";
      assert(!"Should not get here");
      throw std::logic_error("ribi::WinnerToStr: unknown square");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::WinnerToStr: unknown square");
}

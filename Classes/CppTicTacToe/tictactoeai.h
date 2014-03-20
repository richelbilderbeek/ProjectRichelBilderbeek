#ifndef TICTACTOEAI_H
#define TICTACTOEAI_H

#include <utility>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include "tictactoefwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tictactoe {

///An artifical intelligence for a tic tac toe game
struct Ai
{
  Ai() {}
  virtual ~Ai() {}
  virtual std::pair<int,int> SuggestMove(const Game& game) const = 0;
};

///Try to enforce a draw
struct AiEnforceDraw : public Ai
{
  std::pair<int,int> SuggestMove(const Game& game) const;
};

///Try to enforce a win
struct AiEnforceWin : public Ai
{
  std::pair<int,int> SuggestMove(const Game& game) const;
};

///Play randomly
struct AiPlayRandom : public Ai
{
  std::pair<int,int> SuggestMove(const Game& game) const;
};

} //~namespace tictactoe
} //~namespace ribi

#endif // TICTACTOEAI_H

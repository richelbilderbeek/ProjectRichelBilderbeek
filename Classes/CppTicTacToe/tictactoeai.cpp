#include "tictactoeai.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>

#include "tictactoeboard.h"
#include "tictactoegame.h"
#include "tictactoehelper.h"
#include "trace.h"
#pragma GCC diagnostic pop

std::string ribi::tictactoe::Ai::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::tictactoe::Ai::GetVersionHistory() noexcept
{
  return {
    "2014-03-21: version 1.0: initial version"
  };
}

std::vector<std::string> ribi::tictactoe::Ai::GetVersionHistory() noexcept;

std::pair<int,int> ribi::tictactoe::AiEnforceDraw::SuggestMove(
  const ribi::tictactoe::Game& game
) const
{
  boost::multi_array<int,2> like(boost::extents[3][3]);

  if (game.GetWinner() != Winner::no_winner)
  {
    throw std::logic_error("AiEnforceDraw::SuggestMove: Cannot suggest a move when there is a winner");
  }

  //Not interested in taken squares
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      like[col][row] = game.GetBoard()->GetSquare(col,row) != Square::empty
        || !game.CanDoMove(col,row)
      ? -1
      :  1;
    }
  }

  //Not interested in winning the game
  const auto me(game.GetCurrentPlayer());

  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      if (like[col][row] <= 0) continue;
      //Horizontal
      if ( game.GetBoard()->GetSquare((col + 1) % 3,(row + 0) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 0) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 0;
      }
      //Vertical
      if ( game.GetBoard()->GetSquare((col + 0) % 3,(row + 1) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 0) % 3,(row + 2) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 0;
      }
      //Diagonal, top-left to bottom-right
      if ( col == row
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 1) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 2) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 0;
      }
      //Diagonal, top-left to bottom-right
      if ( col == 2 - row
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 1) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 2) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 0;
      }
    }
  }

  //Interested in blocking the other
  const auto other(Helper().GetOtherPlayer(me));
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      if (like[col][row] <= 0) continue;
      //Horizontal
      if ( game.GetBoard()->GetSquare((col + 1) % 3,(row + 0) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 0) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
      //Vertical
      if ( game.GetBoard()->GetSquare((col + 0) % 3,(row + 1) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 0) % 3,(row + 2) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
      //Diagonal, top-left to bottom-right
      if ( col == row
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 1) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 2) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
      //Diagonal, top-left to bottom-right
      if ( col == 2 - row
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 1) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 2) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
    }
  }
  //Collect moves at likedness
  std::map<int,std::vector<std::pair<int,int>>> moves;
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      const int likedness = like[col][row];
      if (moves.count(likedness) == 0)
      {
        moves.insert(moves.begin(),std::make_pair(likedness,std::vector<std::pair<int,int>>()));
      }
      moves[ likedness ].push_back(std::make_pair(col,row));
    }
  }
  //Find moves with maximum likedness
  std::vector<std::pair<int,int>> best_liked( (*moves.rbegin()).second);
  //Choose one at random
  std::random_shuffle(best_liked.begin(),best_liked.end());
  assert(!best_liked.empty());
  assert(game.CanDoMove(best_liked[0].first,best_liked[0].second));
  return best_liked[0];
}

std::pair<int,int> ribi::tictactoe::AiEnforceWin::SuggestMove(
  const ribi::tictactoe::Game& game
) const
{
  boost::multi_array<int,2> like(boost::extents[3][3]);

  if (game.GetWinner() != Winner::no_winner)
  {
    throw std::logic_error("AiEnforceDraw::SuggestMove: Cannot suggest a move when there is a winner");
  }

  //Not interested in taken squares
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      like[col][row] = game.GetBoard()->GetSquare(col,row) != Square::empty
        || !game.CanDoMove(col,row)
      ? -1
      :  1;
    }
  }

  //Interested in winning the game
  const auto me(game.GetCurrentPlayer());

  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      if (like[col][row] <= 0) continue;
      //Horizontal
      if ( game.GetBoard()->GetSquare((col + 1) % 3,(row + 0) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 0) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 3;
      }
      //Vertical
      if ( game.GetBoard()->GetSquare((col + 0) % 3,(row + 1) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 0) % 3,(row + 2) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 3;
      }
      //Diagonal, top-left to bottom-right
      if ( col == row
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 1) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 2) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 3;
      }
      //Diagonal, top-left to bottom-right
      if ( col == 2 - row
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 1) % 3) == Helper().PlayerToSquare(me)
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 2) % 3) == Helper().PlayerToSquare(me)
      )
      {
        like[col][row] = 3;
      }
    }
  }

  //Interested in blocking the other
  const auto other(Helper().GetOtherPlayer(me));
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      if (like[col][row] <= 0) continue;
      //Horizontal
      if ( game.GetBoard()->GetSquare((col + 1) % 3,(row + 0) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 0) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
      //Vertical
      if ( game.GetBoard()->GetSquare((col + 0) % 3,(row + 1) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 0) % 3,(row + 2) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
      //Diagonal, top-left to bottom-right
      if ( col == row
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 1) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 2) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
      //Diagonal, top-left to bottom-right
      if ( col == 2 - row
        && game.GetBoard()->GetSquare((col + 2) % 3,(row + 1) % 3) == Helper().PlayerToSquare(other)
        && game.GetBoard()->GetSquare((col + 1) % 3,(row + 2) % 3) == Helper().PlayerToSquare(other)
      )
      {
        like[col][row] = 2;
      }
    }
  }
  //Collect moves at likedness
  std::map<int,std::vector<std::pair<int,int>>> moves;
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      const int likedness = like[col][row];
      if (moves.count(likedness) == 0)
      {
        moves.insert(moves.begin(),std::make_pair(likedness,std::vector<std::pair<int,int>>()));
      }
      moves[ likedness ].push_back(std::make_pair(col,row));
    }
  }

  //Find moves with maximum likedness
  std::vector<std::pair<int,int>> best_liked( (*moves.rbegin()).second);
  //Choose one at random
  std::random_shuffle(best_liked.begin(),best_liked.end());
  assert(!best_liked.empty());
  assert(game.CanDoMove(best_liked[0].first,best_liked[0].second));
  return best_liked[0];
}

std::pair<int,int> ribi::tictactoe::AiPlayRandom::SuggestMove(
  const ribi::tictactoe::Game& game
) const
{
  boost::multi_array<int,2> like(boost::extents[3][3]);

  if (game.GetWinner() != Winner::no_winner)
  {
    throw std::logic_error("AiEnforceDraw::SuggestMove: Cannot suggest a move when there is a winner");
  }

  //Not interested in taken squares
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      like[col][row] = game.GetBoard()->GetSquare(col,row) != Square::empty
        || !game.CanDoMove(col,row)
      ? -1
      :  1;
    }
  }

  //Collect moves at likedness
  std::map<int,std::vector<std::pair<int,int>>> moves;
  for (int row=0; row!=3; ++row)
  {
    for (int col=0; col!=3; ++col)
    {
      const int likedness = like[col][row];
      if (moves.count(likedness) == 0)
      {
        moves.insert(moves.begin(),std::make_pair(likedness,std::vector<std::pair<int,int>>()));
      }
      moves[ likedness ].push_back(std::make_pair(col,row));
    }
  }

  //Find moves with maximum likedness
  std::vector<std::pair<int,int>> best_liked( (*moves.rbegin()).second);
  //Choose one at random
  std::random_shuffle(best_liked.begin(),best_liked.end());
  assert(!best_liked.empty());
  assert(game.CanDoMove(best_liked[0].first,best_liked[0].second));
  return best_liked[0];
}

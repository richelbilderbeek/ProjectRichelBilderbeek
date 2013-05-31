#include "chessgame.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

#ifdef SADC_USE_THREADS
#include <thread>
#endif

//#include <boost/bind.hpp>
#include <boost/foreach.hpp>
//#include <boost/lambda/lambda.hpp>

#include "chessbitboard.h"
#include "chessboard.h"
#include "chessboardfactory.h"
#include "chessfile.h"
#include "chessmove.h"
#include "chesspiece.h"
#include "chessplayer.h"
#include "chessrank.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "trace.h"

namespace Chess {

Game::Game()
  : m_board(BoardFactory::Create())
{
  #ifndef NDEBUG
  Test();
  #endif
}

/*
Game::Game(const Game& other)
  : m_moves(other.m_moves)
{
  TRACE_FUNC();
  //Copy all Pieces
  //m_pieces = other.m_pieces;
  std::for_each(other.m_pieces.begin(), other.m_pieces.end(),
    [&m_pieces](const PiecePtr& p)
    {
      PiecePtr q(p->Clone());
      m_pieces.push_back(q);
    }
  );

  ///Copy the Score if the game has ended by agreement (instead of by checkmate)
  if (other.Score()) m_score.reset(new Chess::Score(*other.Score().get()));

  assert(*this == other);
}
*/

bool Game::CanDoGame(const std::vector<std::string>& moves)
{
  const int n_moves = static_cast<int>(moves.size());
  return CanDoGameUntil(moves) == n_moves;
}

int Game::CanDoGameUntil(const std::vector<std::string>& moves)
{
  Chess::Game game;
  const int n_moves = static_cast<int>(moves.size());
  for (int i=0; i!=n_moves; ++i)
  {
    const std::string s = moves[i];
    if (!game.CanDoMove(Chess::Move(s))) return i;
    game.DoMove(Chess::Move(s));
  }
  return n_moves;
}

bool Game::CanDoMove(const Move& move) const
{
  return m_board->CanDoMove(move,GetActivePlayer());
}

void Game::DoMove(const Move& move)
{
  //assert(CanDoMove(move));
  assert(!m_score);
  m_moves.push_back(move);
  if (move.From())
  {
    PiecePtr p = GetPiece(*move.From());
    assert(p);
    assert(p->CanDoMove(move));
    p->DoMove(move);
  }
  else if (move.Score())
  {
    m_score = move.Score();
  }
}

const Game::PiecePtr Game::GetPiece(const Square& square) const
{
  return m_board->GetPiece(square);
}

Player Game::GetActivePlayer() const
{
  return m_moves.size() % 2 ? Player::black : Player::white;
}

const std::vector<boost::shared_ptr<Move> > Game::GetMoves() const
{
  return m_board->GetMoves(GetActivePlayer());
}

const std::vector<boost::shared_ptr<Move> > Game::GetMoves(const Square& square) const
{
  return m_board->GetMoves(square);
}

const std::string Game::GetVersion()
{
  return "0.1";
}

const std::vector<std::string> Game::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-06-16: version 0.1: initial seperation from Chess::Board");
  return v;
}

const BitBoard Game::GetVisibleSquares() const
{
  return m_board->GetVisibleSquares(GetActivePlayer());
}

bool Game::IsCheck() const
{
  return m_board->IsCheck(GetActivePlayer());
}

bool Game::IsCheckmate() const
{
  ///TODO
  return IsCheck();
}

const boost::shared_ptr<Chess::Score>& Game::Score() const
{
  return m_score;
}

void Game::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SADC_USE_THREADS
  std::thread t(
    []
  #endif
    {
      FTRACE("Testing Game");
      Chess::Game();
    }
  #ifdef SADC_USE_THREADS
  );
  t.detach();
  #endif
}

bool operator==(const Game& lhs, const Game& rhs)
{
  if (!lhs.Score() &&  rhs.Score()) return false;
  if ( lhs.Score() && !rhs.Score()) return false;
  if ( lhs.Score() &&  rhs.Score())
  {
    if (*lhs.Score() != *rhs.Score()) return false;
  }
  return IsEqual(*lhs.m_board,*rhs.m_board);
  return true;
}

bool operator!=(const Game& lhs, const Game& rhs)
{
  return !(lhs == rhs);
}

} //~ namespace Chess


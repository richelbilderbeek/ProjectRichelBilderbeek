#include "chessgame.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "chessbitboard.h"
#include "chessboard.h"
#include "chessboardfactory.h"
#include "chesssquarefactory.h"
#include "chessfile.h"
#include "chessmove.h"
#include "chessmovefactory.h"
#include "chesspiece.h"
#include "chessplayer.h"
#include "chessrank.h"
#include "chessscore.h"
#include "chesssquare.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::Game::Game()
  : m_board(BoardFactory().Create()),
    m_moves{},
    m_score{}
{
  #ifndef NDEBUG
  Test();
  #endif
}

/*
ribi::Chess::Game::Game(const Game& other)
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

bool ribi::Chess::Game::CanDoGame(const std::vector<std::string>& moves)
{
  const int n_moves = static_cast<int>(moves.size());
  return CanDoGameUntil(moves) == n_moves;
}

int ribi::Chess::Game::CanDoGameUntil(const std::vector<std::string>& moves)
{
  Chess::Game game;
  const int n_moves = static_cast<int>(moves.size());
  for (int i=0; i!=n_moves; ++i)
  {
    const std::string s = moves[i];
    if (!game.CanDoMove(MoveFactory().Create(s))) return i;
    game.DoMove(Chess::MoveFactory().Create(s));
  }
  return n_moves;
}

bool ribi::Chess::Game::CanDoMove(const boost::shared_ptr<const Move> move) const
{
  return m_board->CanDoMove(move,GetActivePlayer());
}

void ribi::Chess::Game::DoMove(const boost::shared_ptr<const Move> move)
{
  //assert(CanDoMove(move));
  assert(!m_score);
  m_moves.push_back(move);
  if (move->From())
  {
    PiecePtr p = GetPiece(move->From());
    assert(p);
    assert(p->CanDoMove(move));
    p->DoMove(move);
  }
  else if (move->Score())
  {
    m_score = move->Score();
  }
}

const ribi::Chess::Game::PiecePtr ribi::Chess::Game::GetPiece(const boost::shared_ptr<const Square> square) const
{
  return m_board->GetPiece(square);
}

ribi::Chess::Player ribi::Chess::Game::GetActivePlayer() const
{
  return m_moves.size() % 2 ? Player::black : Player::white;
}

const std::vector<boost::shared_ptr<ribi::Chess::Move>> ribi::Chess::Game::GetMoves() const
{
  return m_board->GetMoves(GetActivePlayer());
}

const std::vector<boost::shared_ptr<ribi::Chess::Move>> ribi::Chess::Game::GetMoves(const boost::shared_ptr<const Square> square) const
{
  return m_board->GetMoves(square);
}

std::string ribi::Chess::Game::GetVersion()
{
  return "0.1";
}

std::vector<std::string> ribi::Chess::Game::GetVersionHistory()
{
  return {
    "2012-06-16: version 0.1: initial seperation from Chess::Board"
  };
}

const ribi::Chess::BitBoard ribi::Chess::Game::GetVisibleSquares() const
{
  return m_board->GetVisibleSquares(GetActivePlayer());
}

bool ribi::Chess::Game::IsCheck() const
{
  return m_board->IsCheck(GetActivePlayer());
}

bool ribi::Chess::Game::IsCheckmate() const
{
  ///TODO
  return IsCheck();
}

const boost::shared_ptr<ribi::Chess::Score>& ribi::Chess::Game::Score() const
{
  return m_score;
}

#ifndef NDEBUG
void ribi::Chess::Game::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    Chess::File(0);
    Chess::Rank(3);
    Chess::SquareFactory();
    Chess::Score("1-0");
    Chess::MoveFactory();
    Chess::BoardFactory();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  {
    if (verbose) { TRACE("Testing Game"); }
    Chess::Game();
  }
}
#endif

bool ribi::Chess::operator==(const Game& lhs, const Game& rhs)
{
  if (!lhs.Score() &&  rhs.Score()) return false;
  if ( lhs.Score() && !rhs.Score()) return false;
  if ( lhs.Score() &&  rhs.Score())
  {
    if (*lhs.Score() != *rhs.Score()) return false;
  }
  return *lhs.m_board == *rhs.m_board;
}

bool ribi::Chess::operator!=(const Game& lhs, const Game& rhs)
{
  return !(lhs == rhs);
}

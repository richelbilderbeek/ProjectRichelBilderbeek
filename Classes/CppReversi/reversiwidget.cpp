#include "reversiwidget.h"

#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>

#include "reversimove.h"
#include "reversiboard.h"
#include "trace.h"
#pragma GCC diagnostic pop

static_assert(
     static_cast<int>(ribi::reversi::Widget::empty  )
  == static_cast<int>(ribi::reversi::Board::empty  ),"enums must have same value");
static_assert(
     static_cast<int>(ribi::reversi::Widget::player1)
  == static_cast<int>(ribi::reversi::Board::player1),"enums must have same value");
static_assert(
     static_cast<int>(ribi::reversi::Widget::player2)
  == static_cast<int>(ribi::reversi::Board::player2),"enums must have same value");

ribi::reversi::Widget::Widget(const int size)
  : m_board(new Board(size)),
    m_current_player(player1)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(size > 0);
  assert(size == m_board->GetSize());

  #ifndef NDEBUG
  const int x = size / 2 - 1;
  const int y = size / 2 - 1;
  assert(m_board->Get(x  ,y  ) == player1);
  assert(m_board->Get(x+1,y  ) == player2);
  assert(m_board->Get(x  ,y+1) == player2);
  assert(m_board->Get(x+1,y+1) == player1);
  #endif
}

bool ribi::reversi::Widget::CanDoMove(const boost::shared_ptr<const ribi::reversi::Move> move) const noexcept
{
  assert(move);
  if (boost::dynamic_pointer_cast<const ribi::reversi::MovePass>(move))
  {
    //Can always pass for now
    return true;
  }
  const boost::shared_ptr<const ribi::reversi::MovePlacePiece> place {
    boost::dynamic_pointer_cast<const ribi::reversi::MovePlacePiece>(move)
  };
  assert(place);
  return CanDoMove(place->GetX(),place->GetY());
}

bool ribi::reversi::Widget::CanDoMove(const int x, const int y) const noexcept
{
  return m_board->CanDoMove(x,y,GetCurrentPlayer());
}

void ribi::reversi::Widget::DoMove(const boost::shared_ptr<const ribi::reversi::Move> move) noexcept
{
  assert(CanDoMove(move));
  assert(move);
  if (boost::dynamic_pointer_cast<const ribi::reversi::MovePass>(move))
  {
    DoMovePass();
  }
  const boost::shared_ptr<const ribi::reversi::MovePlacePiece> place {
    boost::dynamic_pointer_cast<const ribi::reversi::MovePlacePiece>(move)
  };
  assert(place);
  assert(CanDoMove(place->GetX(),place->GetY()));
  DoMove(place->GetX(),place->GetY());
}


void ribi::reversi::Widget::DoMove(const int x, const int y) noexcept
{
  assert(GetBoard()->CanDoMove(x,y,GetCurrentPlayer()));
  m_board->DoMove(x,y,GetCurrentPlayer());
  TogglePlayer();
}

void ribi::reversi::Widget::DoMovePass() noexcept
{
  TogglePlayer();
}

const std::string ribi::reversi::Widget::GetVersion() noexcept
{
  return "1.0";
}


const std::vector<std::string> ribi::reversi::Widget::GetVersionHistory() noexcept
{
  return {
    "2013-12-19: version 1.0: split off from Reversi",
  };
}

void ribi::reversi::Widget::TogglePlayer()
{
  switch (GetCurrentPlayer())
  {
    case player1: m_current_player = player2; return;
    case player2: m_current_player = player1; return;
    default: assert(!"Should not get here");
  }
}


const std::vector<std::pair<int,int>> ribi::reversi::Widget::GetValidMoves() const noexcept
{
  return m_board->GetValidMoves(GetCurrentPlayer());
}

int ribi::reversi::Widget::GetOtherPlayer() const noexcept
{
  switch (GetCurrentPlayer())
  {
    case player1: return player2;
    case player2: return player1;
    default: assert(!"Should not get here");
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::reversi::Widget::GetOtherPlayer: invalid player");
}

int ribi::reversi::Widget::GetWinner() const noexcept
{
  //static_assert(std::is_same<ribi::reversi::Widget::player1,Board::player1>(),"");
  //If both players cannot do moves, count the tiles
  if (GetBoard()->GetValidMoves(GetCurrentPlayer()).empty())
  {
    Board r(*m_board);
    const int other_player = GetOtherPlayer();
    if (!r.GetValidMoves(other_player).empty())
    {
      static_assert(static_cast<int>(ribi::reversi::Widget::player1) == static_cast<int>(Board::player1),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player2) == static_cast<int>(Board::player2),"enums must have same value");
      const int n_1 { r.Count(ribi::reversi::Widget::player1) };
      const int n_2 { r.Count(ribi::reversi::Widget::player2) };
      if (n_1 > n_2) return ribi::reversi::Widget::player1;
      if (n_2 > n_1) return ribi::reversi::Widget::player2;
      assert(n_1 == n_2);
      return ribi::reversi::Widget::draw;

    }
  }
  return ribi::reversi::Widget::empty;
}

#ifndef NDEBUG
void ribi::reversi::Widget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TestReversiMenuDialog::Test()");
  {
    ribi::reversi::Widget r(4);
    assert(r.GetCurrentPlayer() == Board::player1);
    assert(r.GetBoard()->Get(1,1) == Board::player1);
    assert(r.GetBoard()->Get(1,2) == Board::player2);
    assert(r.GetBoard()->Get(2,1) == Board::player2);
    assert(r.GetBoard()->Get(2,2) == Board::player1);
    assert(r.GetBoard()->Get(0,0) == Board::empty);
    assert(r.GetBoard()->Get(2,0) == Board::empty);
    assert(r.CanDoMove(2,0));
    assert(r.CanDoMove(3,1));
    assert(r.CanDoMove(0,2));
    assert(r.CanDoMove(1,3));
    assert(r.GetValidMoves().size() == 4);
  }
  //Play random games
  for (int sz = 4; sz != 10; ++sz)
  {
    ribi::reversi::Widget r(sz);
    while (!r.GetValidMoves().empty())
    {
      static_assert(static_cast<int>(ribi::reversi::Widget::empty  ) == static_cast<int>(Board::empty  ),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player1) == static_cast<int>(Board::player1),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player2) == static_cast<int>(Board::player2),"enums must have same value");
      assert(r.GetWinner() == ribi::reversi::Widget::empty);
      std::vector<std::pair<int,int>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const std::pair<int,int> move = m[0];
      assert(r.CanDoMove(move.first,move.second));
      r.DoMove(move.first,move.second);
    }
  }
  TRACE("Finished ribi::TestReversiMenuDialog::Test()");
}
#endif

std::ostream& ribi::reversi::operator<<(std::ostream& os, const ribi::reversi::Widget& r)
{
  os << *r.GetBoard()
    << '\n'
    << r.GetCurrentPlayer();

  return os;
}

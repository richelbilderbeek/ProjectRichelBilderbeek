//---------------------------------------------------------------------------
/*
pylos::Game, class for a game of Pylos/Phyraos
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPylos.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include "pylosgame.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/shared_ptr.hpp>

#include "pylosboard.h"
#include "pyloscurrentmovestate.h"
#include "testtimer.h"
#include "pylosmove.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::pylos::Game::Game(const Game& rhs)
  : m_board(rhs.m_board->Clone()),
    m_current_move(new CurrentMoveState(*rhs.m_current_move)),
    m_current_player(rhs.m_current_player),
    m_move_history(rhs.m_move_history)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_board != rhs.m_board);
  assert(m_current_move != rhs.m_current_move);
}

ribi::pylos::Game::Game(const boost::shared_ptr<Board> &board)
  : m_board(board),
    m_current_move(new CurrentMoveState),
    m_current_player(Player::player1),
    m_move_history{}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_board);
}

bool ribi::pylos::Game::CanDo(const pylos::Move& m) const
{
  return m_board->CanDo(m,m_current_player);
}

bool ribi::pylos::Game::CanDo(const std::string& s) const
{
  return m_board->CanDo(s,m_current_player);
}

bool ribi::pylos::Game::CanRemove(const Coordinat& c) const
{
  if (m_board->Get(c) != m_current_player) return false;

  return m_board->CanRemove( std::vector<Coordinat>(1,c), m_current_player);
}

bool ribi::pylos::Game::CanRemove(const std::vector<Coordinat>& v) const
{
  assert(!v.empty());
  if (std::count_if(v.begin(),v.end(),
    [this](const Coordinat& c)
    {
      return m_board->Get(c) != m_current_player;
    }
  ) > 0) return false;

  return m_board->CanRemove(v, m_current_player);
}

bool ribi::pylos::Game::CanSet(const Coordinat& c) const
{
  return m_board->CanSet(c,m_current_player);
}

bool ribi::pylos::Game::CanTransfer(const Coordinat& c) const
{
  if (m_board->Get(c) != GetCurrentTurn()) return false;

  return m_board->CanTransfer(c,m_current_player);
}

bool ribi::pylos::Game::CanTransfer(const Coordinat& from,
  const Coordinat& to) const
{
  if (m_board->Get(from) != GetCurrentTurn()) return false;

  return m_board->CanTransfer(from,to,m_current_player);
}

void ribi::pylos::Game::Do(const std::string& s)
{
  #ifndef NDEBUG
  if (!CanDo(s)) TRACE(s);
  #endif
  assert(CanDo(s));
  Do(pylos::Move(s));
}

void ribi::pylos::Game::Do(const pylos::Move& m)
{
  assert(CanDo(m));
  m_board->Do(m,m_current_player);
  m_current_move->SetMove(m);
  TogglePlayer();
}

boost::shared_ptr<ribi::pylos::Game> ribi::pylos::Game::CreateAdvancedGame()
{
  boost::shared_ptr<Board> board(Board::CreateAdvancedBoard());
  return boost::shared_ptr<Game>(new Game(board));
}

boost::shared_ptr<ribi::pylos::Game> ribi::pylos::Game::CreateBasicGame()
{
  boost::shared_ptr<Board> board(Board::CreateBasicBoard());
  return boost::shared_ptr<Game>(new Game(board));
}

const std::vector<ribi::pylos::Move> ribi::pylos::Game::GetAllPossibleMoves() const noexcept
{
  return m_board->GetAllPossibleMoves(m_current_player);
}

ribi::pylos::Player ribi::pylos::Game::GetCurrentTurn() const noexcept
{
  return m_current_player;
}

std::string ribi::pylos::Game::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::Game::GetVersionHistory() noexcept
{
  return {
    "2010-09-19: version 0.1: initial version",
    "2010-09-21: version 0.2: use of Coordinat",
    "2010-09-21: version 0.3: added Move",
    "2010-09-22: version 1.0: fixed bug in Coordinat, added move history",
    "2012-05-05: version 2.0: major achitectural rewrite"
  };
}

ribi::pylos::Winner ribi::pylos::Game::GetWinner() const noexcept
{
  return m_board->GetWinner();
}

ribi::pylos::MustRemoveState ribi::pylos::Game::GetMustRemove() const noexcept
{
  return m_current_move->GetMustRemove();
}

ribi::pylos::Winner ribi::pylos::Game::PlayRandomGame(const boost::shared_ptr<Board>& board)
{
  boost::shared_ptr<Game> p;
  if (board)
  {
    p.reset(new Game(board->Clone()));
  }
  else
  {
    if ((std::rand() >> 4) % 2)
      p.reset(new Game(Board::CreateAdvancedBoard()));
    else
      p.reset(new Game(Board::CreateBasicBoard()));
  }
  while (1)
  {
    if (p->GetWinner() != Winner::none)
    {
      return p->GetWinner();
    }
    //Choose algorithm to draw next move
    if ((std::rand() >> 4) % 2)
    {
      //Use random move from GetAllPossibleMoves
      const std::vector<Move> v = p->GetAllPossibleMoves();
      const int i = std::rand() % v.size();
      //TRACE(v[i]);
      p->Do(v[i]);
    }
    else
    {
      //Use random coordinats and random responses
      const Coordinat c = GetRandomCoordinat();
      if (p->CanTransfer(c))
      {
        std::vector<pylos::Coordinat> v = pylos::GetAllCoordinats();
        std::random_shuffle(std::begin(v),std::end(v));
        const std::size_t sz = v.size();
        for (std::size_t i = 0; i!=sz; ++i)
        {
          if (p->CanTransfer(c,v[i]))
          {
            p->Transfer(c,v[i]);
            break;
          }
        }
      }
      else if (p->CanSet(c))
      {
         p->Set(c);
      }
      while (p->GetMustRemove() != MustRemoveState::no)
      {
        std::vector<Coordinat> v;
        v.push_back(GetRandomCoordinat());
        if ((std::rand() >> 4) % 2) v.push_back(GetRandomCoordinat());
        if (p->CanRemove(v)) p->Remove(v);
      }
    }
  }
}

void ribi::pylos::Game::Remove(const Coordinat& c)
{
  assert(GetMustRemove() != MustRemoveState::no);
  assert(m_board->Get(c)==m_current_player);
  assert(m_board->CanRemove(std::vector<Coordinat>(1,c),m_current_player));
  m_board->Remove(std::vector<Coordinat>(1,c),m_current_player);
  ///\warning: do not allow these lines: this method
  ///is an internal function used by
  ///void ribi::pylos::Game::Remove(const std::vector<Coordinat>& v).
  //m_must_remove = false;
  //TogglePlayer();

}

void ribi::pylos::Game::Remove(const std::vector<Coordinat>& v)
{
  //Cannot call RemoveMarbles(c), because this
  //also toggles the player
  assert(GetMustRemove() != MustRemoveState::no);
  assert(CanRemove(v));
  assert(v.size() == 1 || v.size() == 2);
  assert(m_board->Get(v[0]) == m_current_player);
  assert(v.size() == 1 || m_board->Get(v[1]) == m_current_player);
  assert(v.size() == 1 || v[0] != v[1]);
  //Proper ordering: v[0] must be marble above
  if (v.size() == 2 && v[0].GetLayer() < v[1].GetLayer())
  {
    std::vector<Coordinat> w(v);
    std::swap(w[0],w[1]);
    Remove(w); //Call the same method with different order
    return;
  }
  //Assert proper ordering
  assert(v.size() == 1 || v[0].GetLayer() >= v[1].GetLayer());
  std::for_each(v.begin(),v.end(),
    [this](const Coordinat& c)
    {
      assert(m_board->Get(c)==m_current_player);
      this->Remove(c);
    }
  );

  ///Three lines below must be executed exactly once per move
  m_current_move->SetRemove(v);
  m_current_move->SetMustRemove(MustRemoveState::no);
  TogglePlayer();
}

void ribi::pylos::Game::Set(const Coordinat& c)
{
  #ifndef NDEBUG
  if (!CanSet(c)) TRACE(c);
  #endif
  //Set is always done as the first part of a Move
  assert(CanSet(c));

  MustRemoveState must_remove = GetMustRemove();
  assert(!must_remove && "Player must not remove a marble when placing a new one");
  m_board->Set(c,m_current_player,must_remove);
  if (must_remove != MustRemoveState::no) m_current_move->SetMustRemove(
    ToMustRemoveState(m_current_player));

  m_current_move->SetMoveSet(c);

  if (must_remove != MustRemoveState::no)
  {
    const Player player = ToPlayer(m_board->Get(c));
    m_current_move->SetMustRemove(ToMustRemoveState(player));
  }
  else
  {
    //If player must not remove another marble,
    //his/her turn is over
    TogglePlayer();
  }
}

#ifndef NDEBUG
void ribi::pylos::Game::Test() noexcept
{
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  const int testing_depth = 1;

  if (verbose) { TRACE("Test ribi::pylos::Game::operator== for different game types"); }
  {
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    assert(*a != *b);
    a->Set(Coordinat("(0,0,0)"));
    assert(*a != *b);
    b->Do("(0,0,0)");
    assert(*a != *b);
  }
  if (verbose) { TRACE("Test ribi::pylos::Game::operator== for same game types"); }
  {
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateAdvancedGame();
    assert(*a == *b);
    a->Do("(0,0,0)");
    assert(*a != *b);
    b->Do("(0,0,0)");
    assert(*a == *b);
  }
  if (verbose) { TRACE("Test basic Game dynamics using Set and Remove"); }
  {
    // 1
    // 1
    // 1 22
    // 1 22
    // Only advanced game must detect player 1's line
    // Both games must detect player 2's square
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    assert(*a != *b);
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    a->Set(Coordinat("(0,0,0)"));
    b->Set(Coordinat("(0,0,0)"));
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Set(Coordinat("(0,3,0)"));
    b->Set(Coordinat("(0,3,0)"));
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    a->Set(Coordinat("(0,0,1)"));
    b->Set(Coordinat("(0,0,1)"));
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Set(Coordinat("(0,2,0)"));
    b->Set(Coordinat("(0,2,0)"));
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    a->Set(Coordinat("(0,0,2)"));
    b->Set(Coordinat("(0,0,2)"));
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Set(Coordinat("(0,2,1)"));
    b->Set(Coordinat("(0,2,1)"));
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    //BoardAdvanced responds to the creation of a line
    a->Set(Coordinat("(0,0,3)")); //Line
    b->Set(Coordinat("(0,0,3)")); //Line
    assert(a->GetCurrentTurn() == Player::player1); //No toggle
    assert(b->GetCurrentTurn() == Player::player2); //Toggle
    assert( a->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    assert(!b->GetCurrentMove()->GetMustRemove());
    assert( a->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,0,0)"))));
    assert(!b->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,0,0)"))));
    a->Remove(std::vector<Coordinat>(1,Coordinat("(0,0,0)")));
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    assert(a->GetCurrentTurn() == Player::player2); //Toggle
    assert(b->GetCurrentTurn() == Player::player2);

    //BoardAdvanced and BoardBasic respond to the creation of a square
    a->Set(Coordinat("(0,3,1)")); //Square
    b->Set(Coordinat("(0,3,1)")); //Square
    assert(a->GetCurrentTurn() == Player::player2); //No toggle
    assert(b->GetCurrentTurn() == Player::player2); //No toggle
    assert(a->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    assert(b->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    assert(a->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    assert(b->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    a->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    b->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
  }
  if (verbose) { TRACE("Test ribi::pylos::Game::Clone of GameBasic"); }
  {
    boost::shared_ptr<Game> a = CreateBasicGame();
    boost::shared_ptr<Game> b(new Game(*a));
    boost::shared_ptr<Game> c = CreateAdvancedGame();
    assert(*a == *b);
    assert(*a != *c);
    a->Set(Coordinat("(0,0,0)"));
    assert(*a != *b);
    assert(*a != *c);
    b->Set(Coordinat("(0,0,0)"));
    assert(*a == *b);
    assert(*a != *c);
    c->Set(Coordinat("(0,0,0)"));
    assert(*a != *c);
    assert(*b != *c);
  }
  if (verbose) { TRACE("Test ribi::pylos::Game::Clone of GameAdvanced"); }
  {
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b(new Game(*a));
    boost::shared_ptr<Game> c = CreateBasicGame();
    assert(*a == *b);
    assert(*a != *c);
    a->Set(Coordinat("(0,0,0)"));
    assert(*a != *b);
    assert(*a != *c);
    b->Set(Coordinat("(0,0,0)"));
    assert(*a == *b);
    assert(*a != *c);
  }
  if (verbose) { TRACE("Test Clone of played GameBasic"); }
  {
    boost::shared_ptr<Game> a = CreateBasicGame();
    a->Set(Coordinat("(0,0,0)"));
    const boost::shared_ptr<Game> b(new Game(*a));
    assert(*a == *b);
    b->Set(Coordinat("(0,1,0)"));
    assert(*a != *b);
  }
  if (verbose) { TRACE("Test Clone of played BoardAdvanced"); }
  {
    const boost::shared_ptr<Game> a = CreateAdvancedGame();
    a->Set(Coordinat("(0,0,0)"));
    const boost::shared_ptr<Game> b(new Game(*a));
    assert(*a == *b);
    b->Set(Coordinat("(0,1,0)"));
    assert(*a != *b);
  }
  if (verbose) { TRACE("Test basic Game dynamics using full moves"); }
  {
    // 1
    // 1
    // 1 22
    // 1 22
    // Only advanced game must detect player 1's line
    // Both games must detect player 2's square
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    assert(*a != *b);
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,0,0)"));
    b->Do(Move("(0,0,0)"));
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,3,0)"));
    b->Do(Move("(0,3,0)"));
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    a->Do(Move("(0,0,1)"));
    b->Do(Move("(0,0,1)"));
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,2,0)"));
    b->Do(Move("(0,2,0)"));
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    a->Do(Move("(0,0,2)"));
    b->Do(Move("(0,0,2)"));
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,2,1)"));
    b->Do(Move("(0,2,1)"));
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());

    //BoardAdvanced responds to the creation of a line
    assert(!a->CanDo("(0,0,3)"));
    assert(a->CanDo("(0,0,3) !(0,0,0)"));
    assert(a->CanDo("(0,0,3) !(0,0,1)"));
    assert(a->CanDo("(0,0,3) !(0,0,2)"));
    assert(a->CanDo("(0,0,3) !(0,0,3)"));
    assert(a->CanDo("(0,0,3) !(0,0,0) !(0,0,1)"));
    assert(a->CanDo("(0,0,3) !(0,0,0) !(0,0,2)"));
    assert(a->CanDo("(0,0,3) !(0,0,0) !(0,0,3)"));
    assert(a->CanDo("(0,0,3) !(0,0,1) !(0,0,0)"));
    assert(a->CanDo("(0,0,3) !(0,0,1) !(0,0,2)"));
    assert(a->CanDo("(0,0,3) !(0,0,1) !(0,0,3)"));
    assert(a->CanDo("(0,0,3) !(0,0,2) !(0,0,0)"));
    assert(a->CanDo("(0,0,3) !(0,0,2) !(0,0,1)"));
    assert(a->CanDo("(0,0,3) !(0,0,2) !(0,0,3)"));
    assert(a->CanDo("(0,0,3) !(0,0,3) !(0,0,0)"));
    assert(a->CanDo("(0,0,3) !(0,0,3) !(0,0,1)"));
    assert(a->CanDo("(0,0,3) !(0,0,3) !(0,0,2)"));
    assert(!a->CanDo("(0,0,3) !(0,0,0) !(0,0,0)"));
    assert(!a->CanDo("(0,0,3) !(0,0,1) !(0,0,1)"));
    assert(!a->CanDo("(0,0,3) !(0,0,2) !(0,0,2)"));
    assert(!a->CanDo("(0,0,3) !(0,0,3) !(0,0,3)"));
    assert(b->CanDo("(0,0,3)"));
    assert(!b->CanDo("(0,0,3) !(0,0,0)"));
    assert(!b->CanDo("(0,0,3) !(0,0,1)"));
    assert(!b->CanDo("(0,0,3) !(0,0,2)"));
    assert(!b->CanDo("(0,0,3) !(0,0,3)"));
    assert(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,1)"));
    assert(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,2)"));
    assert(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,3)"));
    assert(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,0)"));
    assert(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,2)"));
    assert(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,3)"));
    assert(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,0)"));
    assert(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,1)"));
    assert(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,3)"));
    assert(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,0)"));
    assert(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,1)"));
    assert(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,2)"));
    assert(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,0)"));
    assert(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,1)"));
    assert(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,2)"));
    assert(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,3)"));
    a->Do(Move("(0,0,3) !(0,0,0)")); //Line
    b->Do(Move("(0,0,3)")); //Line
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    assert(a->GetCurrentTurn() == Player::player2);
    assert(b->GetCurrentTurn() == Player::player2);

    //BoardAdvanced and BoardBasic respond to the creation of a square
    a->Set(Coordinat("(0,3,1)")); //Square
    b->Set(Coordinat("(0,3,1)")); //Square
    assert(a->GetCurrentTurn() == Player::player2); //No toggle
    assert(b->GetCurrentTurn() == Player::player2); //No toggle
    assert(a->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    assert(b->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    assert(a->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    assert(b->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    a->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    b->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    assert(!a->GetCurrentMove()->GetMustRemove());
    assert(!b->GetCurrentMove()->GetMustRemove());
    assert(a->GetCurrentTurn() == Player::player1);
    assert(b->GetCurrentTurn() == Player::player1);
  }


  if (verbose) { TRACE("Test Game history"); }
  {
    // 12..
    // 34..
    // 56..
    // 7...
    //Test that in basic play, no marbles must be removed. Test that in advanced play, marbles must be removed.
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    assert(a->GetMoveHistory().empty());
    assert(b->GetMoveHistory().empty());
    const std::vector<Move> v =
      {
        Move("(0,0,0)"),
        Move("(0,1,0)"),
        Move("(0,0,1)"),
        Move("(0,1,1)"),
        Move("(1,0,0)")
      };
    const std::size_t j = v.size();
    for (std::size_t i = 0; i!=j; ++i)
    {
      assert(a->GetMoveHistory().size() == i);
      assert(b->GetMoveHistory().size() == i);
      a->Do(v[i]);
      b->Do(v[i]);
      assert(a->GetMoveHistory()[i] == v[i]);
      assert(b->GetMoveHistory()[i] == v[i]);
    }
  }


  if (verbose) { TRACE("Game test #1"); }
  {
    // 12..
    // 34..
    // 56..
    // 7...
    //Test that in basic play, no marbles must be removed. Test that in advanced play, marbles must be removed.
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    a->Do(Move("(0,0,0)")); //1
    b->Do(Move("(0,0,0)"));
    a->Do(Move("(0,1,0)")); //2
    b->Do(Move("(0,1,0)"));
    a->Do(Move("(0,0,1)")); //3
    b->Do(Move("(0,0,1)"));
    a->Do(Move("(0,1,1)")); //4
    b->Do(Move("(0,1,1)"));
    a->Do(Move("(0,0,2)")); //5
    b->Do(Move("(0,0,2)"));
    a->Do(Move("(0,1,2)")); //6
    b->Do(Move("(0,1,2)"));
    assert(!a->CanDo(Move("(0,0,3)"))); //7
    assert( a->CanDo(Move("(0,0,3) !(0,0,3)"))); //7
    assert( b->CanDo(Move("(0,0,3)")));
  }
  if (verbose) { TRACE("Game test #2"); }
  {
    // ....
    // ....
    // ....
    // ....
    //Test that in basic play, no marbles must be removed. Test that in advanced play, marbles must be removed.
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    const std::vector<Move> v =
      {
        Move("(0,0,0)"), Move("(0,0,1)"), Move("(0,1,1)"), Move("(0,1,0)"),
        Move("(1,0,0)"), Move("(0,0,2)"), Move("(0,1,2)"), Move("(0,2,0)"),
        Move("(0,2,2)"), Move("(0,3,0)")
      };
    std::for_each(v.begin(),v.end(),
      [a,b](const Move& m)
      {
        #ifndef NDEBUG
        if (!a->CanDo(m)) TRACE(m);
        if (!b->CanDo(m)) TRACE(m);
        #endif
        assert(a->CanDo(m));
        assert(b->CanDo(m));
        a->Do(m);
        b->Do(m);
      }
    );
    assert(!a->CanDo(Move("(0,2,1)")));
    assert(!a->CanDo(Move("(0,2,1) !(0,0,0)")));
    assert( a->CanDo(Move("(0,2,1) !(1,0,0)")));
    assert( a->CanDo(Move("(0,2,1) !(0,0,0) !(1,0,0)")));
    assert( a->CanDo(Move("(0,2,1) !(1,0,0) !(0,0,0)")));
    assert(!a->CanDo(Move("(0,2,1) !(0,1,1)")));
    assert( a->CanDo(Move("(0,2,1) !(0,1,1) !(1,0,0)")));
    assert( a->CanDo(Move("(0,2,1) !(1,0,0) !(0,1,1)")));

    assert(!b->CanDo(Move("(0,2,1)")));
    assert(!b->CanDo(Move("(0,2,1) !(0,0,0)")));
    assert( b->CanDo(Move("(0,2,1) !(1,0,0)")));
    assert( b->CanDo(Move("(0,2,1) !(0,0,0) !(1,0,0)")));
    assert( b->CanDo(Move("(0,2,1) !(1,0,0) !(0,0,0)")));
    assert(!b->CanDo(Move("(0,2,1) !(0,1,1)")));
    assert( b->CanDo(Move("(0,2,1) !(0,1,1) !(1,0,0)")));
    assert( b->CanDo(Move("(0,2,1) !(1,0,0) !(0,1,1)")));
  }
  if (testing_depth < 2) return;

  if (verbose) { TRACE("Playing 5 random basic Pylos games"); }
  for (int i=0; i!=5; ++i)
  {
    ribi::pylos::Game::PlayRandomGame(pylos::Board::CreateBasicBoard());
  }
  if (verbose) { TRACE("Playing 5 random advanced Pylos games"); }
  for (int i=0; i!=5; ++i)
  {
    ribi::pylos::Game::PlayRandomGame(pylos::Board::CreateAdvancedBoard());
  }
  if (verbose) { TRACE("Playing 5 random Pylos games"); }
  for (int i=0; i!=5; ++i)
  {
    ribi::pylos::Game::PlayRandomGame();
  }
}
#endif

void ribi::pylos::Game::TogglePlayer()
{
  assert(!m_current_move->GetMustRemove()
    && "First the current player must remove one or two marbles");
  m_move_history.push_back(m_current_move->GetMove());
  m_current_move.reset(new CurrentMoveState);
  m_current_player = (m_current_player == Player::player1 ? Player::player2 : Player::player1);
}

void ribi::pylos::Game::Transfer(
    const Coordinat& from,
    const Coordinat& to)
{
  assert(CanTransfer(from,to));

  m_board->Remove(std::vector<Coordinat>(1,from),m_current_player);
  MustRemoveState must_remove = MustRemoveState::no;
  m_board->Set(to,m_current_player,must_remove);

  m_current_move->SetMoveTransfer(from,to);

  if (must_remove != MustRemoveState::no)
  {
    const Player player = ToPlayer(m_board->Get(to));
    m_current_move->SetMustRemove(ToMustRemoveState(player));
  }
  else
  {
    //If player must not remove another marble,
    //his/her turn is over
    TogglePlayer();
  }
}

bool ribi::pylos::operator==(const Game& lhs, const Game& rhs)
{
  return *lhs.m_board          == *rhs.m_board
    &&   *lhs.m_current_move   == *rhs.m_current_move
    &&    lhs.m_current_player ==  rhs.m_current_player
    &&    lhs.m_move_history   ==  rhs.m_move_history;
}

bool ribi::pylos::operator!=(const Game& lhs, const Game& rhs)
{
  return !(lhs == rhs);
}

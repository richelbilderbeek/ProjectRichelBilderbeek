#include "tictactoegame.h"

#include <cassert>

#include "textcanvas.h"
#include "tictactoeai.h"
#include "tictactoeboard.h"
#include "tictactoehelper.h"
#include "trace.h"

ribi::tictactoe::Game::Game() noexcept
  : m_signal_changed{},
    m_board(new Board),
    m_current_player(Player::player1)

{
  #ifndef NDEBUG
  Test();
  #endif

  assert(GetCurrentTurn() == 0);
}

bool ribi::tictactoe::Game::CanDoMove(const int x, const int y) const noexcept
{
  return GetBoard()->CanDoMove(x,y);
}

void ribi::tictactoe::Game::DoMove(const int x, const int y) noexcept
{
  assert(CanDoMove(x,y));
  m_board->DoMove(x,y,m_current_player);
  m_current_player = (m_current_player == Player::player1 ? Player::player2 : Player::player1);
}

boost::shared_ptr<const ribi::tictactoe::Board> ribi::tictactoe::Game::GetBoard() const noexcept
{
  assert(m_board);
  return m_board;
}

int ribi::tictactoe::Game::GetCurrentTurn() const noexcept
{
  int turn = 0;
  for (int i=0; i!=9; ++i)
  {
    if (GetBoard()->GetSquare(i/3,i%3) != Square::empty) ++turn;
  }
  return turn;
}

int ribi::tictactoe::Game::GetSummarizedState() const noexcept
{
  //MSB: player
  //LSB: board
  int z = m_board->GetSummarizedState();
  z += (PlayerToState(m_current_player) * Helper().IntPower(3,9));
  return z;
}

std::string ribi::tictactoe::Game::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::tictactoe::Game::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2014-03-17: version 1.0: initial version, extracted from Board"
  };
  return v;
}

ribi::tictactoe::Winner ribi::tictactoe::Game::GetWinner() const noexcept
{
  return GetBoard()->GetWinner();
}

void ribi::tictactoe::Game::Restart() noexcept
{
  m_board->Restart();

  if (m_current_player != Player::player1)
  {
    m_current_player = Player::player1;
    m_signal_changed(this);
  }
}

void ribi::tictactoe::Game::SetSummarizedState(const int original_state) noexcept
{
  if (GetSummarizedState() == original_state) return;

  //MSB: player
  //LSB: board

  //9 for the board, 1 for the current player
  assert(original_state < Helper().IntPower(3,9 + 1));

  int s = original_state;
  m_board->SetSummarizedState(s % Helper().IntPower(3,9));
  s /= Helper().IntPower(3,9);
  m_current_player = StateToPlayer(s);

  //Internal check
  assert(GetSummarizedState()==original_state);

  m_signal_changed(this);
}


#ifndef NDEBUG
void ribi::tictactoe::Game::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::tictactoe::Game::Test");
  {
    //Check draw detection
    {
      Game t;
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 0);
      t.DoMove(1,1);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 1);
      t.DoMove(0,0);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 2);
      t.DoMove(1,2);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 3);
      t.DoMove(1,0);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 4);
      t.DoMove(2,0);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 5);
      t.DoMove(0,2);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 6);
      t.DoMove(0,1);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 7);
      t.DoMove(2,1);
      assert(t.GetCurrentPlayer() == Player::player1);
      assert(t.GetCurrentTurn()   == 8);
      t.DoMove(2,2);
      assert(t.GetCurrentPlayer() == Player::player2);
      assert(t.GetCurrentTurn()   == 9);
      assert(t.GetWinner() == Winner::draw);
    }
    //Check player1 wins horizontally detection
    {
      Game t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,2);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check player2 wins vertically detection
    {
      Game t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == Winner::player2);
    }
    //Check player1 wins diagonally detection
    {
      Game t;
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(0,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,0);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,1);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(1,2);
      assert(t.GetWinner() == Winner::no_winner);
      t.DoMove(2,2);
      assert(t.GetWinner() == Winner::player1);
    }
    //Check no-winner detection
    {
      Game t;
      t.DoMove(1,1);
      t.DoMove(0,0);
      t.DoMove(1,2);
      t.DoMove(1,0);
      t.DoMove(2,0);
      t.DoMove(0,2);
      t.DoMove(0,1);
      t.DoMove(2,1);
      //t.DoMove(2,2); //Final move to make a draw
      assert(t.GetWinner() == Winner::no_winner);
    }
    //Check CanDoMove
    for (int i=0; i!=9; ++i)
    {
      Game t;
      t.DoMove(i/3,i%3);
      assert(t.CanDoMove(i/3,i%3)==false);
    }
    //Check AI's
    {
      for (int a = 0; a!=3; ++a)
      {
        for (int b = 0; b!=3; ++b)
        {
          TRACE(a);
          TRACE(b);
          boost::shared_ptr<Ai> c;
          switch (a)
          {
            case 0: c.reset(new AiEnforceDraw); break;
            case 1: c.reset(new AiEnforceWin); break;
            case 2: c.reset(new AiPlayRandom); break;
          }
          assert(c);
          boost::shared_ptr<Ai> d;
          switch (b)
          {
            case 0: d.reset(new AiEnforceDraw); break;
            case 1: d.reset(new AiEnforceWin); break;
            case 2: d.reset(new AiPlayRandom); break;
          }
          assert(d);
          Game g;
          while (g.GetWinner() == Winner::no_winner)
          {
            const std::pair<int,int> move_1(c->SuggestMove(g));
            assert(g.CanDoMove(move_1.first,move_1.second));
            g.DoMove(move_1.first,move_1.second);
            if (g.GetWinner() != Winner::no_winner) break;
            const std::pair<int,int> move_2(c->SuggestMove(g));
            assert(g.CanDoMove(move_2.first,move_2.second));
            g.DoMove(move_2.first,move_2.second);
          }
          TRACE(WinnerToName(g.GetWinner()));
        }
      }
      assert(1==2);
    }
  }
  TRACE("Finished ribi::tictactoe::Board::Test successfully");
}
#endif

boost::shared_ptr<ribi::TextCanvas> ribi::tictactoe::Game::ToTextCanvas() const noexcept
{
  return GetBoard()->ToTextCanvas();
}


std::ostream& ribi::tictactoe::operator<<(std::ostream& os,const ribi::tictactoe::Game& t) noexcept
{
  os << (*t.GetBoard());
  return os;
}

bool ribi::tictactoe::operator==(const ribi::tictactoe::Game& lhs, const ribi::tictactoe::Game& rhs) noexcept
{
  return *lhs.GetBoard() == *rhs.GetBoard()
      && lhs.GetCurrentPlayer() == rhs.GetCurrentPlayer()
  ;
}

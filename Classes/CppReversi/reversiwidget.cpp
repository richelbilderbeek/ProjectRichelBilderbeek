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
    m_current_player(player1),
    m_undo{}
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

ribi::reversi::Widget::Widget(const Widget& other)
  : m_board(boost::shared_ptr<Board>(new Board(*other.m_board))),
    m_current_player(other.m_current_player),
    m_undo(other.m_undo)
{
  assert(m_board);
  assert(*m_board == *other.m_board && "Must be a copy");
  assert( m_board !=  other.m_board && "Must be a deep copy");
  assert(m_current_player == other.m_current_player);
  assert(*this == other && "Must be a copy");
}

ribi::reversi::Widget& ribi::reversi::Widget::operator=(const Widget& other)
{
  m_board = boost::shared_ptr<Board>(new Board(*other.m_board));
  m_current_player = other.m_current_player;
  m_undo = other.m_undo;

  assert(m_board);
  assert(*m_board == *other.m_board && "Must be a copy");
  assert( m_board !=  other.m_board && "Must be a deep copy");
  assert(m_current_player == other.m_current_player);
  assert(*this == other && "Must be a copy");
  return *this;
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
  assert(move);
  return CanDoMove(place->GetX(),place->GetY());
}

bool ribi::reversi::Widget::CanDoMove(const int x, const int y) const noexcept
{
  return m_board->CanDoMove(x,y,GetCurrentPlayer());
}

void ribi::reversi::Widget::DoMove(const boost::shared_ptr<const ribi::reversi::Move> move) noexcept
{
  #ifndef NDEBUG
  assert(move);
  if(!CanDoMove(move))
  {
    TRACE("ERROR");
    TRACE(*this);
    TRACE(move->ToStr());
    TRACE("ERROR");
  }
  #endif
  assert(CanDoMove(move));

  //Undo
  {
    const boost::shared_ptr<Widget> prev_widget {
      new Widget(*this)
    };
    m_undo.push_back(std::make_pair(prev_widget,move));
    assert(prev_widget->GetCurrentPlayer() == this->GetCurrentPlayer());
  }
  //Actually do the move
  assert(move);
  if (boost::dynamic_pointer_cast<const ribi::reversi::MovePass>(move))
  {
    DoMovePass();
  }
  else
  {
    const boost::shared_ptr<const ribi::reversi::MovePlacePiece> place {
      boost::dynamic_pointer_cast<const ribi::reversi::MovePlacePiece>(move)
    };
    assert(place);
    assert(CanDoMove(place->GetX(),place->GetY()));
    DoMove(place->GetX(),place->GetY());
  }
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

const std::vector<boost::shared_ptr<ribi::reversi::Move>> ribi::reversi::Widget::GetValidMoves() const noexcept
{
  std::vector<boost::shared_ptr<Move>> moves;
  for (const std::pair<int,int> p: m_board->GetValidMoves(GetCurrentPlayer()))
  {
    const boost::shared_ptr<Move> move {
      new MovePlacePiece(p.first,p.second)
    };
    assert(move);
    moves.push_back(move);
  }
  const boost::shared_ptr<Move> move_pass {
    new MovePass
  };
  moves.push_back(move_pass);
  return moves;
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
    assert(r.GetValidMoves().size() == 5); //4 place moves and one pass
  }
  TRACE("Play random games")
  for (int sz = 4; sz != 6; ++sz)
  {
    ribi::reversi::Widget r(sz);
    while (r.GetValidMoves().size() > 1) //Pass is always allowed
    {
      static_assert(static_cast<int>(ribi::reversi::Widget::empty  ) == static_cast<int>(Board::empty  ),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player1) == static_cast<int>(Board::player1),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player2) == static_cast<int>(Board::player2),"enums must have same value");
      assert(r.GetWinner() == ribi::reversi::Widget::empty);
      std::vector<boost::shared_ptr<ribi::reversi::Move>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const boost::shared_ptr<ribi::reversi::Move> move = m[0];
      assert(r.CanDoMove(move));
      r.DoMove(move);
    }
  }
  TRACE("Test copy constructor and operator== and operator!=");
  {
    const int sz = 4;
    ribi::reversi::Widget r(sz);
    while (r.GetValidMoves().size() > 1) //Pass is always allowed
    {
      static_assert(static_cast<int>(ribi::reversi::Widget::empty  ) == static_cast<int>(Board::empty  ),"enums must have same value");
      assert(r.GetWinner() == ribi::reversi::Widget::empty);
      assert(r == r);
      std::vector<boost::shared_ptr<ribi::reversi::Move>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const boost::shared_ptr<ribi::reversi::Move> move = m[0];
      assert(move);
      assert(r.CanDoMove(move));
      Widget before(r);
      assert(r == before);

      r.DoMove(move);

      assert(before != r);
      assert(before.CanDoMove(move));

      before.DoMove(move);

      assert(before == r);
    }
  }
  TRACE("Test undo functionality in a single game");
  {
    const int sz = 4;
    ribi::reversi::Widget r(sz);
    while (r.GetValidMoves().size() > 1) //Pass is always allowed
    {
      static_assert(static_cast<int>(ribi::reversi::Widget::empty  ) == static_cast<int>(Board::empty  ),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player1) == static_cast<int>(Board::player1),"enums must have same value");
      static_assert(static_cast<int>(ribi::reversi::Widget::player2) == static_cast<int>(Board::player2),"enums must have same value");
      assert(r.GetWinner() == ribi::reversi::Widget::empty);
      std::vector<boost::shared_ptr<ribi::reversi::Move>> m {
        r.GetValidMoves()
      };
      assert(!m.empty());
      std::random_shuffle(m.begin(),m.end());
      const boost::shared_ptr<ribi::reversi::Move> move = m[0];
      assert(move);
      assert(r.CanDoMove(move));
      const Widget before(r);
      assert(before.CanDoMove(move));
      r.DoMove(move);
      assert(before != r);
      r.Undo();
      assert(before.GetCurrentPlayer() == r.GetCurrentPlayer());
      assert(*before.GetBoard() == *r.GetBoard());
      assert(before == r);
      assert(before.CanDoMove(move));
      assert(r.CanDoMove(move));
      r.DoMove(move);
    }
  }
  TRACE("Finished ribi::TestReversiMenuDialog::Test()");
}
#endif

void ribi::reversi::Widget::Undo()
{
  assert(!m_undo.empty());
  this->m_board = (m_undo.back().first)->GetBoard();
  assert(*m_board == *(m_undo.back().first)->GetBoard());
  #ifndef NDEBUG
  if (this->m_current_player == (m_undo.back().first)->GetCurrentPlayer())
  {
    TRACE("ERROR");
    std::clog << "\n" << *this << std::endl;
    TRACE(this->m_current_player);
  }
  #endif
  assert(this->m_current_player != (m_undo.back().first)->GetCurrentPlayer());
  this->m_current_player = (m_undo.back().first)->GetCurrentPlayer();
  m_undo.pop_back();
}

bool ribi::reversi::operator==(const ribi::reversi::Widget& lhs, const ribi::reversi::Widget& rhs)
{
  if (*lhs.GetBoard() != *rhs.GetBoard()) return false;
  if (lhs.GetCurrentPlayer() != rhs.GetCurrentPlayer()) return false;
  if (lhs.m_undo.size() != rhs.m_undo.size()) return false;
  return std::equal(
    std::begin(lhs.m_undo),
    std::end(lhs.m_undo),
    std::begin(rhs.m_undo),
    [](
      const std::pair<boost::shared_ptr<Widget>,boost::shared_ptr<const Move>> lhs,
      const std::pair<boost::shared_ptr<Widget>,boost::shared_ptr<const Move>> rhs
    )
    {
      return *(lhs.first) == *(rhs.first)
        && lhs.second->ToStr() == rhs.second->ToStr();
    }
  );
}

bool ribi::reversi::operator!=(const ribi::reversi::Widget& lhs, const ribi::reversi::Widget& rhs)
{
  return !(lhs == rhs);
}

std::ostream& ribi::reversi::operator<<(std::ostream& os, const ribi::reversi::Widget& r)
{
  os << *r.GetBoard()
    << '\n'
    << r.GetCurrentPlayer();

  return os;
}

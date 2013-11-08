
#include <cassert>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "chessboard.h"
#include "chessfile.h"
#include "chessmove.h"
#include "chesspiece.h"
#include "chesssquare.h"
#include "chesssquarefactory.h"
#include "chesssquareselector.h"
#include "chessmove.h"
#include "chesswidget.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::Chess::SquareSelector::SquareSelector()
  : m_signal_changed{},
    m_cursor(GetInitialSquare()),
    m_selected{}
{
  assert(m_cursor);
}

void ribi::Chess::SquareSelector::Click(
  const boost::shared_ptr<const Square> square,
  const bool can_select_square)
{
  assert(m_cursor);

  //No square selected: set cursor and selector on selected piece
  if (!m_selected)
  {
    m_cursor = square;
    if (can_select_square)
    {
      m_selected = square;
    }
    else
    {
      const boost::shared_ptr<const Square> no_selection;
      m_selected = no_selection;
    }
    m_signal_changed();
  }
  else
  {
    //A square is already selected

    //The selected piece is unselected: set cursor on unselected square, set selector to null
    if (*m_cursor == *m_selected)
    {
      m_cursor = square;
      const boost::shared_ptr<const Square> no_selection;
      m_selected = no_selection;
      m_signal_changed();
    }
    else
    {
      //Another square is selected: keep selector on selected piece
      //Don't care if move is valid:
      //- if move is valid,   piece   is moved and selector is removed
      //- if move is invalid, nothing is moved and selector is removed
      m_cursor = square;
      const boost::shared_ptr<const Square> no_selection;
      m_selected = no_selection;
    }
  }
  assert(m_cursor);
}

void ribi::Chess::SquareSelector::DoSelect()
{
  assert(m_cursor);

  //No square selected
  if (!m_selected)
  {
    m_selected.reset(new Square(*m_cursor));
    m_signal_changed();
  }
  else
  {
    //A square is already selected

    //The selected piece is unselected
    if (*m_cursor == *m_selected)
    {
      const boost::shared_ptr<const Square> no_selection;
      m_selected = no_selection;
      m_signal_changed();
    }
    else
    {
      //Another square is selected
      m_selected.reset(new Square(*m_cursor));
    }
  }
}

boost::shared_ptr<ribi::Chess::Square> ribi::Chess::SquareSelector::GetInitialSquare()
{
  const std::string s { "c3" };
  return SquareFactory::Create<Square>(s);
}

const std::string ribi::Chess::SquareSelector::GetVersion() noexcept
{
  return "1.0";
}

const boost::shared_ptr<const ribi::Chess::Square> ribi::Chess::SquareSelector::GetSelected() const noexcept
{
  return m_selected;
}

const std::vector<std::string> ribi::Chess::SquareSelector::GetVersionHistory() noexcept
{
  return {
    "2012-01-25: version 1.0: initial version"
  };
}

void ribi::Chess::SquareSelector::MoveDown()
{
  assert(m_cursor);
  if (m_cursor->GetRank().ToInt() != 7)
  {
    const boost::shared_ptr<const Square> square {
      SquareFactory::Create(
        File(m_cursor->GetFile().ToInt() + 0),
        Rank(m_cursor->GetRank().ToInt() + 1)
      )
    };
    m_cursor = square;

    this->m_signal_changed();
  }
}

void ribi::Chess::SquareSelector::MoveLeft()
{
  assert(m_cursor);
  if (m_cursor->GetFile().ToInt() != 0)
  {
    const boost::shared_ptr<const Square> square {
      SquareFactory::Create(
        File(m_cursor->GetFile().ToInt() - 1),
        Rank(m_cursor->GetRank().ToInt() + 0)
      )
    };
    m_cursor = square;
    this->m_signal_changed();
  }
}

void ribi::Chess::SquareSelector::MoveRight()
{
  assert(m_cursor);
  if (m_cursor->GetFile().ToInt() != 7)
  {
    const boost::shared_ptr<const Square> square {
      SquareFactory::Create(
        File(m_cursor->GetFile().ToInt() + 1),
        Rank(m_cursor->GetRank().ToInt() + 0)
      )
    };
    m_cursor = square;
    this->m_signal_changed();
  }
}


void ribi::Chess::SquareSelector::MoveUp()
{
  assert(m_cursor);
  if (m_cursor->GetRank().ToInt() != 0)
  {
    const boost::shared_ptr<const Square> square {
      SquareFactory::Create(
        File(m_cursor->GetFile().ToInt() + 0),
        Rank(m_cursor->GetRank().ToInt() - 1)
      )
    };
    m_cursor = square;
    this->m_signal_changed();
  }
}

const std::string ribi::Chess::SquareSelector::ToStr() const
{
  assert(m_cursor);
  std::string s = "Cursor: " + m_cursor->ToStr();
  if (m_selected)
  {
    s += ", selected: " + m_selected->ToStr();
  }
  return s;
}

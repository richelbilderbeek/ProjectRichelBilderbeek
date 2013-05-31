
#include <cassert>

#include <boost/lexical_cast.hpp>

#include "chessboard.h"
#include "chessfile.h"
#include "chessmove.h"
#include "chesspiece.h"
#include "chesssquare.h"
#include "chesssquareselector.h"
#include "chessmove.h"
#include "chesswidget.h"
#include "trace.h"

namespace Chess {

SquareSelector::SquareSelector()
  : m_cursor(GetInitialSquare().release())
{
  assert(m_cursor);
}

void SquareSelector::Click(
  const Chess::Square& square,
  const bool can_select_square)
{
  assert(m_cursor);

  //No square selected: set cursor and selector on selected piece
  if (!m_selected)
  {
    m_cursor.reset(new Square(square));
    if (can_select_square)
    {
      m_selected.reset(new Square(square));
    }
    else
    {
      m_selected.reset(0);
    }
    m_signal_changed();
  }
  else
  {
    //A square is already selected

    //The selected piece is unselected: set cursor on unselected square, set selector to null
    if (*m_cursor == *m_selected)
    {
      m_cursor.reset(new Square(square));
      m_selected.reset(0);
      m_signal_changed();
    }
    else
    {
      //Another square is selected: keep selector on selected piece
      //Don't care if move is valid:
      //- if move is valid,   piece   is moved and selector is removed
      //- if move is invalid, nothing is moved and selector is removed
      m_cursor.reset(new Square(square));
      m_selected.reset(0);
    }
  }
  assert(m_cursor);
}

void SquareSelector::DoSelect()
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
      m_selected.reset(0);
      m_signal_changed();
    }
    else
    {
      //Another square is selected
      m_selected.reset(new Square(*m_cursor));
    }
  }
}

std::unique_ptr<const Square> SquareSelector::GetInitialSquare()
{
  std::unique_ptr<const Square> s(new Square("c3"));
  return s;
}

const std::string SquareSelector::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> SquareSelector::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("YYYY-MM-DD: version X.Y: [description]");
  v.push_back("2012-01-25: version 1.0: initial version");
  return v;
}

void SquareSelector::MoveDown()
{
  assert(m_cursor);
  if (m_cursor->GetRank().ToInt() != 7)
  {
    m_cursor.reset(new Square(m_cursor->GetFile(),m_cursor->GetRank().ToInt() + 1));
    this->m_signal_changed();
  }
}

void SquareSelector::MoveLeft()
{
  assert(m_cursor);
  if (m_cursor->GetFile().ToInt() != 0)
  {
    m_cursor.reset(new Square(m_cursor->GetFile().ToInt() - 1,m_cursor->GetRank()));
    this->m_signal_changed();
  }
}

void SquareSelector::MoveRight()
{
  assert(m_cursor);
  if (m_cursor->GetFile().ToInt() != 7)
  {
    m_cursor.reset(new Square(m_cursor->GetFile().ToInt() + 1,m_cursor->GetRank()));
    this->m_signal_changed();
  }
}


void SquareSelector::MoveUp()
{
  assert(m_cursor);
  if (m_cursor->GetRank().ToInt() != 0)
  {
    m_cursor.reset(new Square(m_cursor->GetFile(),m_cursor->GetRank().ToInt() - 1));
    this->m_signal_changed();
  }
}

const std::string SquareSelector::ToStr() const
{
  assert(m_cursor);
  std::string s = "Cursor: " + m_cursor->ToStr();
  if (m_selected)
  {
    s += ", selected: " + m_selected->ToStr();
  }
  return s;
}

} //~namespace Chess


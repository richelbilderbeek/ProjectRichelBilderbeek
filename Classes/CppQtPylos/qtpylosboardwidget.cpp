//---------------------------------------------------------------------------
/*
PylosWidget, widget to display Pylos class
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpylosboardwidget.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "pylosboard.h"
#include "pylosmove.h"
#include "pylosmustremovestate.h"
#include "pylosplayer.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::pylos::QtPylosBoardWidget::QtPylosBoardWidget() :
    m_board(new pylos::BoardBasic),
    m_must_remove(pylos::MustRemoveState::no),
    m_player(pylos::Player::player1)
{

}

bool ribi::pylos::QtPylosBoardWidget::CanRemove(const std::vector<pylos::Coordinat>& v) const
{
  return m_board->CanRemove(v,m_player);
}

bool ribi::pylos::QtPylosBoardWidget::CanSet(const pylos::Coordinat& c) const
{
  return m_board->CanSet(c,m_player);
}

bool ribi::pylos::QtPylosBoardWidget::CanSetPlayer(const pylos::Player) const
{
  return m_must_remove == pylos::MustRemoveState::no;
}

bool ribi::pylos::QtPylosBoardWidget::CanTransfer(const pylos::Coordinat& c) const
{
  return m_board->CanTransfer(c,m_player);
}

bool ribi::pylos::QtPylosBoardWidget::CanTransfer(
  const pylos::Coordinat& from,
  const pylos::Coordinat& to) const
{
  return m_board->CanTransfer(from,to,m_player);
}

ribi::pylos::PositionState ribi::pylos::QtPylosBoardWidget::Get(const pylos::Coordinat& c) const
{
  return m_board->Get(c);
}

ribi::pylos::Player ribi::pylos::QtPylosBoardWidget::GetCurrentTurn() const
{
  return m_player;
}

int ribi::pylos::QtPylosBoardWidget::GetLayerSize(const int layer) const
{
  return m_board->GetLayerSize(layer);
}

std::string ribi::pylos::QtPylosBoardWidget::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::QtPylosBoardWidget::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2010-09-22: version 1.2: initial release version");
  v.push_back("2010-10-06: version 1.3: disallow clicking when there is a winner");
  v.push_back("2010-05-28: version 2.0: inherit from QtPylosWidget");
  return v;
}

ribi::pylos::Winner ribi::pylos::QtPylosBoardWidget::GetWinner() const
{
  return m_board->GetWinner();
}

void ribi::pylos::QtPylosBoardWidget::Remove(const std::vector<pylos::Coordinat>& v)
{
  m_board->Remove(v,m_player);
  m_must_remove = pylos::MustRemoveState::no;
}

void ribi::pylos::QtPylosBoardWidget::Set(const pylos::Coordinat& c)
{
  m_board->Set(c,m_player,m_must_remove);
}

void ribi::pylos::QtPylosBoardWidget::SetPlayer(const pylos::Player player)
{
  assert(CanSetPlayer(player));
  if (m_player != player)
  {
    m_player = player;
    repaint();
    emit PlayerChanged();
  }
}

void ribi::pylos::QtPylosBoardWidget::StartAdvanced()
{
  m_board = pylos::Board::CreateAdvancedBoard();
  m_select = pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<pylos::Coordinat>();
  repaint();
}

void ribi::pylos::QtPylosBoardWidget::StartBasic()
{
  m_board = pylos::Board::CreateBasicBoard();
  m_select = pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<pylos::Coordinat>();
  repaint();
}

void ribi::pylos::QtPylosBoardWidget::Transfer(
  const pylos::Coordinat& from,
  const pylos::Coordinat& to)
{
  m_board->Transfer(from,to,m_must_remove);
}

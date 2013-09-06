//---------------------------------------------------------------------------
/*
PylosWidget, widget to display Pylos class
Copyright (C) 2010 Richel Bilderbeek

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

ribi::QtPylosBoardWidget::QtPylosBoardWidget() :
    m_board(new Pylos::BoardBasic),
    m_must_remove(Pylos::MustRemoveState::no),
    m_player(Pylos::Player::player1)
{

}

bool ribi::QtPylosBoardWidget::CanRemove(const std::vector<Pylos::Coordinat>& v) const
{
  return m_board->CanRemove(v,m_player);
}

bool ribi::QtPylosBoardWidget::CanSet(const Pylos::Coordinat& c) const
{
  return m_board->CanSet(c,m_player);
}

bool ribi::QtPylosBoardWidget::CanSetPlayer(const Pylos::Player) const
{
  return m_must_remove == Pylos::MustRemoveState::no;
}

bool ribi::QtPylosBoardWidget::CanTransfer(const Pylos::Coordinat& c) const
{
  return m_board->CanTransfer(c,m_player);
}

bool ribi::QtPylosBoardWidget::CanTransfer(
  const Pylos::Coordinat& from,
  const Pylos::Coordinat& to) const
{
  return m_board->CanTransfer(from,to,m_player);
}

ribi::Pylos::PositionState ribi::QtPylosBoardWidget::Get(const Pylos::Coordinat& c) const
{
  return m_board->Get(c);
}

ribi::Pylos::Player ribi::QtPylosBoardWidget::GetCurrentTurn() const
{
  return m_player;
}

int ribi::QtPylosBoardWidget::GetLayerSize(const int layer) const
{
  return m_board->GetLayerSize(layer);
}

const std::string ribi::QtPylosBoardWidget::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::QtPylosBoardWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-09-22: version 1.2: initial release version");
  v.push_back("2010-10-06: version 1.3: disallow clicking when there is a winner");
  v.push_back("2010-05-28: version 2.0: inherit from QtPylosWidget");
  return v;
}

ribi::Pylos::Winner ribi::QtPylosBoardWidget::GetWinner() const
{
  return m_board->GetWinner();
}

void ribi::QtPylosBoardWidget::Remove(const std::vector<Pylos::Coordinat>& v)
{
  m_board->Remove(v,m_player);
  m_must_remove = Pylos::MustRemoveState::no;
}

void ribi::QtPylosBoardWidget::Set(const Pylos::Coordinat& c)
{
  m_board->Set(c,m_player,m_must_remove);
}

void ribi::QtPylosBoardWidget::SetPlayer(const Pylos::Player player)
{
  assert(CanSetPlayer(player));
  if (m_player != player)
  {
    m_player = player;
    repaint();
    emit PlayerChanged();
  }
}

void ribi::QtPylosBoardWidget::StartAdvanced()
{
  m_board = Pylos::Board::CreateAdvancedBoard();
  m_select = Pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<Pylos::Coordinat>();
  repaint();
}

void ribi::QtPylosBoardWidget::StartBasic()
{
  m_board = Pylos::Board::CreateBasicBoard();
  m_select = Pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<Pylos::Coordinat>();
  repaint();
}

void ribi::QtPylosBoardWidget::Transfer(
  const Pylos::Coordinat& from,
  const Pylos::Coordinat& to)
{
  m_board->Transfer(from,to,m_must_remove);
}


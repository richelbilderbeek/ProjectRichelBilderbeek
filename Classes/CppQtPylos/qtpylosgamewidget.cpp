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
#include "qtpylosgamewidget.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include <boost/numeric/conversion/cast.hpp>

#include <QMouseEvent>
#include <QPainter>

#include "pylosboard.h"
#include "pylosgame.h"
#include "pylosmove.h"
#include "pylosmustremovestate.h"
#include "pylosplayer.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::pylos::QtPylosGameWidget::QtPylosGameWidget() :
    m_pylos(pylos::Game::CreateBasicGame())
{

}

ribi::pylos::QtPylosGameWidget::~QtPylosGameWidget() noexcept
{
  //OK
}

bool ribi::pylos::QtPylosGameWidget::CanRemove(const std::vector<pylos::Coordinat>& v) const
{
  return m_pylos->CanRemove(v);
}

bool ribi::pylos::QtPylosGameWidget::CanSet(const pylos::Coordinat& c) const
{
  return m_pylos->CanSet(c);
}

bool ribi::pylos::QtPylosGameWidget::CanTransfer(const pylos::Coordinat& c) const
{
  return m_pylos->CanTransfer(c);
}

bool ribi::pylos::QtPylosGameWidget::CanTransfer(
  const pylos::Coordinat& from,
  const pylos::Coordinat& to) const
{
  return m_pylos->CanTransfer(from,to);
}

ribi::pylos::PositionState ribi::pylos::QtPylosGameWidget::Get(const pylos::Coordinat& c) const
{
  return m_pylos->GetBoard()->Get(c);
}

ribi::pylos::Player ribi::pylos::QtPylosGameWidget::GetCurrentTurn() const
{
  return m_pylos->GetCurrentTurn();
}

int ribi::pylos::QtPylosGameWidget::GetLayerSize(const int layer) const
{
  return m_pylos->GetBoard()->GetLayerSize(layer);
}

ribi::pylos::MustRemoveState ribi::pylos::QtPylosGameWidget::GetMustRemove() const
{
  return m_pylos->GetMustRemove();
}

std::string ribi::pylos::QtPylosGameWidget::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::pylos::QtPylosGameWidget::GetVersionHistory() noexcept
{
  std::vector<std::string> v {
    "2010-09-22: version 1.2: initial release version",
    "2010-10-06: version 1.3: disallow clicking when there is a winner",
    "2010-05-28: version 2.0: inherit from QtPylosWidget",
    "2014-06-20: version 2.1: moved destructor definition to implementation file to solve segmentation fault"
  };
  return v;
}

ribi::pylos::Winner ribi::pylos::QtPylosGameWidget::GetWinner() const
{
  return m_pylos->GetWinner();
}

void ribi::pylos::QtPylosGameWidget::Remove(const std::vector<pylos::Coordinat>& v)
{
  m_pylos->Remove(v);
}

void ribi::pylos::QtPylosGameWidget::Set(const pylos::Coordinat& c)
{
  m_pylos->Set(c);
}

void ribi::pylos::QtPylosGameWidget::StartAdvanced()
{
  m_pylos = pylos::Game::CreateAdvancedGame();
  m_select = pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<pylos::Coordinat>();
  repaint();
}

void ribi::pylos::QtPylosGameWidget::StartBasic()
{
  m_pylos = pylos::Game::CreateBasicGame();
  m_select = pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<pylos::Coordinat>();
  repaint();
}

void ribi::pylos::QtPylosGameWidget::Transfer(
  const pylos::Coordinat& from,
  const pylos::Coordinat& to)
{
  m_pylos->Transfer(from,to);
}


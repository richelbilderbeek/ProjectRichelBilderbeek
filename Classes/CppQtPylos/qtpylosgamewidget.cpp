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

QtPylosGameWidget::QtPylosGameWidget() :
    m_pylos(Pylos::Game::CreateBasicGame())
{

}

bool QtPylosGameWidget::CanRemove(const std::vector<Pylos::Coordinat>& v) const
{
  return m_pylos->CanRemove(v);
}

bool QtPylosGameWidget::CanSet(const Pylos::Coordinat& c) const
{
  return m_pylos->CanSet(c);
}

bool QtPylosGameWidget::CanTransfer(const Pylos::Coordinat& c) const
{
  return m_pylos->CanTransfer(c);
}

bool QtPylosGameWidget::CanTransfer(
  const Pylos::Coordinat& from,
  const Pylos::Coordinat& to) const
{
  return m_pylos->CanTransfer(from,to);
}

Pylos::PositionState QtPylosGameWidget::Get(const Pylos::Coordinat& c) const
{
  return m_pylos->GetBoard()->Get(c);
}

Pylos::Player QtPylosGameWidget::GetCurrentTurn() const
{
  return m_pylos->GetCurrentTurn();
}

int QtPylosGameWidget::GetLayerSize(const int layer) const
{
  return m_pylos->GetBoard()->GetLayerSize(layer);
}

Pylos::MustRemoveState QtPylosGameWidget::GetMustRemove() const
{
  return m_pylos->GetMustRemove();
}

const std::string QtPylosGameWidget::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> QtPylosGameWidget::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-09-22: version 1.2: initial release version");
  v.push_back("2010-10-06: version 1.3: disallow clicking when there is a winner");
  v.push_back("2010-05-28: version 2.0: inherit from QtPylosWidget");
  return v;
}

Pylos::Winner QtPylosGameWidget::GetWinner() const
{
  return m_pylos->GetWinner();
}

void QtPylosGameWidget::Remove(const std::vector<Pylos::Coordinat>& v)
{
  m_pylos->Remove(v);
}

void QtPylosGameWidget::Set(const Pylos::Coordinat& c)
{
  m_pylos->Set(c);
}

void QtPylosGameWidget::StartAdvanced()
{
  m_pylos = Pylos::Game::CreateAdvancedGame();
  m_select = Pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<Pylos::Coordinat>();
  repaint();
}

void QtPylosGameWidget::StartBasic()
{
  m_pylos = Pylos::Game::CreateBasicGame();
  m_select = Pylos::Coordinat(0,0,0);
  m_other_selectors = std::vector<Pylos::Coordinat>();
  repaint();
}

void QtPylosGameWidget::Transfer(
  const Pylos::Coordinat& from,
  const Pylos::Coordinat& to)
{
  m_pylos->Transfer(from,to);
}


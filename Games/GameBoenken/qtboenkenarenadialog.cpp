//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtboenkenarenadialog.h"

#include <cassert>
#include <stdexcept>

#include <QDesktopWidget>

#include "ui_qtboenkenarenadialog.h"
#pragma GCC diagnostic pop

ribi::QtBoenkenArenaDialog::QtBoenkenArenaDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenArenaDialog)
{
  ui->setupUi(this);
  QObject::connect(
    ui->button_done,&QPushButton::clicked,this,&QtBoenkenArenaDialog::close);
}

ribi::QtBoenkenArenaDialog::~QtBoenkenArenaDialog() noexcept
{
  delete ui;
}

///The purpose of QtBoenkenArenaDialog is to create
///an ArenaSettings
const ribi::Boenken::ArenaSettings ribi::QtBoenkenArenaDialog::GetSettings() const noexcept
{
  Boenken::ArenaSettings s;
  s.formation = this->GetFormation();
  s.friction = this->GetFriction();
  s.n_balls = this->GetNballs();
  s.n_obstacles = this->GetNobstacles();
  s.screen_size = this->GetScreenSize();
  return s;
}

const std::pair<int,int> ribi::QtBoenkenArenaDialog::GetScreenSize() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_screen_size;
  assert(b->count()==2);
  switch(b->currentIndex())
  {
    case 0:
      assert(b->currentText() == "Full screen");
      {
        // -8, because of the application fame
        const int width
          = QApplication::desktop()->width()
          - 8;
        // -50, because of the app's title bar and those Ubuntu panels
        const int height
          = QApplication::desktop()->height() - 96;
        return std::make_pair(width,height);
      }
    case 1:
      assert(b->currentText() == "640x400");
      return std::make_pair(640,400);
    default:
      assert(!"Should not get here");
      throw std::logic_error("ribi::QtBoenkenArenaDialog::GetScreenSize");
  }
}

int ribi::QtBoenkenArenaDialog::GetNballs() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_nballs;
  assert(b->count()==2);
  switch(b->currentIndex())
  {
    case 0:
      assert(b->currentText() == "One");
      return 1;
    case 1:
      assert(b->currentText() == "Two");
      return 2;
    default:
      assert(!"Should not get here");
      throw std::logic_error("ribi::QtBoenkenArenaDialog::GetNballs");
  }
}

int ribi::QtBoenkenArenaDialog::GetNobstacles() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_obstacles;
  assert(b->count()==2);
  switch(b->currentIndex())
  {
    case 0:
      assert(b->currentText() == "None");
      return 0;
    case 1:
      assert(b->currentText() == "Two");
      return 2;
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::QtBoenkenArenaDialog::GetNobstacles");
}

ribi::Boenken::Formation ribi::QtBoenkenArenaDialog::GetFormation() const noexcept
{
  //Makes the code shorter and copy-pastable
  const QComboBox * const b = ui->box_formation;
  assert(b->count()==3);
  switch(b->currentIndex())
  {
    case 0:
      assert(b->currentText() == "Line");
      return Boenken::straight_line;
    case 1:
      assert(b->currentText() == "Circle, inward");
      return Boenken::circle_inward;
    case 2:
      assert(b->currentText() == "Circle, outward");
      return Boenken::circle_outward;
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::QtBoenkenArenaDialog::GetFormation");
}

double ribi::QtBoenkenArenaDialog::GetFriction() const noexcept
{
  const QComboBox * const b = ui->box_friction;
  assert(b->count()==3);
  switch(b->currentIndex())
  {
    case 0:
      assert(b->currentText() == "None");
      return 1.0;
    case 1:
      assert(b->currentText() == "Low");
      return 0.999;
    case 2:
      assert(b->currentText() == "Medium");
      return 0.99;
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::QtBoenkenArenaDialog::GetFriction");
}


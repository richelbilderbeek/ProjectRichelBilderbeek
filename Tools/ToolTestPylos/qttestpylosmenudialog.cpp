//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestpylosmenudialog.h"

#include "qtaboutdialog.h"
#include "qttestpylostestboarddialog.h"
#include "qttestpylostestgamedialog.h"
#include "qttestpylosgametestsdialog.h"
#include "qttestpylosrandomplaydialog.h"
#include "testpylosmenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestpylosmenudialog.h"
#pragma GCC diagnostic pop

ribi::pylos::QtTestPylosMenuDialog::QtTestPylosMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPylosMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::pylos::QtTestPylosMenuDialog::~QtTestPylosMenuDialog() noexcept
{
    delete ui;
}

void ribi::pylos::QtTestPylosMenuDialog::on_button_test_board_clicked()
{
  QtTestPylosTestBoardDialog d;
  this->ShowChild(&d);
}

void ribi::pylos::QtTestPylosMenuDialog::on_button_test_game_clicked()
{
  QtTestPylosTestGameDialog d;
  this->ShowChild(&d);
}

void ribi::pylos::QtTestPylosMenuDialog::on_button_show_game_tests_clicked()
{
  QtTestPylosGameTestsDialog d;
  this->ShowChild(&d);
}

void ribi::pylos::QtTestPylosMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestPylosMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::pylos::QtTestPylosMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::pylos::QtTestPylosMenuDialog::on_button_random_play_clicked()
{
  QtTestPylosRandomPlayDialog d;
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::pylos::QtTestPylosMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

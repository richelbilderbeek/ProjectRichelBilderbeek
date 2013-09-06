//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
Copyright (C) 2010-2012 Richel Bilderbeek

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


#include "qttestpylosmenudialog.h"

#include "qtaboutdialog.h"
#include "qttestpylostestboarddialog.h"
#include "qttestpylostestgamedialog.h"
#include "qttestpylosgametestsdialog.h"
#include "qttestpylosrandomplaydialog.h"
#include "testpylosmenudialog.h"
#include "ui_qttestpylosmenudialog.h"
//---------------------------------------------------------------------------
QtTestPylosMenuDialog::QtTestPylosMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestPylosMenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtTestPylosMenuDialog::~QtTestPylosMenuDialog()
{
    delete ui;
}
//---------------------------------------------------------------------------
void QtTestPylosMenuDialog::on_button_test_board_clicked()
{
  QtTestPylosTestBoardDialog d;
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtTestPylosMenuDialog::on_button_test_game_clicked()
{
  QtTestPylosTestGameDialog d;
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtTestPylosMenuDialog::on_button_show_game_tests_clicked()
{
  QtTestPylosGameTestsDialog d;
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtTestPylosMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestPylosMenuDialog::GetAbout());
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------
void QtTestPylosMenuDialog::on_button_quit_clicked()
{
  close();
}
//---------------------------------------------------------------------------
void QtTestPylosMenuDialog::on_button_random_play_clicked()
{
  QtTestPylosRandomPlayDialog d;
  this->hide();
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/*
TestChess, program to test my chess classes
Copyright (C) 2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestChess.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestchessmenudialog.h"

#include <QBitmap>
#include <QPainter>
#include <QPixmap>

#include "qtaboutdialog.h"
#include "qtchessboardwidget.h"
#include "qtchessresources.h"
#include "qttestchessboarddialog.h"
#include "qttestchessgamedialog.h"
#include "qttestchessviewresourcesdialog.h"
#include "testchessmenudialog.h"
#include "ui_qttestchessmenudialog.h"

#pragma GCC diagnostic pop

ribi::QtTestChessMenuDialog::QtTestChessMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestChessMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtTestChessMenuDialog::~QtTestChessMenuDialog()
{
  delete ui;
}

void ribi::QtTestChessMenuDialog::on_button_about_clicked()
{
  About a = TestChessMenuDialog().GetAbout();
  a.AddLibrary("QtChessBoardWidget version: " + Chess::QtChessBoardWidget::GetVersion());
  a.AddLibrary("Chess::QtResources version: " + Chess::QtResources::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestChessMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestChessMenuDialog::on_button_view_resources_clicked()
{
  QtTestChessViewResourcesDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestChessMenuDialog::on_button_test_board_clicked()
{
  QtTestChessBoardDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestChessMenuDialog::on_button_test_game_clicked()
{
  QtTestChessGameDialog d;
  this->ShowChild(&d);
}

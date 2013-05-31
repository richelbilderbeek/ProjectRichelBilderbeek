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
#include "about.h"
#include "qtaboutdialog.h"
#include "qtchessboardwidget.h"
#include "qtchessresources.h"
#include "qttestchessboarddialog.h"
#include "qttestchessgamedialog.h"
#include "qttestchessmenudialog.h"
#include "qttestchessviewresourcesdialog.h"
#include "testchessmenudialog.h"
#include "ui_qttestchessmenudialog.h"
//---------------------------------------------------------------------------
#include <QBitmap>
#include <QPainter>
#include <QPixmap>
//---------------------------------------------------------------------------
QtTestChessMenuDialog::QtTestChessMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestChessMenuDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtTestChessMenuDialog::~QtTestChessMenuDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtTestChessMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = TestChessMenuDialog::GetAbout();
  a.AddLibrary("QtChessBoardWidget version: " + QtChessBoardWidget::GetVersion());
  a.AddLibrary("Chess::QtResources version: " + Chess::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  this->show();

}
//---------------------------------------------------------------------------
void QtTestChessMenuDialog::on_button_quit_clicked()
{
  close();
}
//---------------------------------------------------------------------------
void QtTestChessMenuDialog::on_button_view_resources_clicked()
{
  this->hide();
  QtTestChessViewResourcesDialog d;
  d.exec();
  this->show();

}
//---------------------------------------------------------------------------
void QtTestChessMenuDialog::on_button_test_board_clicked()
{
  this->hide();
  QtTestChessBoardDialog d;
  d.exec();
  this->show();

}
//---------------------------------------------------------------------------
void QtTestChessMenuDialog::on_button_test_game_clicked()
{
  this->hide();
  QtTestChessGameDialog d;
  d.exec();
  this->show();
}
//---------------------------------------------------------------------------

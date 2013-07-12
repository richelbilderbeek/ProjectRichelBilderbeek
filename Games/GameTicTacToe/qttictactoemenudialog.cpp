
/*
TicTacToe, tic-tac-toe game
Copyright (C) 2010-2011 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/GameTicTacToe.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttictactoemenudialog.h"

#include "qtaboutdialog.h"
#include "qttictactoegamedialog.h"
#include "qttictactoewidget.h"
#include "tictactoemenudialog.h"
#include "ui_qttictactoemenudialog.h"

QtTicTacToeMenuDialog::QtTicTacToeMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTicTacToeMenuDialog)
{
  ui->setupUi(this);
}

QtTicTacToeMenuDialog::~QtTicTacToeMenuDialog()
{
  delete ui;
}

void QtTicTacToeMenuDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtTicTacToeMenuDialog::on_button_start_clicked()
{
  QtTicTacToeGameDialog d;
  this->hide();
  d.exec();
  this->show();
}

void QtTicTacToeMenuDialog::on_button_about_clicked()
{
  About a = TicTacToeMenuDialog::GetAbout();
  a.AddLibrary("QtTicTacToeWidget version: " + QtTicTacToeWidget::GetVersion());
  QtAboutDialog d(a);
  this->hide();
  d.exec();
  this->show();
}

void QtTicTacToeMenuDialog::on_button_quit_clicked()
{
  close();
}


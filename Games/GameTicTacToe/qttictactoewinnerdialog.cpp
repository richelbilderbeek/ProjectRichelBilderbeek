//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/GameTicTacToe.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttictactoewinnerdialog.h"
#include "ui_qttictactoewinnerdialog.h"
//---------------------------------------------------------------------------
QtTicTacToeWinnerDialog::QtTicTacToeWinnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTicTacToeWinnerDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtTicTacToeWinnerDialog::~QtTicTacToeWinnerDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
void QtTicTacToeWinnerDialog::changeEvent(QEvent *e)
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
//---------------------------------------------------------------------------
void QtTicTacToeWinnerDialog::SetDraw()
{
  ui->label_title->setText("Draw");
  this->setWindowTitle("Draw");
  ui->label_winner->setText(" ");
}
//---------------------------------------------------------------------------
void QtTicTacToeWinnerDialog::SetWinnerCross()
{
  ui->label_winner->setPixmap(QPixmap(":/images/X.png"));
}
//---------------------------------------------------------------------------
void QtTicTacToeWinnerDialog::SetWinnerCircle()
{
  ui->label_winner->setPixmap(QPixmap(":/images/O.png"));
}
//---------------------------------------------------------------------------

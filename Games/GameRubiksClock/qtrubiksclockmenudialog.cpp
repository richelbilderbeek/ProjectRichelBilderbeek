
/*
RubiksClock. Rubik's Clock game.
Copyright (C) 2007-2012  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//From http://www.richelbilderbeek.nl/GameRubiksClock.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtrubiksclockmenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "qthideandshowdialog.h"
#include "qtrubiksclockmaindialog.h"
#include "qtrubiksclockwidget.h"
#include "qttogglebuttonwidget.h"
#include "rubiksclockmenudialog.h"
#include "ui_qtrubiksclockmenudialog.h"

QtRubiksClockMenuDialog::QtRubiksClockMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRubiksClockMenuDialog)
{
  ui->setupUi(this);
}

QtRubiksClockMenuDialog::~QtRubiksClockMenuDialog()
{
  delete ui;
}

void QtRubiksClockMenuDialog::changeEvent(QEvent *e)
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

void QtRubiksClockMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void QtRubiksClockMenuDialog::on_button_about_clicked()
{
  About a = RubiksClockMenuDialog::GetAbout();
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtRubiksClockWidget version: " + QtRubiksClockWidget::GetVersion());
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtRubiksClockMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtRubiksClockMenuDialog::on_button_start_clicked()
{
  QtRubiksClockMainDialog d;
  ShowChild(&d);
}


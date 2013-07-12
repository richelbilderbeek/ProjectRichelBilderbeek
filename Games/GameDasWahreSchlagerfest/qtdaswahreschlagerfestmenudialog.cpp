//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtdaswahreschlagerfestmenudialog.h"

#include "daswahreschlagerfestmenudialog.h"
#include "qtaboutdialog.h"
#include "qtdaswahreschlagerfestmaindialog.h"
#include "ui_qtdaswahreschlagerfestmenudialog.h"

QtDasWahreSchlagerfestMenuDialog::QtDasWahreSchlagerfestMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDasWahreSchlagerfestMenuDialog)
{
  ui->setupUi(this);
}

QtDasWahreSchlagerfestMenuDialog::~QtDasWahreSchlagerfestMenuDialog()
{
  delete ui;
}

void QtDasWahreSchlagerfestMenuDialog::on_button_start_clicked()
{
  QtDasWahreSchlagerfestMainDialog d;
  this->hide();
  d.exec();
  this->show();
}

void QtDasWahreSchlagerfestMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(DasWahreSchlagerfestMenuDialog::GetAbout());
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtDasWahreSchlagerfestMenuDialog::on_button_quit_clicked()
{
  close();
}

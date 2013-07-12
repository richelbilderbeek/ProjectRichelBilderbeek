//---------------------------------------------------------------------------
/*
GaborFilter, tool to demonstrate Gabor filtering
Copyright (C) 2012  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolGaborFilter.htm
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
#include "qttoolgaborfiltermenudialog.h"


#include "qtaboutdialog.h"
#include "toolgaborfiltermenudialog.h"
#include "qttoolgaborfiltermaindialog.h"
#include "ui_qttoolgaborfiltermenudialog.h"

QtToolGaborFilterMenuDialog::QtToolGaborFilterMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtToolGaborFilterMenuDialog)
{
    ui->setupUi(this);
}

QtToolGaborFilterMenuDialog::~QtToolGaborFilterMenuDialog()
{
    delete ui;
}

void QtToolGaborFilterMenuDialog::on_button_start_clicked()
{
  QtToolGaborFilterMainDialog d;
  this->hide();
  d.exec();
  this->show();
}

void QtToolGaborFilterMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(ToolGaborFilterMenuDialog::GetAbout());
  this->hide();
  d.exec();
  this->show();
}

void QtToolGaborFilterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

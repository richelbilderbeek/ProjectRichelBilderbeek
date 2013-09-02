//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestfunctionparsermenudialog.h"

#include "qtaboutdialog.h"
#include "qttestfunctionparsermaindialog.h"
#include "testfunctionparsermenudialog.h"
#include "ui_qttestfunctionparsermenudialog.h"

QtTestFunctionParserMenuDialog::QtTestFunctionParserMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestFunctionParserMenuDialog)
{
  ui->setupUi(this);
}

QtTestFunctionParserMenuDialog::~QtTestFunctionParserMenuDialog()
{
  delete ui;
}

void QtTestFunctionParserMenuDialog::on_button_start_clicked()
{
  QtTestFunctionParserMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  ShowChild(&d);
}

void QtTestFunctionParserMenuDialog::on_button_about_clicked()
{
  About a = TestFunctionParserMenuDialog::GetAbout();
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  hide();
  d.exec();
  show();
}

void QtTestFunctionParserMenuDialog::on_button_quit_clicked()
{
  close();
}


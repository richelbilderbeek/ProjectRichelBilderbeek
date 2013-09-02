//---------------------------------------------------------------------------
/*
TestToggleButton, tool to test the ToggleButton class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestToggleButton.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttesttogglebuttonmenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qttogglebuttonwidget.h"
#include "qttesttogglebuttonmaindialog.h"
#include "rainbow.h"
#include "testtogglebuttonmenudialog.h"
#include "ui_qttesttogglebuttonmenudialog.h"

QtTestToggleButtonMenuDialog::QtTestToggleButtonMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestToggleButtonMenuDialog)
{
  ui->setupUi(this);
}

QtTestToggleButtonMenuDialog::~QtTestToggleButtonMenuDialog()
{
  delete ui;
}

void QtTestToggleButtonMenuDialog::on_button_start_clicked()
{
  QtTestToggleButtonMainDialog d;
  hide();
  d.exec();
  show();
}

void QtTestToggleButtonMenuDialog::on_button_about_clicked()
{
  hide();
  About a = TestToggleButtonMenuDialog::GetAbout();
  a.AddLibrary("QtToggleButtonWidget version: " + QtToggleButtonWidget::GetVersion());
  a.AddLibrary("Rainbow version: " + Rainbow::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  show();
}

void QtTestToggleButtonMenuDialog::on_button_quit_clicked()
{
  close();
}



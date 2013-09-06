//---------------------------------------------------------------------------
/*
TestDial, tool to test the Dial and DialWidget classes
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
//From http://www.richelbilderbeek.nl/ToolTestDial.htm
//---------------------------------------------------------------------------


#include "testdialmenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qtdialwidget.h"
#include "qttestdialmaindialog.h"
#include "qttestdialmenudialog.h"
#include "ui_qttestdialmenudialog.h"

QtTestDialMenuDialog::QtTestDialMenuDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtTestDialMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

QtTestDialMenuDialog::~QtTestDialMenuDialog()
{
  delete ui;
}

void QtTestDialMenuDialog::on_button_start_clicked()
{
  hide();
  QtTestDialMainDialog d;
  d.exec();
  show();
}

void QtTestDialMenuDialog::on_button_about_clicked()
{
  hide();
  About a = TestDialMenuDialog::GetAbout();
  a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  show();
}

void QtTestDialMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtTestDialMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtTestDialMainDialog d;
  }
}


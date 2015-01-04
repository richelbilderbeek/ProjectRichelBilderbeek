//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtasciiartermenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "asciiartermenudialog.h"
#include "qtasciiartermaindialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtasciiartermenudialog.h"
#pragma GCC diagnostic pop


ribi::QtAsciiArterMenuDialog::QtAsciiArterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtAsciiArterMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtAsciiArterMenuDialog::~QtAsciiArterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtAsciiArterMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtAsciiArterMenuDialog::on_button_start_clicked()
{
  QtAsciiArterMainDialog d;
  ShowChild(&d);
}

void ribi::QtAsciiArterMenuDialog::on_button_about_clicked()
{
  About a = AsciiArterMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtAsciiArterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtAsciiArterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtAsciiArterMenuDialog();
}
#endif

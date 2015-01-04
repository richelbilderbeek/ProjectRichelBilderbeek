//---------------------------------------------------------------------------
/*
CaesarCipher, Caesar cipher tool
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCaesarCipher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtcaesarciphermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "caesarciphermenudialog.h"
#include "qtaboutdialog.h"
#include "qtcaesarciphermaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtcaesarciphermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtCaesarCipherMenuDialog::QtCaesarCipherMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCaesarCipherMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtCaesarCipherMenuDialog::~QtCaesarCipherMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtCaesarCipherMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtCaesarCipherMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = ribi::CaesarCipherMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtCaesarCipherMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtCaesarCipherMenuDialog::on_button_start_clicked() noexcept
{
  QtCaesarCipherMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtCaesarCipherMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  CaesarCipherMenuDialog();
  QtCaesarCipherMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

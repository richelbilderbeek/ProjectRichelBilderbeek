//---------------------------------------------------------------------------
/*
VigenereCipher, Vigenere cipher tool
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
//From http://www.richelbilderbeek.nl/ToolVigenereCipher.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtvigenereciphermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "vigenereciphermenudialog.h"
#include "qtaboutdialog.h"
#include "qtvigenereciphermaindialog.h"
#include "testtimer.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qtvigenereciphermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtVigenereCipherMenuDialog::QtVigenereCipherMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtVigenereCipherMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtVigenereCipherMenuDialog::~QtVigenereCipherMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtVigenereCipherMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtVigenereCipherMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = ribi::VigenereCipherMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtVigenereCipherMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtVigenereCipherMenuDialog::on_button_start_clicked() noexcept
{
  QtVigenereCipherMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtVigenereCipherMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtVigenereCipherMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

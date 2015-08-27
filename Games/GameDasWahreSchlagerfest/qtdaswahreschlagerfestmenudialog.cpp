//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtdaswahreschlagerfestmenudialog.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "daswahreschlagerfestmenudialog.h"
#include "qtaboutdialog.h"
#include "qtcanvasdialog.h"
#include "testtimer.h"
#include "qtdaswahreschlagerfestmaindialog.h"
#include "ui_qtdaswahreschlagerfestmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::dws::QtMenuDialog::QtMenuDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDwsMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::dws::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}

void ribi::dws::QtMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void ribi::dws::QtMenuDialog::on_button_start_clicked() noexcept
{
  QtMainDialog d;
  this->ShowChild(&d);
}

void ribi::dws::QtMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(MenuDialog().GetAbout());
  d.setWindowIcon(windowIcon());
  d.setStyleSheet(styleSheet());
  ShowChild(&d);
}

void ribi::dws::QtMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::dws::QtMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

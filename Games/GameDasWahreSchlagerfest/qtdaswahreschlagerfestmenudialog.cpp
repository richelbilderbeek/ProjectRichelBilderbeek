//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2014 Richel Bilderbeek

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

#include "daswahreschlagerfestmenudialog.h"
#include "qtaboutdialog.h"
#include "qtdaswahreschlagerfestcanvas.h"
#include "qtdaswahreschlagerfestmaindialog.h"
#include "ui_qtdaswahreschlagerfestmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtDasWahreSchlagerfestMenuDialog::QtDasWahreSchlagerfestMenuDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDasWahreSchlagerfestMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtDasWahreSchlagerfestMenuDialog::~QtDasWahreSchlagerfestMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtDasWahreSchlagerfestMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->Key() == Qt::Key_At || e->Key() == Qt::Key_Dollar)
  {
    QtDasWahreSchlagerfestCanvas c;
    c.show();
    c.showNormal();
  }
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_start_clicked() noexcept
{
  QtDasWahreSchlagerfestMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(DasWahreSchlagerfestMenuDialog().GetAbout());
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtDasWahreSchlagerfestMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtDasWahreSchlagerfestMenuDialog::Test");
  QtDasWahreSchlagerfestMainDialog();
  TRACE("Finished ribi::QtDasWahreSchlagerfestMenuDialog::Test successfully");
}
#endif

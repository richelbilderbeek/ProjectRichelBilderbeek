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
#include "qtdaswahreschlagerfestmaindialog.h"

#include <QKeyEvent>
#include "qtdaswahreschlagerfestwidget.h"
#include "ui_qtdaswahreschlagerfestmaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtDasWahreSchlagerfestMainDialog::QtDasWahreSchlagerfestMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDasWahreSchlagerfestMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtDasWahreSchlagerfestMainDialog::~QtDasWahreSchlagerfestMainDialog() noexcept
{
  delete ui;
}

void ribi::QtDasWahreSchlagerfestMainDialog::closeEvent(QCloseEvent * /*event*/ )
{
  close_me();
}

void ribi::QtDasWahreSchlagerfestMainDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}


#ifndef NDEBUG
void ribi::QtDasWahreSchlagerfestMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtDasWahreSchlagerfestMainDialog::Test");
  QtDasWahreSchlagerfestWidget();
  TRACE("Finished ribi::QtDasWahreSchlagerfestMainDialog::Test successfully");
}
#endif

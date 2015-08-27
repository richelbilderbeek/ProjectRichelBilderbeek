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
#include "qtdaswahreschlagerfestmaindialog.h"

#include <QKeyEvent>
#include "qtdaswahreschlagerfestwidget.h"
#include "ui_qtdaswahreschlagerfestmaindialog.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::dws::QtDwsMainDialog::QtDwsMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDwsMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  QObject::connect(ui->widget,SIGNAL(destroyed()),this,SLOT(close()));
}

ribi::dws::QtDwsMainDialog::~QtDwsMainDialog() noexcept
{
  delete ui;
}

void ribi::dws::QtDwsMainDialog::closeEvent(QCloseEvent * /*event*/ )
{
  close_me();
}

void ribi::dws::QtDwsMainDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}


#ifndef NDEBUG
void ribi::dws::QtDwsMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtDwsWidget w;
  w.show();
  Widget g(&w);
  g.Execute();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

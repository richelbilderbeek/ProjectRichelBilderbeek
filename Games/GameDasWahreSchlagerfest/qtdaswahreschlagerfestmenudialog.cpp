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
#include "qtdaswahreschlagerfestcanvas.h"
#include "testtimer.h"
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
  if (e->key() == Qt::Key_Escape) { close(); }
  if (e->key() == Qt::Key_At || e->key() == Qt::Key_Dollar || e->key() == Qt::Key_0)
  {
    on_button_start_oldschool_clicked();
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
  d.setWindowIcon(windowIcon());
  d.setStyleSheet(styleSheet());
  ShowChild(&d);
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtDasWahreSchlagerfestMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtDasWahreSchlagerfestMainDialog();
  {
    const boost::shared_ptr<QtDasWahreSchlagerfestCanvas> c {
      new QtDasWahreSchlagerfestCanvas(9,5)
    };
    assert(c);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_start_oldschool_clicked()
{
  QtCanvas * const qtcanvas {
    new QtDasWahreSchlagerfestCanvas(9,5)
  };
  boost::scoped_ptr<QtCanvasDialog> d {
    new QtCanvasDialog(qtcanvas)
  };
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    d->setGeometry(
      0,0,102,102);
    d->move( screen.center() - this->rect().center() );
  }
  d->setWindowTitle("Das Wahre Schlagerfest");
  ShowChild(d.get());
  //canvas will be deleted by QtCanvasDialog
}

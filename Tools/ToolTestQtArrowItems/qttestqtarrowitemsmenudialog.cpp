// ---------------------------------------------------------------------------
/*
TestQtArrowItems, tool to test Qt arrow QGraphicsItems
Copyright (C) 2012-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
// ---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQtArrowItems.htm
// ---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtarrowitemsmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "testtimer.h"
#include "qthideandshowdialog.h"
#include "qttestqtarrowitemscomparedialog.h"
#include "qttestqtarrowitemsmodifydialog.h"
#include "testqtarrowitemsmenudialog.h"
#include "trace.h"
#include "ui_qttestqtarrowitemsmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtArrowItemsMenuDialog::QtTestQtArrowItemsMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtArrowItemsMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQtArrowItemsMenuDialog::~QtTestQtArrowItemsMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtArrowItemsMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestQtArrowItemsMenuDialog::on_button_about_clicked()
{
  About a = TestQtArrowItemsMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestQtArrowItemsMenuDialog::on_button_compare_clicked()
{
  QtTestQtArrowItemsCompareDialog d;
  ShowChild(&d);
}

void ribi::QtTestQtArrowItemsMenuDialog::on_button_modify_clicked()
{
  QtTestQtArrowItemsModifyDialog d;
  ShowChild(&d);
}


void ribi::QtTestQtArrowItemsMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestQtArrowItemsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestQtArrowItemsMenuDialog();
  QtTestQtArrowItemsModifyDialog();
  QtTestQtArrowItemsCompareDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif



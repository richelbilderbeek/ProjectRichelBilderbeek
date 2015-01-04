//---------------------------------------------------------------------------
/*
TestQtRoundedEditRectItem, tool to test QtRoundedEditRectItem
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedEditRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtroundededitrectitemmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtkeyboardfriendlygraphicsview.h"
#include "qtroundedrectitem.h"
#include "qtroundededitrectitem.h"
#include "testqtroundededitrectitemmenudialog.h"
#include "qtaboutdialog.h"
#include "qttestqtroundededitrectitemcomparedialog.h"
#include "qttestqtroundededitrectitemmodifydialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qttestqtroundededitrectitemmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedEditRectItemMenuDialog::QtTestQtRoundedEditRectItemMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedEditRectItemMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQtRoundedEditRectItemMenuDialog::~QtTestQtRoundedEditRectItemMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedEditRectItemMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestQtRoundedEditRectItemMenuDialog::on_button_about_clicked()
{
  About a = TestQtRoundedEditRectItemMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  a.AddLibrary("QtRoundedRectItem version: " + QtRoundedRectItem::GetVersion());
  a.AddLibrary("QtRoundedEditRectItem version: " + QtRoundedEditRectItem::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestQtRoundedEditRectItemMenuDialog::on_button_compare_clicked()
{
  QtTestQtRoundedEditRectItemCompareDialog d;
  d.setWindowIcon(this->windowIcon());
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtTestQtRoundedEditRectItemMenuDialog::on_button_modify_clicked()
{
  QtTestQtRoundedEditRectItemModifyDialog d;
  d.setWindowIcon(this->windowIcon());
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtTestQtRoundedEditRectItemMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestQtRoundedEditRectItemMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtRoundedRectItem();
  QtRoundedEditRectItem();
  QtTestQtRoundedEditRectItemCompareDialog();
  QtTestQtRoundedEditRectItemModifyDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

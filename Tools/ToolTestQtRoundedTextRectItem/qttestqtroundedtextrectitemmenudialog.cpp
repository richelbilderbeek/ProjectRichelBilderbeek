//---------------------------------------------------------------------------
/*
TestQtRoundedTextRectItem, tool to test QtRoundedTextRectItem
Copyright (C) 2012  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtRoundedTextRectItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestqtroundedtextrectitemmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtkeyboardfriendlygraphicsview.h"
#include "qtroundedrectitem.h"
#include "qtroundedtextrectitem.h"
#include "testqtroundedtextrectitemmenudialog.h"
#include "trace.h"
#include "qtaboutdialog.h"
#include "qttestqtroundedtextrectitemmaindialog.h"
#include "ui_qttestqtroundedtextrectitemmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedTextRectItemMenuDialog::QtTestQtRoundedTextRectItemMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedTextRectItemMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQtRoundedTextRectItemMenuDialog::~QtTestQtRoundedTextRectItemMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedTextRectItemMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestQtRoundedTextRectItemMenuDialog::on_button_about_clicked()
{
  About a = TestQtRoundedTextRectItemMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  a.AddLibrary("QtRoundedRectItem version: " + QtRoundedRectItem::GetVersion());
  a.AddLibrary("QtRoundedTextRectItem version: " + QtRoundedTextRectItem::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestQtRoundedTextRectItemMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestQtRoundedTextRectItemMenuDialog::on_button_start_clicked()
{
  QtTestQtRoundedTextRectItemMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestQtRoundedTextRectItemMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestQtRoundedTextRectItemMenuDialog::Test");
  TRACE("Finished ribi::QtTestQtRoundedTextRectItemMenuDialog::Test successfully");
}
#endif

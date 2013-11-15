// ---------------------------------------------------------------------------
/*
TestQtArrowItems, tool to test Qt arrow QGraphicsItems
Copyright (C) 2012-2013  Richel Bilderbeek

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
#include "qttestqtarrowitemsmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testqtarrowitemsmenudialog.h"
#include "qtaboutdialog.h"
#include "qttestqtarrowitemsmaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qttestqtarrowitemsmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtArrowItemsMenuDialog::QtTestQtArrowItemsMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtArrowItemsMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtTestQtArrowItemsMenuDialog::~QtTestQtArrowItemsMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtArrowItemsMenuDialog::keyPressEvent(QKeyEvent * event)
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

void ribi::QtTestQtArrowItemsMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestQtArrowItemsMenuDialog::on_button_start_clicked()
{
  QtTestQtArrowItemsMainDialog d;
  ShowChild(&d);
}


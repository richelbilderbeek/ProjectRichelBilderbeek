//---------------------------------------------------------------------------
/*
TestKeyboardFriendlyGraphicsView, tests QtKeyboardFriendlyGraphicsView
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
//From http://www.richelbilderbeek.nl/ToolTestKeyboardFriendlyGraphicsView.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestqtkeyboardfriendlygraphicsviewmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>
#include "about.h"
#include "qtaboutdialog.h"
#include "qtarrowitem.h"
#include "qtdisplaypositem.h"
#include "qtleftrightrectitem.h"
#include "qtpatharrowitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtroundedrectitem.h"
#include "qtroundededitrectitem.h"
#include "testtimer.h"
#include "qttestqtkeyboardfriendlygraphicsviewwidget.h"
#include "testqtkeyboardfriendlygraphicsviewmenudialog.h"
#include "trace.h"
#include "ui_qttestqtkeyboardfriendlygraphicsviewmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::QtTestKeyboardFriendlyGraphicsViewMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestKeyboardFriendlyGraphicsViewMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  {
    typedef QtTestKeyboardFriendlyGraphicsViewWidget Widget;
    Widget * const widget = new Widget;
    widget->m_signal_request_about.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ShowAbout,this));
    widget->m_signal_request_quit.connect(
      boost::bind(&ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Quit,this));
    ui->layout->addWidget(widget,0,0);
  }
  //Make this dialog big and centered
  {
    const QRect rect = QDesktopWidget().geometry();
    this->setGeometry(rect.adjusted(64,64,-64,-64));
  }
}

ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::~QtTestKeyboardFriendlyGraphicsViewMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) close();
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::ShowAbout()
{
  About about = TestKeyboardFriendlyGraphicsViewMenuDialog().GetAbout();
  about.AddLibrary("QtArrowItem version: " + QtArrowItem::GetVersion());
  about.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  about.AddLibrary("QtDisplayPosItem version: " + QtDisplayPosItem::GetVersion());
  about.AddLibrary("QtKeyboardFriendlyGraphicsView version: " + QtKeyboardFriendlyGraphicsView::GetVersion());
  about.AddLibrary("QtLeftRightRectItem version: " + QtLeftRightRectItem::GetVersion());
  about.AddLibrary("QtPathArrowItem version: " + QtPathArrowItem::GetVersion());
  about.AddLibrary("QtQuadBezierArrowItem version: " + QtQuadBezierArrowItem::GetVersion());
  about.AddLibrary("QtRoundedRectItem version: " + QtRoundedRectItem::GetVersion());
  about.AddLibrary("QtRoundedEditRectItem version: " + QtRoundedEditRectItem::GetVersion());
  QtAboutDialog d(about);
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Quit()
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestKeyboardFriendlyGraphicsViewMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

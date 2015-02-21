//---------------------------------------------------------------------------
/*
TestQtModels, tool to test the QtModel classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQtModels.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestqtmodelsmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qthideandshowdialog.h"
#include "qtstdvectorfunctionmodel.h"
#include "qtstdvectorstringmodel.h"
#include "qttestqtmodelsmaindialog.h"
#include "qttestqtmodelsmenudialog.h"
#include "qtublasvectorintmodel.h"
#include "qtublasmatrixdoublemodel.h"
#include "testtimer.h"
#include "qtublasvectordoublemodel.h"
#include "testqtmodelsmenudialog.h"
#include "trace.h"
#include "ui_qttestqtmodelsmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolTestQtModelsMenuDialog::QtToolTestQtModelsMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolTestQtModelsMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolTestQtModelsMenuDialog::~QtToolTestQtModelsMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolTestQtModelsMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolTestQtModelsMenuDialog::on_button_about_clicked()
{
  About a = ToolTestQtModelsMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtStdVectorFunctionModel version: " + QtStdVectorFunctionModel::GetVersion());
  a.AddLibrary("QtStdVectorStringModel version: " + QtStdVectorStringModel::GetVersion());
  a.AddLibrary("QtUblasMatrixDoubleModel version: " + QtUblasMatrixDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorDoubleModel version: " + QtUblasVectorDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorIntModel version: " + QtUblasVectorIntModel::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtToolTestQtModelsMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtToolTestQtModelsMenuDialog::on_button_start_clicked()
{
  QtToolTestQtModelsMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolTestQtModelsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    ToolTestQtModelsMenuDialog();
    QtToolTestQtModelsMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

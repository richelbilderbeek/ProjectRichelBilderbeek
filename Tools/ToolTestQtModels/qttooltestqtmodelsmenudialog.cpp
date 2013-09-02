//---------------------------------------------------------------------------
/*
TestQtModels, tool to test the QtModel classes
Copyright (C) 2013 Richel Bilderbeek

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
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestqtmodelsmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qthideandshowdialog.h"
#include "qtstdvectorfunctionmodel.h"
#include "qtstdvectorstringmodel.h"
#include "qttooltestqtmodelsmaindialog.h"
#include "qttooltestqtmodelsmenudialog.h"
#include "qtublasvectorintmodel.h"
#include "qtublasmatrixdoublemodel.h"
#include "qtublasvectordoublemodel.h"
#include "tooltestqtmodelsmenudialog.h"
#include "trace.h"
#include "ui_qttooltestqtmodelsmenudialog.h"

QtToolTestQtModelsMenuDialog::QtToolTestQtModelsMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolTestQtModelsMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

QtToolTestQtModelsMenuDialog::~QtToolTestQtModelsMenuDialog()
{
  delete ui;
}

void QtToolTestQtModelsMenuDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtToolTestQtModelsMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtToolTestQtModelsMenuDialog::on_button_about_clicked()
{
  About a = ToolTestQtModelsMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtStdVectorFunctionModel version: " + QtStdVectorFunctionModel::GetVersion());
  a.AddLibrary("QtStdVectorStringModel version: " + QtStdVectorStringModel::GetVersion());
  a.AddLibrary("QtUblasMatrixDoubleModel version: " + QtUblasMatrixDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorDoubleModel version: " + QtUblasVectorDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorIntModel version: " + QtUblasVectorIntModel::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtToolTestQtModelsMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtToolTestQtModelsMenuDialog::on_button_start_clicked()
{
  QtToolTestQtModelsMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void QtToolTestQtModelsMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Start of QtToolTestQtModelsMenuDialog::Test");
  {
    QtToolTestQtModelsMainDialog d;
  }
  TRACE("Finished QtToolTestQtModelsMenuDialog::Test successfully");
}
#endif

//---------------------------------------------------------------------------
/*
CreateGlossary, tool to create my glossaries
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCreateGlossary.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtcreateglossarymaindialog.h"

#include <QTimer>
#include "createglossarymaindialog.h"
#include "ui_qtcreateglossarymaindialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtCreateGlossaryMainDialog::QtCreateGlossaryMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtCreateGlossaryMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  CreateGlossaryMainDialog().CreateAllGlossaries();
  ui->label->setText("Done!");
}

ribi::QtCreateGlossaryMainDialog::~QtCreateGlossaryMainDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtCreateGlossaryMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  CreateGlossaryMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

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
#include "qttestqtroundededitrectitemcomparedialog.h"
#include <QKeyEvent>

#include "testtimer.h"
#include "trace.h"
#include "ui_qttestqtroundededitrectitemcomparedialog.h"
#pragma GCC diagnostic pop

ribi::QtTestQtRoundedEditRectItemCompareDialog::QtTestQtRoundedEditRectItemCompareDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQtRoundedEditRectItemCompareDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestQtRoundedEditRectItemCompareDialog::~QtTestQtRoundedEditRectItemCompareDialog() noexcept
{
  delete ui;
}

void ribi::QtTestQtRoundedEditRectItemCompareDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::QtTestQtRoundedEditRectItemCompareDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

//---------------------------------------------------------------------------
/*
SimMysteryMachine, simulator of my mystery machine
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
//From http://www.richelbilderbeek.nl/ToolSimMysteryMachine.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsimmysterymachinemaindialog.h"

#include <iostream>

#include <boost/lexical_cast.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "qtmysterymachinewidget.h"
#include "testtimer.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"
#include "ui_qtsimmysterymachinemaindialog.h"
#pragma GCC diagnostic pop

ribi::QtSimMysteryMachineMainDialog::QtSimMysteryMachineMainDialog(QWidget *parent) noexcept
 : QtHideAndShowDialog(parent),
   ui(new Ui::QtSimMysteryMachineMainDialog),
   m_machine(new QtMysteryMachineWidget)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->my_layout->addWidget(m_machine.get());
}

ribi::QtSimMysteryMachineMainDialog::~QtSimMysteryMachineMainDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtSimMysteryMachineMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

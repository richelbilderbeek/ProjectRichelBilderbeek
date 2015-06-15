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
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WTextArea>

#include "about.h"
#include "dial.h"
#include "dialwidget.h"
#include "led.h"
#include "ledwidget.h"
#include "mysterymachine.h"
#include "mysterymachinewidget.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"
#include "wtaboutdialog.h"
#include "wtdialwidget.h"
#include "wtsimmysterymachinemaindialog.h"
#include "wtmysterymachinewidget.h"
#pragma GCC diagnostic pop

ribi::WtSimMysteryMachineMainDialog::Ui::Ui()
 : m_machine(new WtMysteryMachineWidget(300,600))
{

}

ribi::WtSimMysteryMachineMainDialog::WtSimMysteryMachineMainDialog()
  : ui{}
{
  setContentAlignment(Wt::AlignCenter);
  addWidget(ui.m_machine);
}

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
#ifndef QTSIMMYSTERYMACHINEREALMACHINEDIALOG_H
#define QTSIMMYSTERYMACHINEREALMACHINEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtSimMysteryMachineRealMachineDialog;
}

namespace ribi {

class QtSimMysteryMachineRealMachineDialog : public QtHideAndShowDialog
{
    Q_OBJECT

public:
    explicit QtSimMysteryMachineRealMachineDialog(QWidget *parent = 0) noexcept;
    QtSimMysteryMachineRealMachineDialog(const QtSimMysteryMachineRealMachineDialog&) = delete;
    QtSimMysteryMachineRealMachineDialog& operator=(const QtSimMysteryMachineRealMachineDialog&) = delete;
    ~QtSimMysteryMachineRealMachineDialog() noexcept;

private:
    Ui::QtSimMysteryMachineRealMachineDialog *ui;
};

} //~namespace ribi

#endif // QTSIMMYSTERYMACHINEREALMACHINEDIALOG_H

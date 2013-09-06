//---------------------------------------------------------------------------
/*
SimMysteryMachine, simulator of my mystery machine
Copyright (C) 2011-2012 Richel Bilderbeek

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
#ifndef QTSIMMYSTERYMACHINEINSTRUCTIONSDIALOG_H
#define QTSIMMYSTERYMACHINEINSTRUCTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class QtSimMysteryMachineInstructionsDialog;
}

namespace ribi {

class QtSimMysteryMachineInstructionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QtSimMysteryMachineInstructionsDialog(QWidget *parent = 0);
    ~QtSimMysteryMachineInstructionsDialog();

private:
    Ui::QtSimMysteryMachineInstructionsDialog *ui;
};

} //~namespace ribi

#endif // QTSIMMYSTERYMACHINEINSTRUCTIONSDIALOG_H

//---------------------------------------------------------------------------
/*
Maziak, a simple maze game
Copyright (C) 2007-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameMaziak.htm
//---------------------------------------------------------------------------
#ifndef QTMAZIAKINSTRUCTIONSDIALOG_H
#define QTMAZIAKINSTRUCTIONSDIALOG_H

#include <QDialog>

namespace Ui {
    class QtMaziakInstructionsDialog;
}

class QtMaziakInstructionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QtMaziakInstructionsDialog(QWidget *parent = 0);
    ~QtMaziakInstructionsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QtMaziakInstructionsDialog *ui;
};

#endif // QTMAZIAKINSTRUCTIONSDIALOG_H

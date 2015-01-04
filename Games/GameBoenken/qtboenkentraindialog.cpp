//---------------------------------------------------------------------------
/*
Boenken. A multiplayer soccer/billiards game.
Copyright (C) 2007-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameBoenken.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtboenkentraindialog.h"
#include "ui_qtboenkentraindialog.h"
#pragma GCC diagnostic pop

ribi::QtBoenkenTrainDialog::QtBoenkenTrainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtBoenkenTrainDialog)
{
  ui->setupUi(this);
}

ribi::QtBoenkenTrainDialog::~QtBoenkenTrainDialog() noexcept
{
  delete ui;
}

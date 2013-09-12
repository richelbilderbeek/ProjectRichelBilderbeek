//---------------------------------------------------------------------------
/*
Das Wahre Schlagerfest, a simple game
Copyright (C) 2003-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameDasWahreSchlagerfest.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtdaswahreschlagerfestmaindialog.h"

#include <QKeyEvent>
#include "qtdaswahreschlagerfestwidget.h"
#include "ui_qtdaswahreschlagerfestmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtDasWahreSchlagerfestMainDialog::QtDasWahreSchlagerfestMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDasWahreSchlagerfestMainDialog)
{
  ui->setupUi(this);
}

ribi::QtDasWahreSchlagerfestMainDialog::~QtDasWahreSchlagerfestMainDialog()
{
  delete ui;
}


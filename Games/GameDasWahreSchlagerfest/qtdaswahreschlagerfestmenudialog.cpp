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
#include "qtdaswahreschlagerfestmenudialog.h"

#include "daswahreschlagerfestmenudialog.h"
#include "qtaboutdialog.h"
#include "qtdaswahreschlagerfestmaindialog.h"
#include "ui_qtdaswahreschlagerfestmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtDasWahreSchlagerfestMenuDialog::QtDasWahreSchlagerfestMenuDialog(QWidget *parent) noexcept
  : QDialog(parent),
    ui(new Ui::QtDasWahreSchlagerfestMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtDasWahreSchlagerfestMenuDialog::~QtDasWahreSchlagerfestMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_start_clicked() noexcept
{
  QtDasWahreSchlagerfestMainDialog d;
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(DasWahreSchlagerfestMenuDialog::GetAbout());
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtDasWahreSchlagerfestMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

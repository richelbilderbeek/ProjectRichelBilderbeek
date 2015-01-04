//---------------------------------------------------------------------------
/*
PerfectElasticCollision, tool to investigate a perfect elastic collision
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From hhtp://www.richelbilderbeek.nl/ToolPerfectElasticCollision.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtperfectelasticcollisionmenudialog.h"

#include "perfectelasticcollisionmenudialog.h"
#include "qtaboutdialog.h"
#include "qtperfectelasticcollisionmaindialog.h"
#include "ui_qtperfectelasticcollisionmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtPerfectElasticCollisionMenuDialog::QtPerfectElasticCollisionMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPerfectElasticCollisionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtPerfectElasticCollisionMenuDialog::~QtPerfectElasticCollisionMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtPerfectElasticCollisionMenuDialog::on_button_start_clicked()
{
  QtPerfectElasticCollisionMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtPerfectElasticCollisionMenuDialog::on_button_about_clicked()
{
  About a = PerfectElasticCollisionMenuDialog().GetAbout();
  //a.AddLibrary("QtDialWidget version: " + QtDialWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtPerfectElasticCollisionMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtPerfectElasticCollisionMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtPerfectElasticCollisionMainDialog d;
  }
}
#endif

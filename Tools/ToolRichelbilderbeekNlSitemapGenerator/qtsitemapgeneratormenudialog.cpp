//---------------------------------------------------------------------------
/*
RichelbilderbeekNlSitemapGenerator, generates the richelbilderbeek.nl sitemap
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRichelbilderbeekNlSitemapGenerator.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtsitemapgeneratormenudialog.h"

#include <cassert>

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qtsitemapgeneratormaindialog.h"
#include "sitemapgeneratormenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtsitemapgeneratormenudialog.h"
#pragma GCC diagnostic pop

ribi::QtSitemapGeneratorMenuDialog::QtSitemapGeneratorMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSitemapGeneratorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtSitemapGeneratorMenuDialog::~QtSitemapGeneratorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtSitemapGeneratorMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QtHideAndShowDialog::keyPressEvent(e);
}

void ribi::QtSitemapGeneratorMenuDialog::on_button_start_clicked()
{
  QtSitemapGeneratorMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtSitemapGeneratorMenuDialog::on_button_about_clicked()
{
  About about = SitemapGeneratorMenuDialog().GetAbout();
  about.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());

  QtAboutDialog d(about);
  this->ShowChild(&d);
}

void ribi::QtSitemapGeneratorMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtSitemapGeneratorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    SitemapGeneratorMenuDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

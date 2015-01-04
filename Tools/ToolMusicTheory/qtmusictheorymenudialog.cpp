//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtmusictheorymenudialog.h"

#include <QDesktopWidget>

#include "musictheorymenudialog.h"
#include "qtaboutdialog.h"
#include "qtchordedge.h"
#include "qtchordrelationswidget.h"
#include "testtimer.h"
#include "qtchordvertex.h"
#include "qtmultiscalechordrelationswidget.h"
#include "qtmusictheorysinglescaledialog.h"
#include "qtmusictheorymultiscaledialog.h"
#include "ui_qtmusictheorymenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtMusicTheoryMenuDialog::QtMusicTheoryMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtMusicTheoryMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtMusicTheoryMenuDialog::~QtMusicTheoryMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtMusicTheoryMenuDialog::on_button_about_clicked()
{
  About a = MusicTheoryMenuDialog().GetAbout();
  a.AddLibrary("QtChordEdge version: " + QtChordEdge::GetVersion());
  a.AddLibrary("QtChordVertex version: " + QtChordVertex::GetVersion());
  a.AddLibrary("QtChordRelationsWidget version: " + QtChordRelationsWidget::GetVersion());
  a.AddLibrary("QtMultiScaleChordRelationsWidget version: " + QtMultiScaleChordRelationsWidget::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtMusicTheoryMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtMusicTheoryMenuDialog::on_button_start_singlescale_clicked()
{
  QtMusicTheorySingleScaleDialog d;
  this->ShowChild(&d);
}

void ribi::QtMusicTheoryMenuDialog::on_button_start_multiscale_clicked()
{
  QtMusicTheoryMultiScaleDialog d;
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtMusicTheoryMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

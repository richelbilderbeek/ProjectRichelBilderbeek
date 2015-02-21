//---------------------------------------------------------------------------
/*
RandomCode, tool to generate random C++ code
Copyright (C) 2007-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolRandomCode.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtrandomcodemaindialog.h"

#include <string>
#include <vector>

#include <QDesktopWidget>
#include <QKeyEvent>

#include "about.h"
#include "qtaboutdialog.h"
#include "ui_qtrandomcodemaindialog.h"
#include "randomcode.h"
#include "testtimer.h"
#include "randomcodemenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtRandomCodeMainDialog::QtRandomCodeMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRandomCodeMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->setGeometry( screen.adjusted(64,64,-64,-64));
  this->move( screen.center() - this->rect().center() );

  ui->button_generate->click();
}

ribi::QtRandomCodeMainDialog::~QtRandomCodeMainDialog() noexcept
{
  delete ui;
}

void ribi::QtRandomCodeMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtRandomCodeMainDialog::on_button_generate_clicked()
{
  const std::vector<std::string> v = RandomCode::CreateRandomCode();
  ui->textEdit->clear();
  for(const std::string& s: v)
  {
    ui->textEdit->append(s.c_str());
  }
}

void ribi::QtRandomCodeMainDialog::on_button_about_clicked()
{
  About about = RandomCodeMenuDialog().GetAbout();
  //about.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  this->ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtRandomCodeMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

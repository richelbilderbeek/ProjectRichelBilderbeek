//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
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
//From http://www.richelbilderbeek.nl/ToolTestShinyButton.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestshinybuttonmenudialog.h"

#include "qtaboutdialog.h"
#include "qtshinybuttonwidget.h"
#include "qttestshinybuttonmaindialog.h"
#include "testshinybuttonmenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestshinybuttonmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestShinyButtonMenuDialog::QtTestShinyButtonMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestShinyButtonMenuDialog),
    m_button_start(new QtShinyButtonWidget(0.25,0.25,"Start")),
    m_button_about(new QtShinyButtonWidget(0.50,0.25,"About")),
    m_button_quit( new QtShinyButtonWidget(0.75,0.25,"Quit"))
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->layout->addWidget(m_button_start.get());
  ui->layout->addWidget(m_button_about.get());
  ui->layout->addWidget(m_button_quit.get());

  m_button_start->GetWidget()->m_signal_clicked.connect(boost::bind(
    &ribi::QtTestShinyButtonMenuDialog::OnButtonStartClicked,this));
  m_button_about->GetWidget()->m_signal_clicked.connect(boost::bind(
    &ribi::QtTestShinyButtonMenuDialog::OnButtonAboutClicked,this));
  m_button_quit->GetWidget()->m_signal_clicked.connect(boost::bind(
    &ribi::QtTestShinyButtonMenuDialog::OnButtonQuitClicked,this));
}

ribi::QtTestShinyButtonMenuDialog::~QtTestShinyButtonMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestShinyButtonMenuDialog::OnButtonStartClicked()
{
  QtTestShinyButtonMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestShinyButtonMenuDialog::OnButtonAboutClicked()
{
  this->hide();
  About a = TestShinyButtonMenuDialog().GetAbout();
  a.AddLibrary("QtShinyButtonWidget version: " + QtShinyButtonWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestShinyButtonMenuDialog::OnButtonQuitClicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestShinyButtonMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

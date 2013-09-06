//---------------------------------------------------------------------------
/*
TestShinyButton, tool to test the ShinyButton class
Copyright (C) 2011 Richel Bilderbeek

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


#include "qttestshinybuttonmenudialog.h"

#include "qtaboutdialog.h"
#include "qtshinybuttonwidget.h"
#include "qttestshinybuttonmaindialog.h"
#include "testshinybuttonmenudialog.h"
#include "ui_qttestshinybuttonmenudialog.h"

ribi::QtTestShinyButtonMenuDialog::QtTestShinyButtonMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtTestShinyButtonMenuDialog),
    m_button_start(new QtShinyButtonWidget(0.25,0.25,"Start")),
    m_button_about(new QtShinyButtonWidget(0.50,0.25,"About")),
    m_button_quit( new QtShinyButtonWidget(0.75,0.25,"Quit"))
{
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

ribi::QtTestShinyButtonMenuDialog::~QtTestShinyButtonMenuDialog()
{
  delete ui;
}

void ribi::QtTestShinyButtonMenuDialog::OnButtonStartClicked()
{
  this->hide();
  QtTestShinyButtonMainDialog d;
  d.exec();
  this->show();
}

void ribi::QtTestShinyButtonMenuDialog::OnButtonAboutClicked()
{
  this->hide();
  About a = TestShinyButtonMenuDialog::GetAbout();
  a.AddLibrary("QtShinyButtonWidget version: " + QtShinyButtonWidget::GetVersion());
  QtAboutDialog d(a);
  d.exec();
  this->show();
}

void ribi::QtTestShinyButtonMenuDialog::OnButtonQuitClicked()
{
  this->close();
}


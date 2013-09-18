//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtconnectthreemenudialog.h"
#include "connectthreemenudialog.h"
#include "qtaboutdialog.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreeresources.h"
#include "qtconnectthreewidget.h"
#include "qtselectplayerwidget.h"
#include "ui_qtconnectthreemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtConnectThreeMenuDialog::QtConnectThreeMenuDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtConnectThreeMenuDialog),
    m_resources(new QtConnectThreeResources),
    m_select(new QtSelectPlayerWidget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->layout_horizontal->addWidget(m_select.get());
}

ribi::QtConnectThreeMenuDialog::~QtConnectThreeMenuDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtConnectThreeMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const boost::shared_ptr<const ConnectThreeResources> resources(new QtConnectThreeResources);
  QtConnectThreeGameDialog d(resources,nullptr,std::bitset<3>(false));
}
#endif

void ribi::QtConnectThreeMenuDialog::on_button_start_clicked() noexcept
{
  QtConnectThreeGameDialog d(m_resources, nullptr,this->m_select->GetIsPlayerHuman());
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtConnectThreeMenuDialog::on_button_about_clicked() noexcept
{
  About about = ConnectThreeMenuDialog::GetAbout();
  about.AddLibrary("QtConnectThreeWidget version: " + QtConnectThreeWidget::GetVersion());
  QtAboutDialog d(about);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtConnectThreeMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

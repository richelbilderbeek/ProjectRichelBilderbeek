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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorPperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtconnectthreemenudialog.h"


#include "connectthreemenudialog.h"
#include "qtaboutdialog.h"
#include "qtconnectthreegamedialog.h"
#include "qtconnectthreeresources.h"
#include "qtconnectthreewidget.h"
#include "qtselectplayerwidget.h"
#include "ui_qtconnectthreemenudialog.h"

QtConnectThreeMenuDialog::QtConnectThreeMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtConnectThreeMenuDialog),
    m_select(new QtSelectPlayerWidget)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  ui->layout_horizontal->addWidget(m_select.get());
}

QtConnectThreeMenuDialog::~QtConnectThreeMenuDialog()
{
  delete ui;
}

void QtConnectThreeMenuDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

#ifndef NDEBUG
void QtConnectThreeMenuDialog::Test()
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

void QtConnectThreeMenuDialog::on_button_start_clicked()
{
  const boost::shared_ptr<const ConnectThreeResources> resources(new QtConnectThreeResources);
  QtConnectThreeGameDialog d(resources, nullptr,this->m_select->GetIsPlayerHuman());
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void QtConnectThreeMenuDialog::on_button_about_clicked()
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

void QtConnectThreeMenuDialog::on_button_quit_clicked()
{
  close();
}

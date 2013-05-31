//---------------------------------------------------------------------------
/*
UbuntuOneWatcher, tool to see what Ubuntu One is doing
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolUbuntuOneWatcher.htm
//---------------------------------------------------------------------------
#include <algorithm>
#include <cstdlib>
#include <string>
//---------------------------------------------------------------------------
#include <boost/version.hpp>
//---------------------------------------------------------------------------
#include <QFile>
//---------------------------------------------------------------------------
#include "dialogabout.h"
#include "dialogmain.h"
#include "dialogwhatsnew.h"
#include "ui_dialogabout.h"
//---------------------------------------------------------------------------
DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
  ui->setupUi(this);

  QObject::connect(ui->button_whats_new,SIGNAL(clicked()),
    this,SLOT(onWhatsNew()));
  QObject::connect(ui->button_about_qt,SIGNAL(clicked()),
    qApp,SLOT(aboutQt()));

  ui->label_title->setText(
    QString("UbuntuOneWatcher version ")
    + QString(DialogMain::GetVersion().c_str()));


  ui->label_boost_version->setText(
    QString("Boost version: ")
    + QString(GetBoostVersion().c_str()));
}
//---------------------------------------------------------------------------
DialogAbout::~DialogAbout()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogAbout::changeEvent(QEvent *e)
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
//---------------------------------------------------------------------------
void DialogAbout::onWhatsNew()
{
  DialogWhatsNew d;
  d.exec();
}
//---------------------------------------------------------------------------
///GetBoostVersion returns the version of the current Boost library.
///From http://www.richelbilderbeek.nl/CppGetBoostVersion.htm
const std::string GetBoostVersion()
{
  std::string s = BOOST_LIB_VERSION;
  std::replace(s.begin(),s.end(),'_','.');
  return s;
}
//---------------------------------------------------------------------------

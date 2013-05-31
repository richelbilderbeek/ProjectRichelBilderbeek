//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
Copyright (C) 2010-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolRegexTester.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtregextestermenudialog.h"


#include <cassert>
#include <string>
#include <trace.h>

#include <boost/shared_ptr.hpp>
#include <QIcon>
#include "qtaboutdialog.h"
#include "qtregextestermaindialog.h"
#include "regextesterboostmaindialog.h"
#include "regextestercpp11maindialog.h"
#include "regextestermaindialog.h"
#include "regextestermenudialog.h"
#include "regextesterqtmaindialog.h"
#include "ui_qtregextestermenudialog.h"

QtRegexTesterMenuDialog::QtRegexTesterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRegexTesterMenuDialog)
{
  ui->setupUi(this);
}

QtRegexTesterMenuDialog::~QtRegexTesterMenuDialog()
{
  delete ui;
}

void QtRegexTesterMenuDialog::changeEvent(QEvent *e)
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

void QtRegexTesterMenuDialog::on_button_about_clicked()
{
  const About a = RegexTesterMenuDialog::GetAbout();
  this->hide();
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.exec();
  this->show();
}

void QtRegexTesterMenuDialog::on_button_quit_clicked()
{
  close();
}


void QtRegexTesterMenuDialog::on_button_find_cpp11_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterCpp11MainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicCpp11.png")));
  this->ShowChild(&qd);
}

void QtRegexTesterMenuDialog::on_button_find_boost_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterBoostMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicBoost.png")));
  this->ShowChild(&qd);
}

void QtRegexTesterMenuDialog::on_button_find_qt_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterQtMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicQt.png")));
  this->ShowChild(&qd);
}

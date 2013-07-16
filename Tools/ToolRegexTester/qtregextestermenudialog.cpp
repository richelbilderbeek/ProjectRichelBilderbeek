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

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <QIcon>

#include "qtaboutdialog.h"
#include "qtregextestermaindialog.h"
#include "regextesterboostregexmaindialog.h"
#include "regextesterboostxpressivemaindialog.h"
#include "regextestercpp11maindialog.h"
#include "regextestermaindialog.h"
#include "regextestermenudialog.h"
#include "regextesterqtmaindialog.h"
#include "trace.h"
#include "ui_qtregextestermenudialog.h"

QtRegexTesterMenuDialog::QtRegexTesterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRegexTesterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

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


void QtRegexTesterMenuDialog::on_button_cpp11_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterCpp11MainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicCpp11.png")));
  this->ShowChild(&qd);
}

void QtRegexTesterMenuDialog::on_button_qt_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterQtMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicQt.png")));
  this->ShowChild(&qd);
}

void QtRegexTesterMenuDialog::on_button_boost_regex_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterBoostRegexMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicBoost.png")));
  this->ShowChild(&qd);
}

void QtRegexTesterMenuDialog::on_button_boost_xpressive_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterBoostXpressiveMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicBoost.png")));
  this->ShowChild(&qd);
}

#ifndef NDEBUG
void QtRegexTesterMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtRegexTesterMenuDialog::Test");
  {
    const boost::shared_ptr<RegexTesterMainDialog> d(
      new RegexTesterCpp11MainDialog);
    assert(d);
  }
  {
    boost::shared_ptr<RegexTesterMainDialog> d(
      new RegexTesterQtMainDialog);
    assert(d);
  }
  {
    boost::shared_ptr<RegexTesterMainDialog> d(
      new RegexTesterBoostRegexMainDialog);
    assert(d);
  }
  {
    boost::shared_ptr<RegexTesterMainDialog> d(
      new RegexTesterBoostXpressiveMainDialog);
    assert(d);
  }
  TRACE("Finished QtRegexTesterMenuDialog::Test successfully");
}
#endif

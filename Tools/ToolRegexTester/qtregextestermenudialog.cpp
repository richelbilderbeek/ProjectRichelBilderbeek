//---------------------------------------------------------------------------
/*
RegexTester, regular expression tester
Copyright (C) 2010-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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
#include "testtimer.h"
#include "regextesterqtmaindialog.h"
#include "trace.h"
#include "ui_qtregextestermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtRegexTesterMenuDialog::QtRegexTesterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtRegexTesterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::QtRegexTesterMenuDialog::~QtRegexTesterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtRegexTesterMenuDialog::on_button_about_clicked()
{
  const About a = RegexTesterMenuDialog().GetAbout();
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtRegexTesterMenuDialog::on_button_quit_clicked()
{
  close();
}


void ribi::QtRegexTesterMenuDialog::on_button_cpp11_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterCpp11MainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicCpp11.png")));
  this->ShowChild(&qd);
}

void ribi::QtRegexTesterMenuDialog::on_button_qt_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterQtMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicQt.png")));
  this->ShowChild(&qd);
}

void ribi::QtRegexTesterMenuDialog::on_button_boost_regex_clicked()
{
  #ifdef TOOLREGEXTESTER_ADD_BOOST_REGEX
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterBoostRegexMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicBoost.png")));
  this->ShowChild(&qd);
  #else
  ui->button_boost_regex->setText("Boost.Regex omitted from (cross)compile");
  #endif
}

void ribi::QtRegexTesterMenuDialog::on_button_boost_xpressive_clicked()
{
  boost::shared_ptr<RegexTesterMainDialog> d(new RegexTesterBoostXpressiveMainDialog);
  QtRegexTesterMainDialog qd(d);
  qd.setWindowIcon(QIcon(QPixmap(":/images/PicBoost.png")));
  this->ShowChild(&qd);
}

#ifndef NDEBUG
void ribi::QtRegexTesterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
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
  #ifdef TOOLREGEXTESTER_ADD_BOOST_REGEX
  {
    boost::shared_ptr<RegexTesterMainDialog> d(
      new RegexTesterBoostRegexMainDialog);
    assert(d);
  }
  #endif
  {
    boost::shared_ptr<RegexTesterMainDialog> d(
      new RegexTesterBoostXpressiveMainDialog);
    assert(d);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

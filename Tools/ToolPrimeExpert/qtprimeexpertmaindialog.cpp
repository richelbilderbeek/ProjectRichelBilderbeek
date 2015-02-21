//---------------------------------------------------------------------------
/*
PrimeExpert, tool to test if a number is prime
Copyright (C) 2008-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolPrimeExpert.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtprimeexpertmaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

#include "about.h"
#include "qtaboutdialog.h"
#include "primeexpert.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtprimeexpertmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtToolPrimeExpertMainDialog::QtToolPrimeExpertMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolPrimeExpertMainDialog),
    m_expert(new PrimeExpert)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  ui->edit_value->setText("2");
}

ribi::QtToolPrimeExpertMainDialog::~QtToolPrimeExpertMainDialog() noexcept
{
  delete ui;
}

void ribi::QtToolPrimeExpertMainDialog::on_edit_value_textChanged(QString s)
{
  ui->text->clear();
  try
  {
    boost::lexical_cast<int>(s.toStdString());
  }
  catch (boost::bad_lexical_cast&)
  {
    ui->text->appendPlainText("NaN");
    return;
  }
  const int value = boost::lexical_cast<int>(s.toStdString());
  if (value < 2)
  {
    ui->text->appendPlainText("Not prime");
    return;
  }
  if (value == 2)
  {
    ui->text->appendPlainText("Prime");
    return;
  }
  const boost::timer t;
  const bool isPrime = m_expert->IsPrime(value);
  const double time = t.elapsed();
  const std::string text
    = std::string(isPrime ? "Prime" : "Not prime")
    + " ("
    + boost::lexical_cast<std::string>(time)
    + " sec)";
  ui->text->appendPlainText(text.c_str());
}

#ifndef NDEBUG
void ribi::QtToolPrimeExpertMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

//---------------------------------------------------------------------------
/*
TestPrimeExpert, tool to test the PrimeExpert class
Copyright (C) 2008-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPrimeExpert.htm
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>
//------------------------------------------------------------
#include "about.h"
#include "qtaboutdialog.h"
#include "testprimeexpertdialog.h"
#include "ui_testprimeexpertdialog.h"
//------------------------------------------------------------
TestPrimeExpertDialog::TestPrimeExpertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestPrimeExpertDialog)
{
  ui->setupUi(this);
  ui->edit_value->setText("2");
}
//------------------------------------------------------------
TestPrimeExpertDialog::~TestPrimeExpertDialog()
{
  delete ui;
}
//------------------------------------------------------------
void TestPrimeExpertDialog::changeEvent(QEvent *e)
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
//------------------------------------------------------------
const std::string TestPrimeExpertDialog::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> TestPrimeExpertDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2008-07-12: Version 1.0: initial version in C++ Builder");
  v.push_back("2011-02-26: Version 2.0: port to Qt Creator");
  return v;
}
//---------------------------------------------------------------------------
void TestPrimeExpertDialog::on_edit_value_textChanged(QString s)
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
  const bool isPrime = m_expert.IsPrime(value);
  const double time = t.elapsed();
  const std::string text
    = std::string(isPrime ? "Prime" : "Not prime")
    + " ("
    + boost::lexical_cast<std::string>(time)
    + " sec)";
  ui->text->appendPlainText(text.c_str());
}
//------------------------------------------------------------
void TestPrimeExpertDialog::on_button_about_clicked()
{
  About about(
    "Richel Bilderbeek",
    "TestPrimeExpert",
    "Tool to test the PrimeExpert class",
    "the 26th of February 2011",
    "2008-2011",
    "http://www.richelbilderbeek.nl/ToolTestPrimeExpert.htm",
    GetVersion(),
    GetVersionHistory());
  about.AddLibrary("PrimeExpert version: " + PrimeExpert::GetVersion());
  QtAboutDialog d(about);
  d.exec();
}
//------------------------------------------------------------


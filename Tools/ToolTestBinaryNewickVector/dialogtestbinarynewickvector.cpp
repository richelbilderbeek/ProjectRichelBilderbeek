//---------------------------------------------------------------------------
/*
TestBinaryNewickVector, GUI tool to test BinaryNewickVector
Copyright (C) 2010-2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestBinaryNewickVector.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
//---------------------------------------------------------------------------
#include <QTimer>
//---------------------------------------------------------------------------
#include "BigIntegerLibrary.hh"
//---------------------------------------------------------------------------
#include "about.h"
#include "dialogtestbinarynewickvector.h"
#include "newick.h"
#include "newickstorage.h"
#include "binarynewickvector.h"
#include "sortedbinarynewickvector.h"
#include "qtaboutdialog.h"
#include "ui_dialogtestbinarynewickvector.h"
//---------------------------------------------------------------------------
///DialogTestBinaryNewickVector constructor performs most Newick tests
DialogTestBinaryNewickVector::DialogTestBinaryNewickVector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTestBinaryNewickVector),
    m_timer(new QTimer)
{
  ui->setupUi(this);
  QObject::connect(
    ui->edit_newick,SIGNAL(textChanged(QString)),
    this,SLOT(OnAnyChange()));
  QObject::connect(
    ui->edit_theta,SIGNAL(textChanged(QString)),
    this,SLOT(OnAnyChange()));
  QObject::connect(
    m_timer,SIGNAL(timeout()),
    this,SLOT(OnDemoTick()));

  #ifndef NDEBUG
  setWindowTitle(windowTitle()+" (debug)");
  #else
  setWindowTitle(windowTitle()+" (release)");
  #endif

  #ifndef NDEBUG
  //Test general Newick functions
  Newick::Test();
  BinaryNewickVector::Test();

  #endif //~#ifndef NDEBUG

  this->OnAnyChange();
}
//---------------------------------------------------------------------------
DialogTestBinaryNewickVector::~DialogTestBinaryNewickVector()
{
  m_timer->stop();
  delete ui;
  delete m_timer;
}
//---------------------------------------------------------------------------
void DialogTestBinaryNewickVector::changeEvent(QEvent *e)
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
const std::string DialogTestBinaryNewickVector::GetVersion()
{
  return "3.1";
}
//---------------------------------------------------------------------------
const std::vector<std::string> DialogTestBinaryNewickVector::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-08-20: Version 1.0: initial version, tool was called TestNewickVector");
  v.push_back("2010-08-21: Version 1.1: added more debug checks, added IsBinary,  GetSimpler and GetRootBranches");
  v.push_back("2010-08-24: Version 1.2: calculates the total number of derived Newicks and (related to this) the number of symmetries in a Newick");
  v.push_back("2010-08-25: Version 1.3: calculates the Ewens probability of simple Newicks");
  v.push_back("2010-09-04: Version 1.4: '(1,(3))' is added to the set of invalid Newicks");
  v.push_back("2010-09-16: Version 1.5: added library version numbers, created difference in debug and release version, fixed a bug in BinaryNewickVector::GetSimplerNewicks, added '(0)' to the set of invalid Newicks");
  v.push_back("2010-10-01: Version 1.6: transition from CLN to BigInt library, so TestBinaryNewickVector can run under Windows. Kept checks comparing CLN and BigInt library in under Ubuntu");
  v.push_back("2011-02-20: Version 2.0: major revision of architecture, removed use of CLN library, renamed program to TestBinaryNewickVector");
  v.push_back("2011-03-01: Version 3.0: major rewrite of algorithms");
  v.push_back("2011-03-08: Version 3.1: minor rewrite of algorithms");
  return v;
}
//---------------------------------------------------------------------------
void DialogTestBinaryNewickVector::OnAnyChange()
{
  //Set the lables that everything failed
  //ui->label_valid->setText("Valid Newick: No");
  //ui->label_simpler->setText("Simpler Newicks: N/A");
  //ui->label_branches->setText("(X,Y) = N/A");
  //ui->label_is_binary->setText("Binary Newick: N/A");
  ui->edit_text->clear();

  const std::string s = ui->edit_newick->text().toStdString();
  if (!Newick::IsNewick(s))
  {
    ui->edit_text->appendPlainText("Valid Newick: No");
    //No Newick, why not?
    try
    {
      Newick::CheckNewick(s);
    }
    catch (std::exception& e)
    {
      //Must get here
      ui->edit_text->appendPlainText(QString("Exception: ")
        + QString(e.what()));
    }
    return;
  }
  assert(Newick::IsNewick(s));
  ui->edit_text->appendPlainText("Valid Newick: Yes");
  try
  {
    boost::lexical_cast<double>(
      std::string(ui->edit_theta->text().toStdString()));
  }
  catch (boost::bad_lexical_cast&)
  {
    ui->edit_text->appendPlainText("Valid theta: No");
    return;
  }
  ui->edit_text->appendPlainText("Valid theta: Yes");

  //Check the std::vector Newick
  try
  {
    const std::vector<int> v = Newick::StringToNewick(s);
    Newick::CheckNewick(v);
  }
  catch (std::exception& e)
  {
    //Should not get here
    ui->edit_text->appendPlainText(
      QString(
          "Unexpected exception after checking conversion to std::vector: ")
      + QString(e.what()));
    return;
  }
  //Calculate the complexity
  {
    const BinaryNewickVector n(s);
    const BigInteger c = Newick::CalcComplexity(n.Peek());
    ui->edit_text->appendPlainText("Newick complexity: "
      + QString(bigIntegerToString(c).c_str()));
  }
  //Check if simple Newick
  if (Newick::IsSimple(Newick::StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("Simple Newick: Yes");
    const double theta = boost::lexical_cast<double>(
      std::string(ui->edit_theta->text().toStdString()));
    const double p = Newick::CalcProbabilitySimpleNewick(Newick::StringToNewick(s),theta);
    ui->edit_text->appendPlainText("Ewens probability: "
      + QString(boost::lexical_cast<std::string>(p).c_str()));
  }
  else
  {
    ui->edit_text->appendPlainText("Simple Newick: No");
  }
  //Check if binary Newick
  if (Newick::IsBinaryNewick(Newick::StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("Binary Newick: Yes");
  }
  else
  {
    ui->edit_text->appendPlainText("Binary Newick: No");
  }
  if (Newick::IsTrinaryNewick(Newick::StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("Trinary Newick: Yes");
  }
  else
  {
    ui->edit_text->appendPlainText("Trinary Newick: No");
  }


  //Check the simpler Newicks
  if(!Newick::IsBinaryNewick(Newick::StringToNewick(s))) return;
  assert(Newick::IsBinaryNewick(Newick::StringToNewick(s)));
  if (Newick::IsBinaryNewick(Newick::StringToNewick(s)))
  {
    const std::vector<std::vector<int> > simpler
      = Newick::GetSimplerBinaryNewicks(Newick::StringToNewick(s));
    std::string text = "Simpler Newicks:\n";
    BOOST_FOREACH(const std::vector<int> simple,simpler)
    {
      try
      {
        Newick::CheckNewick(simple);
        text+="  ";
        text+=Newick::NewickToString(simple);
        text+='\n';
      }
      catch (std::exception& e)
      {
        //Should not get here
        text += std::string(e.what()) + std::string("\n");
      }
    }
    if (simpler.empty()) text+=" [none]\n";
    //Pop the trailing '\n'
    text.resize(text.size() - 1);
    ui->edit_text->appendPlainText(text.c_str());
  }
  assert(Newick::IsBinaryNewick(Newick::StringToNewick(s)));
  if (Newick::StringToNewick(s).size()>3
    && Newick::IsBinaryNewick(Newick::StringToNewick(s)))
  {
    std::string text = "(X,Y) =\n";

    const std::pair<std::vector<int>,std::vector<int> > b
      = Newick::GetRootBranchesBinary(
          Newick::StringToNewick(s));
    try
    {
      Newick::CheckNewick(b.first);
      text+=std::string("  ") + Newick::NewickToString(b.first);
    }
    catch (std::exception& e)
    {
      text+=std::string(e.what());
    }
    text+="\n";
    try
    {
      Newick::CheckNewick(b.second);
      text+=std::string("  ") + Newick::NewickToString(b.second);
    }
    catch (std::exception& e)
    {
      text+=std::string(e.what());
    }
    ui->edit_text->appendPlainText(text.c_str());
  }
  //Check CalcNumOfCombinations and CalcNumOfSymmetries
  {
    const BinaryNewickVector n(s);
    const BigInteger n_s = n.CalcNumOfSymmetries();
    const BigInteger n_c = n.CalcNumOfCombinations();
    ui->edit_text->appendPlainText(
      QString("Number of symmetries: ")
      + QString(boost::lexical_cast<std::string>(n_s).c_str()));
    ui->edit_text->appendPlainText(
      QString("Number of combinations: ")
      + QString(bigIntegerToString(n_c).c_str()));
  }
}
//---------------------------------------------------------------------------
void DialogTestBinaryNewickVector::OnDemoTick()
{
  //Get any Newick
  if ((std::rand() >> 4) % 2)
  {
    const std::vector<std::string> v = Newick::CreateValidNewicks();
    const std::string s = v[std::rand() % v.size()];
    ui->edit_newick->setText(QString(s.c_str()));
  }
  else
  {
    const std::vector<std::string> v = Newick::CreateInvalidNewicks();
    const std::string s = v[std::rand() % v.size()];
    ui->edit_newick->setText(QString(s.c_str()));
  }
}
//---------------------------------------------------------------------------
//#ifndef WIN32
///CliToStr converts a cln::cl_I to std::string.
///From http://www.richelbilderbeek.nl/CppCliToStr.htm
//const std::string CliToStr(const cln::cl_I& i)
//{
//  std::stringstream s;
//  s << i;
//  return s.str();
//}
//#endif
//---------------------------------------------------------------------------
void DialogTestBinaryNewickVector::on_button_demo_clicked()
{
  if (m_timer->isActive())
  {
    m_timer->stop();
    assert(!m_timer->isActive());
    ui->button_demo->setText("&Start demo");
  }
  else
  {
    m_timer->start(1000);
    assert(m_timer->isActive());
    ui->button_demo->setText("&Stop demo");
  }
}
//---------------------------------------------------------------------------
void DialogTestBinaryNewickVector::on_button_about_clicked()
{
  About about(
    "Richel Bilderbeek",
    "TestBinaryNewickVector",
    "GUI tool to test BinaryNewickVector",
    "the 8th of March 2011",
    "2010-2011",
    "http://www.richelbilderbeek.nl/ToolTestBinaryNewickVector.htm",
    GetVersion(),
    GetVersionHistory());
  about.AddLibrary("BigInt: version 2010.04.30");
  about.AddLibrary("BinaryNewickVector: " + BinaryNewickVector::GetVersion());

  QtAboutDialog d(about);
  d.exec();
}
//---------------------------------------------------------------------------
void DialogTestBinaryNewickVector::on_button_calculate_clicked()
{
  OnAnyChange();
  const std::string s = ui->edit_newick->text().toStdString();
  if (!Newick::IsNewick(s))
  {
    ui->edit_text->appendPlainText("NOT A VALID NEWICK");
    return;
  }
  if (!Newick::IsBinaryNewick(Newick::StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("NOT A VALID BINARY NEWICK");
    return;
  }
  try
  {
    boost::lexical_cast<double>(std::string(ui->edit_theta->text().toStdString()));
  }
  catch (std::exception& e)
  {
    ui->edit_text->appendPlainText("NOT A VALID THETA");
    return;
  }
  const SortedBinaryNewickVector newick(s);
  const double theta = boost::lexical_cast<double>(
    std::string(ui->edit_theta->text().toStdString()));
  NewickStorage<SortedBinaryNewickVector> storage(newick);

  const double probability
    = Newick::CalculateProbability(
        newick,
        theta,
        storage);

  ui->edit_text->appendPlainText(
    QString("PROBABILITY: ")
    + boost::lexical_cast<std::string>(probability).c_str());
}

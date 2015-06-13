//---------------------------------------------------------------------------
/*
TestBinaryNewickVector, GUI tool to test BinaryNewickVector
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
//From http://www.richelbilderbeek.nl/ToolTestBinaryNewickVector.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <boost/foreach.hpp>

#include <QTimer>

#include "BigIntegerLibrary.hh"

#include "about.h"
#include "qttestbinarynewickvectormaindialog.h"
#include "testtimer.h"
#include "testbinarynewickvectormenudialog.h"
#include "newick.h"
#include "newickstorage.h"
#include "binarynewickvector.h"
#include "sortedbinarynewickvector.h"
#include "qtaboutdialog.h"
#include "ui_qttestbinarynewickvectormaindialog.h"

#pragma GCC diagnostic pop

///QtTestBinaryNewickVectorMainDialog constructor performs most Newick tests
ribi::QtTestBinaryNewickVectorMainDialog::QtTestBinaryNewickVectorMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestBinaryNewickVectorMainDialog),
    m_timer(new QTimer)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
  QObject::connect(
    ui->edit_newick,
    static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
    this,
    &ribi::QtTestBinaryNewickVectorMainDialog::OnAnyChange
  );
  QObject::connect(
    ui->edit_theta,
    static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),
    this,
    &ribi::QtTestBinaryNewickVectorMainDialog::OnAnyChange
  );
  QObject::connect(
    m_timer,&QTimer::timeout,
    this,
    &ribi::QtTestBinaryNewickVectorMainDialog::OnAnyChange
  );

  #ifndef NDEBUG
  setWindowTitle(windowTitle()+" (debug)");
  #else
  setWindowTitle(windowTitle()+" (release)");
  #endif

  #ifndef NDEBUG
  //Test general Newick functions
  Newick().Test();
  BinaryNewickVector::Test();

  #endif //~#ifndef NDEBUG

  this->OnAnyChange();
}

ribi::QtTestBinaryNewickVectorMainDialog::~QtTestBinaryNewickVectorMainDialog() noexcept
{
  m_timer->stop();
  delete ui;
  delete m_timer;
}


void ribi::QtTestBinaryNewickVectorMainDialog::OnAnyChange()
{
  //Set the lables that everything failed
  //ui->label_valid->setText("Valid Newick: No");
  //ui->label_simpler->setText("Simpler Newicks: N/A");
  //ui->label_branches->setText("(X,Y) = N/A");
  //ui->label_is_binary->setText("Binary Newick: N/A");
  ui->edit_text->clear();

  const std::string s = ui->edit_newick->text().toStdString();
  if (!Newick().IsNewick(s))
  {
    ui->edit_text->appendPlainText("Valid Newick: No");
    //No Newick, why not?
    try
    {
      Newick().CheckNewick(s);
    }
    catch (std::exception& e)
    {
      //Must get here
      ui->edit_text->appendPlainText(QString("Exception: ")
        + QString(e.what()));
    }
    return;
  }
  assert(Newick().IsNewick(s));
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
    const std::vector<int> v = Newick().StringToNewick(s);
    Newick().CheckNewick(v);
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
    const BigInteger c = Newick().CalcComplexity(n.Peek());
    ui->edit_text->appendPlainText("Newick complexity: "
      + QString(bigIntegerToString(c).c_str()));
  }
  //Check if simple Newick
  if (Newick().IsSimple(Newick().StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("Simple Newick: Yes");
    const double theta = boost::lexical_cast<double>(
      std::string(ui->edit_theta->text().toStdString()));
    const double p = Newick().CalcProbabilitySimpleNewick(Newick().StringToNewick(s),theta);
    ui->edit_text->appendPlainText("Ewens probability: "
      + QString(boost::lexical_cast<std::string>(p).c_str()));
  }
  else
  {
    ui->edit_text->appendPlainText("Simple Newick: No");
  }
  //Check if binary Newick
  if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("Binary Newick: Yes");
  }
  else
  {
    ui->edit_text->appendPlainText("Binary Newick: No");
  }
  if (Newick().IsTrinaryNewick(Newick().StringToNewick(s)))
  {
    ui->edit_text->appendPlainText("Trinary Newick: Yes");
  }
  else
  {
    ui->edit_text->appendPlainText("Trinary Newick: No");
  }


  //Check the simpler Newicks
  if(!Newick().IsBinaryNewick(Newick().StringToNewick(s))) return;
  assert(Newick().IsBinaryNewick(Newick().StringToNewick(s)));
  if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
  {
    const std::vector<std::vector<int> > simpler
      = Newick().GetSimplerBinaryNewicks(Newick().StringToNewick(s));
    std::string text = "Simpler Newicks:\n";
    BOOST_FOREACH(const std::vector<int> simple,simpler)
    {
      try
      {
        Newick().CheckNewick(simple);
        text+="  ";
        text+=Newick().NewickToString(simple);
        text+='\n';
      }
      catch (std::exception& e)
      {
        //Should not get here
        text += std::string(e.what()) + "\n";
      }
    }
    if (simpler.empty()) text+=" [none]\n";
    //Pop the trailing '\n'
    text.resize(text.size() - 1);
    ui->edit_text->appendPlainText(text.c_str());
  }
  assert(Newick().IsBinaryNewick(Newick().StringToNewick(s)));
  if (Newick().StringToNewick(s).size()>3
    && Newick().IsBinaryNewick(Newick().StringToNewick(s)))
  {
    std::string text = "(X,Y) =\n";

    const std::pair<std::vector<int>,std::vector<int> > b
      = Newick().GetRootBranchesBinary(
          Newick().StringToNewick(s));
    try
    {
      Newick().CheckNewick(b.first);
      text+="  " + Newick().NewickToString(b.first);
    }
    catch (std::exception& e)
    {
      text+=std::string(e.what());
    }
    text+="\n";
    try
    {
      Newick().CheckNewick(b.second);
      text+="  " + Newick().NewickToString(b.second);
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

void ribi::QtTestBinaryNewickVectorMainDialog::OnDemoTick()
{
  //Get any Newick
  if ((std::rand() >> 4) % 2)
  {
    const std::vector<std::string> v = Newick().CreateValidNewicks();
    const std::string s = v[std::rand() % v.size()];
    ui->edit_newick->setText(QString(s.c_str()));
  }
  else
  {
    const std::vector<std::string> v = Newick().CreateInvalidNewicks();
    const std::string s = v[std::rand() % v.size()];
    ui->edit_newick->setText(QString(s.c_str()));
  }
}

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

void ribi::QtTestBinaryNewickVectorMainDialog::on_button_demo_clicked()
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

void ribi::QtTestBinaryNewickVectorMainDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestBinaryNewickVectorMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtTestBinaryNewickVectorMainDialog::on_button_calculate_clicked()
{
  OnAnyChange();
  const std::string s = ui->edit_newick->text().toStdString();
  if (!Newick().IsNewick(s))
  {
    ui->edit_text->appendPlainText("NOT A VALID NEWICK");
    return;
  }
  if (!Newick().IsBinaryNewick(Newick().StringToNewick(s)))
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
    = Newick().CalculateProbability(
        newick,
        theta,
        storage);

  ui->edit_text->appendPlainText(
    QString("PROBABILITY: ")
    + boost::lexical_cast<std::string>(probability).c_str());
}

#ifndef NDEBUG
void ribi::QtTestBinaryNewickVectorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

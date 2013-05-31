//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
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
//From http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <QtGui/QDesktopWidget>
//---------------------------------------------------------------------------
#include "BigIntegerUtils.hh"
//---------------------------------------------------------------------------
#include "newickvector.h"
#include "qtaboutdialog.h"
#include "dialogsimplifynewick.h"
#include "newick.h"
#include "ui_dialogsimplifynewick.h"
//---------------------------------------------------------------------------
DialogSimplifyNewick::DialogSimplifyNewick(QWidget *parent) :
    QDialog(parent, Qt::Window),
    ui(new Ui::DialogSimplifyNewick)
{
  ui->setupUi(this);

  QObject::connect(
    ui->edit_newick,
    SIGNAL(textChanged(QString)),
    this,SLOT(onEditChange()));
  QObject::connect(
    ui->edit_max_complexity,
    SIGNAL(textChanged(QString)),
    this,SLOT(onEditChange()));
  QObject::connect(
    ui->button_start,SIGNAL(clicked()),
    this,SLOT(onStart()));
  QObject::connect(
    ui->button_about,SIGNAL(clicked()),
    this,SLOT(onAbout()));

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );

  #ifndef NDEBUG
  setWindowTitle(windowTitle()+" (debug)");
  #else
  setWindowTitle(windowTitle()+" (release)");
  #endif

  onEditChange();
}
//---------------------------------------------------------------------------
DialogSimplifyNewick::~DialogSimplifyNewick()
{
  delete ui;
}
//---------------------------------------------------------------------------
void DialogSimplifyNewick::changeEvent(QEvent *e)
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
const std::string DialogSimplifyNewick::GetVersion()
{
  return "2.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> DialogSimplifyNewick::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2010-09-12: version 1.0: initial version");
  v.push_back("2010-09-16: version 1.1: use of BinaryNewickVector version 1.0, added library version numbers in About screen, added 'What's New?' dialog, added difference in debug and release version");
  v.push_back("2010-09-16: version 1.2: simplification is frequency dependent. For example: (100,2) will be simplified to (99,2) 50x more often than to (100,1)");
  v.push_back("2011-05-07: version 2.0: use NewickVector instead of BinaryNewickVector, replace custom about and whats new dialog by QtAboutDialog");
  return v;
}
//---------------------------------------------------------------------------
void DialogSimplifyNewick::onAbout()
{
  About a(
    "Richel Bilderbeek",
    "SimplifyNewick",
    "tool to randomly simplify Newick phylogenies",
    "the 7th of May 2011",
    "2010-2011",
    "http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("NewickVector version: " + NewickVector::GetVersion());
  //a.AddLibrary("LoopReader version: " + LoopReader<int>::GetVersion());

  QtAboutDialog d(a);
  d.exec();
}
//---------------------------------------------------------------------------
void DialogSimplifyNewick::onEditChange()
{
  ui->button_start->setEnabled(false);
  ui->text_output->clear();
  //Check newick
  try
  {
    const std::string s
      = ui->edit_newick->text().toStdString();
    Newick::CheckNewick(s);
    ui->text_output->appendPlainText(
      QString("Current Newick: ")
      + QString(s.c_str()));
  }
  catch (std::exception& e)
  {
    ui->text_output->appendPlainText(
      QString("Invalid Newick: ")
      + QString(e.what()));
    return;
  }
  //Display current complexity
  {
    const NewickVector n(
      ui->edit_newick->text().toStdString());
    const std::string s
      = ::bigIntegerToString(Newick::CalcComplexity(n.Peek()));
    ui->text_output->appendPlainText(
      QString("Current complexity: ")
      + QString(s.c_str()));
  }

  //Check complexity
  try
  {
    const std::string s
      = ui->edit_max_complexity->text().toStdString();

    const BigInteger i = ::stringToBigInteger(s);
    if (i < 0)
    {
      ui->text_output->appendPlainText(
        "Invalid input of maximum complexity: "
        "must be bigger than zero");
      return;
    }
  }
  catch (std::exception&)
  {
    ui->text_output->appendPlainText(
      "Invalid input of maximum complexity: "
      "must be a number");
  }
  //Set current maximum complexity to Newick complexity minus one
  {
    const NewickVector n(
      ui->edit_newick->text().toStdString());

    const BigInteger newick_complexity
      = Newick::CalcComplexity(n.Peek());
    const BigInteger current_complexity
      = ::stringToBigInteger(ui->edit_max_complexity->text().toStdString());
    if (current_complexity > newick_complexity)
    {

      ui->edit_max_complexity->setText(
        QString(::bigIntegerToString(newick_complexity - 1).c_str()));
    }
  }

  ui->button_start->setEnabled(true);
}
//---------------------------------------------------------------------------
void DialogSimplifyNewick::onStart()
{
  ui->text_output->clear();
  //Obtain the onEditChange output
  onEditChange();

  #ifdef NDEBUG
  RandomizeTimer();
  #endif

  const std::string s_in = ui->edit_newick->text().toStdString();
  const BigInteger max_complexity = ::stringToBigInteger(
    ui->edit_max_complexity->text().toStdString());

  const std::string s_out = SimplifyNewick(s_in,max_complexity);
  NewickVector n(s_out);

  const std::string complexity
    = ::bigIntegerToString(Newick::CalcComplexity(n.Peek()));
  ui->text_output->appendHtml("Newick found:");
  ui->text_output->appendHtml(n.ToStr().c_str());
  ui->text_output->appendHtml("Newick complexity:");
  ui->text_output->appendHtml(boost::lexical_cast<std::string>(complexity).c_str());

}
//---------------------------------------------------------------------------
///IntToStrWithSep converts an integer to std::string
///and adds thousands seperators.
///From http://www.richelbilderbeek.nl/CppIntToStrWithSep.htm
/*
const std::string IntToStrWithSep(cln::cl_I i)
{
  std::string s
    = boost::lexical_cast<std::string>(cln::mod(i,10));
  i = cln::floor1(i,10);
  int d = 1;
  while (!cln::zerop(i))
  {
    s = boost::lexical_cast<std::string>(cln::mod(i,10))
      + (d % 3 == 0 ? "," : "")
      + s;
    i = cln::floor1(i,10);
    ++d;
  }
  return s;
}
*/
//---------------------------------------------------------------------------
///SafeIntToCli converts an int to cln::cl_I safely.
///From http://www.richelbilderbeek.nl/CppSafeIntToCli.htm
/*
const cln::cl_I SafeIntToCli(const int i)
{
  //A cln::cl_I can handle integer values to 2^29 in its constructor
  if (i < 536870912)
  {
    return cln::cl_I(i);
  }
  const std::string s = boost::lexical_cast<std::string>(i);
  return cln::cl_I(s.c_str());
}
*/
//---------------------------------------------------------------------------
///GetMaxInt returns the highest possible value of a int.
///From http://www.richelbilderbeek.nl/CppGetMaxInt.htm
int GetMaxInt()
{
  return boost::numeric::bounds<int>::highest();
}
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppIntToStrWithSep.htm
template <class T, class U>
int SumSecond(const std::vector<std::pair<T,U> >& v)
{
  int sum = 0;
  typedef std::pair<T,U> Pair;
  BOOST_FOREACH(const Pair& p,v)
  {
    sum+=p.second;
  }
  return sum;
}
//---------------------------------------------------------------------------
///SimplifyNewick simplifies a Newick below a certain complexity,
///in a frequency dependent way.
///For example, for the phylogeny (100,2), SimplifyNewick
///returns (99,2) 50x as often as (100,1).
///From http://www.richelbilderbeek.nl/CppSimplifyNewick.htm
const std::string SimplifyNewick(
  const std::string& s, const BigInteger& max_complexity)
{
  NewickVector n(s);
  while (1)
  {
    const BigInteger complexity = Newick::CalcComplexity(n.Peek());
    if (complexity <= max_complexity) return n.ToStr();
    const std::vector<std::pair<std::vector<int>,int> > v
      = Newick::GetSimplerNewicksFrequencyPairs(n.Peek());
    if (v.empty()) return n.ToStr();
    const int sum = SumSecond(v);

    const int index_chosen = std::rand() % sum;
    //std::clog << "Index chosen: " << index_chosen << '\n';
    int current_sum = 0;
    for (int i=0; ;++i)
    {
      assert(i != boost::numeric_cast<int>(v.size()));
      current_sum+=v[i].second;
      //std::clog << "Index " << i << ", sum: " << current_sum << '\n';
      if (current_sum >= index_chosen)
      {
        //std::clog << "Index " << i << " chosen\n";
        n = v[i].first;
        break;
      }
    }

  }
}
//---------------------------------------------------------------------------
///SimplifyNewickFreqInd simplifies a Newick below a certain
///complexity, independent of the frequencies in the
///phylogeny.
///For example, for the phylogeny (100,2), SimplifyNewickFreqInd
///returns (99,2) as often as (100,1).
///From http://www.richelbilderbeek.nl/CppSimplifyNewickFreqInd.htm
/*
const std::string SimplifyNewickFreqInd(
  const std::string& s, const cln::cl_I& max_complexity)
{
  BinaryNewickVector n(s);
  while (1)
  {
    const cln::cl_I complexity = CalcComplexity(n.Get());
    if (complexity <= max_complexity) return n.ToStr();
    const std::vector<NewickVector> v = n.GetSimplerNewicks();
    if (v.empty()) return n.ToStr();
    const int i = std::rand() % boost::numeric_cast<int>(v.size());
    n = v[i];
  }
}
*/
//---------------------------------------------------------------------------
///From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------
///CliToStr converts a cln::cl_I to std::string.
///From http://www.richelbilderbeek.nl/CppCliToStr.htm
/*
const std::string CliToStr(const cln::cl_I& i)
{
  std::stringstream s;
  s << i;
  return s.str();
}
*/
//---------------------------------------------------------------------------

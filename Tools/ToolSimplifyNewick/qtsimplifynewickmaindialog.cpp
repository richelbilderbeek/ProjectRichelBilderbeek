//---------------------------------------------------------------------------
/*
SimplifyNewick, tool to randomly simplify Newick phylogenies
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
//From http://www.richelbilderbeek.nl/ToolSimplifyNewick.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>

#include "BigIntegerUtils.hh"

#include "newickvector.h"
#include "qtaboutdialog.h"
#include "simplifynewickmaindialog.h"
#include "qtsimplifynewickmaindialog.h"
#include "testtimer.h"
#include "newick.h"
#include "ui_qtsimplifynewickmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtToolSimplifyNewickMainDialog::QtToolSimplifyNewickMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolSimplifyNewickMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );

  #ifndef NDEBUG
  setWindowTitle(windowTitle()+" (debug)");
  #else
  setWindowTitle(windowTitle()+" (release)");
  #endif

  OnAnyEditChange();
}

ribi::QtToolSimplifyNewickMainDialog::~QtToolSimplifyNewickMainDialog() noexcept
{
  delete ui;
}

void ribi::QtToolSimplifyNewickMainDialog::OnAnyEditChange() noexcept
{
  ui->button_start->setEnabled(false);
  ui->text_output->clear();
  //Check newick
  try
  {
    const std::string s
      = ui->edit_newick->text().toStdString();
    Newick().CheckNewick(s);
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
      = ::bigIntegerToString(Newick().CalcComplexity(n.Peek()));
    ui->text_output->appendPlainText(
      QString("Current complexity: ")
      + QString(s.c_str()));
  }

  //Check complexity
  try
  {
    const std::string s
      = ui->edit_max_complexity->text().toStdString();

    const BigInteger i = stringToBigInteger(s);
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
    //Too bad: BigInteger throws ordinary char pointers :-(
    ui->text_output->appendPlainText(
      "Invalid input of maximum complexity: "
      "must be a number");
    return;
  }
  catch (...)
  {
    ui->text_output->appendPlainText(
      "Invalid input of maximum complexity: "
      "must be a number");
    return;
  }
  //Set current maximum complexity to Newick complexity minus one
  {
    const NewickVector n(
      ui->edit_newick->text().toStdString());

    const BigInteger newick_complexity
      = Newick().CalcComplexity(n.Peek());
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

void ribi::QtToolSimplifyNewickMainDialog::on_button_start_clicked() noexcept
{
  ui->text_output->clear();
  //Obtain the onEditChange output
  OnAnyEditChange();

  #ifdef NDEBUG
  std::srand(std::time(0)); //RandomizeTimer();
  #endif

  const std::string s_in = ui->edit_newick->text().toStdString();
  const BigInteger max_complexity = ::stringToBigInteger(
    ui->edit_max_complexity->text().toStdString());

  const std::string s_out = ToolSimplifyNewickMainDialog::SimplifyNewick(s_in,max_complexity);
  NewickVector n(s_out);

  const std::string complexity
    = ::bigIntegerToString(Newick().CalcComplexity(n.Peek()));
  ui->text_output->appendHtml("Newick found:");
  ui->text_output->appendHtml(n.ToStr().c_str());
  ui->text_output->appendHtml("Newick complexity:");
  ui->text_output->appendHtml(boost::lexical_cast<std::string>(complexity).c_str());
}

void ribi::QtToolSimplifyNewickMainDialog::on_edit_newick_textChanged(const QString &) noexcept
{
  OnAnyEditChange();
}

void ribi::QtToolSimplifyNewickMainDialog::on_edit_max_complexity_textChanged(const QString &) noexcept
{
  OnAnyEditChange();
}

#ifndef NDEBUG
void ribi::QtToolSimplifyNewickMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

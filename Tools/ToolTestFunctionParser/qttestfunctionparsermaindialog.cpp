//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestFunctionParser.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestfunctionparsermaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/locale.hpp>
#include <boost/math/constants/constants.hpp>

#include "fparser.hh"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestfunctionparsermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestFunctionParserMainDialog::QtTestFunctionParserMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestFunctionParserMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  const double pi = boost::math::constants::pi<double>();
  ui->edit_value->setText(boost::lexical_cast<std::string>(pi).c_str());
  Parse();
}

ribi::QtTestFunctionParserMainDialog::~QtTestFunctionParserMainDialog() noexcept
{
  delete ui;
}

void ribi::QtTestFunctionParserMainDialog::on_edit_value_textChanged(QString ) noexcept
{
  Parse();
}

void ribi::QtTestFunctionParserMainDialog::on_edit_function_textChanged(QString ) noexcept
{
  Parse();
}

void ribi::QtTestFunctionParserMainDialog::Parse() noexcept
{
  FunctionParser f;

  //Parse the formula
  f.Parse(ui->edit_function->text().toStdString().c_str(),"x");
  if (f.GetParseErrorType() != FunctionParser::FP_NO_ERROR)
  {
    ui->label_result->setText("Function could not be parsed");
    return;
  }

  //Check if x can be converted to double
  try
  {
    boost::lexical_cast<double>(ui->edit_value->text().toStdString());
  }
  catch (boost::bad_lexical_cast&)
  {
    ui->label_result->setText("Value of x is not a valid double");
    return;
  }

  //Evaluate the parsed formula
  const double x = boost::lexical_cast<double>(ui->edit_value->text().toStdString());
  const double xs[1] = { x };
  const double y = f.Eval(xs);

  if (f.EvalError()!=0)
  {
    ui->label_result->setText("Function could not be evaluated");
    return;
  }

  //Write down the solution
  ui->label_result->setText(boost::lexical_cast<std::string>(y).c_str());
}

#ifndef NDEBUG
void ribi::QtTestFunctionParserMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  const double pi = boost::math::constants::pi<double>();

  TRACE(std::locale().name());
  //TRACE(boost::lexical_cast<std::string>(pi)[1]);
  //assert(boost::lexical_cast<std::string>(pi)[1] == ',' && "Dutch please?");

  boost::locale::generator gen;
  std::locale::global(gen("")); //Or explicitly: "en_US.UTF-8"
  std::locale::global(gen("en_US.UTF-8")); //Or explicitly: "en_US.UTF-8"

  TRACE(std::locale().name());
  //TRACE(boost::lexical_cast<std::string>(pi)[1]);
  assert(boost::lexical_cast<std::string>(pi)[1] == '.' && "No Dutch please");

  assert(!"Refactor");
}
#endif

//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2013 Richel Bilderbeek

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


#include "qttestfunctionparsermaindialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#pragma GCC diagnostic pop

#include "fparser.hh"
#include "ui_qttestfunctionparsermaindialog.h"

ribi::QtTestFunctionParserMainDialog::QtTestFunctionParserMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestFunctionParserMainDialog)
{
  ui->setupUi(this);

  const double pi = boost::math::constants::pi<double>();
  ui->edit_value->setText(boost::lexical_cast<std::string>(pi).c_str());
  Parse();
}

ribi::QtTestFunctionParserMainDialog::~QtTestFunctionParserMainDialog()
{
  delete ui;
}

void ribi::QtTestFunctionParserMainDialog::on_edit_value_textChanged(QString )
{
  Parse();
}

void ribi::QtTestFunctionParserMainDialog::on_edit_function_textChanged(QString )
{
  Parse();
}

void ribi::QtTestFunctionParserMainDialog::Parse()
{
 FunctionParser f;

  //Parse the formula
  f.Parse(ui->edit_function->text().toStdString().c_str(),"x");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
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


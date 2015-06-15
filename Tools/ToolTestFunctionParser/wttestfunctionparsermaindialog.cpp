//---------------------------------------------------------------------------
/*
TestFunctionParser, tool to demonstrate Warp's FunctionParser class
Copyright (C) 2010-2015 Richel Bilderbeek

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
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WString>

#include "about.h"
#include "wtaboutdialog.h"
#include "fparser.hh"
#include "wttestfunctionparsermaindialog.h"
#pragma GCC diagnostic pop

WtTestFunctionParserMainDialog::WtTestFunctionParserMainDialog()
  : m_edit_function(0),
    m_edit_value(0),
    m_label_result(0)
{
  Show();
}

void WtTestFunctionParserMainDialog::Show()
{
  m_edit_function = new Wt::WLineEdit("sin(x)*sqrt(x)");
  m_edit_value = new Wt::WLineEdit(
    boost::lexical_cast<std::string>(
      boost::math::constants::pi<double>()
    )
  );
  m_label_result = new Wt::WLabel("...");

  this->clear();
  this->setContentAlignment(Wt::AlignCenter);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WLabel("y(x)="));
  this->addWidget(m_edit_function);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WLabel("  x="));
  this->addWidget(m_edit_value);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(m_label_result);

  m_edit_function->setMinimumSize(400,Wt::WLength::Auto);
  m_edit_value->setMinimumSize(400,Wt::WLength::Auto);
  m_label_result->setMinimumSize(400,Wt::WLength::Auto);
  m_edit_function->changed().connect(
    this,&WtTestFunctionParserMainDialog::Parse);
  m_edit_value->changed().connect(
    this,&WtTestFunctionParserMainDialog::Parse);
  Parse();
}

void WtTestFunctionParserMainDialog::Parse()
{
 FunctionParser f;

  //Parse the formula
  f.Parse(m_edit_function->text().toUTF8(),"x");
  if (f.GetParseErrorType()!= FunctionParser::FP_NO_ERROR)
  {
    m_label_result->setText("Function could not be parsed");
    return;
  }

  //Check if x can be converted to double
  try
  {
    boost::lexical_cast<double>(m_edit_value->text().toUTF8());
  }
  catch (boost::bad_lexical_cast&)
  {
    m_label_result->setText("Value of x is not a valid double");
    return;
  }

  //Evaluate the parsed formula
  const double x = boost::lexical_cast<double>(m_edit_value->text().toUTF8());
  const double xs[1] = { x };
  const double y = f.Eval(xs);

  if (f.EvalError()!=0)
  {
    m_label_result->setText("Function could not be evaluated");
    return;
  }

  //Write down the solution
  m_label_result->setText(boost::lexical_cast<std::string>(y).c_str());
}


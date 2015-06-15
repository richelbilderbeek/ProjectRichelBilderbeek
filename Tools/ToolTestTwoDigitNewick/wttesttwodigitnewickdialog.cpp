//---------------------------------------------------------------------------
/*
WtTestTwoDigitNewickDialog, Wt dialog to test the TwoDigitNewick class
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
//From http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTextArea>

#include "binarynewickvector.h"
#include "encranger.h"
#include "newick.h"
//#include "sortedbinarynewick.h"
#include "twodigitnewick.h"
#include "wttesttwodigitnewickdialog.h"
#pragma GCC diagnostic pop

ribi::WtTestTwoDigitNewickDialog::WtTestTwoDigitNewickDialog()
  : m_signal_about{},
    m_signal_any_change{},
    m_edit_newick(new Wt::WLineEdit("((2,2),2)")),
    m_edit_password(new Wt::WLineEdit),
    m_edit_theta(new Wt::WLineEdit("10")),
    m_text(new Wt::WTextArea)

{
  {
    Wt::WText * const title = new Wt::WText("TestTwoDigitNewick");
    title->setStyleClass("title");
    this->addWidget(title);
    this->addWidget(new Wt::WBreak);
  }

  new Wt::WLabel("Password ",this);
  m_edit_password->setEchoMode(Wt::WLineEdit::Password);
  this->addWidget(m_edit_password);
  this->addWidget(new Wt::WBreak);

  new Wt::WLabel("Newick   ",this);
  this->addWidget(m_edit_newick);
  this->addWidget(new Wt::WBreak);

  new Wt::WLabel("Theta    ",this);
  this->addWidget(m_edit_theta);
  this->addWidget(new Wt::WBreak);

  this->addWidget(m_text);
  m_text->setMinimumSize(600,Wt::WLength::Auto);
  m_text->setReadOnly(true);
  this->addWidget(new Wt::WBreak);

  Wt::WPushButton * const button_calculate = new Wt::WPushButton("Calculate",this);
  //Wt::WPushButton * const button_about = new Wt::WPushButton("About",this);

  button_calculate->clicked().connect(
    this,&ribi::WtTestTwoDigitNewickDialog::OnCalculate);
  //button_about->clicked().connect(
  //  this,&ribi::WtTestTwoDigitNewickDialog::OnAbout);

}

const ribi::About ribi::WtTestTwoDigitNewickDialog::GetAbout()
{
  About about(
    "Richel Bilderbeek",
    "WtTestTwoDigitNewickDialog",
    "Wt dialog to test the TwoDigitNewick class",
    "the 8th of March 2011",
    "2010-2011",
    "http://www.richelbilderbeek.nl/ToolTestTwoDigitNewick.htm",
    GetVersion(),
    GetVersionHistory());
  about.AddLibrary("BigInt: version 2010.04.30");
  about.AddLibrary("BinaryNewickVector: version " + BinaryNewickVector::GetVersion());
  about.AddLibrary("Encranger: version " + Encranger::GetVersion());
  about.AddLibrary("TwoDigitNewick: version " + TwoDigitNewick::GetVersion());
  return about;


}

const std::string ribi::WtTestTwoDigitNewickDialog::GetVersion()
{
  return "2.2";
}

const std::vector<std::string> ribi::WtTestTwoDigitNewickDialog::GetVersionHistory()
{
  return {
    "2011-03-06: version 2.1: initial version, same versioning as QtTestTwoDigitNewickDialog",
    "2011-03-08: version 2.2: minor changes in Newick namespace, added About screen"
  };
}

void ribi::WtTestTwoDigitNewickDialog::OnAbout()
{
  //Emit that about is clicked
  m_signal_about();
}

void ribi::WtTestTwoDigitNewickDialog::OnCalculate()
{
  {
    const std::string s = m_edit_password->text().toUTF8();
    Encranger e(2);
    const std::string t = e.Encrypt(s);
    if (t != "3BImP[7K(L32fjzko)p|X8#+Dy1q=[pWAP")
    {
      m_text->setText("Invalid password");
      return;
    }
  }

  const std::string s = m_edit_newick->text().toUTF8();
  if (!Newick().IsNewick(s))
  {
    m_text->setText("Invalid Newick");
    return;
  }
  const std::string theta_str
    = m_edit_theta->text().toUTF8();
  try
  {
    boost::lexical_cast<double>(theta_str);
  }
  catch (boost::bad_lexical_cast&)
  {
    m_text->setText("Invalid theta");
    return;
  }
  const double theta = boost::lexical_cast<double>(theta_str);
  if (Newick().IsBinaryNewick(Newick().StringToNewick(s)))
  {
    if (Newick().CalcComplexity(Newick().StringToNewick(s))
      > 10000)
    {
      m_text->setText("Can only calculate Newicks with complexities lower than 10000");
      return;
    }
    m_text->setText("Probability: "
      + boost::lexical_cast<std::string>(
        TwoDigitNewick::CalculateProbability(s,theta)));
  }
  else
  {
    m_text->setText("Can only calculate unary and binary Newicks");
    return;
  }
}


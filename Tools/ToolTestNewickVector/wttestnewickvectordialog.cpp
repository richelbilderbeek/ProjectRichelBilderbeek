#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wttestnewickvectordialog.h"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/tuple/tuple.hpp>

#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTextArea>

#include "encranger.h"
#include "newick.h"
#include "newickvector.h"
#include "trace.h"
#include "twodigitnewick.h"

#pragma GCC diagnostic pop

ribi::WtTestNewickVectorDialog::WtTestNewickVectorDialog()
  : m_signal_about{},
    m_signal_any_change{},
    m_dialog{},
    m_box_show_calculation(new Wt::WCheckBox),
    m_box_compare(new Wt::WCheckBox),
    m_edit_newick(new Wt::WLineEdit("((2,2),2)")),
    m_edit_password(new Wt::WLineEdit),
    m_edit_theta(new Wt::WLineEdit("10")),
    m_text(new Wt::WTextArea)
{
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WText * const title = new Wt::WText("TestNewickVector");
    title->setStyleClass("title");
    this->addWidget(title);
    this->addWidget(new Wt::WBreak);
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
  this->addWidget(new Wt::WBreak);

  m_box_show_calculation->setText("Show calculation");
  this->addWidget(m_box_show_calculation);
  this->addWidget(new Wt::WBreak);

  m_box_compare->setText("Compare to TwoDigitNewick");
  this->addWidget(m_box_compare);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);

  Wt::WPushButton * const button_calculate = new Wt::WPushButton("Calculate",this);
  //Wt::WPushButton * const button_about = new Wt::WPushButton("About",this);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);

  this->addWidget(m_text);
  m_text->setMinimumSize(800,600);
  m_text->setReadOnly(true);
  this->addWidget(new Wt::WBreak);

  button_calculate->clicked().connect(
    this,&ribi::WtTestNewickVectorDialog::OnCalculate);
  //button_about->clicked().connect(
  //  this,&ribi::WtTestNewickVectorDialog::OnAbout);
}

void ribi::WtTestNewickVectorDialog::Display()
{
  {
    const std::vector<std::string> v = m_dialog.GetText();
    Wt::WString ws;
    BOOST_FOREACH(const std::string& s,v)
    {
      ws+=s;
      ws+=boost::lexical_cast<std::string>('\n');
    }
    m_text->setText(ws);
  }
}

void ribi::WtTestNewickVectorDialog::OnAbout()
{
  //Emit that about is clicked
  m_signal_about();
}

void ribi::WtTestNewickVectorDialog::OnCalculate()
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
  m_dialog.SetAnalyseCalculation(m_box_show_calculation->isChecked());
  m_dialog.SetCompareToTwoDigitNewick(m_box_compare->isChecked());
  m_dialog.SetNewick(m_edit_newick->text().toUTF8());
  m_dialog.SetTheta(m_edit_theta->text().toUTF8());
  m_dialog.Calculate();

  Display();


}


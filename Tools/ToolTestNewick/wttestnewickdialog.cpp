//---------------------------------------------------------------------------
#include <cstdlib>
#include <ctime>
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/tuple/tuple.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTextArea>
//---------------------------------------------------------------------------
#include "binarynewickvector.h"
#include "encranger.h"
#include "manydigitnewick.h"
#include "newick.h"
#include "newickravindran.h"
#include "newickvector.h"
#include "sortedbinarynewickvector.h"
#include "trace.h"
#include "testnewick.h"
#include "testnewickresult.h"
#include "twodigitnewick.h"
#include "wttestnewickdialog.h"
//---------------------------------------------------------------------------
WtTestNewickDialog::WtTestNewickDialog()
  : m_edit_newick(new Wt::WLineEdit("((2,2),2)")),
    m_edit_password(new Wt::WLineEdit),
    m_edit_theta(new Wt::WLineEdit("10")),
    m_table(new Wt::WTable),
    m_text(new Wt::WTextArea)
{
  this->setContentAlignment(Wt::AlignCenter);
  {
    Wt::WText * const title = new Wt::WText("TestNewick");
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
  this->addWidget(new Wt::WBreak);

  m_table->elementAt(0, 0)->addWidget(new Wt::WText("Newick"));
  m_table->elementAt(0, 1)->addWidget(new Wt::WText("Theta"));
  m_table->elementAt(0, 2)->addWidget(new Wt::WText("Test"));
  m_table->elementAt(0, 3)->addWidget(new Wt::WText("Probability"));
  m_table->elementAt(0, 4)->addWidget(new Wt::WText("Time (sec)"));
  m_table->elementAt(1, 0)->addWidget(new Wt::WText("..."));
  m_table->elementAt(1, 1)->addWidget(new Wt::WText("..."));
  m_table->elementAt(1, 2)->addWidget(new Wt::WText("..."));
  m_table->elementAt(1, 3)->addWidget(new Wt::WText("..."));
  m_table->elementAt(1, 4)->addWidget(new Wt::WText("..."));

  this->addWidget(m_table);
  this->addWidget(new Wt::WBreak);

  this->addWidget(m_text);
  m_text->setMinimumSize(600,Wt::WLength::Auto);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);

  Wt::WPushButton * const button_calculate = new Wt::WPushButton("Calculate",this);
  Wt::WPushButton * const button_about = new Wt::WPushButton("About",this);
  Wt::WPushButton * const button_close = new Wt::WPushButton("Close",this);

  button_calculate->clicked().connect(
    this,&WtTestNewickDialog::OnCalculate);
  button_about->clicked().connect(
    this,&WtTestNewickDialog::OnAbout);
  button_close->clicked().connect(
    this,&WtTestNewickDialog::OnClose);

}
//---------------------------------------------------------------------------
void WtTestNewickDialog::Display()
{
  m_text->setText(m_dialog.GetText().c_str());

  //Display table
  m_table->clear();
  m_table->setHeaderCount(1);
  m_table->elementAt(0, 0)->addWidget(new Wt::WText("Newick"));
  m_table->elementAt(0, 1)->addWidget(new Wt::WText("Theta"));
  m_table->elementAt(0, 2)->addWidget(new Wt::WText("Test"));
  m_table->elementAt(0, 3)->addWidget(new Wt::WText("Probability"));
  m_table->elementAt(0, 4)->addWidget(new Wt::WText("Time (sec)"));

  const std::vector<TestNewickResult>& table = m_dialog.GetTable();
  const int n_results = boost::numeric_cast<int>(table.size());

  for (int result = 0; result!=n_results; ++result)
  {
    const std::string newick = table[result].newick;
    const std::string theta = boost::lexical_cast<std::string>(table[result].theta);
    const std::string prob = boost::lexical_cast<std::string>(table[result].probability);
    const std::string name = table[result].test_name;
    const std::string time = boost::lexical_cast<std::string>(table[result].time);
    m_table->elementAt(result+1,0)->clear();
    m_table->elementAt(result+1,1)->clear();
    m_table->elementAt(result+1,2)->clear();
    m_table->elementAt(result+1,3)->clear();
    m_table->elementAt(result+1,4)->clear();
    m_table->elementAt(result+1,0)->addWidget(new Wt::WText(newick));
    m_table->elementAt(result+1,1)->addWidget(new Wt::WText(theta));
    m_table->elementAt(result+1,2)->addWidget(new Wt::WText(name));
    m_table->elementAt(result+1,3)->addWidget(new Wt::WText(prob));
    m_table->elementAt(result+1,4)->addWidget(new Wt::WText(time));
  }
}
//---------------------------------------------------------------------------
void WtTestNewickDialog::OnAbout()
{
  //Emit that about is clicked
  m_signal_about();
}
//---------------------------------------------------------------------------
void WtTestNewickDialog::OnCalculate()
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
  m_dialog.DoAutoCalculate(
    m_edit_newick->text().toUTF8(),
    m_edit_theta->text().toUTF8(),
    "10000");

  Display();


}
//---------------------------------------------------------------------------
void WtTestNewickDialog::OnClose()
{
  //emit that this dialog closes
  m_signal_close();
}
//---------------------------------------------------------------------------

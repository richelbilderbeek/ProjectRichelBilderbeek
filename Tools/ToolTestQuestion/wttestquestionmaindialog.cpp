//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQuestion.htm
//---------------------------------------------------------------------------
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "questiondialog.h"
#include "testquestionmaindialog.h"
#include "wtaboutdialog.h"
#include "wtopenquestiondialog.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wttestquestionmaindialog.h"

WtTestQuestionMainDialog::Ui::Ui()
  : m_box(new Wt::WGroupBox),
    m_edit(new Wt::WLineEdit("[Question here]")),
    m_label(new Wt::WLabel("Status: ?"))
{

}

WtTestQuestionMainDialog::WtTestQuestionMainDialog()
{
  this->addWidget(ui.m_box);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_edit);
  this->addWidget(new Wt::WBreak);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_label);

  ui.m_edit->setMinimumSize(600,Wt::WLength::Auto);
  ui.m_edit->enterPressed().connect(this,&WtTestQuestionMainDialog::OnEditChanged);
  ui.m_edit->keyWentUp().connect(this,&WtTestQuestionMainDialog::OnEditChanged);
  ui.m_edit->setText("-,Is this a multiple choice question?,yes,no,do not know");
  OnEditChanged();
}

void WtTestQuestionMainDialog::OnEditChanged()
{
  const std::string s = ui.m_edit->text().toUTF8();

  try
  {
    //Test
    boost::shared_ptr<WtQuestionDialog> tmp(new WtOpenQuestionDialog(s));
    //Add
    ui.m_box->clear();
    ui.m_box->setContentAlignment(Wt::AlignLeft);
    ui.m_box->addWidget(new Wt::WBreak);
    WtQuestionDialog * question = new WtOpenQuestionDialog(s);
    ui.m_box->addWidget(question);
    ui.m_box->addWidget(new Wt::WBreak);
    ui.m_box->addWidget(new Wt::WBreak);
    ui.m_label->setText("Successfully parsed an open question");
    return;
  }
  catch(std::exception&)
  {
    //No problem
  }
  try
  {
    //Test
    boost::shared_ptr<WtQuestionDialog> tmp(new WtMultipleChoiceQuestionDialog(s));
    ui.m_box->clear();
    ui.m_box->setContentAlignment(Wt::AlignLeft);
    ui.m_box->addWidget(new Wt::WBreak);
    WtQuestionDialog * question = new WtMultipleChoiceQuestionDialog(s);
    ui.m_box->addWidget(question);
    ui.m_box->addWidget(new Wt::WBreak);
    ui.m_label->setText("Successfully parsed a multiple choice question");
    return;
  }
  catch(std::exception&)
  {
    //No problem
  }
  ui.m_label->setText("Invalid input");
}

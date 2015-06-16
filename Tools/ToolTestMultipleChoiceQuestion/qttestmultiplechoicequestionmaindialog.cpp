//---------------------------------------------------------------------------
/*
TestMultipleChoiceQuestion, tests multiple choice question classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestMultipleChoiceQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestmultiplechoicequestionmaindialog.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QLabel>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "qtaboutdialog.h"
#include "qtmultiplechoicequestiondialog.h"
#include "questiondialog.h"
#include "testmultiplechoicequestionmaindialog.h"
#include "trace.h"
#include "ui_qttestmultiplechoicequestionmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestMultipleChoiceQuestionMainDialog::QtTestMultipleChoiceQuestionMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestMultipleChoiceQuestionMainDialog),
    m_dialog{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  this->SetQuestion("-,1+1=,2,1,3,4,5,6");
}

ribi::QtTestMultipleChoiceQuestionMainDialog::~QtTestMultipleChoiceQuestionMainDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::QtMultipleChoiceQuestionDialog> ribi::QtTestMultipleChoiceQuestionMainDialog::CreateQtMultipleChoiceQuestionDialog(const std::string& s)
{
  boost::shared_ptr<QtMultipleChoiceQuestionDialog> p;

  try
  {
    const boost::shared_ptr<MultipleChoiceQuestionDialog> d(new MultipleChoiceQuestionDialog(s));
    if (d) p.reset(new QtMultipleChoiceQuestionDialog(d));
    assert(p);
    return p;
  }
  catch(std::exception&)
  {
    //No problem
  }
  return p;
}


void ribi::QtTestMultipleChoiceQuestionMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestMultipleChoiceQuestionMainDialog::on_edit_question_textChanged(const QString &arg1)
{
  const std::string s = arg1.toStdString();
  m_dialog = CreateQtMultipleChoiceQuestionDialog(s);

  if (ui->contents_here->layout())
  {
    delete ui->contents_here->layout();
  }
  assert(!ui->contents_here->layout());

  if (m_dialog)
  {
    assert(m_dialog);
    assert(!ui->contents_here->layout());
    QLayout * const my_layout = new QVBoxLayout;
    ui->contents_here->setLayout(my_layout);
    assert(ui->contents_here->layout());
    my_layout->addWidget(m_dialog.get());
  }
}

void ribi::QtTestMultipleChoiceQuestionMainDialog::SetQuestion(const std::string& s)
{
  this->ui->edit_question->setText(s.c_str());
}

#ifndef NDEBUG
void ribi::QtTestMultipleChoiceQuestionMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestMultipleChoiceQuestionMainDialog::Test");
  QtTestMultipleChoiceQuestionMainDialog d;
  d.SetQuestion("-,1+1=,2,1,3"); //Valid: multiple choice question
  assert(d.GetDialog());
  d.SetQuestion("nonsense");
  assert(!d.GetDialog() && "A single word cannot be parsed as a multiple choice question");
  d.SetQuestion("-,1+1=,2");
  assert(!d.GetDialog() && "Open questions cannot be parsed as multiple choice question");
  d.SetQuestion("more nonsense");
  assert(!d.GetDialog());
  TRACE("Finished ribi::QtTestMultipleChoiceQuestionMainDialog::Test successfully");
}
#endif

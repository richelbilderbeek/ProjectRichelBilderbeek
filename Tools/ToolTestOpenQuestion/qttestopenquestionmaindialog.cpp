//---------------------------------------------------------------------------
/*
TestOpenQuestion, tool to test the OpenQuestion and OpenQuestionDialog classes
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
//From http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestopenquestionmaindialog.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>

#include "openquestion.h"
#include "openquestiondialog.h"
#include "openquestiondialogfactory.h"
#include "qtaboutdialog.h"
#include "qtopenquestiondialog.h"
#include "questiondialog.h"
#include "testopenquestionmaindialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestopenquestionmaindialog.h"
#pragma GCC diagnostic pop

ribi::QtTestOpenQuestionMainDialog::QtTestOpenQuestionMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestOpenQuestionMainDialog),
    m_dialog_1(new QtOpenQuestionDialog),
    m_dialog_2(new QtOpenQuestionDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  assert(layout());
  QGridLayout * const my_layout = dynamic_cast<QGridLayout*>(this->layout());
  assert(my_layout);
  {
    QLabel * const label = new QLabel("#1");
    my_layout->addWidget(label,1,0);
  }
  my_layout->addWidget(m_dialog_1.get(),2,0);
  {
    QLabel * const label = new QLabel("#2");
    my_layout->addWidget(label,1,1);
  }
  my_layout->addWidget(m_dialog_2.get(),2,1);

  this->SetQuestion("-,1+1=,2");
}

ribi::QtTestOpenQuestionMainDialog::~QtTestOpenQuestionMainDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::OpenQuestionDialog> ribi::QtTestOpenQuestionMainDialog::CreateOpenQuestionDialog(const std::string& s)
{

  try
  {
    const auto d = OpenQuestionDialogFactory().Create(s);
    return d;
  }
  catch(std::exception&)
  {
    //No problem
    boost::shared_ptr<OpenQuestionDialog> null;
    return null;
  }
}


void ribi::QtTestOpenQuestionMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestOpenQuestionMainDialog::on_edit_question_textChanged(const QString &arg1)
{
  const std::string s = arg1.toStdString();
  const auto openquestion_dialog = CreateOpenQuestionDialog(s);
  if (!openquestion_dialog) return;
  m_dialog_1->SetDialog(openquestion_dialog);
  m_dialog_2->SetDialog(openquestion_dialog);
 }

void ribi::QtTestOpenQuestionMainDialog::SetQuestion(const std::string& s)
{
  this->ui->edit_question->setText(s.c_str());
}

#ifndef NDEBUG
void ribi::QtTestOpenQuestionMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestOpenQuestionMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestOpenQuestionMainDialog d;
  d.SetQuestion("-,1+1=,2");
  assert(d.GetDialog());
  d.SetQuestion("nonsense");
  assert(d.GetDialog());
  d.SetQuestion("-,1+1=,2");
  assert(d.GetDialog());
  d.SetQuestion("more nonsense");
  assert(d.GetDialog());
}
#endif

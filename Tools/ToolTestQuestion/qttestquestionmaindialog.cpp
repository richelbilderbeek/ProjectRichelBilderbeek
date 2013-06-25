//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2012 Richel Bilderbeek

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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestquestionmaindialog.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>
#include <QLabel>

#include "qtaboutdialog.h"
#include "qtopenquestiondialog.h"
#include "qtmultiplechoicequestiondialog.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "questiondialog.h"
#include "testquestionmaindialog.h"
#include "ui_qttestquestionmaindialog.h"

QtTestQuestionMainDialog::QtTestQuestionMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQuestionMainDialog),
    m_dialog(CreateQtQuestionDialog("-,1+1=,2,1,3"))

{
  ui->setupUi(this);

  assert(ui->contents_here->layout());
  delete  ui->contents_here->layout();
  assert(!ui->contents_here->layout());
  QGridLayout * const my_layout = new QGridLayout;
  ui->contents_here->setLayout(my_layout);
  assert(ui->contents_here->layout());

  my_layout->addWidget(m_dialog.get());
}

QtTestQuestionMainDialog::~QtTestQuestionMainDialog()
{
  delete ui;
}

void QtTestQuestionMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

boost::shared_ptr<QtQuestionDialog> QtTestQuestionMainDialog::CreateQtQuestionDialog(const std::string& s)
{
  boost::shared_ptr<QtQuestionDialog> p;

  try
  {
    boost::shared_ptr<QuestionDialog> d(new OpenQuestionDialog(s));
    if (d) p.reset(new QtQuestionDialog(d));
    assert(p);
    return p;
  }
  catch(std::exception&)
  {
    //No problem
  }
  try
  {
    boost::shared_ptr<QuestionDialog> d(new MultipleChoiceQuestionDialog(s));
    if (d) p.reset(new QtQuestionDialog(d));
    assert(p);
    return p;
  }
  catch(std::exception&)
  {
    //No problem
  }
  return p;
}


void QtTestQuestionMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtTestQuestionMainDialog::on_edit_question_textChanged(const QString &arg1)
{
  const std::string s = arg1.toStdString();

  if (ui->contents_here->layout())
  {
    delete ui->contents_here->layout();
  }
  assert(!ui->contents_here->layout());

  m_dialog = CreateQtQuestionDialog(s);
  if (m_dialog)
  {
    assert(m_dialog);
    assert(!ui->contents_here->layout());
    QGridLayout * const my_layout = new QGridLayout;
    ui->contents_here->setLayout(my_layout);
    assert(ui->contents_here->layout());
    my_layout->addWidget(m_dialog.get());
    QLabel * const label = new QLabel("Created dialog!");
    my_layout->addWidget(label);
  }
}

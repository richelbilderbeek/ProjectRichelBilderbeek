#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qthometrainermaindialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <QKeyEvent>
#include <QTimer>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "qtmultiplechoicequestiondialog.h"
#include "qtopenquestiondialog.h"
#include "questiondialog.h"
#include "trace.h"
#include "ui_qthometrainermaindialog.h"

#pragma GCC diagnostic pop

ribi::QtHometrainerMainDialog::QtHometrainerMainDialog(
  const std::vector<std::string>& questions,
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtHometrainerMainDialog),
    m_current_question_index{0},
    m_dialog{},
    m_n_correct{0},
    m_n_incorrect{0},
    m_questions{questions}
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  assert(!m_questions.empty());
  if (m_questions.empty())
  {
    throw std::logic_error("QtHometrainerMainDialog: must have questions");
  }
  SetQuestion(m_questions[m_current_question_index]);
  DisplayScore();
}

ribi::QtHometrainerMainDialog::~QtHometrainerMainDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<ribi::QtQuestionDialog> ribi::QtHometrainerMainDialog::CreateQtQuestionDialog(const std::string& s)
{
  boost::shared_ptr<QtQuestionDialog> p;

  try
  {
    boost::shared_ptr<QuestionDialog> d(new OpenQuestionDialog(s));
    if (d) p.reset(new QtOpenQuestionDialog(d));
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
    if (d) p.reset(new QtMultipleChoiceQuestionDialog(d));
    assert(p);
    return p;
  }
  catch(std::exception&)
  {
    //No problem
  }
  //Possible other question types

  //No question type could parse the question:
  //now there is a problem
  throw std::logic_error(
    "QtHometrainerMainDialog::CreateQtQuestionDialog: "
    "cannot create QtQuestionDialog");
}

void ribi::QtHometrainerMainDialog::DisplayScore()
{
  std::stringstream s;
  s << "Questions: "
    << (1 + m_current_question_index) //Human 1 based
    << " / "
    << m_questions.size()
    << ", correct: "
    << m_n_correct
    << ", incorrect: "
    << m_n_incorrect;
  ui->label_score->setText(s.str().c_str());
}


void ribi::QtHometrainerMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtHometrainerMainDialog::NewQuestion()
{
  ++m_current_question_index;
  if (m_current_question_index == m_questions.size())
  {
    std::random_shuffle(m_questions.begin(),m_questions.end());
    m_current_question_index = 0;
  }
  assert(m_current_question_index < m_questions.size());
  SetQuestion(m_questions[m_current_question_index]);
}

void ribi::QtHometrainerMainDialog::OnSubmitted(const bool is_correct)
{
  if (is_correct) ++m_n_correct; else ++m_n_incorrect;
  DisplayScore();

  QTimer::singleShot(
    is_correct ? 1000 : 5000,
    this,SLOT(NewQuestion()));

}

void ribi::QtHometrainerMainDialog::SetQuestion(const std::string& s)
{
  m_dialog = CreateQtQuestionDialog(s);
  assert(m_dialog);
  m_dialog->m_signal_submitted.connect(
    boost::bind(&ribi::QtHometrainerMainDialog::OnSubmitted,this,boost::lambda::_1)
  );

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

#ifndef NDEBUG
void ribi::QtHometrainerMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtHometrainerMainDialog::Test");
  const std::vector<std::string> v {
    "-,1+1=,2,1,3",
    "-,1+1=,2/Two/two"
  };
  QtHometrainerMainDialog d(v);
  TRACE("Finished ribi::QtHometrainerMainDialog::Test successfully");
}
#endif





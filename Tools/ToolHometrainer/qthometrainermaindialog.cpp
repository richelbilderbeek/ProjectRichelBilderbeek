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
#include "openquestionfactory.h"
#include "openquestiondialog.h"
#include "openquestiondialogfactory.h"
#include "qtmultiplechoicequestiondialog.h"
#include "hometrainermaindialog.h"
#include "qtopenquestiondialog.h"
#include "questiondialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qthometrainermaindialog.h"

#pragma GCC diagnostic pop

ribi::QtHometrainerMainDialog::QtHometrainerMainDialog(
  const boost::shared_ptr<const HometrainerMainDialog> dialog,
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtHometrainerMainDialog),
    m_dialog{dialog},
    m_qtdialog{}
    //m_questions{dialog->GetQuestions()}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  assert(m_dialog);
  SetQuestion(m_dialog->GetCurrentQuestion());
}

ribi::QtHometrainerMainDialog::~QtHometrainerMainDialog() noexcept
{
  delete ui;
}
/*
const boost::shared_ptr<ribi::HometrainerMainDialog> ribi::QtHometrainerMainDialog::CreateMainDialog()
{
  boost::shared_ptr<ribi::HometrainerMainDialog> d(new ribi::HometrainerMainDialog(
}
*/
boost::shared_ptr<ribi::QtQuestionDialog> ribi::QtHometrainerMainDialog::CreateQtQuestionDialog(
  const boost::shared_ptr<const Question> s)
{
  boost::shared_ptr<QtQuestionDialog> p;

  try
  {
    //const boost::shared_ptr<const OpenQuestion> q {
    //  boost::dynamic_pointer_cast<const OpenQuestion>(s)
    //};
    //if (!q) throw std::runtime_error("q cannot be converted to OpenQuestion");
    //assert(q);
    //const boost::shared_ptr<OpenQuestionDialog> d(new OpenQuestionDialog(q));
    const auto d = OpenQuestionDialogFactory().Create(s->ToStr());
    const auto qd = boost::make_shared<QtOpenQuestionDialog>();
    qd->SetDialog(d);
    assert(qd);
    if (qd) p = qd;
    //assert(d);
    //if (d) p.reset(new QtOpenQuestionDialog(d));
    assert(p);
    return p;
  }
  catch(std::exception&)
  {
    //No problem
  }
  try
  {
    const boost::shared_ptr<const MultipleChoiceQuestion> q {
      boost::dynamic_pointer_cast<const MultipleChoiceQuestion>(s)
    };
    assert(q);
    const boost::shared_ptr<MultipleChoiceQuestionDialog> d(new MultipleChoiceQuestionDialog(q));
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
  s << "Correct: "
    << m_dialog->GetNumberCorrect()
    << ", incorrect: "
    << m_dialog->GetNumberIncorrect();
  ui->label_score->setText(s.str().c_str());
}


void ribi::QtHometrainerMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtHometrainerMainDialog::NewQuestion()
{
  SetQuestion(m_dialog->GetCurrentQuestion());
}

void ribi::QtHometrainerMainDialog::OnSubmitted(const bool is_correct)
{
  DisplayScore();

  QTimer::singleShot(
    is_correct ? 1000 : 5000,
    this,SLOT(NewQuestion())
  );

}

void ribi::QtHometrainerMainDialog::SetQuestion(const boost::shared_ptr<const Question> s)
{
  assert(s);
  const auto new_qtdialog = CreateQtQuestionDialog(s);
  assert(new_qtdialog);
  new_qtdialog->GetDialog()->m_signal_submitted.connect(
    boost::bind(&ribi::QtHometrainerMainDialog::OnSubmitted,this,boost::lambda::_1)
  );  
  if (ui->contents_here->layout())
  {
    delete ui->contents_here->layout();
  }
  assert(!ui->contents_here->layout());

  if (m_qtdialog)
  {
    new_qtdialog->GetDialog()->m_signal_submitted.disconnect(
      boost::bind(&ribi::QtHometrainerMainDialog::OnSubmitted,this,boost::lambda::_1)
    );
  }
  m_qtdialog = new_qtdialog;
  if (m_qtdialog)
  {
    assert(!ui->contents_here->layout());
    QLayout * const my_layout = new QVBoxLayout;
    ui->contents_here->setLayout(my_layout);
    assert(ui->contents_here->layout());
    my_layout->addWidget(m_qtdialog.get());
  }
  DisplayScore();
}

#ifndef NDEBUG
void ribi::QtHometrainerMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  std::vector<boost::shared_ptr<const Question> > v;
  {
    const boost::shared_ptr<const Question> q {
      new MultipleChoiceQuestion("-,1+1=,2,1,3")
    };
    v.push_back(q);
  }
  {
    const auto q = OpenQuestionFactory().Create("-,1+1=,2/Two/two");
    //const boost::shared_ptr<const Question> q {
    //  new OpenQuestion("-,1+1=,2/Two/two")
    //};
    v.push_back(q);
  }
  const boost::shared_ptr<const HometrainerMainDialog> dialog {
    new HometrainerMainDialog(v)
  };

  QtHometrainerMainDialog d(dialog);
}
#endif

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtmultiplechoicequestiondialog.h"

//---------------------------------------------------------------------------
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "qtquestiondialog.h"
#include "questiondialog.h"
#include "ui_qtmultiplechoicequestiondialog.h"
//---------------------------------------------------------------------------
#include <QFile>
//---------------------------------------------------------------------------
QtMultipleChoiceQuestionDialog::QtMultipleChoiceQuestionDialog(
  QWidget *parent) :
  QtQuestionDialog(
    boost::shared_ptr<QuestionDialog>(
      new MultipleChoiceQuestionDialog(
        boost::shared_ptr<MultipleChoiceQuestion>(
          new MultipleChoiceQuestion(
            "*","1+1=","2",{"1","3","4"})))),
    parent),
  ui(new Ui::QtMultipleChoiceQuestionDialog)
{
  ui->setupUi(this);
}
//---------------------------------------------------------------------------
QtMultipleChoiceQuestionDialog::QtMultipleChoiceQuestionDialog(
  const boost::shared_ptr<QuestionDialog>& dialog,
  QWidget *parent) :
  QtQuestionDialog(dialog,parent),
  ui(new Ui::QtMultipleChoiceQuestionDialog)
{
  ui->setupUi(this);
  this->SetQuestion(dialog->GetQuestion());
}
//---------------------------------------------------------------------------
QtMultipleChoiceQuestionDialog::~QtMultipleChoiceQuestionDialog()
{
  delete ui;
}
//---------------------------------------------------------------------------
const std::string QtMultipleChoiceQuestionDialog::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> QtMultipleChoiceQuestionDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-28: version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
///Set the Question
void QtMultipleChoiceQuestionDialog::SetQuestion(
  const boost::shared_ptr<Question>& question)
{
  m_dialog->SetQuestion(question);

  if (QFile::exists(question->GetFilename().c_str()))
  {
    ui->image->setPixmap(QPixmap(question->GetFilename().c_str()));
  }

  const MultipleChoiceQuestion * const q
    = dynamic_cast<const MultipleChoiceQuestion *>(question.get());
  assert(q);

  ui->stackedWidget->setCurrentWidget(ui->page_question);
  ui->label_question->setText(question->GetQuestion().c_str());
  ui->label_question_again->setText(q->GetQuestion().c_str());
  ui->label_answer->setText(q->GetAnswer().c_str());


  const std::vector<QRadioButton* > buttons
    = { ui->radio_1, ui->radio_2, ui->radio_3, ui->radio_4, ui->radio_5, ui->radio_6 };
  const std::vector<std::string> options = q->GetOptions();
  const int sz = 6;
  assert(sz == boost::numeric_cast<int>(buttons.size()));
  assert(sz >= boost::numeric_cast<int>(options.size()));
  for (int i = 0; i!=sz; ++i)
  {
    if (i < boost::numeric_cast<int>(options.size()))
    {
      buttons[i]->setText(options[i].c_str());
    }
    else
    {
      buttons[i]->setVisible(false);
    }
  }


}
//---------------------------------------------------------------------------
void QtMultipleChoiceQuestionDialog::on_button_submit_clicked()
{
  assert(m_dialog->CanSubmit());
  const std::vector<const QRadioButton* > buttons
    = { ui->radio_1, ui->radio_2, ui->radio_3, ui->radio_4, ui->radio_5, ui->radio_6 };

  if (std::find_if(
    buttons.begin(), buttons.end(),
    boost::bind(&QRadioButton::isChecked,boost::lambda::_1)
      == true) == buttons.end()) return;

  const std::string s =
    (*std::find_if(
      buttons.begin(), buttons.end(),
      boost::bind(&QRadioButton::isChecked,boost::lambda::_1)
        == true))->text().toStdString();

  this->m_dialog->Submit(s);

  const bool is_correct = m_dialog->IsAnswerCorrect();

  this->ui->stackedWidget->setCurrentWidget(is_correct
    ? ui->page_correct
    : ui->page_incorrect);


  m_signal_submitted(is_correct);
}
//---------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthometrainermenudialog.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include "hometrainermenudialog.h"
#include "hometrainermaindialog.h"
#include "multiplechoicequestion.h"
#include "openquestion.h"
#include "openquestionfactory.h"
#include "qtaboutdialog.h"
#include "qthometrainermaindialog.h"
#include "trace.h"
#include "ui_qthometrainermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtHometrainerMenuDialog::QtHometrainerMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtHometrainerMenuDialog),
    m_main_dialog{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->button_start_exercise->setEnabled( m_main_dialog.get() );
}

ribi::QtHometrainerMenuDialog::~QtHometrainerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtHometrainerMenuDialog::on_button_about_clicked() noexcept
{
  About a = HometrainerMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtHometrainerMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtHometrainerMenuDialog::on_button_start_exercise_clicked() noexcept
{
  QtHometrainerMainDialog d(m_main_dialog);
  ShowChild(&d);
}

void ribi::QtHometrainerMenuDialog::on_button_load_exercise_clicked() noexcept
{
  try
  {
    const std::string filename
      = QFileDialog::getOpenFileName(0,"Please select a Hometrainer file").toStdString();
    const boost::shared_ptr<const HometrainerMainDialog> dialog {
      new HometrainerMainDialog(filename)
    };
    m_main_dialog = dialog;
  }
  catch (std::exception&)
  {
    //No problem
  }
  ui->button_start_exercise->setEnabled( m_main_dialog.get() );
  this->show();
}

void ribi::QtHometrainerMenuDialog::on_button_create_examples_clicked()
{
  HometrainerMenuDialog::CreateExamples();
  ui->button_create_examples->setVisible(false);
}

#ifndef NDEBUG
void ribi::QtHometrainerMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtHometrainerMenuDialog::Test");
  std::vector<boost::shared_ptr<const Question> > v;
  {
    const boost::shared_ptr<const MultipleChoiceQuestion> q {
      new MultipleChoiceQuestion("-,1+1=,2,1,3")
    };
    v.push_back(q);
  }
  {
    const auto openquestion = OpenQuestionFactory().Create("-,1+1=,2/Two/two");
    assert(openquestion);
    v.push_back(openquestion);
  }
  const boost::shared_ptr<const HometrainerMainDialog> dialog {
    new HometrainerMainDialog(v)
  };

  QtHometrainerMainDialog d(dialog);
  TRACE("Finished ribi::QtHometrainerMenuDialog::Test successfully");
}
#endif

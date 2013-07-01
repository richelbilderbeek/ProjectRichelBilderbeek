#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtkalmanfilterexamplesdialog.h"

#include <cassert>
#include <cstdlib>
#include <memory>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QKeyEvent>
#include <QPushButton>
#include <QVBoxLayout>

#include "kalmanfilterexample.h"
#include "matrix.h"
#include "qtkalmanfilterermaindialog.h"
#include "standardkalmanfilterparameters.h"
#include "qtmatrix.h"
#include "trace.h"
#include "ui_qtkalmanfilterexamplesdialog.h"

QtKalmanFilterExamplesDialog::QtKalmanFilterExamplesDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtKalmanFilterExamplesDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  {
    assert(this->layout());
    this->layout()->setSpacing(1);
    const std::size_t sz = KalmanFilterExample::CreateExamples().size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(KalmanFilterExample::CreateExamples()[i]);
      const std::string title = KalmanFilterExample::CreateExamples()[i]->GetTitle();
      const std::string text = boost::lexical_cast<std::string>(i) + ". " + title;
      QPushButton * const button = new QPushButton(text.c_str());
      button->setFlat(true);
      this->layout()->addWidget(button);
      QObject::connect(button,SIGNAL(clicked()),this,SLOT(OnButtonClicked()));
    }
  }
}

QtKalmanFilterExamplesDialog::~QtKalmanFilterExamplesDialog()
{
  delete ui;
}

void QtKalmanFilterExamplesDialog::EmitExample(const int index)
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(index);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::OnButtonClicked()
{
  const QPushButton * const button = dynamic_cast<QPushButton*>(this->focusWidget());
  if (!button) return;
  assert(button);
  const std::string text = button->text().toStdString();
  assert(text.size() > 0);
  const int index = boost::lexical_cast<int,char>(text[0]);
  EmitExample(index);
}


void QtKalmanFilterExamplesDialog::ClickButton(const int button_index)
{
  EmitExample(button_index);
}

void QtKalmanFilterExamplesDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;
  if (event->modifiers() == Qt::AltModifier)
  {
    const int index = event->key() - '0';
    const int max_index = boost::numeric_cast<int>(KalmanFilterExample::CreateExamples().size());
    TRACE(index);
    if (index >= 0 && index < max_index) { EmitExample(index); return; }
  }
  QDialog::keyPressEvent(event);
}

#ifndef NDEBUG
void QtKalmanFilterExamplesDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtKalmanFilterExamplesDialog d;
    const int max_index = boost::numeric_cast<int>(KalmanFilterExample::CreateExamples().size());
    for (int i=0; i!=max_index; ++i) { d.ClickButton(i); }
  }
}
#endif

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
    const std::size_t sz = KalmanFilterExample::CreateExamples().size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      assert(KalmanFilterExample::CreateExamples()[i]);
      const std::string title = KalmanFilterExample::CreateExamples()[i]->GetTitle();
      const std::string text = boost::lexical_cast<std::string>(i) + ". " + title;
      ui->box->addItem(QString(text.c_str()));
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

void QtKalmanFilterExamplesDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;
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
    for (int i=0; i!=max_index; ++i) { d.EmitExample(i); }
  }
}
#endif

void QtKalmanFilterExamplesDialog::on_button_clicked()
{
  const int index = ui->box->currentIndex();
  EmitExample(index);
}

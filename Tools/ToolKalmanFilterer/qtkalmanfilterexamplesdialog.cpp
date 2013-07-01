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
}

QtKalmanFilterExamplesDialog::~QtKalmanFilterExamplesDialog()
{
  delete ui;
}

void QtKalmanFilterExamplesDialog::ClickButton(const int i)
{
  
  std::vector<QPushButton * > v;
  v.push_back(ui->button_1);
  v.push_back(ui->button_2);
  v.push_back(ui->button_3);
  v.push_back(ui->button_4);
  v.push_back(ui->button_5);
  v.push_back(ui->button_6);
  assert(i >= 0);
  assert(i < boost::numeric_cast<int>(v.size()));
  assert(v[i]);
  v[i]->click();
}

void QtKalmanFilterExamplesDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;
  QDialog::keyPressEvent(event);
}

void QtKalmanFilterExamplesDialog::on_button_1_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(1);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_2_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(2);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_3_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(3);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_4_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(4);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_5_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(5);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_6_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(6);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

#ifndef NDEBUG
void QtKalmanFilterExamplesDialog::Test()
{

}
#endif

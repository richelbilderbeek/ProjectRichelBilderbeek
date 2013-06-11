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
  v.push_back(ui->button_7);
  v.push_back(ui->button_8);
  v.push_back(ui->button_9);
  v.push_back(ui->button_10);
  assert(i >= 0);
  assert(i < boost::numeric_cast<int>(v.size()));
  assert(v[i]);
  TRACE(i);
  TRACE(v[i]->text().toStdString());
  v[i]->click();
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

void QtKalmanFilterExamplesDialog::on_button_7_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(7);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_8_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(8);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_9_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(9);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  emit signal_example(p);
}

void QtKalmanFilterExamplesDialog::on_button_10_clicked()
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(10);
  assert(example);
  assert(example->GetKalmanFilterParameters());
  assert(example->GetKalmanFilterParameters()->GetObservation().size1() == 8);
  assert(example->GetKalmanFilterParameters()->GetObservation().size2() == 8);
  assert(example->GetKalmanFilterParameters()->GetObservation()(5,5) == 1.0);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  assert(p->GetKalmanFilterParameters());
  assert(p->GetKalmanFilterParameters()->GetObservation().size1() == 8);
  assert(p->GetKalmanFilterParameters()->GetObservation().size2() == 8);
  assert(p->GetKalmanFilterParameters()->GetObservation()(5,5) == 1.0);
  emit signal_example(p);
}

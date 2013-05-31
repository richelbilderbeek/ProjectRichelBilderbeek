#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtkalmanfilterexamplesdialog.h"

#include <cassert>
#include <cstdlib>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include <QVBoxLayout>

#include "kalmanfilterexample.h"
#include "matrix.h"
#include "qtkalmanfilterermaindialog.h"
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
  v[i]->click();
}

void QtKalmanFilterExamplesDialog::on_button_1_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(1);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_2_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(2);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_3_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(3);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_4_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(4);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_5_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(5);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_6_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(6);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_7_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(7);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_8_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(8);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_9_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(9);
  emit signal_example(example);
}

void QtKalmanFilterExamplesDialog::on_button_10_clicked()
{
  const boost::shared_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(10);
  emit signal_example(example);
}

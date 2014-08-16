#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
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

#pragma GCC diagnostic pop

ribi::kalman::QtKalmanFilterExamplesDialog::QtKalmanFilterExamplesDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    m_signal_example{},
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

ribi::kalman::QtKalmanFilterExamplesDialog::~QtKalmanFilterExamplesDialog() noexcept
{
  delete ui;
}

void ribi::kalman::QtKalmanFilterExamplesDialog::EmitExample(const int index) const
{
  std::unique_ptr<KalmanFilterExample> example = KalmanFilterExample::CreateExample(index);
  assert(example);
  const KalmanFilterExample * const p = example.release();
  assert(p);
  m_signal_example(p);
}

void ribi::kalman::QtKalmanFilterExamplesDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) return;
  QDialog::keyPressEvent(event);
}

#ifndef NDEBUG
void ribi::kalman::QtKalmanFilterExamplesDialog::Test() noexcept
{
  {
    static bool is_tested{false};
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

void ribi::kalman::QtKalmanFilterExamplesDialog::on_button_clicked()
{
  assert(ui->box->currentIndex() != -1);
  const int index = ui->box->currentIndex();
  EmitExample(index);
}

void ribi::kalman::QtKalmanFilterExamplesDialog::on_box_currentIndexChanged(int index)
{
  ui->button->setEnabled(index != -1);
}

void ribi::kalman::QtKalmanFilterExamplesDialog::SetShowNoExample()
{
  ui->box->setCurrentIndex(-1);
}

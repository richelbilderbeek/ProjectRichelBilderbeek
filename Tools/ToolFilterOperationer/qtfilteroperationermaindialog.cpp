#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtfilteroperationermaindialog.h"

#include <cassert>

#include <QFileDialog>
#include <QLabel>

#include "filteroperationermaindialog.h"
#include "matrix.h"
#include "qtublasmatrixdoublemodel.h"
#include "testtimer.h"
#include "ui_qtfilteroperationermaindialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtFilterOperationerMainDialog::QtFilterOperationerMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtFilterOperationerMainDialog),
    m_model{new QtUblasMatrixDoubleModel},
    m_result{nullptr},
    m_source{nullptr}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->filter->setModel(m_model);
  {
    const boost::numeric::ublas::matrix<double> m {
      Matrix::CreateMatrix(3,3,
        {
          -1.0, -1.0, -1.0,
           0.0,  0.0,  0.0,
           1.0,  1.0,  1.0
        }
      )
    };
    m_model->SetRawData(m);
  }

  QPixmap p(":/filteroperationer/images/ToolFilterOperationerTest.png");
  assert(!p.isNull());
  ShowLoadedPixmap(p);
}

ribi::QtFilterOperationerMainDialog::~QtFilterOperationerMainDialog() noexcept
{
  delete ui;
}

void ribi::QtFilterOperationerMainDialog::on_button_load_clicked()
{
  const std::string filename {
    QFileDialog::getOpenFileName(0,"Please select a file").toStdString()
  };
  if (filename.empty()) return;

  //Check if the pixmap is valid
  {
    const QPixmap pixmap(filename.c_str());
    if (pixmap.isNull()) return;
    ShowLoadedPixmap(pixmap);
  }
  //this->showNormal();

}

void ribi::QtFilterOperationerMainDialog::on_button_save_clicked()
{
  const std::string filename {
    QFileDialog::getSaveFileName(0,"Please select a file").toStdString()
  };
  if (filename.empty()) return;
  if (!m_result) return;

  m_result->pixmap()->toImage().save(filename.c_str());
}

void ribi::QtFilterOperationerMainDialog::ShowLoadedPixmap(const QPixmap& pixmap)
{
  //Load source target
  {
    if (ui->content_source->layout())
    {
      delete m_source;
      m_source = nullptr;
      delete ui->content_source->layout();
    }
    assert(!ui->content_source->layout());

    QVBoxLayout * const layout = new QVBoxLayout;
    ui->content_source->setLayout(layout);
    m_source = new QLabel;
    layout->addWidget(m_source);
    m_source->setPixmap(pixmap);
    m_source->setAlignment(Qt::AlignCenter);
    assert(m_source);
    assert(!m_source->pixmap()->isNull());
  }
}

void ribi::QtFilterOperationerMainDialog::on_button_do_clicked()
{
  const QPixmap& p { *m_source->pixmap() };
  const boost::numeric::ublas::matrix<double> m {
    m_model->GetRawData()
  };
  const QPixmap q {
    FilterOperationerMainDialog::DoFilterOperation(p,m)
  };

  //Load source target
  if (ui->content_result->layout())
  {
    delete m_result;
    m_result = nullptr;
    delete ui->content_result->layout();
  }
  assert(!ui->content_result->layout());

  QVBoxLayout * const layout = new QVBoxLayout;
  ui->content_result->setLayout(layout);
  m_result = new QLabel;
  layout->addWidget(m_result);
  m_result->setAlignment(Qt::AlignCenter);
  m_result->setPixmap(q);
  assert(m_result);
  assert(!m_result->pixmap()->isNull());
}

#ifndef NDEBUG
void ribi::QtFilterOperationerMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::QtFilterOperationerMainDialog::on_box_filter_cols_valueChanged(int arg1)
{
  QAbstractTableModel * const abstract_model
    = dynamic_cast<QAbstractTableModel *>(ui->filter->model());
  assert(abstract_model);
  QtUblasMatrixDoubleModel * const model = dynamic_cast<QtUblasMatrixDoubleModel*>(abstract_model);
  assert(model);
  {
    const boost::numeric::ublas::matrix<double> v = model->GetRawData();
    const int n_rows = v.size1();
    //const int n_cols = v.size2();
    const int n_cols = arg1;
    boost::numeric::ublas::matrix<double> w(n_rows,n_cols);
    for (int y = 0; y != n_rows; ++y)
    {
      for (int x = 0; x != n_cols; ++x)
      {
        //In old range?
        if (y < static_cast<int>(v.size1()) && x < static_cast<int>(v.size2()))
        {
          w(y,x) = v(y,x);
        }
        else
        {
          w(y,x) = 0.0;
        }
      }
    }
    model->SetRawData(w);
  }
  OnAnyChange();
}

void ribi::QtFilterOperationerMainDialog::on_box_filter_rows_valueChanged(int arg1)
{
  QAbstractTableModel * const abstract_model
    = dynamic_cast<QAbstractTableModel *>(ui->filter->model());
  assert(abstract_model);
  QtUblasMatrixDoubleModel * const model = dynamic_cast<QtUblasMatrixDoubleModel*>(abstract_model);
  assert(model);
  {
    const boost::numeric::ublas::matrix<double> v = model->GetRawData();
    //const int n_rows = v.size1();
    const int n_rows = arg1;
    const int n_cols = v.size2();
    //const int n_cols = arg1;
    boost::numeric::ublas::matrix<double> w(n_rows,n_cols);
    for (int y = 0; y != n_rows; ++y)
    {
      for (int x = 0; x != n_cols; ++x)
      {
        //In old range?
        if (y < static_cast<int>(v.size1()) && x < static_cast<int>(v.size2()))
        {
          w(y,x) = v(y,x);
        }
        else
        {
          w(y,x) = 0.0;
        }
      }
    }
    model->SetRawData(w);
  }
  OnAnyChange();
}

void ribi::QtFilterOperationerMainDialog::OnAnyChange() noexcept
{
  QAbstractTableModel * const abstract_model
    = dynamic_cast<QAbstractTableModel *>(ui->filter->model());
  assert(abstract_model);
  QtUblasMatrixDoubleModel * const model = dynamic_cast<QtUblasMatrixDoubleModel*>(abstract_model);
  assert(model);
  const boost::numeric::ublas::matrix<double> v = model->GetRawData();
  const int n_rows = v.size1();
  const int n_cols = v.size2();
  assert(n_rows > 0);
  assert(n_cols > 0);
  ui->button_do->setEnabled(n_rows > 1 || n_cols > 1);
}

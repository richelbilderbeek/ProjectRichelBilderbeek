#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtkalmanfilterermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "kalmanfilterermenudialog.h"
#include "kalmanfilterexample.h"
#include "matrix.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "qthideandshowdialog.h"
#include "qtkalmanfilterermaindialog.h"
#include "qtmatrix.h"
#include "qtstdvectorfunctionmodel.h"
#include "qtstdvectorstringmodel.h"
#include "qtublasmatrixdoublemodel.h"
#include "qtublasvectordoublemodel.h"
#include "qtwhitenoisesystemparametersdialog.h"
#include "standardwhitenoisesystemparameters.h"
#include "trace.h"
#include "ui_qtkalmanfilterermenudialog.h"
#pragma GCC diagnostic pop

ribi::kalman::QtKalmanFiltererMenuDialog::QtKalmanFiltererMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtKalmanFiltererMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::kalman::QtKalmanFiltererMenuDialog::~QtKalmanFiltererMenuDialog() noexcept
{
  delete ui;
}

void ribi::kalman::QtKalmanFiltererMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::kalman::QtKalmanFiltererMenuDialog::on_button_about_clicked()
{
  About a = KalmanFiltererMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  a.AddLibrary("QtMatrix version: " + QtMatrix::GetVersion());
  a.AddLibrary("QtStdVectorFunctionModel version: " + QtStdVectorFunctionModel::GetVersion());
  a.AddLibrary("QtStdVectorStringModel version: " + QtStdVectorStringModel::GetVersion());
  a.AddLibrary("QtUblasMatrixDoubleModel version: " + QtUblasMatrixDoubleModel::GetVersion());
  a.AddLibrary("QtUblasVectorDoubleModel version: " + QtUblasVectorDoubleModel::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::kalman::QtKalmanFiltererMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::kalman::QtKalmanFiltererMenuDialog::on_button_start_clicked()
{
  const boost::shared_ptr<QtKalmanFiltererMainDialog> d = QtKalmanFiltererMainDialog::Create();
  assert(d);
  ShowChild(d.get());
}

#ifndef NDEBUG
void ribi::kalman::QtKalmanFiltererMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Matrix::Test();
    QtMatrix::Test();
    KalmanFiltererMenuDialog();
    QtKalmanFiltererMainDialog::Create();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

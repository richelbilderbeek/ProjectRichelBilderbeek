#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttesthistogrammenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "testhistogrammenudialog.h"
#include "qttesthistogrammaindialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qttesthistogrammenudialog.h"
#pragma GCC diagnostic pop


ribi::QtTestHistogramMenuDialog::QtTestHistogramMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestHistogramMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtTestHistogramMenuDialog::~QtTestHistogramMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestHistogramMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtTestHistogramMenuDialog::on_button_start_clicked()
{
  QtTestHistogramMainDialog d;
  ShowChild(&d);
}

void ribi::QtTestHistogramMenuDialog::on_button_about_clicked()
{
  About a = TestHistogramMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtTestHistogramMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestHistogramMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestHistogramMenuDialog();
}
#endif

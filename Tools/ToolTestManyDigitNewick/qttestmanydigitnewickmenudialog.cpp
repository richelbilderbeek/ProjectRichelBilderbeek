#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestmanydigitnewickmenudialog.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "testmanydigitnewickmenudialog.h"
#include "qtaboutdialog.h"
#include "qttestmanydigitnewickmaindialog.h"
#include "testtimer.h"
#include "testmanydigitnewickmenudialog.h"
#include "ui_qttestmanydigitnewickmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtTestManyDigitNewickMenuDialog::QtTestManyDigitNewickMenuDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestManyDigitNewickMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestManyDigitNewickMenuDialog::~QtTestManyDigitNewickMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestManyDigitNewickMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void ribi::QtTestManyDigitNewickMenuDialog::on_button_start_clicked() noexcept
{
  QtTestManyDigitNewickMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestManyDigitNewickMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(TestManyDigitNewickMenuDialog().GetAbout());
  d.setWindowIcon(windowIcon());
  d.setStyleSheet(styleSheet());
  ShowChild(&d);
}

void ribi::QtTestManyDigitNewickMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestManyDigitNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtTestManyDigitNewickMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

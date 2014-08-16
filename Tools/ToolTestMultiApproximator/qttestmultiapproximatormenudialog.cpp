#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestmultiapproximatormenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testmultiapproximatormenudialog.h"
#include "qtaboutdialog.h"
#include "qttestmultiapproximatormaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestmultiapproximatormenudialog.h"

#pragma GCC diagnostic pop

ribi::QtToolTestMultiApproximatorMenuDialog::QtToolTestMultiApproximatorMenuDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestMultiApproximatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolTestMultiApproximatorMenuDialog::~QtToolTestMultiApproximatorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolTestMultiApproximatorMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolTestMultiApproximatorMenuDialog::on_button_about_clicked() noexcept
{
  About a = ToolTestMultiApproximatorMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtToolTestMultiApproximatorMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtToolTestMultiApproximatorMenuDialog::on_button_start_clicked() noexcept
{
  QtToolTestMultiApproximatorMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolTestMultiApproximatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtToolTestMultiApproximatorMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

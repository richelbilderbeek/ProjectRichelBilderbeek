#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttesthideandshowdialogmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testhideandshowdialogmenudialog.h"
#include "qtaboutdialog.h"
#include "qttesthideandshowdialogmaindialog.h"
#include "testtimer.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttesthideandshowdialogmenudialog.h"

#pragma GCC diagnostic pop

ribi::QtTestHideAndShowDialogMenuDialog::QtTestHideAndShowDialogMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestHideAndShowDialogMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::QtTestHideAndShowDialogMenuDialog::~QtTestHideAndShowDialogMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestHideAndShowDialogMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestHideAndShowDialogMenuDialog::on_button_about_clicked()
{
  About a = TestHideAndShowDialogMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestHideAndShowDialogMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestHideAndShowDialogMenuDialog::on_button_start_clicked()
{
  QtTestHideAndShowMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestHideAndShowDialogMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestHideAndShowMainDialog();
  assert(!QtTestHideAndShowDialogMenuDialog().GetVersion().empty());
}
#endif

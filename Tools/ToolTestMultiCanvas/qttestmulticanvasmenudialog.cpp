#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestmulticanvasmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testmulticanvasmenudialog.h"
#include "qtaboutdialog.h"
#include "qttestmulticanvasmaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestmulticanvasmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestMultiCanvasMenuDialog::QtTestMultiCanvasMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestMultiCanvasMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestMultiCanvasMenuDialog::~QtTestMultiCanvasMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestMultiCanvasMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestMultiCanvasMenuDialog::on_button_about_clicked()
{
  About a = TestMultiCanvasMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestMultiCanvasMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestMultiCanvasMenuDialog::on_button_start_canvas_clicked()
{
  QtTestMultiCanvasMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestMultiCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestMultiCanvasMenuDialog();
  QtTestMultiCanvasMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

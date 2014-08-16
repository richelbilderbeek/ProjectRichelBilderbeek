#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestdrawcanvasmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testdrawcanvasmenudialog.h"
#include "qtaboutdialog.h"
#include "qttestdrawcanvasmaindialog.h"
#include "testtimer.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttestdrawcanvasmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestDrawCanvasMenuDialog::QtTestDrawCanvasMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestDrawCanvasMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestDrawCanvasMenuDialog::~QtTestDrawCanvasMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestDrawCanvasMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestDrawCanvasMenuDialog::on_button_about_clicked()
{
  About a = TestDrawCanvasMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestDrawCanvasMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestDrawCanvasMenuDialog::on_button_start_canvas_clicked()
{
  QtTestDrawCanvasMainDialog d;
  d.setWindowIcon(this->windowIcon());
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestDrawCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtTestDrawCanvasMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

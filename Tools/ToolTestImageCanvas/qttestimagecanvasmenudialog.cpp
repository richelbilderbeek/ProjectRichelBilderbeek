#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttestimagecanvasmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testimagecanvasmenudialog.h"
#include "qtaboutdialog.h"
#include "qttestimagecanvasmaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestimagecanvasmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestImageCanvasMenuDialog::QtTestImageCanvasMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestImageCanvasMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestImageCanvasMenuDialog::~QtTestImageCanvasMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestImageCanvasMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestImageCanvasMenuDialog::on_button_about_clicked()
{
  About a = TestImageCanvasMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestImageCanvasMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestImageCanvasMenuDialog::on_button_start_canvas_clicked()
{
  QtTestImageCanvasMainDialog d;
  d.setWindowIcon(this->windowIcon());
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestImageCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtTestImageCanvasMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttesttextcanvasmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testtextcanvasmenudialog.h"
#include "qtaboutdialog.h"
#include "qttesttextcanvasmaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttesttextcanvasmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTextCanvasMenuDialog::QtTestTextCanvasMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTextCanvasMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestTextCanvasMenuDialog::~QtTestTextCanvasMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTextCanvasMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestTextCanvasMenuDialog::on_button_about_clicked()
{
  About a = TestTextCanvasMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestTextCanvasMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestTextCanvasMenuDialog::on_button_start_canvas_clicked()
{
  QtTestTextCanvasMainDialog d;
  d.setWindowIcon(this->windowIcon());
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestTextCanvasMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    TestTextCanvasMenuDialog();
    QtTestTextCanvasMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

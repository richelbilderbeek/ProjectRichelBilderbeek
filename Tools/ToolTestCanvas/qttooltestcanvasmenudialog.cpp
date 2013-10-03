#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttooltestcanvasmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltestcanvasmenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestcanvasmaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestcanvasmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolTestCanvasMenuDialog::QtToolTestCanvasMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolTestCanvasMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolTestCanvasMenuDialog::~QtToolTestCanvasMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolTestCanvasMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolTestCanvasMenuDialog::on_button_about_clicked()
{
  About a = ToolTestCanvasMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtToolTestCanvasMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtToolTestCanvasMenuDialog::on_button_start_clicked()
{
  QtToolTestCanvasMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolTestCanvasMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtToolTestCanvasMenuDialog::Test");
  QtToolTestCanvasMainDialog();
  TRACE("Finished ribi::QtToolTestCanvasMenuDialog::Test successfully");
}
#endif

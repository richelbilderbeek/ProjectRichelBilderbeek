//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestcanvasmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltestcanvasmenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestcanvasmaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestcanvasmenudialog.h"

QtToolTestCanvasMenuDialog::QtToolTestCanvasMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolTestCanvasMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtToolTestCanvasMenuDialog::~QtToolTestCanvasMenuDialog()
{
  delete ui;
}

void QtToolTestCanvasMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtToolTestCanvasMenuDialog::on_button_about_clicked()
{
  About a = ToolTestCanvasMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtToolTestCanvasMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtToolTestCanvasMenuDialog::on_button_start_clicked()
{
  QtToolTestCanvasMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void QtToolTestCanvasMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtToolTestCanvasMenuDialog::Test");
  QtToolTestCanvasMainDialog();
  TRACE("Finished QtToolTestCanvasMenuDialog::Test successfully");
}
#endif

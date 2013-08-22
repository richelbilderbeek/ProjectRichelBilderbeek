//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestapproximatormenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltestapproximatormenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestapproximatormaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestapproximatormenudialog.h"

QtToolTestApproximatorMenuDialog::QtToolTestApproximatorMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestApproximatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtToolTestApproximatorMenuDialog::~QtToolTestApproximatorMenuDialog()
{
  delete ui;
}

void QtToolTestApproximatorMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtToolTestApproximatorMenuDialog::on_button_about_clicked()
{
  About a = ToolTestApproximatorMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtToolTestApproximatorMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtToolTestApproximatorMenuDialog::on_button_start_clicked()
{
  QtToolTestApproximatorMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void QtToolTestApproximatorMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtToolTestApproximatorMenuDialog::Test");
  QtToolTestApproximatorMainDialog();
  TRACE("Finished QtToolTestApproximatorMenuDialog::Test successfully");
}
#endif

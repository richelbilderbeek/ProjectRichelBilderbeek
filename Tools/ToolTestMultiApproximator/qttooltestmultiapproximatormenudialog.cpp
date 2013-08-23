//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestmultiapproximatormenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltestmultiapproximatormenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestmultiapproximatormaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestmultiapproximatormenudialog.h"

QtToolTestMultiApproximatorMenuDialog::QtToolTestMultiApproximatorMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestMultiApproximatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtToolTestMultiApproximatorMenuDialog::~QtToolTestMultiApproximatorMenuDialog()
{
  delete ui;
}

void QtToolTestMultiApproximatorMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtToolTestMultiApproximatorMenuDialog::on_button_about_clicked()
{
  About a = ToolTestMultiApproximatorMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtToolTestMultiApproximatorMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtToolTestMultiApproximatorMenuDialog::on_button_start_clicked()
{
  QtToolTestMultiApproximatorMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void QtToolTestMultiApproximatorMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtToolTestMultiApproximatorMenuDialog::Test");
  QtToolTestMultiApproximatorMainDialog();
  TRACE("Finished QtToolTestMultiApproximatorMenuDialog::Test successfully");
}
#endif

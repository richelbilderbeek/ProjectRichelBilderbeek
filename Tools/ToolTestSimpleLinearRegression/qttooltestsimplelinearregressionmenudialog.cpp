//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestsimplelinearregressionmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltestsimplelinearregressionmenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestsimplelinearregressionmaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestsimplelinearregressionmenudialog.h"

QtToolTestSimpleLinearRegressionMenuDialog::QtToolTestSimpleLinearRegressionMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestSimpleLinearRegressionMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

QtToolTestSimpleLinearRegressionMenuDialog::~QtToolTestSimpleLinearRegressionMenuDialog()
{
  delete ui;
}

void QtToolTestSimpleLinearRegressionMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtToolTestSimpleLinearRegressionMenuDialog::on_button_about_clicked()
{
  About a = ToolTestSimpleLinearRegressionMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtToolTestSimpleLinearRegressionMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtToolTestSimpleLinearRegressionMenuDialog::on_button_start_clicked()
{
  QtToolTestSimpleLinearRegressionMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void QtToolTestSimpleLinearRegressionMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtToolTestSimpleLinearRegressionMenuDialog::Test");
  QtToolTestSimpleLinearRegressionMainDialog();
  TRACE("Finished QtToolTestSimpleLinearRegressionMenuDialog::Test successfully");
}
#endif

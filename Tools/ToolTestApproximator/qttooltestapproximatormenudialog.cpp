//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttooltestapproximatormenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltestapproximatormenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltestapproximatorxymaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooltestapproximatormenudialog.h"

ribi::QtToolTestApproximatorMenuDialog::QtToolTestApproximatorMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestApproximatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolTestApproximatorMenuDialog::~QtToolTestApproximatorMenuDialog()
{
  delete ui;
}

void ribi::QtToolTestApproximatorMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_about_clicked()
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

void ribi::QtToolTestApproximatorMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_start_xy_clicked()
{
  QtToolTestApproximatorXyMainDialog d;
  ShowChild(&d);
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_start_xyz_clicked()
{
  //QtToolTestApproximatorXyzMainDialog d;
  //ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolTestApproximatorMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtToolTestApproximatorMenuDialog::Test");
  QtToolTestApproximatorXyMainDialog();
  //QtToolTestApproximatorMainXyzDialog();
  TRACE("Finished ribi::QtToolTestApproximatorMenuDialog::Test successfully");
}
#endif

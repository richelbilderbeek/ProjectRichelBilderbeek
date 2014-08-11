#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestapproximatormenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testapproximatormenudialog.h"
#include "qtaboutdialog.h"
#include "qttestapproximatorxymaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestapproximatormenudialog.h"

#pragma GCC diagnostic pop

ribi::QtToolTestApproximatorMenuDialog::QtToolTestApproximatorMenuDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtToolTestApproximatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolTestApproximatorMenuDialog::~QtToolTestApproximatorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolTestApproximatorMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_about_clicked() noexcept
{
  About a = ToolTestApproximatorMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_start_xy_clicked() noexcept
{
  QtToolTestApproximatorXyMainDialog d;
  ShowChild(&d);
}

void ribi::QtToolTestApproximatorMenuDialog::on_button_start_xyz_clicked() noexcept
{
  //QtToolTestApproximatorXyzMainDialog d;
  //ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolTestApproximatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtToolTestApproximatorXyMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

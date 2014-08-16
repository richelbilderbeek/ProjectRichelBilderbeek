#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtquadraticsolvermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "quadraticsolvermenudialog.h"
#include "qtaboutdialog.h"
#include "qtquadraticsolvermaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtquadraticsolvermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtQuadraticSolverMenuDialog::QtQuadraticSolverMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtQuadraticSolverMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtQuadraticSolverMenuDialog::~QtQuadraticSolverMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtQuadraticSolverMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtQuadraticSolverMenuDialog::on_button_about_clicked()
{
  About a = QuadraticSolverMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtQuadraticSolverMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtQuadraticSolverMenuDialog::on_button_start_clicked()
{
  QtQuadraticSolverMainDialog d;
  //d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtQuadraticSolverMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtdotmatrixmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "dotmatrixmenudialog.h"
#include "qtaboutdialog.h"
#include "qtdotmatrixsinglelinemaindialog.h"
#include "qtdotmatrixmultilinemaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtdotmatrixmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtDotMatrixMenuDialog::QtDotMatrixMenuDialog(
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtDotMatrixMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtDotMatrixMenuDialog::~QtDotMatrixMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtDotMatrixMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtDotMatrixMenuDialog::on_button_about_clicked()
{
  About a = DotMatrixMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtDotMatrixMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::QtDotMatrixMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  DotMatrixMenuDialog();
  QtDotMatrixSingleLineMainDialog();
  QtDotMatrixMultiLineMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::QtDotMatrixMenuDialog::on_button_start_single_line_clicked()
{
  QtDotMatrixSingleLineMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtDotMatrixMenuDialog::on_button_start_multi_line_clicked()
{
  QtDotMatrixMultiLineMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

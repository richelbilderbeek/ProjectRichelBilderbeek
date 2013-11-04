#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttooldotmatrixmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooldotmatrixmenudialog.h"
#include "qtaboutdialog.h"
#include "qttooldotmatrixmaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttooldotmatrixmenudialog.h"
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
  About a = ToolDotMatrixMenuDialog().GetAbout();
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

void ribi::QtDotMatrixMenuDialog::on_button_start_clicked()
{
  QtToolDotMatrixMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtDotMatrixMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtDotMatrixMenuDialog::Test");
  QtToolDotMatrixMainDialog();
  TRACE("Finished ribi::QtDotMatrixMenuDialog::Test successfully");
}
#endif

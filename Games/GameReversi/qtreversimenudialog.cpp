#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtreversimenudialog.h"

#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "reversimenudialog.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "qtreversimaindialog.h"
#include "reversimenudialog.h"
#include "ui_qtreversimenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::reversi::QtReversiMenuDialog::QtReversiMenuDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtReversiMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::reversi::QtReversiMenuDialog::~QtReversiMenuDialog() noexcept
{
  delete ui;
}

void ribi::reversi::QtReversiMenuDialog::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Escape) { close(); }
}

void ribi::reversi::QtReversiMenuDialog::on_button_start_clicked() noexcept
{
  QtReversiMainDialog d;
  this->ShowChild(&d);
}

void ribi::reversi::QtReversiMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(MenuDialog().GetAbout());
  d.setWindowIcon(windowIcon());
  d.setStyleSheet(styleSheet());
  ShowChild(&d);
}

void ribi::reversi::QtReversiMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::reversi::QtReversiMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtReversiMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

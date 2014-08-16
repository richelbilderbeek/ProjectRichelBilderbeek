#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttesttictactoemenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tictactoeais.h"
#include "testtictactoemenudialog.h"
#include "qtaboutdialog.h"
#include "qttesttictactoemaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qttesttictactoemenudialog.h"
#pragma GCC diagnostic pop

ribi::tictactoe::QtTestTicTacToeMenuDialog::QtTestTicTacToeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTicTacToeMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::tictactoe::QtTestTicTacToeMenuDialog::~QtTestTicTacToeMenuDialog() noexcept
{
  delete ui;
}

void ribi::tictactoe::QtTestTicTacToeMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::tictactoe::QtTestTicTacToeMenuDialog::on_button_about_clicked()
{
  About a = TestTicTacToeMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::tictactoe::QtTestTicTacToeMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::tictactoe::QtTestTicTacToeMenuDialog::on_button_start_clicked()
{
  QtTestTicTacToeMainDialog d(nullptr,nullptr);
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::tictactoe::QtTestTicTacToeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TestTicTacToeMenuDialog();
  for (const auto& ai: Ais().GetAll())
  {
    QtTestTicTacToeMainDialog(nullptr,ai);
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

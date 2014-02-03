#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttesttictactoemenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "testtictactoemenudialog.h"
#include "qtaboutdialog.h"
#include "qttesttictactoemaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttesttictactoemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTicTacToeMenuDialog::QtTestTicTacToeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTicTacToeMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
}

ribi::QtTestTicTacToeMenuDialog::~QtTestTicTacToeMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTicTacToeMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtTestTicTacToeMenuDialog::on_button_about_clicked()
{
  About a = TestTicTacToeMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtTestTicTacToeMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtTestTicTacToeMenuDialog::on_button_start_clicked()
{
  QtTestTicTacToeMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtTestTicTacToeMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTicTacToeMenuDialog::Test");
  QtTestTicTacToeMainDialog();
  //assert(1==2); //TEMP
  TRACE("Finished ribi::QtTestTicTacToeMenuDialog::Test successfully");
}
#endif

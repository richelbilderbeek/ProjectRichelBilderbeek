#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttooltesttictactoemenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "tooltesttictactoemenudialog.h"
#include "qtaboutdialog.h"
#include "qttooltesttictactoemaindialog.h"
#include "qthideandshowdialog.h"
#include "ui_qttooltesttictactoemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTicTacToeMenuDialog::QtTestTicTacToeMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTicTacToeMenuDialog)
{
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


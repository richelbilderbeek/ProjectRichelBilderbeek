#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qttoolprimeexpertmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "toolprimeexpertmenudialog.h"
#include "qtaboutdialog.h"
#include "qttoolprimeexpertmaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttoolprimeexpertmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolPrimeExpertMenuDialog::QtToolPrimeExpertMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolPrimeExpertMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolPrimeExpertMenuDialog::~QtToolPrimeExpertMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolPrimeExpertMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolPrimeExpertMenuDialog::on_button_about_clicked()
{
  About a = PrimeExpertMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtToolPrimeExpertMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::QtToolPrimeExpertMenuDialog::on_button_start_clicked()
{
  QtToolPrimeExpertMainDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolPrimeExpertMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtToolPrimeExpertMenuDialog::Test");
  TRACE("Finished ribi::QtToolPrimeExpertMenuDialog::Test successfully");
}
#endif

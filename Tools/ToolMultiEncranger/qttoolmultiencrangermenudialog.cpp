#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttoolmultiencrangermenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "toolmultiencrangermenudialog.h"
#include "qtaboutdialog.h"
#include "qttoolmultiencrangermaindialog.h"
#include "qthideandshowdialog.h"
#include "trace.h"
#include "ui_qttoolmultiencrangermenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolMultiEncrangerMenuDialog::QtToolMultiEncrangerMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtToolMultiEncrangerMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolMultiEncrangerMenuDialog::~QtToolMultiEncrangerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolMultiEncrangerMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtToolMultiEncrangerMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = ribi::ToolMultiEncrangerMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtToolMultiEncrangerMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtToolMultiEncrangerMenuDialog::on_button_start_clicked() noexcept
{
  QtToolMultiEncrangerMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolMultiEncrangerMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting QtToolMultiEncrangerMenuDialog::Test");
  QtToolMultiEncrangerMainDialog();
  TRACE("Finished QtToolMultiEncrangerMenuDialog::Test successfully");
}
#endif

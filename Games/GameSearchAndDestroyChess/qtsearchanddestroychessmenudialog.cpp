#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsearchanddestroychessmenudialog.h"

#include <future>

#include "searchanddestroychessmenudialog.h"
#include "qtaboutdialog.h"
#include "qtsearchanddestroychessgamedialog.h"
#include "ui_qtsearchanddestroychessmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::sadc::QtSearchAndDestroyChessMenuDialog::QtSearchAndDestroyChessMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSearchAndDestroyChessMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //TODO: Add transparency to the resources
}

ribi::sadc::QtSearchAndDestroyChessMenuDialog::~QtSearchAndDestroyChessMenuDialog() noexcept
{
  delete ui;
}

void ribi::sadc::QtSearchAndDestroyChessMenuDialog::on_button_start_clicked()
{
  QtSearchAndDestroyChessGameDialog d;
  ShowChild(&d);
}

void ribi::sadc::QtSearchAndDestroyChessMenuDialog::on_button_about_clicked()
{
  const About a = sadc::MenuDialog().GetAbout();
  QtAboutDialog d(a);
  ShowChild(&d);
}

void ribi::sadc::QtSearchAndDestroyChessMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::sadc::QtSearchAndDestroyChessMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtSearchAndDestroyChessGameDialog();
  }
}
#endif

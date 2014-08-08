#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstaircasecardcreatormenudialog.h"

#include "about.h"
#include "trace.h"
#include "qtaboutdialog.h"
#include "testtimer.h"
#include "qtstaircasecardcreatormaindialog.h"
#include "staircasecardcreatormenudialog.h"
#include "ui_qtstaircasecardcreatormenudialog.h"
#pragma GCC diagnostic pop

ribi::scc::QtStaircaseCardCreatorMenuDialog::QtStaircaseCardCreatorMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtStaircaseCardCreatorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::scc::QtStaircaseCardCreatorMenuDialog::~QtStaircaseCardCreatorMenuDialog() noexcept
{
  delete ui;
}


void ribi::scc::QtStaircaseCardCreatorMenuDialog::on_button_about_clicked() noexcept
{
  ::ribi::About a = ::ribi::scc::MenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ::ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::scc::QtStaircaseCardCreatorMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::scc::QtStaircaseCardCreatorMenuDialog::on_button_start_clicked() noexcept
{
  QtStaircaseCardCreatorMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::scc::QtStaircaseCardCreatorMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ribi::scc::MenuDialog();
  QtStaircaseCardCreatorMainDialog();
}
#endif

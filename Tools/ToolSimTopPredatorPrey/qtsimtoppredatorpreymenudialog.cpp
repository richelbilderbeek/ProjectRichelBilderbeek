#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtsimtoppredatorpreymenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "simtoppredatorpreymenudialog.h"
#include "qtaboutdialog.h"
#include "qtsimtoppredatorpreymaindialog.h"
#include "qtsimpredatorpreymaindialog.h"
#include "qthideandshowdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtsimtoppredatorpreymenudialog.h"
#pragma GCC diagnostic pop

ribi::QtSimTopPredatorPreyMenuDialog::QtSimTopPredatorPreyMenuDialog(QWidget *parent) noexcept :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSimTopPredatorPreyMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtSimTopPredatorPreyMenuDialog::~QtSimTopPredatorPreyMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtSimTopPredatorPreyMenuDialog::keyPressEvent(QKeyEvent * event) noexcept
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void ribi::QtSimTopPredatorPreyMenuDialog::on_button_about_clicked() noexcept
{
  ribi::About a = ribi::SimTopPredatorPreyMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  ribi::QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::QtSimTopPredatorPreyMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtSimTopPredatorPreyMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtSimTopPredatorPrayMainDialog();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

void ribi::QtSimTopPredatorPreyMenuDialog::on_button_start_tpp_clicked()
{
  QtSimTopPredatorPrayMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtSimTopPredatorPreyMenuDialog::on_button_start_pp_clicked()
{
  QtSimPredatorPrayMainDialog d;
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);

}

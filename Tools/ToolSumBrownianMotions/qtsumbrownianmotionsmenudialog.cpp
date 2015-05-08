#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtsumbrownianmotionsmenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "sumbrownianmotionsmenudialog.h"
#include "qtsumbrownianmotionsmaindialog.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtsumbrownianmotionsmenudialog.h"
#pragma GCC diagnostic pop


ribi::QtSumBrownianMotionsMenuDialog::QtSumBrownianMotionsMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSumBrownianMotionsMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtSumBrownianMotionsMenuDialog::~QtSumBrownianMotionsMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtSumBrownianMotionsMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtSumBrownianMotionsMenuDialog::on_button_start_clicked()
{
  QtSumBrownianMotionsMainDialog d;
  ShowChild(&d);
}

void ribi::QtSumBrownianMotionsMenuDialog::on_button_about_clicked()
{
  About a = SumBrownianMotionsMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtSumBrownianMotionsMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtSumBrownianMotionsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtSumBrownianMotionsMenuDialog();
}
#endif

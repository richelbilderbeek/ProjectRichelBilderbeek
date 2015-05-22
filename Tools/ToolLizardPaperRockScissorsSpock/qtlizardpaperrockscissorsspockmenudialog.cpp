#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtlizardpaperrockscissorsspockmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "lizardpaperrockscissorsspockmenudialog.h"
#include "qtlizardpaperrockscissorsspockmaindialog.h"
#include "qtlizardpaperrockscissorsspockwidget.h"
#include "trace.h"
#include "testtimer.h"
#include "ui_qtlizardpaperrockscissorsspockmenudialog.h"
#pragma GCC diagnostic pop


ribi::QtLizardPaperRockScissorsSpockMenuDialog::QtLizardPaperRockScissorsSpockMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtLizardPaperRockScissorsSpockMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtLizardPaperRockScissorsSpockMenuDialog::~QtLizardPaperRockScissorsSpockMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtLizardPaperRockScissorsSpockMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtLizardPaperRockScissorsSpockMenuDialog::on_button_start_clicked()
{
  QtLizardPaperRockScissorsSpockMainDialog d;
  ShowChild(&d);
  /*
  QtWidget * const w{new QtWidget};
  QtHideAndShowDialog d(this);
  d.setWindowTitle("LizardPaperRockScissorsSpock");
  QGridLayout * const my_layout{new QGridLayout};
  assert(!d.layout());
  d.setLayout(my_layout);
  assert(d.layout());
  my_layout->addWidget(w);
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    d.setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    d.move( screen.center() - d.rect().center() );
  }
  ShowChild(&d);
  */
}

void ribi::QtLizardPaperRockScissorsSpockMenuDialog::on_button_about_clicked()
{
  About a = LizardPaperRockScissorsSpockMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtLizardPaperRockScissorsSpockMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtLizardPaperRockScissorsSpockMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtLizardPaperRockScissorsSpockWidget();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtLizardPaperRockScissorsSpockMenuDialog();
}
#endif

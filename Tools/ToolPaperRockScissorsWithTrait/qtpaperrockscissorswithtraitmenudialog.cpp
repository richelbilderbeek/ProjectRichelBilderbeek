#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpaperrockscissorswithtraitmenudialog.h"

#include <QDesktopWidget>
#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "paperrockscissorswithtraitmenudialog.h"
#include "qtpaperrockscissorswidget.h"
#include "qtpaperrockscissorswithtraitmaindialog.h"

#include "trace.h"
#include "testtimer.h"
#include "ui_qtpaperrockscissorswithtraitmenudialog.h"
#pragma GCC diagnostic pop


ribi::QtPaperRockScissorsMenuDialog::QtPaperRockScissorsMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtPaperRockScissorsMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtPaperRockScissorsMenuDialog::~QtPaperRockScissorsMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtPaperRockScissorsMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtPaperRockScissorsMenuDialog::on_button_start_clicked()
{
  QtPaperRockScissorsMainDialog d;
  ShowChild(&d);
  /*
  QtPaperRockScissorsWidget * const w{new QtPaperRockScissorsWidget};
  QtPaperRockScissorsDialog d(this);
  d.setWindowTitle("PaperRockScissors");
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

void ribi::QtPaperRockScissorsMenuDialog::on_button_about_clicked()
{
  About a = PaperRockScissorsMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtPaperRockScissorsMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtPaperRockScissorsMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtPaperRockScissorsWidget();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtPaperRockScissorsMenuDialog();
}
#endif

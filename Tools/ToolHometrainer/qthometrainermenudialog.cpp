#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qthometrainermenudialog.h"

#include <QDesktopWidget>
#include "hometrainermenudialog.h"
#include "qtaboutdialog.h"
#include "qthometrainermaindialog.h"
#include "ui_qthometrainermenudialog.h"

QtHometrainerMenuDialog::QtHometrainerMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtHometrainerMenuDialog)
{
  ui->setupUi(this);
}

QtHometrainerMenuDialog::~QtHometrainerMenuDialog()
{
  delete ui;
}

void QtHometrainerMenuDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void QtHometrainerMenuDialog::on_button_about_clicked()
{
  About a = HometrainerMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  this->hide();
  d.exec();
  this->show();
}

void QtHometrainerMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtHometrainerMenuDialog::on_button_start_clicked()
{
  QtHometrainerMainDialog d;
  ShowChild(&d);
}


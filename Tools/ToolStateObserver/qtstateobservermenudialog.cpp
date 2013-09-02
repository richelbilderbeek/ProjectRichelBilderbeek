//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtstateobservermenudialog.h"

#include "qtaboutdialog.h"
#include "qtstateobservermaindialog.h"
#include "qthideandshowdialog.h"
#include "stateobservermenudialog.h"
#include "ui_qtstateobservermenudialog.h"

QtStateObserverMenuDialog::QtStateObserverMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtStateObserverMenuDialog)
{
  ui->setupUi(this);
}

QtStateObserverMenuDialog::~QtStateObserverMenuDialog()
{
  delete ui;
}

void QtStateObserverMenuDialog::on_button_start_clicked()
{
  QtStateObserverMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void QtStateObserverMenuDialog::on_button_about_clicked()
{
  this->hide();
  About a = StateObserverMenuDialog::GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  d.exec();
  this->show();
}

void QtStateObserverMenuDialog::on_button_quit_clicked()
{
  close();
}


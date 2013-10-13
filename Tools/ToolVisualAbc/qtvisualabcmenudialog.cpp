
#include "about.h"
#include "qtaboutdialog.h"
#include "qtmaindialog.h"
#include "qtvisualabcmenudialog.h"
#include "ui_qtvisualabcmenudialog.h"
#include "menudialog.h"

QtVisualAbcMenuDialog::QtVisualAbcMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtVisualAbcMenuDialog)
{
  ui->setupUi(this);
}

QtVisualAbcMenuDialog::~QtVisualAbcMenuDialog()
{
  delete ui;
}

void QtVisualAbcMenuDialog::on_button_start_clicked()
{
  QtMainDialog d;
  this->showChile(&d);
}

void QtVisualAbcMenuDialog::on_button_about_clicked()
{
  About a = VisualAbcMenuDialog::GetAbout();
  QtAboutDialog d(a);
  this->showChile(&d);
}

void QtVisualAbcMenuDialog::on_button_quit_clicked()
{
  close();
}


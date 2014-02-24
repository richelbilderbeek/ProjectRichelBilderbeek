#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtaboutdialog.h"
#include "qtsecretmessagecreatedialog.h"
#include "qtsecretmessageextractdialog.h"
#include "qtsecretmessagemenudialog.h"
#include "secretmessagemenudialog.h"
#include "trace.h"
#include "ui_qtsecretmessagemenudialog.h"
#pragma GCC diagnostic pop

ribi::sema::QtMenuDialog::QtMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSecretMessageMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::sema::QtMenuDialog::~QtMenuDialog() noexcept
{
  delete ui;
}


void ribi::sema::QtMenuDialog::on_button_about_clicked()
{
  About a = sema::MenuDialog().GetAbout();
  //a.AddLibrary("QtRichelBilderbeekGalleryDialog version: " + QtRichelBilderbeekGalleryDialog::GetVersion());
  //a.AddLibrary("QtRichelBilderbeekResources version: " + RichelBilderbeek::QtResources::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::sema::QtMenuDialog::on_button_create_clicked()
{
  QtSecretMessageCreateDialog d;
  this->ShowChild(&d);
}

void ribi::sema::QtMenuDialog::on_button_extract_clicked()
{
  QtSecretMessageExtractDialog2 d;
  this->ShowChild(&d);
}


void ribi::sema::QtMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::sema::QtMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::sema::QtMenuDialog::Test");
  TRACE("Finished ribi::sema::QtMenuDialog::Test successfully");
}
#endif

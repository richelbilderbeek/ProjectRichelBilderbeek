#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtvalentinecarddecryptermaindialog.h"

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <QFileDialog>
#include <QLabel>

#include "valentinecarddecryptermaindialog.h"
#include "trace.h"
#include "ui_qtvalentinecarddecryptermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtValentineCardDecrypterMainDialog::QtValentineCardDecrypterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtValentineCardDecrypterMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtValentineCardDecrypterMainDialog::~QtValentineCardDecrypterMainDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtValentineCardDecrypterMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtValentineCardDecrypterMainDialog::Test");
  TRACE("Finished ribi::QtValentineCardDecrypterMainDialog::Test successfully");
}
#endif

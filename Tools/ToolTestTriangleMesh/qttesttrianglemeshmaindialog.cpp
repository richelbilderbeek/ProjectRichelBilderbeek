#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <boost/lexical_cast.hpp>
#include <QDesktopWidget>

#include "fparser.hh"
#include "qttesttrianglemeshmaindialog.h"
#include "trace.h"
#include "ui_qttesttrianglemeshmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtTestTriangleMeshMainDialog::QtTestTriangleMeshMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTriangleMeshMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestTriangleMeshMainDialog::~QtTestTriangleMeshMainDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtTestTriangleMeshMainDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTriangleMeshMainDialog::Test");
  TRACE("Finished ribi::QtTestTriangleMeshMainDialog::Test successfully");
}
#endif

#include "qtstaircasecardcreatormaindialog.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtstaircasecardcreatormaindialog.h"
#pragma GCC diagnostic pop

ribi::scc::QtStaircaseCardCreatorMainDialog::QtStaircaseCardCreatorMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStaircaseCardCreatorMainDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::scc::QtStaircaseCardCreatorMainDialog::~QtStaircaseCardCreatorMainDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::scc::QtStaircaseCardCreatorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

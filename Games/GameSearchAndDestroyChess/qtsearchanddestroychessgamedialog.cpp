#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsearchanddestroychessgamedialog.h"

#include "ui_qtsearchanddestroychessgamedialog.h"
#pragma GCC diagnostic pop

ribi::QtSearchAndDestroyChessGameDialog::QtSearchAndDestroyChessGameDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSearchAndDestroyChessGameDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::QtSearchAndDestroyChessGameDialog::~QtSearchAndDestroyChessGameDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtSearchAndDestroyChessGameDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    ribi::Chess::QtChessBoardWidget();
  }

}
#endif

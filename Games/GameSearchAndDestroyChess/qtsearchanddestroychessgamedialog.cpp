#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsearchanddestroychessgamedialog.h"

#ifdef MXE_SUPPORTS_THREADS
#include <future>
#endif

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
  #ifdef MXE_SUPPORTS_THREADS
  std::thread t(
    []
  #endif
    {
      ribi::Chess::QtChessBoardWidget();
    }
  #ifdef MXE_SUPPORTS_THREADS
  );
  t.join();
  #endif

}
#endif

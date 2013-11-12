#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtsearchanddestroychessgamedialog.h"

#include <future>

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

ribi::QtSearchAndDestroyChessGameDialog::~QtSearchAndDestroyChessGameDialog()
{
  delete ui;
}

void ribi::QtSearchAndDestroyChessGameDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::thread t(
    []
    {
      ribi::Chess::QtChessBoardWidget();
    }
  );
  t.join();

}

#include "qtsearchanddestroychessgamedialog.h"

#include <future>

#include "ui_qtsearchanddestroychessgamedialog.h"

QtSearchAndDestroyChessGameDialog::QtSearchAndDestroyChessGameDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSearchAndDestroyChessGameDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
}

QtSearchAndDestroyChessGameDialog::~QtSearchAndDestroyChessGameDialog()
{
  delete ui;
}

void QtSearchAndDestroyChessGameDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::thread t(
    []
    {
      QtChessBoardWidget();
    }
  );
  t.join();

}

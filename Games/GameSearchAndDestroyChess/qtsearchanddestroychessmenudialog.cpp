#include "qtsearchanddestroychessmenudialog.h"

#include <future>

#include "searchanddestroychessmenudialog.h"
#include "qtaboutdialog.h"
#include "qtsearchanddestroychessgamedialog.h"
#include "ui_qtsearchanddestroychessmenudialog.h"

QtSearchAndDestroyChessMenuDialog::QtSearchAndDestroyChessMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtSearchAndDestroyChessMenuDialog)
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  //TODO: Add transparency to the resources
}

QtSearchAndDestroyChessMenuDialog::~QtSearchAndDestroyChessMenuDialog()
{
  delete ui;
}

void QtSearchAndDestroyChessMenuDialog::on_button_start_clicked()
{
  QtSearchAndDestroyChessGameDialog d;
  ShowChild(&d);
}

void QtSearchAndDestroyChessMenuDialog::on_button_about_clicked()
{
  const About a = SearchAndDestroyChess::MenuDialog().GetAbout();
  QtAboutDialog d(a);
  d.exec();
}

void QtSearchAndDestroyChessMenuDialog::on_button_quit_clicked()
{
  close();
}

void QtSearchAndDestroyChessMenuDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  std::thread t(
    []
    {
      QtSearchAndDestroyChessGameDialog();
    }
  );
  t.join();
}

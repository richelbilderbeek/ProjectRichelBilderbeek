#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtreversimaindialog.h"
#include "qtreversiwidget.h"
#include "ui_qtreversimaindialog.h"
#pragma GCC diagnostic pop

ribi::reversi::QtReversiMainDialog::QtReversiMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtReversiMainDialog),
  m_reversi(new QtWidget)
{
  ui->setupUi(this);

  ui->layout->addWidget(m_reversi.get());
}

ribi::reversi::QtReversiMainDialog::~QtReversiMainDialog() noexcept
{
  delete ui;
}


